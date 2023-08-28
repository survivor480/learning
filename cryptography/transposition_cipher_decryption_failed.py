import math

def decrypt_transposition_cipher(key, message):
    originalKey = math.ceil(len(message)/key)
    originaltext = [''] * originalKey

    for col in range(originalKey):
        pointer = col

        while pointer < len(message):
            originaltext[col] += message[pointer]
            pointer += originalKey
    return "".join(originaltext)

if __name__ == '__main__':
    message = str(input("Enter the message: "))
    myKey = 8
    ciphertext = decrypt_transposition_cipher(myKey, message)
    print(ciphertext)