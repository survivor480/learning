message = str(input("Enter the string"))

action = input('Enter e for encrypt and d for decrypt')
if action == 'd':
    key = int(input("Enter the key to which you want to decrypt"))
elif action == 'e':
    key = int(input("Enter the key to which you want to encrypt"))

LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
translated = ''

message = message.upper()

for symbol in message:
    if symbol in LETTERS:
        num = LETTERS.find(symbol)
        if action == 'e':
            num = num + key
        elif action == 'd':
            num = num - key
    
        if num >= len(LETTERS):
            num = num - len(LETTERS)
        elif num < 0:
            num = num + len(LETTERS)

        translated = translated + LETTERS[num]

    else:
        translated = translated + symbol

print(translated)