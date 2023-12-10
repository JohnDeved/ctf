import struct

# The specific string is represented as a sequence of 8-byte integers
part1 = 0x743474737b425448
part2 = 0x5f3562316c5f6331
part3 = 0x6c3030635f747562
part4 = 0x7d7233

# Combine the parts into a single string
target = struct.pack('<Q', part1)
target += struct.pack('<Q', part2)
target += struct.pack('<Q', part3)
target += struct.pack('<I', part4)

# Print the target string
print(target.decode('utf-8'))