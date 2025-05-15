import os
from openai import OpenAI
from openai import _exceptions as OpenAIExceptions
from dotenv import load_dotenv
from google import genai
from google.genai.errors import APIError, ClientError, UnknownFunctionCallArgumentError
import pandas as pd
from typing import Literal, List, Tuple
import sys
import google.generativeai as genai
import time

Model = Literal['gemini', 'deepseek', 'chatgpt']

load_dotenv()

deepseek = None
gemini = None
chatgpt = None

model_csv_names = {
  'gemini': 'gemini_2.0_flash_solutions.csv',
  'deepseek': 'deepseek_r1_flash_solutions.csv',
  'chatgpt': 'chatgpt_4o_solutions.csv',
}

INPUT_CSV = './prompts/input.csv'
RESPONSE_PATH = './responses/'

all_prompts = pd.read_csv(INPUT_CSV)

def initDeepSeekV3Model() -> bool:
  try:
    api_key = os.getenv("DEEPSEEK_API_KEY")
    base_url = os.getenv("DEEPSEEK_BASE_URL")

    if not api_key:
      print("DEEPSEEK_API_KEY not found.")
      return False
    
    if not base_url:
      print("DEEPSEEK_BASE_URL not found.")
      return False

    client = OpenAI(api_key=api_key,base_url=base_url)

    global deepseek
    deepseek = client
    return True
  except Exception as e:
    print(f"Unexpected error: {str(e)}")
    return False
    

def initGeminiPro25PreviewModel() -> bool:
    try:
        api_key = os.getenv("GEMINI_API_KEY")
        if not api_key:
            print("GEMINI_API_KEY not found.")
            return False

        genai.configure(api_key=api_key)

        global gemini
        # gemini = genai.GenerativeModel(model_name="gemini-2.5-pro-exp-03-25")  # ✅
        gemini = genai.GenerativeModel(model_name="gemini-2.5-flash-preview-04-17")  # ✅

        print("Gemini Initialized.")
        return True
    except UnknownFunctionCallArgumentError as e:
        print(f"Invalid input: {e.message}")
        return False
    except APIError as e:
        print(f"API error: {e.message}")
        return False
    except ClientError as e:
        print(f"Client error: {e.message}")
        return False
    except Exception as e:
        print(f"Unexpected error: {str(e)}")
        return False


def initChatGPT4oModel() -> bool:
  try:
    api_key = os.getenv("CHATGPT_API_KEY")
    base_url = os.getenv("CHATGPT_BASE_URL")

    if not api_key:
      print("CHATGPT_API_KEY not found.")
      return False
    
    if not base_url:
      print("CHATGPT_BASE_URL not found.")
      return True

    client = OpenAI(api_key=api_key, base_url=base_url)

    global chatgpt
    chatgpt = client
    return True
  except Exception as e:
    print(f"Unexpected error: {str(e)}")
    return False
  
def getPrompt(idx: int) -> str:
  return all_prompts.loc[idx, 'prompts']

def completePrompt(idx: int) -> None:
  all_prompts.loc[idx, 'done'] = True

def unload() -> None:
  all_prompts.to_csv('./prompts/input.csv')

def promptDeepSeek(idx: int) -> str:
  global deepseek

  if deepseek is None:
    raise Exception("DeepSeek model is not initialized.")
  
  try:
    response = deepseek.completions.create(
      model='deepseek-chat',
      messages=[
        {
          "role": "user",
          "content": getPrompt(idx)
        },
      ],
      stream=False,
      temperature=0.0,
    )
    return response.choices[0].message.content
  except OpenAIExceptions.RateLimitError as e:
    print(f'Rate Limit Error: {e.message}')
  except Exception as e:
    print(f'Unexpected Error: {str(e)}')
  
  return ""

def promptGemini(idx: int) -> str:
    global gemini

    if gemini is None:
        raise Exception("Gemini model is not initialized.")

    try:
        response = gemini.generate_content(
            contents=getPrompt(idx),
            generation_config={
                'temperature': 0.0,
            }
        )
        return response.text
    except Exception as e:
        print(f"Error while prompting Gemini: {str(e)}")
        return ""

def promptChatGPT(idx: int) -> str:
  global chatgpt

  if chatgpt == None:
    raise Exception("ChatGPT model is not initialized.")
  
  response = chatgpt.completions.create(
    model='gpt-4o-latest',
    messages=[
      {
        "role": "user",
        "content": getPrompt(idx)
      },
    ],
    stream=False,
    temperature=0.0,
  )

  return response.choices[0].message.content

def save_responses(responses: List[Tuple[int, str]], model: Model) -> int:
  saved_response_count = 0

  path = f'{RESPONSE_PATH}/{model_csv_names[model]}'
  df = None
  if os.path.isfile(path):
    df = pd.read_csv(path)
  else:
    columns = list(all_prompts.columns[:-1]) + ['response']
    df = pd.DataFrame(columns=columns)

  new_responses = []

  for response in responses:
    try:
      # new_response = all_prompts.iloc[response[0], :-1].copy()
      new_response = all_prompts.loc[response[0]].drop('done').copy()
      new_response['response'] = response[1]
      new_responses.append(new_response)
      completePrompt(response[0])
      saved_response_count += 1
    except Exception as e:
      print(f'Unexpected Error: {str(e)}')

  if new_responses and len(new_responses):
    df = pd.concat([df, pd.DataFrame(new_responses)], ignore_index=True)
    df.to_csv(path, index=False)

  return saved_response_count

if __name__ == '__main__':
  args = sys.argv

  try:
    model = args[1]
    number_of_row = int(args[2])
    delayevery = int(args[3])
    delaytime = int(args[4])
  except Exception as e:
    print(f'The second argument must be an integer: {e}')
  
  if model not in ['deepseek', 'chatgpt', 'gemini']:
    raise Exception("The first argument must be deepseek, chatgpt, or gemini")

  try:
    available_indices = all_prompts[~all_prompts['done']].index
    if number_of_row > len(available_indices):
      raise ValueError(f"Requested {number_of_row} rows, but only {len(available_indices)} available.")
    indices = all_prompts[~all_prompts['done']].sample(number_of_row).index.sort_values()
  except Exception as e:
    print(f'Error while sampling: {str(e)}')
    available = len(all_prompts[~all_prompts['done']])
    print(f'Only {available} rows are available.')
    sys.exit(1)
  
  if model == 'deepseek':
    initDeepSeekV3Model()
    fn_call = promptDeepSeek
  elif model == 'chatgpt':
    initChatGPT4oModel()
    fn_call = promptChatGPT
  elif model == 'gemini':
    initGeminiPro25PreviewModel()
    fn_call = promptGemini

  responses = []
  prompt_count = 0
  for i,index in enumerate(indices):
    try:
      print(f'Prompting {i}...')
      start_time = time.time()
      response = fn_call(index)
      elapsed = time.time() - start_time
      print(f'Prompt {i} took {elapsed:.2f} seconds.')
      responses.append((index, response))
      prompt_count += 1
      print(f'================ Next Prompt ================\n\n')
      if (i + 1) % delayevery == 0:
        print(f'Waiting for {delaytime} seconds to avoid rate limit...')
        time.sleep(delaytime)
    except Exception as e:
      print(f'Unexpected Error: {str(e)}')
      sys.exit(1)
  
  print(f'Prompted {prompt_count} problem sets.')

  saved_response_count = save_responses(responses, model)
  print(f'Saved {saved_response_count} responses.')

  unload()