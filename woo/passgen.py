# The reference array
arr = [
    0x9c, 0x96, 0xbd, 0xaf, 0x93, 0xc3, 0x94, 0x60, 0xa2, 0xd1, 0xc2, 0xcf, 0x9c, 0xa3, 0xa6, 0x68,
    0x94, 0xc1, 0xd7, 0xac, 0x96, 0x93, 0x93, 0xd6, 0xa8, 0x9f, 0xd2, 0x94, 0xa7, 0xd6, 0x8f, 0xa0,
    0xa3, 0xa1, 0xa3, 0x56, 0x9e
]

# Initialize the password with two characters
password = chr(arr[0] // 2) + chr(arr[0] // 2)

# Generate the rest of the password
for i in range(1, 37):
    # Calculate the next character based on the current sum and the previous character
    next_char = arr[i] - ord(password[i])
    # Check if next_char is negative
    if next_char < 0:
        # If it is, add 256 to bring it into the valid range for chr()
        next_char += 256
    # Add the next character to the password
    password += chr(next_char)

# Print the password
print(password)