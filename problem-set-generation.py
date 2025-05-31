from schema import Schema, And, Use, Optional, Or
from typing import Literal
import os
import shutil
import uuid
import json
import pandas as pd

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

from schema import SchemaError
import yaml

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
  }

  try:
    metadata_interface.validate(data)
  except SchemaError as e:
    print(e)
    return False

  with open("./temp/problem.yaml", "w") as file:
    yaml.dump(data, file)
  
  return True

def parse_time_limit(time_limit: str) -> float:
  tl = time_limit.split(" ")
  tl_idx = 0

  if len(tl) > 2:
    tl_idx = 2

  return float(tl[tl_idx]) if tl_idx != 2 else float(tl[tl_idx]) * 1.2

def parse_memory_limit(memory_limit: str) -> float:
  ml = memory_limit.split(" ")

  return ml[0] if ml[1] == 'megabytes' else float(ml[0]) / 1e-6
  
def generate_input_output_dir(problem_set):
  io_obj = json.loads(problem_set['input_output'])

  inputs = io_obj["inputs"]
  outputs = io_obj["outputs"]

  io_count = len(inputs)

  split_index = io_count // 5

  sample_in = inputs[:split_index]
  test_in = inputs[split_index:]

  sample_out = outputs[:split_index]
  test_out = outputs[split_index:]

  for i, (sample_input, sample_output) in enumerate(zip(sample_in, sample_out)):
    with open(f"./temp/data/sample{i}.in", "w") as file:
      file.write(sample_input)
    
    with open(f"./temp/data/sample{i}.out", "w") as file:
      file.write(sample_output)

  for i, (test_input, test_output) in enumerate(zip(test_in, test_out)):
    with open(f"./temp/data/secret/test{i}.in", "w") as file:
      file.write(test_input)
    
    with open(f"./temp/data/secret/test{i}.out", "w") as file:
      file.write(test_output)

def generate_problem_statement(problem_set):
  with open("./temp/problem.tex", "w") as file:
    file.write(problem_set["prompts"])

def generate_problem_archive(problem_set):
  create_tmp_folder()
  generate_metadata(name=problem_set["name"],
                    uuid=str(uuid.uuid4()),
                    author=problem_set["source"],
                    source=problem_set["source"],
                    source_url=problem_set["url"],
                    rights_owner="cc0",
                    limits={
                      'time': parse_time_limit(problem_set["time_limit"]),
                      'memory': parse_memory_limit(problem_set["memory_limit"]),
                    })
  generate_input_output_dir(problem_set)
  generate_problem_statement(problem_set)
  compress_tmp_folder("./problem-sets/new-problem")
  delete_tmp_dir()

problem_df = pd.read_csv("./prompts.csv")

for i, row in problem_df.iterrows():
  generate_problem_archive(row)