import rospy
from std_msgs.msg import ByteMultiArray, String
import gtts
import io


def tts_bytes(input):
  mp3_fp = io.BytesIO()

  tts = gtts.gTTS(input, lang='en')

  tts.write_to_fp(mp3_fp)
  mp3_fp.seek(0)
  return mp3_fp

def tts_text_to_sound_cb(input):
  publish = False
  publisher:rospy.Publisher = None
  rospy.loginfo('tts got input ' + input.data)
  output = tts_bytes(input.data)
  if(publish):
    publisher.publish(output.read())
    

def tts_node():
  pub = rospy.Publisher('tts_audio', ByteMultiArray, queue_size=10)
  sub = rospy.Subscriber('tts_text', String, queue_size=10, callback=tts_text_to_sound_cb)
  rospy.init_node('tts_node', anonymous=True)
  rate = rospy.Rate(10) # 10hz
  rospy.loginfo('started tts node')
  while not rospy.is_shutdown():
    rate.sleep()

if __name__ == '__main__':
  try:
    tts_node()
  except rospy.ROSInterruptException:
    pass