import requests
import io
import json 
import gtts
from pydub import AudioSegment
from pydub.playback import play

def tts_bytes(input):
  mp3_fp = io.BytesIO()

  tts = gtts.gTTS(input, lang='en')

  tts.write_to_fp(mp3_fp)
  mp3_fp.seek(0)
  return mp3_fp

def play_tts(input):
  mp3_fp = tts_bytes(input)
  song = AudioSegment.from_file(mp3_fp, format="mp3")
  play(song)

if __name__ == '__main__':
  play_tts('hello')