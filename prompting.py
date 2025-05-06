import os
from openai import OpenAI
from dotenv import load_dotenv
from google import genai

load_dotenv()

deepseek = None
gemini = None
chatgpt = None

def initDeepSeekV3Model():
  api_key = os.getenv("DEEPSEEK_API_KEY")
  base_url = os.getenv("DEEPSEEK_BASE_URL")

  if api_key == None or len(api_key) <= 0:
    raise Exception("DEEPSEEK_API_KEY not found.")
  
  if base_url == None or len(base_url) <= 0:
    raise Exception("DEEPSEEK_BASE_URL not found.")

  client = OpenAI(api_key=api_key,base_url=base_url)

  global deepseek
  deepseek = client

def initGeminiPro25PreviewModel():
  api_key = os.getenv("GEMINI_API_KEY")

  if api_key == None or len(api_key) <= 0:
    raise Exception("GEMINI_API_KEY not found.")

  client = genai.Client(api_key=api_key)

  global gemini
  gemini = client

def initChatGPT4oModel():
  api_key = os.getenv("CHATGPT_API_KEY")
  base_url = os.getenv("CHATGPT_BASE_URL")

  if api_key == None or len(api_key) <= 0:
    raise Exception("CHATGPT_API_KEY not found.")
  
  if base_url == None or len(base_url) <= 0:
    raise Exception("CHATGPT_BASE_URL not found.")

  client = OpenAI(api_key=api_key, base_url=base_url)

  global chatgpt
  chatgpt = client

def promptDeepSeek(prompt: str) -> bool:
  global deepseek

  if deepseek == None:
    raise Exception("DeepSeek model is not initialized.")
  
  response = deepseek.completions.create(
    model='deepseek-chat',
    messages=[
      {
        "role": "user",
        "content": prompt
      },
    ],
    stream=False,
  )

  return response.choices[0].message.content

def promptGemini(prompt: str) -> bool:
  global gemini

  if gemini == None:
    raise Exception("Gemini model is not initialized.")
  
  response = gemini.models.generate_content(
    model="gemini-2.5-pro-preview", content=prompt
  )

  return response.text

def promptChatGPT(prompt: str) -> bool:
  global chatgpt

  if chatgpt == None:
    raise Exception("ChatGPT model is not initialized.")
  
  response = chatgpt.completions.create(
    model='gpt-4o-latest',
    messages=[
      {
        "role": "user",
        "content": prompt
      },
    ],
    stream=False,
  )

  return response.choices[0].message.content