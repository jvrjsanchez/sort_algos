#insertion_sort
import random

def insertion_sort(arr):
    for i in range(1, len(arr)):
        copy = arr[i]
        j = i - 1
    while j >= 0 and arr[j] > copy:
        arr[j + 1] = arr[j]
        j = j - 1
    arr[j + 1] = copy


# O(n^2)

X = [random.randrange(0,100) for i in range(25)]

print("before sort: ", X)
insertion_sort(X)
print("after sort: ", X)