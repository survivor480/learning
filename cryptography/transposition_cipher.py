def encryptMessage(key, message):
    ciphertext = [''] * key

    for col in range(key):
        pointer = col

        while pointer < len(message):
            ciphertext[col] += message[pointer]
            pointer += key

    return "".join(ciphertext)

if __name__ == '__main__':
    message = str(input("Enter the message: "))

    myKey = int(input("Enter the key: "))

    ciphertext = encryptMessage(myKey, message)

    print(ciphertext + '|')