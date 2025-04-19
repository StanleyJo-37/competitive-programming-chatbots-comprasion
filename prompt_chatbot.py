from dotenv import load_dotenv
import requests
import os
import pandas as pd

INPUT_PATH = './prompts'
INPUT_FILENAME = 'input.csv'
INPUT_DIRECTORY = f'{INPUT_PATH}/{INPUT_FILENAME}'

OUTPUT_PATH = './responses'

MODELS = [('chatgpt-4o-latest', 'chatgpt_4o_solutions.csv'), ('deepseek/deepseek-r1', 'deepseek-r1-solutions.csv'), ('google/gemini-2.0-flash', 'gemini_2.0_flash_solutions.csv')]
model_index = 0
model = MODELS[model_index][0]
response_directory = f'{INPUT_PATH}/{MODELS[model_index][1]}'

input_df = pd.DataFrame(INPUT_DIRECTORY)
response_df = pd.DataFrame(response_directory)

load_dotenv()

api_key = os.getenv("AIMLAPI")

if api_key:
  print("API key loaded successfully")
else:
  print("API key not found in .env file")

prompts = input_df.head(10)

for prompt in prompts:
  response = requests.post(
    "https://api.aimlapi.com/v1/chat/completions",
    headers={
      "Authorization":f"Bearer {api_key}",
      "Content-Type":"application/json"
    },
    json={
      "model": model,
      "messages":[
        {
          "role":"user",
          "content":prompt
        }
      ]
    }
  )
  
  # Get JSON response
  data = response.json()
  
  # Create a DataFrame from this response
  if 'choices' in data and len(data['choices']) > 0:
    # Extract the message content
    message_content = data['choices'][0]['message']['content'] if 'message' in data['choices'][0] else ""
    
    # Create a row with model name and response
    row_data = {
      'model': model,
      'content': message_content,
      'completion_tokens': data.get('usage', {}).get('completion_tokens', 0),
      'prompt_tokens': data.get('usage', {}).get('prompt_tokens', 0),
      'timestamp': pd.Timestamp.now()
    }

    # Append to the results DataFrame
    row_df = pd.DataFrame([row_data])
    response_df = pd.concat([response_df, row_df], axis=1)

input_df = input_df.iloc[:, 10:].reset_index(drop=True)
input_df.to_csv(INPUT_DIRECTORY)
response_df.to_csv(response_directory)