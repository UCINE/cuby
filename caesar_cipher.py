def caesar_cipher_decrypt(text, shift):
    decrypted = ""

    for char in text:
        if char.isalpha():
            shifted = ord(char) - shift
            if char.islower():
                if shifted < ord('a'):
                    shifted += 26
            elif char.isupper():
                if shifted < ord('A'):
                    shifted += 26
            decrypted += chr(shifted)
        else:
            decrypted += char

    return decrypted

text = "Zl jnl vf gur evtug jnl!"
decrypted_message = caesar_cipher_decrypt(text, 13)
print(decrypted_message)
