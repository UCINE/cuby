def caesar_cipher_decrypt(text, expected_output):
    for shift in range(1, 26):
        decrypted = ""

        for char in text:
            if char.isalpha():
                if char.islower():
                    shifted = (ord(char) - ord('a') - shift) % 26 + ord('a')
                else:
                    shifted = (ord(char) - ord('A') - shift) % 26 + ord('A')
                decrypted += chr(shifted)
            else:
                decrypted += char

        if decrypted.lower() == expected_output.lower():
            formatted_decrypted = decrypted.replace(' ', '_').replace('\'', '')
            flag = f"flag{{{formatted_decrypted}}}"
            return flag, shift

    return "No matching shift found", None

ciphertext = "Se cge oy znk xomnz cge!"
expected_output = "you're too close to get it lfg!!"

flag, shift = caesar_cipher_decrypt(ciphertext, expected_output)

if flag != "No matching shift found":
    print(f"Flag: {flag}\nShift used: {shift}")
else:
    print(flag)
