import os
import tempfile
import uuid
import soundfile as sf
from openai import OpenAI
import config

# Create an instance of the OpenAI client using the API key from the config module
client = OpenAI(api_key=config.OPENAI_API_KEY)

# Define the output directory for audio files
OUTPUT_DIR = os.path.join(tempfile.gettempdir(), 'openai_telegram', 'audios')

# Create the output directory if it doesn't exist
os.makedirs(OUTPUT_DIR, exist_ok=True)


def transcript_audio(ogg_file_path: str, file_id: str) -> dict:
    try:
        # Read the audio data and sample rate from the OGG file
        audio_data, sample_rate = sf.read(ogg_file_path)

        # Convert the audio to MP3 format
        mp3_file_path = f'{OUTPUT_DIR}/{file_id}.mp3'
        sf.write(mp3_file_path, audio_data, sample_rate)

        # Open the MP3 file in binary mode
        audio_file = open(mp3_file_path, 'rb')

        # Delete the original OGG and MP3 files
        os.unlink(ogg_file_path)
        os.unlink(mp3_file_path)

        # Transcribe the audio using the OpenAI API
        transcript = client.audio.transcriptions.create(
            model='whisper-1',
            file=audio_file,
            response_format="text"
        )

        # Return the transcript and status
        return {
            'status': 1,
            'transcript': transcript
        }
    except Exception as e:
        # Handle any exceptions and return an error status
        print('Error at transcript_audio...')
        print(e)
        return {
            'status': 0,
            'transcript': ''
        }


def chat_completion(text: str) -> str:
    try:
        # Generate a chat completion response using the OpenAI API
        response = client.chat.completions.create(
            model='gpt-3.5-turbo',
            messages=[
                {'role': 'system', 'content': 'You are a helpful assistant.'},
                {'role': 'user', 'content': text}
            ]
        )

        # Return the generated response
        return response.choices[0].message.content
    except Exception as e:
        # Handle any exceptions and return a generic error message
        print('Error at chat_completion...')
        print(e)
        return 'We are facing an issue at this moment.'


# Example usage of the chat_completion function
chat_completion('hi')


def text_to_speech(text: str) -> tuple[str, str]:
    # Generate a unique file name for the audio file
    file_name = f'{uuid.uuid1()}.{config.AUDIO_FILE_FORMAT}'

    # Define the path for the audio file
    audio_file_path = os.path.join(config.OUTPUT_DIR, file_name)

    # Generate speech from the text using the OpenAI API
    response = client.audio.speech.create(
        model="tts-1",
        voice="alloy",
        input=text,
        response_format=config.AUDIO_FILE_FORMAT
    )

    # Write the generated audio to the file
    response.write_to_file(audio_file_path)

    # Return the path and file name of the generated audio file
    return audio_file_path, file_name
