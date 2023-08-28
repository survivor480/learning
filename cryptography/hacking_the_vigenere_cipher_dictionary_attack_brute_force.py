import detectEnglish, vigenere_cipher

def main():
    ciphertext = """Tzx isnz eccjxkg nfq lol mys bbqq I lxcz."""

    hackedMessage = hackVigenere(ciphertext)

    if hackedMessage != None:
        print(hackedMessage)
    else:
        print('Failed to hack encryption')

def hackVigenere(ciphertext):
    fo = open('dictionary.txt')
    words = fo.readlines()
    fo.close()

    for word in words:
        word = word.strip()
        decryptedText = vigenere_cipher.decryptMessage(word, ciphertext)
        if detectEnglish.isEnglish(decryptedText, wordPercentage=40):
            print()
            print('Possible Encryption break:')
            print('Key ' + str(word) + ': ' + decryptedText[:100])
            print()
            print('Enter D for done, or just press Enter to continue breaking:')
            response = input('> ')

            if response.upper().startswith('D'):
                return decryptedText

if __name__ == '__main__':
    main()

