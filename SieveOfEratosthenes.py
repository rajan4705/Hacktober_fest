MAX = 100000
prime = [True] * MAX

def sieve():
    global prime
    for i in range(MAX):
        if not prime[i]:
            continue
        for j in range(i * i, MAX, i):
            prime[j] = False

def main():
    prime[0] = False
    prime[1] = False

    sieve()

    x = int(input("Enter number to check if it is prime: "))

    print("PRIME!!" if prime[x] else "NOT PRIME :(")


if __name__ == "__main__":
    main()
