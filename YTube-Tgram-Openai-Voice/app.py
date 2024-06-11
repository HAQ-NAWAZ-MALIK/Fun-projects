from fastapi import APIRouter, Request
from openai_apis import text_to_speech, transcript_audio, chat_completion
from telegram_api import send_audio, send_message, set_webhook, get_file_path, save_file_and_get_local_path
from utils import upload_file_to_gcs
import config

# Create an API router
router = APIRouter(
    prefix='',
    responses={404: {'description': 'Not found'}}
)

# Define the home route
@router.get('/')
def home():
    return 'OK', 200 

# Define the Telegram route
@router.post('/telegram')
async def telegram(request: Request):
    try:
        # Get the request body
        body = await request.json()
        print(body)
        
        # Extract the sender ID from the request body
        sender_id = body['message']['from']['id']
        
        # Check if the message contains a voice file
        if 'voice' in body['message'].keys():
            file_id = body['message']['voice']['file_id']
            file_path = get_file_path(file_id)
            
            # Check if the file path is valid
            if file_path['status'] == 1:
                local_file_path = save_file_and_get_local_path(file_path['file_path'])
                
                # Check if the local file path is valid
                if local_file_path['status'] == 1:
                    # Transcribe the audio file
                    transcript = transcript_audio(local_file_path['local_file_path'], local_file_path['file_id'])
                    
                    # Check if the transcription is successful
                    if transcript['status'] == 1:
                        # Generate a response using chat completion
                        query = chat_completion(transcript['transcript'])
        else:
            # If the message does not contain a voice file, use the text message as the query
            query = body['message']['text']
        
        # Generate a response using chat completion
        response = chat_completion(query)
        
        # Convert the response to audio
        audio_file_path, audio_file_name = text_to_speech(response)
        
        # Upload the audio file to a cloud storage and get the public URL
        public_url = upload_file_to_gcs(audio_file_path, audio_file_name)
        
        # Send the audio or text response to the sender
        if config.REPLY_TYPE == 'audio':
            send_audio(sender_id, public_url, 'Response')
        else:
            send_message(sender_id, response)
        
        return 'OK', 200
    except Exception as e:
        print('Error at telegram...')
        print(e)
        return 'OK', 200

# Define the set Telegram webhook route
@router.post('/set-telegram-webhook')
async def set_telegram_webhook(request: Request):
    try:
        # Get the request body
        body = await request.json()
        
        # Set the Telegram webhook URL and secret token
        flag = set_webhook(body['url'], body['secret_token'])
        
        if flag:
            return 'OK', 200
        else:
            return 'BAD REQUEST', 400
    except Exception as e:
        print('Error at set_telegram_webhook...')
        print(e)
        return 'BAD REQUEST', 400
