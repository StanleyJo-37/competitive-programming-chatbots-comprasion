import requests, sys, pandas as pd, os

args = sys.argv

USERNAME = args[1]
PASSWORD = args[2]
CSV_PATH = args[3]

API_URL = "http://localhost:8000/api/v4/submissions"

def sanitize_solution(solution):
  return solution

def submit_solution(solutions: pd.DataFrame):
  for i, row in solutions.iterrows():
    solution = sanitize_solution(row["solution"])

    full_path = f"./temp-submission/sub{i}.cpp"

    with open(full_path, "W") as new_file:
      new_file.write(solution)
    
    with open(full_path, "rb") as f:
      files = { 'code': f }

      data = {
        'language_id': 'cpp',
        'problem_id': row['problem_id'],
        'contest_id': 0,
      }

      response = requests.post(API_URL, auth=(USERNAME, PASSWORD), files=files, data=data)
      if response.status_code == 201:
        print(f"✅ Submitted {full_path} to problem {row["problem_id"]}")
      else:
        print(f"❌ Failed to submit {full_path}: {response.status_code} - {response.text}")

    os.remove(full_path)

solution_df = pd.read_csv(f"./responses/{args[1]}.csv")
submit_solution(solution_df)