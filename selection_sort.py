#selection_sort

import random
def selection_sort(arr):
    for i in range(len(arr)-1):
        min_val = arr[i]
        min_index = i
        for j in range(i+1, len(arr)):
            if arr[j] < min_val:
                min_val = arr[j]
                min_index = j
        arr[i], arr[min_index] = arr[min_index], arr[i]

# n(n-1)/2 = O(n^2)

X = [random.randrange(0,100) for i in range(25)]

print("before sort: ", X)
selection_sort(X)
print("after sort: ", X)