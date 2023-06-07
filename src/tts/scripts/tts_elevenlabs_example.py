import requests
import io
import json 
from pydub import AudioSegment
from pydub.playback import play

API_KEY = "a520f0fc9ee10ddcc3dd8da4fe592909"

url = "https://api.elevenlabs.io/v1/voices"

headers = {
  "Accept": "application/json",
  "xi-api-key": API_KEY
}

response = requests.get(url, headers=headers)
response_json = response.json()
voice_id = response_json["voices"][0]["voice_id"]

CHUNK_SIZE = 1024
url = "https://api.elevenlabs.io/v1/text-to-speech/" + voice_id

headers = {
  "Accept": "audio/mpeg",
  "Content-Type": "application/json",
  "xi-api-key": API_KEY
}

data = {
  "text": "Hi! My name is Bella, nice to meet you!",
  "model_id": "eleven_monolingual_v1",
  "voice_settings": {
    "stability": 0.5,
    "similarity_boost": 0.5
  }
}

response = requests.post(url, json=data, headers=headers)
with io.BytesIO() as f:
  for chunk in response.iter_content(chunk_size=CHUNK_SIZE):
    if chunk:
      f.write(chunk)
  f.seek(0)
  song = AudioSegment.from_file(f, format="mp3")
  play(song)
    
