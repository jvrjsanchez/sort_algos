def nextGreaterElements(nums):
    n = len(nums)
    stack = []
    next_greater = [-1] * n
    
    for i in range(2 * n):
        index = i % n
        while stack and nums[stack[-1]] < nums[index]:
            next_greater[stack.pop()] = nums[index]
        stack.append(index)
    
    return next_greater

nums = [1, 2, 1]
print(nextGreaterElements(nums)) 
