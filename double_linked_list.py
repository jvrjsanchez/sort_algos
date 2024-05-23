import random

# Definition for a Node.
class Node:
    def __init__(self, val, prev=None, next=None, child=None):
        self.val = val
        self.prev = prev
        self.next = next
        self.child = child

class Solution:
    def flatten(self, head: 'Optional[Node]') -> 'Optional[Node]':
        if not head:
            return None
        
        dummy = Node(0, None, head, None)  # Dummy node to simplify edge cases
        self.flatten_dfs(dummy, head)
        dummy.next.prev = None  # Set the prev pointer of the first node to None
        return dummy.next
    
    def flatten_dfs(self, prev, curr):
        if not curr:
            return prev
        
        curr.prev = prev
        prev.next = curr
        
        # Save the next pointer since it will be overwritten
        next_node = curr.next
        
        if curr.child:
            child_tail = self.flatten_dfs(curr, curr.child)
            curr.child = None  # Set child pointer to None after flattening
            
            if next_node:
                child_tail.next = next_node
                next_node.prev = child_tail
            return self.flatten_dfs(child_tail, next_node)
        
        return self.flatten_dfs(curr, next_node)

# Helper function to create a doubly linked list for testing
def create_linked_list(arr):
    if not arr:
        return None
    
    head = Node(arr[0])
    curr = head
    for val in arr[1:]:
        new_node = Node(val, prev=curr)
        curr.next = new_node
        curr = new_node
    
    return head

# Helper function to print the doubly linked list
def print_linked_list(head):
    curr = head
    while curr:
        print(curr.val, end=" -> ")
        curr = curr.next
    print("None")

# Create a sample doubly linked list
X = [random.randrange(0, 100) for i in range(25)]
head = create_linked_list(X)

# Instantiate the Solution class
sol = Solution()

# Flatten the doubly linked list
flattened_head = sol.flatten(head)

# Print the original and flattened doubly linked list
print("Original doubly linked list:")
print_linked_list(head)
print("\nFlattened doubly linked list:")
print_linked_list(flattened_head)
