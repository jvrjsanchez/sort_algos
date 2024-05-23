import random

def heap_sort(x):
    h = Heap()
    for i in range(len(x)):
        h.add(x[i])
    result = []
    for i in range(len(x)):
        result.append(h.remove_min())
    return result

class Heap:
    def __init__(self):
        self.arr = []
    
    def remove_min(self):
        if len(self.arr) == 0:
            return None
        
        result = self.arr[0]
        self.arr[0] = self.arr[len(self.arr)-1]
        self.arr.pop()

        i = 0
        while left_child_of(i) < len(self.arr):
            l = left_child_of(i)
            r = right_child_of(i)

            smallest = l
            if r < len(self.arr) and self.arr[r] < self.arr[l]:
                smallest = r

            if self.arr[i] > self.arr[smallest]:
                self.arr[i], self.arr[smallest] = self.arr[smallest], self.arr[i]
            i = smallest

        return result


    def add(self, x):
        self.arr.append(x)
        i = len(self.arr) - 1
        par = parent_of(i)
        while i > 0 and self.arr[par] > self.arr[i]:
            self.arr[par], self.arr[i] = self.arr[i], self.arr[par]
            i = parent_of(i)
            par = parent_of(i)

def parent_of(i):
    return (i - 1)//2

def right_child_of(i):
    return 2*i+2

def left_child_of(i):
    return 2*i+1

X = [random.randrange(0,100) for i in range(25)]
print()

print("before sort: ", X)
sorted_X = heap_sort(X)
print("after sort: ", sorted_X)