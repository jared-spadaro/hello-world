# Level Order Tree Traversal // BFS

class Node:
    def __init__(self, key):
        self.data = key
        self.left = None
        self.right = None

# Print level order traversal of tree
def printLevelOrder(root):
    h = height(root)
    for i in range(1, h+1):
        printGivenLevel(root, i)

# Print nodes at given level
def printGivenLevel(root, level):
    if root is None:
        return
    if level == 1:
        print(root.data, end = " ")
    elif level > 1:
        printGivenLevel(root.left, level - 1)
        printGivenLevel(root.right, level - 1)

def height(node):
    if node is None:
        return 0
    else:
        # Compute height of each subtree
        lheight = height(node.left)
        rheight = height(node.right)

    return lheight + 1 if lheight > rheight else rheight + 1

# Driver
root = Node(1)
root.left = Node(2)
root.right = Node(3)
root.left.left = Node(4)
root.left.right = Node(5)

print("Level order traversal of binary tree is ")
printLevelOrder(root)
