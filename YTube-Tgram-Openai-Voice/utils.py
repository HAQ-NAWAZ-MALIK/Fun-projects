from google.cloud import storage
import os
import config

# Import necessary libraries

# Import configuration settings

# Check if the credentials file exists
if os.path.exists(config.CREDENTIALS_FILE_PATH):
    # If it exists, read the contents of the file
    with open(config.CREDENTIALS_FILE_PATH, "r") as f:
        credentials_json = f.read()
else:
    # If it doesn't exist, create the file and write the credentials
    with open(config.CREDENTIALS_FILE_PATH, "w") as f:
        f.write(config.CREDENTIALS)

# Set the environment variable for Google Application Credentials
os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = config.CREDENTIALS_FILE_PATH

# Create a client for Google Cloud Storage
storage_client = storage.Client()

# Function to generate formatted messages
def generate_messages(messages: list, query: str) -> list:
    # Start with a system message
    formated_messages = [
        {
            'role': 'system',
            'content': 'You are a helpful assistant.'
        }
    ]
    # Iterate through the messages
    for m in messages:
        # Add user message
        formated_messages.append({
            'role': 'user',
            'content': m['query']
        })
        # Add system response
        formated_messages.append({
            'role': 'system',
            'content': m['response']
        })
    # Add user query
    formated_messages.append(
        {
            'role': 'user',
            'content': query
        }
    )

    return formated_messages

# Function to upload a file to Google Cloud Storage
def upload_file_to_gcs(local_file_path, destination_blob_name):
    try:
        # Get the bucket and blob
        bucket = storage_client.bucket(config.GCP_CLOUD_STORAGE_BUCKET_NAME)
        blob = bucket.blob(destination_blob_name)
        # Upload the file with public read access
        blob.upload_from_filename(local_file_path, predefined_acl='publicRead')
        # Get the public URL of the uploaded file
        public_url = f"https://storage.googleapis.com/{config.GCP_CLOUD_STORAGE_BUCKET_NAME}/{destination_blob_name}"
        # Delete the local file
        os.unlink(local_file_path)
        return public_url
    except Exception as e:
        # Print any exceptions that occur during the upload process
        print(e)
