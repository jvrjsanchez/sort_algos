#bubble_sort algo
import random

def bubble_sort(arr):
    swapped = True
    while swapped:
        swapped = False
        for i in range(1, len(arr)):
            if arr[i-1] > arr[i]:
                arr[i-1], arr[i] = arr[i], arr[i-1]
                swapped = True


# O(n^2)
X = [random.randrange(0,100) for i in range(25)]

print()

print("before sort: ", X)
bubble_sort(X)
print("after sort: ", X)
