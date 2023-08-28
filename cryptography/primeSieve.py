import math

def isPrime(num):
    if num < 2:
        return False

    for i in range(2, int(math.sqrt(num)) + 1):
        if num % i == 0:
            return False
    return True

def primeSieve(seiveSize):
    sieve = [True] * seiveSize
    sieve[0] = False
    sieve[1] = False


    for i in range(2, int(math.sqrt(seiveSize)) + 1):
        pointer = i * 2
        while pointer < seiveSize:
            sieve[pointer] = False
            pointer += i

    primes = []
    for i in range(seiveSize):
        if sieve[i] == True:
            primes.append(i)

    return primes