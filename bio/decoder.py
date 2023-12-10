
# load biobundle binary

import os

with open(os.path.join(os.path.dirname(__file__), 'biobundle'), 'rb') as f:
  biobundle = f.read()
  i = biobundle.find(b'\x48\x72\x7B\x71\x35\x36\x36\x37')
  DATA_LENGTH = 15880
  encoded_data = biobundle[i:i+DATA_LENGTH]

  # apply ^ 0x37 to each byte
  decoded_data = bytes([b ^ 0x37 for b in encoded_data])

  # write decoded data to file called "bio_decode"
  with open('bio_decode', 'wb') as f:
    f.write(decoded_data)
