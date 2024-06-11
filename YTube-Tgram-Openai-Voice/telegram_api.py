import os
import json
from typing import List
import tempfile
import uuid
import requests
from dotenv import load_dotenv, find_dotenv

load_dotenv(find_dotenv())

# Define the output directory for saving audio files
OUTPUT_DIR = os.path.join(
    tempfile.gettempdir(),
    'openai_telegram',
    'audios'
)

# Create the output directory if it doesn't exist
os.makedirs(
    OUTPUT_DIR,
    exist_ok=True
)

# Get the Telegram bot token from environment variables
TOKEN = os.getenv('TOKEN')

# Construct the base URL for Telegram API requests
BASE_URL = f'https://api.telegram.org/bot{TOKEN}'


def send_message(chat_id: int, message: str) -> bool:
    '''
    Send a text message to a Telegram user.

    Parameters:
        - chat_id(int): chat id of the user
        - message(str): text message to send

    Returns:
        - bool: True for success, False for error 
    '''

    payload = {
        'chat_id': chat_id,
        'text': message
    }
    headers = {'Content-Type': 'application/json'}

    response = requests.request(
        'POST', f'{BASE_URL}/sendMessage', json=payload, headers=headers)
    status_code = response.status_code
    response = json.loads(response.text)

    if status_code == 200 and response['ok']:
        return True
    else:
        return False


def send_photo(chat_id: int, url: str, caption: str = '') -> bool:
    '''
    Send a photo to a Telegram user.

    Parameters:
        - chat_id(int): chat id of the user
        - url(str): photo url
        - caption(str)(optional): caption for the photo

    Returns:
        - bool: True for success, False for error 
    '''

    payload = {
        'chat_id': chat_id,
        'photo': url
    }

    if caption != '':
        payload['caption'] = caption

    headers = {'Content-Type': 'application/json'}

    response = requests.request(
        'POST', f'{BASE_URL}/sendPhoto', json=payload, headers=headers)
    status_code = response.status_code
    response = json.loads(response.text)

    if status_code == 200 and response['ok']:
        return True
    else:
        return False


def set_webhook(url: str, secret_token: str = '') -> bool:
    '''
    Set a URL as a webhook to receive all incoming messages.

    Parameters:
        - url(str): URL as a webhook
        - secret_token(str)(optional): secret token received from Telegram request as X-Telegram-Bot-Api-Secret-Token

    Returns:
        - bool: True for success, False for error
    '''

    payload = {'url': url}

    if secret_token != '':
        payload['secret_token'] = secret_token

    headers = {'Content-Type': 'application/json'}

    response = requests.request(
        'POST', f'{BASE_URL}/setWebhook', json=payload, headers=headers)
    status_code = response.status_code
    response = json.loads(response.text)

    if status_code == 200 and response['ok']:
        return True
    else:
        return False


def set_menu_commands(commands: List[dict]) -> bool:
    '''
    Set menu commands in the Telegram bot.

    Parameters:
        - commands(List[dict]): a list of objects, each object must have two properties: 'command' and 'description'.
          'command' is the postback to Telegram, while 'description' explains the command to the user.

    Returns:
        - bool: True for success, False for error
    '''

    payload = {'commands': commands}

    headers = {'Content-Type': 'application/json'}

    response = requests.request(
        'POST', f'{BASE_URL}/setMyCommands', json=payload, headers=headers)
    status_code = response.status_code
    response = json.loads(response.text)

    if status_code == 200 and response['ok']:
        return True
    else:
        return False


def get_file_path(file_id: str) -> dict:
    '''
    Get the file path from the file id of the attachment.

    Parameters:
        - file_id(str): file id of the attachment

    Returns:
        - dict: dictionary containing the status and file path of the attachment
    '''

    url = f'https://api.telegram.org/bot{TOKEN}/getFile'
    querystring = {'file_id': file_id}
    response = requests.request('GET', url, params=querystring)

    if response.status_code == 200:
        data = json.loads(response.text)
        file_path = data['result']['file_path']

        return {
            'status': 1,
            'file_path': file_path
        }
    else:
        return {
            'status': 0,
            'file_path': ''
        }


def save_file_and_get_local_path(file_path: str) -> dict:
    '''
    Save the file and get the local file path.

    Parameters:
        - file_path(str): file path of the attachment

    Returns:
        - dict: dictionary containing the status and the local file path of the attachment
    '''

    url = f'https://api.telegram.org/file/bot{TOKEN}/{file_path}'
    response = requests.request('GET', url)
    extension = file_path.split('.')[-1]
    file_id = uuid.uuid1()
    file_name = f'{file_id}.{extension}'
    local_file_path = os.path.join(
        OUTPUT_DIR,
        file_name
    )

    if response.status_code == 200:
        with open(local_file_path, 'wb') as file:
            file.write(response.content)

        return {
            'status': 1,
            'local_file_path': local_file_path,
            'file_name': file_name,
            'file_id': file_id,
            'extension': extension
        }
    else:
        return {
            'status': 0,
            'local_file_path': '',
            'file_name': '',
            'file_id': '',
            'extension': ''
        }


def send_audio(chat_id: int, url: str, caption: str = '') -> bool:
    '''
    Send an audio file to a Telegram user.

    Parameters:
        - chat_id(int): chat id of the user
        - url(str): audio file url
        - caption(str)(optional): caption for the audio file

    Returns:
        - bool: True for success, False for error 
    '''

    payload = {
        'chat_id': chat_id,
        'audio': url
    }

    if caption != '':
        payload['caption'] = caption

    headers = {'Content-Type': 'application/json'}

    response = requests.request(
        'POST', f'{BASE_URL}/sendAudio', json=payload, headers=headers)
    status_code = response.status_code
    response = json.loads(response.text)

    if status_code == 200 and response['ok']:
        return True
    else:
        return False
