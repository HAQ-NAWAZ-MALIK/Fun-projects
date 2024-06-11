import os
import tempfile
from dotenv import load_dotenv, find_dotenv

# Load environment variables from a .env file
load_dotenv(find_dotenv())

# Get the OpenAI API key from the environment variables
OPENAI_API_KEY = os.getenv('OPENAI_API_KEY')

# Get the credentials from the environment variables
CREDENTIALS = os.getenv('CREDENTIALS')

# Get the Google Cloud Storage bucket name from the environment variables
GCP_CLOUD_STORAGE_BUCKET_NAME = os.getenv('GCP_CLOUD_STORAGE_BUCKET_NAME')

# Error message to display when facing an issue
ERROR_MESSAGE = 'We are facing an issue, please try again later.'

# Audio file format to use
AUDIO_FILE_FORMAT = 'mp3'

# Type of reply to expect (text or audio)
REPLY_TYPE = 'text'
# REPLY_TYPE = 'audio'

# Output directory for storing temporary files
OUTPUT_DIR = os.path.join(
    tempfile.gettempdir(),
    'telegrambot'
)

# Create the output directory if it doesn't exist
os.makedirs(OUTPUT_DIR, exist_ok=True)

# File path for storing the credentials
CREDENTIALS_FILE_PATH = os.path.join(
    OUTPUT_DIR,
    'credentials.json'
)
