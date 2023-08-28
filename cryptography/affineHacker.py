import affine_cipher, detectEnglish, cryptomath

SILENT_MODE = False

def main():
    myMessage = """V/ MGw^s\{. CGs`d d{E{.,{ \G 6{ M}``{d y0\{``yK{0\ y4 y\ MGs`d d{M{y,{ } bsw}0 6{y0K y0\G 6{`y{,y0K \b}\ y\ yE bsw}0PV 9/`}0 ls.y0K"""
    hackedMessage = hackAffine(myMessage)

    if hackedMessage != None:
        print('Copying hacked message to clipboard:')
        print(hackedMessage)
    else:
        print('Failed to hack encryption.')

def hackAffine(message):
    print('Hacking...')

    print('(Press Ctrl-C or Ctrl-D to quit at any time.)')

    for key in range(len(affine_cipher.SYMBOLS) ** 2):
        keyA = affine_cipher.getKeyParts(key)[0]
        if cryptomath.gcd(keyA, len(affine_cipher.SYMBOLS)) != 1:
            continue

        decryptedText = affine_cipher.decryptMessage(key, message)
        if not SILENT_MODE:
            print('Tried Key %s...(%s)' % (key, decryptedText[:40]))

        if detectEnglish.isEnglish(decryptedText):
            print()
            print('Possible Encryption hack: ')
            print('Key: %s' % (key))
            print('Decrypted message: ' + decryptedText[:200])
            print()
            print('Enter D for done, or just press Enter to continue hacking:')
            response = input('> ')
            if response.strip().upper().startswith('D'):
                return decryptedText
    return None

if __name__ == '__main__':
    main()