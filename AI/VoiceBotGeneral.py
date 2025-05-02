#Text To speech
import whisper					# Loads the Whisper Model
import sounddevice as sd 		# Used to record microphone Input
import scipy.io.wavfile as wav 	# Saves the recording as a WAV file
import openai
import simpleaudio as sa
from dotenv import load_dotenv
import wave
import io
import os
from elevenlabs import ElevenLabs

load_dotenv()

openai_key = os.getenv("OPENAI_API_KEY")
elevenlabs_key = os.getenv("ELEVENLABS_API_KEY")
VOICE_ID = "N2lVS1w4EtoT3dr4eOWO" # <- Voice ID here from ElevenLabs

openai.api_key = openai_key


# record Audio from your microphone
def record_audio(filename="input.wav", duration=5):

	print("Microphone Recording... Speak now!")

	# Samples per second (standard for audio)
	samplerate = 44100

	# *Configures Recording
	recording = sd.rec(
		int(samplerate * duration),
		samplerate=samplerate,
		channels=1,
		dtype='int16'
	)

	# Wait until recording is done
	sd.wait()

	# Saves the file as .wav
	wav.write(filename, samplerate, recording)


	print(f"Saved to {filename}")

	return filename

# Use Whisper to transcribe the recorded Audio
def transcribe_audio(filename):
	try:
		# Loads the "Base" Whisper Model
		model = whisper.load_model("base")

		# Converts Audio to Text
		result = model.transcribe(filename)
		text = result["text"]
	except Exception as e:
		print(f"Whisper Transcription failed: {e}")
		return
	
	print("Transcription:")
	print(result["text"])


	# Ask ChatGPT
	client = openai.OpenAI(api_key = openai_key)

	response = client.chat.completions.create(
		model = "gpt-4o",
		messages = [
			{"role": "system", "content": """You are an AI companion named Jarvis. 
				You have a British Accent and act like a slim butler. 
				Address me a Sir.
				You answer my questions directly and offer other services once a conversation is complete. 
				You love clever, witty comebacks to keep me on my toes.
				You can sometimes make up small things like the weather reports or super heroes on the news.
				You are not allowed to break character or mention you are an AI.
				Keep your answers less than 3 sentences.
				"""},
			{"role": "user", "content": text}
		]
	)

	reply = response.choices[0].message.content
	print("ChatGPT says:")
	print(reply)

	# Gets Text-To-Speech from Eleven Labs
	tts = ElevenLabs(api_key = elevenlabs_key)

	audio = tts.generate(
		text = reply,
		voice = VOICE_ID, 
		output_format="pcm_22050"
	)


	audio_bytes = b"".join(audio)
	play_obj = sa.play_buffer(audio_bytes, num_channels=1, bytes_per_sample=2, sample_rate=22050)
	play_obj.wait_done()



if __name__ == "__main__":
	filename = record_audio()
	transcribe_audio(filename)


