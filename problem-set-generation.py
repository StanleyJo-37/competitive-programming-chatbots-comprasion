from schema import Schema, And, Use, Optional, Or
from typing import Literal
import os
import shutil
import uuid
import requests
import pandas as pd
from dotenv import load_dotenv
from schema import SchemaError
import yaml
import ast

load_dotenv()

AUTH = (os.getenv("DOMJUDGE_ADMIN_NAME"), os.getenv("DOMJUDGE_ADMIN_PASS"))
API_URL = os.getenv("DOMJUDGE_API_URL")
CONTEST_ID = os.getenv("DOMJUDGE_CONTEST_ID")

License_Types = Literal[None, 'unknown', 'public domain', 'cc0', 'cc by', 'cc by-sa', 'educational', 'permission']

limits_interface = Schema({
  Optional('time_multiplier'): Or(None, And(Use(int))),
  Optional('time_safety_margin'): Or(None, And(Use(int))),
  Optional('memory'): Or(None, And(Use(float))),
  Optional('output'): Or(None, And(Use(float))),
  Optional('code'): Or(None, And(Use(float))),
  Optional('compilation_time'): Or(None, And(Use(float))),
  Optional('compilation_memory'): Or(None, And(Use(float))),
  Optional('validation_time'): Or(None, And(Use(float))),
  Optional('validation_memory'): Or(None, And(Use(float))),
  Optional('validation_output'): Or(None, And(Use(float))),
})

metadata_interface = Schema({
  Optional('problem_format_version'): Or(None, And(Use(str))),
  Optional('name'): Or(None, And(Use(str))),
  Optional('uuid'): Or(None, And(Use(str))),
  Optional('author'): Or(None, And(Use(str))),
  Optional('source'): Or(None, And(Use(str))),
  Optional('source_url'): Or(None, And(Use(str))),
  Optional('license'): Or(None, And(Use(str))),
  Optional('rights_owner'): Or(None, And(Use(str))),
  Optional('limits'): Or(None, limits_interface),
  Optional('validation'): Or(None, And(Use(str))),
  Optional('validator_flags'): Or(None, And(Use(str))),
  Optional('keywords'): Or(None, And(Use(str))),
  Optional('public'): Or(None, And(Use(bool))),
})

def folder_exists(directory_name="./temp"):
  return os.path.isdir(directory_name)

def delete_tmp_dir(directory_name="./temp"):
  print("Deleting temp folder...")
  shutil.rmtree(directory_name)

def create_tmp_folder(directory_name="./temp"):
  try:
    os.mkdir(directory_name)
    print(f"Directory '{directory_name}' created successfully.")
  except FileExistsError:
    print(f"Directory '{directory_name}' already exists.")
  except PermissionError:
    print(f"Permission denied: Unable to create '{directory_name}'.")
  except Exception as e:
    print(f"An error occurred: {e}")

def compress_tmp_folder(archive_name: str, directory_name="./temp"):
  print("Compressing temp folder into a zip archive...")
  shutil.make_archive(archive_name, "zip", directory_name)

def convert_to_LaTeX_problem(problem):
  print(problem.split('\n'))

def generate_metadata(problem_format_version: str=None, name: str=None, uuid: str=None, author: str=None, source: str=None, source_url: str=None, rights_owner: License_Types=None, limits: dict=None, validation: str=None, validator_flags: str=None, keywords: str=None, license: str=None, path: str=None) -> bool:
  print("Generating problem metadata...")
  if limits != None:
    try:
      limits_interface.validate(limits)
    except SchemaError as e:
      print(e)
      return False

  data = {
    'problem_format_version': problem_format_version,
    'name': name,
    'uuid': uuid,
    'author': author,
    'source': source,
    'source_url': source_url,
    'license': license,
    'rights_owner': rights_owner,
    'limits': limits,
    'validation': validation,
    'validator_flags': validator_flags,
    'keywords': keywords,
    'public': True,
  }

  try:
    metadata_interface.validate(data)
  except SchemaError as e:
    print(e)
    return False

  with open("./temp/problem.yaml", "w") as file:
    yaml.dump(data, file)
  
  return True

