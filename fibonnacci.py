import sys 

def f(n):
    a = 0
    b = 1
    for i in range(n):
        temp = a + b
        a = b
        b = temp
    return a

# (0) + 1 (1), 1 + 1 (2), 2+1 (3), 3+2 (5), 5+3 (8), 8+5 (13), 8+13 (21)
# n = 0 will return 0
# n = 1 will return 1 
# n = 2 will return f(n-2) + f(n-1) = f(0) + f(1) = 0 + 1 = 1 i.e f(2) = 1
# n = 3 will return f(1) + f(2) = 1 + 1 = 2 i.e f(3) = 2
# .....
n = int(sys.argv[1])
for i in range(n):
    print(f(i), i)

# ini