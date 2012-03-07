from random import randint

def randomize_in_place(A):
    n = len(A)
    for i in range(n):
        j = randint(0, n-1)
        A[i], A[j] = A[j], A[i]

if __name__ == "__main__":
    A = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    randomize_in_place(A)
    print A
    randomize_in_place(A)
    print A
    randomize_in_place(A)
    print A
    randomize_in_place(A)
    print A
    randomize_in_place(A)
    print A