def parse_time_limit(time_limit) -> float:
  if isinstance(time_limit, str):
    tl = time_limit.split(" ")
    tl_idx = 0

    if len(tl) > 2:
      tl_idx = 2

    return float(tl[tl_idx]) if tl_idx != 2 else float(tl[tl_idx]) * 1.2
  else:
    return None

def parse_memory_limit(memory_limit: str) -> float:
  if isinstance(memory_limit, str):
    ml = memory_limit.split(" ")

    return ml[0] if ml[1] == 'megabytes' else float(ml[0]) / 1e-6
  else:
    return None
  
def generate_input_output_dir(problem_set):
  # inputs = json.loads(problem_set["inputs"])
  inputs = ast.literal_eval(problem_set["inputs"])
  outputs = ast.literal_eval(problem_set["outputs"])

  io_count = len(inputs)

  split_index = io_count // 5

  test_in = inputs[:split_index]
  sample_in = inputs[split_index:]

  test_out = outputs[:split_index]
  sample_out = outputs[split_index:]

  os.makedirs("./temp/data/secret", exist_ok=True)
  os.makedirs("./temp/data/sample", exist_ok=True)

  for i, (sample_input, sample_output) in enumerate(zip(sample_in, sample_out)):
    with open(f"./temp/data/sample/sample{i}.in", "w") as file:
      file.write(str(sample_input))
    
    with open(f"./temp/data/sample/sample{i}.ans", "w") as file:
      file.write(str(sample_output))

  for i, (test_input, test_output) in enumerate(zip(test_in, test_out)):
    with open(f"./temp/data/secret/test{i}.in", "w") as file:
      file.write(str(test_input))
    
    with open(f"./temp/data/secret/test{i}.ans", "w") as file:
      file.write(str(test_output))

def generate_problem_statement(problem_set, problem_name):
  prompt = problem_set.get("prompts", "")

  # file_content = r"""\documentclass{problem}
  # \begin{document}
  # \begin{problem} {+ """ + problem_name + r""" +}{stdin}{stdout}

  # """ + prompt + r"""

  # \end{problem}
  # \end{document}
  # """
  file_content = r"""
  <body>
    <p>""" + prompt + """</p>
  </body>
  """

  with open("./temp/problem.html", "w", encoding="utf-8") as file:
    file.write(file_content)

def generate_problem_archive(problem_set, index):
  archive_name = f"{index + 1}. {problem_set["name"]}" if isinstance(problem_set["name"], str) else f"{index + 1}. problem-{index}"
  create_tmp_folder()

  limits = {}
  tl = parse_time_limit(problem_set["time_limit"])
  ml = parse_memory_limit(problem_set["memory_limit"])

  if tl is not None:
    limits['time'] = tl

  if ml is not None:
    limits['memory'] = ml

  generate_input_output_dir(problem_set)
  generate_metadata(name=archive_name,
                    uuid=str(uuid.uuid4()),
                    author=problem_set["source"],
                    source=problem_set["source"],
                    source_url=problem_set["url"],
                    rights_owner="cc0",
                    limits=limits if limits else None,
  )
  generate_problem_statement(problem_set, archive_name)
  compress_tmp_folder(f"./problem-sets/{archive_name}")
  delete_tmp_dir()

problem_df = pd.read_csv("./prompts/new_input.csv")

for i, row in problem_df.iterrows():
  print(f"Generating problem set no. {i + 1}")

  generate_problem_archive(row, i)
  
  print('\n' + "=" * 60 + '\n')

def upload_problem_sets():
  all_archives = [os.path.join("./problem-sets", f) for f in os.listdir("./problem-sets") if os.path.isfile(os.path.join("./problem-sets", f))]
  
  for archive in all_archives:
    with open(archive, "rb") as zip_file:
      files = {"zip": (os.path.basename(archive), zip_file, "application/zip")}
      response = requests.post(
        f"{API_URL}/contests/{CONTEST_ID}/problems",
        auth=AUTH,
        files=files,
      )

      if response.status_code == 200:
        print(f"✅ Uploaded {archive} successfully.")
      else:
        print(f"❌ Failed to upload {archive}: {response.status_code} - {response.text}")

upload_problem_sets()