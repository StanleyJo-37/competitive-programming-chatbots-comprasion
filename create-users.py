from dotenv import load_dotenv
import os
import requests

load_dotenv()

AUTH = (os.getenv("DOMJUDGE_ADMIN_NAME"), os.getenv("DOMJUDGE_ADMIN_PASS"))
API_URL = os.getenv("DOMJUDGE_API_URL")
CONTEST_ID = os.getenv("DOMJUDGE_CONTEST_ID")

users = {
  'chatgpt': {
    "username": "chatgpt",
    "name": "chatgpt",
    "password": "chatgpt_pw1",
    "roles": ["team"],
  },
  'gemini': {
    "username": "gemini",
    "name": "gemini",
    "password": "gemini_pw1",
    "roles": ["team"],
  },
  'deepseek': {
    "username": "deepseek",
    "name": "deepseek",
    "password": "deepseek_pw1",
    "roles": ["team"],
  },
}

for i, user in enumerate(users.values()):
  user_creation_response = requests.post(
    url=f"{API_URL}/users",
    json=user,
    auth=AUTH,
  )

  if user_creation_response.status_code == 201:
    print(f"✅ User {user['username']} created.")
  else:
    print(f"❌ Failed to create user {user['username']}.\n{user_creation_response.text}")

  user_data = user_creation_response.json()

  team_creation_response = requests.post(
    url=f"{API_URL}/teams",
    json={
      "id": i + 1,
      "name": user["username"],
      "display_name": user["username"],
    },
    auth=AUTH,
  )

  team_data = team_creation_response.json()

  if team_creation_response.status_code == 201:
    print(f"✅ Team {team_data['name']} created.")
  else:
    print(f"❌ Failed to create team {team_data['name']}.\n{team_creation_response.text}")


  team_contest_assignment_response = requests.post(
    url=f"{API_URL}/contests/{CONTEST_ID}/teams",
    json={
      "id": team_data['id'],
      "name": team_data['name'],
      "display_name": team_data["display_name"],
      "user_id": user_data["id"]
    },
    auth=AUTH
  )

  if team_contest_assignment_response.status_code == 201:
    print(f"✅ Team {team_data['name']} assigned.")
  else:
    print(f"❌ Failed to assign team {team_data['name']}.\n{team_contest_assignment_response.text}")