def nextGreaterElement(nums1, nums2):
    stack = []
    next_greater = {}
    
    for num in nums2:
        while stack and stack[-1] < num:
            next_greater[stack.pop()] = num
        stack.append(num)
    
    for num in stack:
        next_greater[num] = -1
    
    result = []
    for num in nums1:
        result.append(next_greater[num])
    
    return result

nums1 = [4, 1, 2]
nums2 = [1, 3, 4, 2]
print(nextGreaterElement(nums1, nums2))
