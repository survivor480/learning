import random, sys
from transposition_cipher import encryptMessage
from transposition_cipher_decryption import decrypt_transposition_cipher

def main():
    random.seed(42)

    for i in range(20):
        message = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'

        message = list(message)
        random.shuffle(message)

        message = ''.join(message)

        print('Test #%s: %s..."' % (i+1, message[:50]))

        for key in range(1, len(message)):
            encrypted = encryptMessage(key, message)
            decrypted = decrypt_transposition_cipher(key, encrypted)

            if message != decrypted:
                print('Mismatch with key %s and message %s.'%(key, message))
                print(decrypted)
                sys.exit()

    print('Transposition cipher test passed')

if __name__ == '__main__':
    main()