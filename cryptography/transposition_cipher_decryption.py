import math

def decrypt_transposition_cipher(key, message):
    numOfColumns = math.ceil(len(message)/key)
    numOfRows = key
    numOfShadedBoxes = (numOfColumns * numOfRows) - len(message)

    plaintext = [''] * numOfColumns

    col = 0
    row = 0

    for symbol in message:
        plaintext[col] += symbol
        col += 1

        if(col == numOfColumns) or (col == numOfColumns -1 and row >= numOfRows - numOfShadedBoxes):
            col = 0
            row += 1
    return ''.join(plaintext)


if __name__ == '__main__':
    myMessage = str(input("Enter the text: "))
    myKey = int(input("Enter the key: "))

    plaintext = decrypt_transposition_cipher(myKey, myMessage)

    print(plaintext + '|')

