import pandas as pd
import argparse
import os

def main():
    """
    Reads a CSV file, extracts 'id' and 'response' columns,
    and saves the 'response' content into .cpp files named after 'id'.
    """
    parser = argparse.ArgumentParser(
        description="Convert CSV 'response' column content to .cpp files."
    )
    parser.add_argument(
        "csv_filepath", 
        help="Path to the input CSV file."
    )
    parser.add_argument(
        "output_folder",
        help="Path to the destination folder where .cpp files will be saved."
    )
    args = parser.parse_args()

    # Ensure the output directory exists
    try:
        os.makedirs(args.output_folder, exist_ok=True)
    except OSError as e:
        print(f"Error creating output directory {args.output_folder}: {e}")
        return

    # Read the CSV file
    try:
        df = pd.read_csv(args.csv_filepath)
    except FileNotFoundError:
        print(f"Error: CSV file not found at {args.csv_filepath}")
        return
    except pd.errors.EmptyDataError:
        print(f"Error: CSV file {args.csv_filepath} is empty.")
        return
    except Exception as e:
        print(f"Error reading CSV file {args.csv_filepath}: {e}")
        return

    # Check for required columns
    if 'id' not in df.columns:
        print("Error: 'id' column not found in the CSV file.")
        return
    if 'response' not in df.columns:
        print("Error: 'response' column not found in the CSV file.")
        return

    # Process each row
    for index, row in df.iterrows():
        try:
            file_id = str(row['id'])
            response_content = str(row['response']) # Ensure content is string

            # Handle potential NaN or empty responses if necessary
            if pd.isna(row['response']) or not response_content.strip():
                print(f"Skipping row {index} (id: {file_id}) due to empty or NaN response.")
                continue

            filename = f"{file_id}.cpp"
            filepath = os.path.join(args.output_folder, filename)

            with open(filepath, 'w', encoding='utf-8') as f:
                f.write(response_content)
            
            # print(f"Successfully created {filepath}") # Optional: for verbose output

        except Exception as e:
            print(f"Error processing row {index} (id: {row.get('id', 'N/A')}): {e}")

    print(f"Processing complete. .cpp files saved to {args.output_folder}")

if __name__ == "__main__":
    main()