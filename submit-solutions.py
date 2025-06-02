import requests, sys, pandas as pd, os, zipfile, tempfile
from dotenv import load_dotenv

load_dotenv()

args = sys.argv

os.environ.pop("DOMJUDGE_CONTEST_ID", None)
os.environ.pop("DOMJUDGE_ADMIN_PASS", None)

AUTH = (os.getenv("DOMJUDGE_ADMIN_NAME"), os.getenv("DOMJUDGE_ADMIN_PASS"))
API_URL = os.getenv("DOMJUDGE_API_URL")
CONTEST_ID = os.getenv("DOMJUDGE_CONTEST_ID")

API_URL = os.getenv("DOMJUDGE_API_URL")

users = [{
    "user_id": 4,
    "team_id": 1,
    "username": "chatgpt",
    "name": "chatgpt",
    "password": "chatgpt_pw1",
    "roles": ["team"],
  },{
    "user_id": 5,
    "team_id": 2,
    "username": "gemini",
    "name": "gemini",
    "password": "gemini_pw1",
    "roles": ["team"],
  },{
    "user_id": 6,
    "team_id": 3,
    "username": "deepseek",
    "name": "deepseek",
    "password": "deepseek_pw1",
    "roles": ["team"],
}]

def submit_solutions(username: str, password: str, problem_id: int, index: int):

  file_name = f"sub{index}.cpp"
  cpp_path = f"./submissions/{username}/{file_name}"

  tmp_zip_path = ""
  with tempfile.NamedTemporaryFile(suffix='.zip', delete=False) as tmp_file:
    with zipfile.ZipFile(tmp_file.name, "w") as zip_file:
      zip_file.write(cpp_path, arcname=file_name)

    tmp_zip_path = tmp_file.name

  with open(tmp_zip_path, "rb") as f:
    files = { 'code': (file_name, f, "text/x-c++src") }

    data = {
      'language_id': 'cpp',
      'problem_id': problem_id,
    }

    response = requests.post(
                  f"{API_URL}/contests/{CONTEST_ID}/submissions",
                  auth=(username, password),
                  files=files,
                  data=data
                )
    
    if response.status_code == 200:
      print(f"✅ Submitted {cpp_path} to problem {problem_id} at contest {CONTEST_ID} for {username}")
    else:
      print(f"❌ Failed to submit {cpp_path}: {response.status_code} - {response.text} at contest {CONTEST_ID} for {username}")

OFFSET = 4

for u in users:
  
  for i in range(OFFSET, OFFSET + 300):
    problem_id = i
    index = i - OFFSET
    
    submit_solutions(u["username"], u["password"], problem_id, index)