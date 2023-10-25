import matplotlib.pyplot as plt
import time
import random
import sys

# Set the new recursion limit (adjust as needed)
new_recursion_limit = 10000
sys.setrecursionlimit(new_recursion_limit)

# TreeNode represents a node in a binary tree.
class TreeNode:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

# BinaryTree is an unbalanced binary tree data structure.
class BinaryTree:
    def __init__(self):
        self.root = None

    # Insert a value into the binary tree.
    def insert(self, value):
        self.root = self._insert_recursive(self.root, value)

    # Recursive helper function to insert a value.
    def _insert_recursive(self, node, value):
        if node is None:
            return TreeNode(value)
        if value < node.value:
            node.left = self._insert_recursive(node.left, value)
        elif value > node.value:
            node.right = self._insert_recursive(node.right, value)
        return node

    # Remove a value from the binary tree.
    def remove(self, value):
        self.root = self._remove_recursive(self.root, value)

    # Recursive helper function to remove a value.
    def _remove_recursive(self, node, value):
        if node is None:
            return node
        if value < node.value:
            node.left = self._remove_recursive(node.left, value)
        elif value > node.value:
            node.right = self._remove_recursive(node.right, value)
        else:
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left
            node.value = self._min_value(node.right)
            node.right = self._remove_recursive(node.right, node.value)
        return node

    # Find the minimum value in the tree.
    def _min_value(self, node):
        while node.left is not None:
            node = node.left
        return node.value

# AVLNode represents a node in an AVL balanced tree.
class AVLNode:
    def __init__(self, value):
        self.value = value
        self.height = 1
        self.left = None
        self.right = None

# BalancedTree is an AVL balanced tree data structure.
class BalancedTree:
    def __init__(self):
        self.root = None

    # Insert a value into the AVL balanced tree.
    def insert(self, value):
        self.root = self._insert_recursive(self.root, value)

    # Recursive helper function to insert a value.
    def _insert_recursive(self, node, value):
        if node is None:
            return AVLNode(value)
        if value < node.value:
            node.left = self._insert_recursive(node.left, value)
        elif value > node.value:
            node.right = self._insert_recursive(node.right, value)
        node.height = 1 + max(self._get_height(node.left), self._get_height(node.right))
        return self._balance(node)

    # Remove a value from the AVL balanced tree.
    def remove(self, value):
        self.root = self._remove_recursive(self.root, value)

    # Recursive helper function to remove a value.
    def _remove_recursive(self, node, value):
        if node is None:
            return node
        if value < node.value:
            node.left = self._remove_recursive(node.left, value)
        elif value > node.value:
            node.right = self._remove_recursive(node.right, value)
        else:
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left
            node.value = self._min_value(node.right)
            node.right = self._remove_recursive(node.right, node.value)
        node.height = 1 + max(self._get_height(node.left), self._get_height(node.right))
        return self._balance(node)

    # Balance the AVL tree.
    def _balance(self, node):
        balance = self._get_balance(node)
        if balance > 1:
            if self._get_balance(node.left) < 0:
                node.left = self._rotate_left(node.left)
            return self._rotate_right(node)
        if balance < -1:
            if self._get_balance(node.right) > 0:
                node.right = self._rotate_right(node.right)
            return self._rotate_left(node)
        return node

    # Get the height of a node.
    def _get_height(self, node):
        if node is None:
            return 0
        return node.height

    # Get the balance factor of a node.
    def _get_balance(self, node):
        if node is None:
            return 0
        return self._get_height(node.left) - self._get_height(node.right)

    # Rotate a node to the left.
    def _rotate_left(self, z):
        y = z.right
        T2 = y.left
        y.left = z
        z.right = T2
        z.height = 1 + max(self._get_height(z.left), self._get_height(z.right))
        y.height = 1 + max(self._get_height(y.left), self._get_height(y.right))
        return y

    # Rotate a node to the right.
    def _rotate_right(self, y):
        x = y.left
        T2 = x.right
        x.right = y
        y.left = T2
        y.height = 1 + max(self._get_height(y.left), self._get_height(y.right))
        x.height = 1 + max(self._get_height(x.left), self._get_height(x.right))
        return x

    # Find the minimum value in the tree.
    def _min_value(self, node):
        while node.left is not None:
            node = node.left
        return node.value

# Timer measures the time taken for tree operations.
class Timer:
    def measure_time(self, data, tree, operation):
        start_time = time.time()
        for value in data:
            if operation == "insert":
                tree.insert(value)
            elif operation == "remove":
                tree.remove(value)
        end_time = time.time()
        return end_time - start_time

# Generate datasets for insertion and removal operations.
data_ascending = [i for i in range(1001)]
data_descending = [i for i in range(1000, -1, -1)]
data_random = [i for i in random.sample(range(1001), 1001)]

# Create instances of binary and balanced trees, and a timer.
binary_tree = BinaryTree()
balanced_tree = BalancedTree()
timer = Timer()

# Lists to store timing measurements
insert_time_ascending_binary = []  # Insertion into unbalanced binary tree (ascending)
insert_time_descending_binary = []  # Insertion into unbalanced binary tree (descending)
insert_time_random_binary = []  # Insertion into unbalanced binary tree (random)

remove_time_ascending_binary = []  # Removal from unbalanced binary tree (ascending)
remove_time_descending_binary = []  # Removal from unbalanced binary tree (descending)
remove_time_random_binary = []  # Removal from unbalanced binary tree (random)

insert_time_ascending_balanced = []  # Insertion into balanced AVL tree (ascending)
insert_time_descending_balanced = []  # Insertion into balanced AVL tree (descending)
insert_time_random_balanced = []  # Insertion into balanced AVL tree (random)

remove_time_ascending_balanced = []  # Removal from balanced AVL tree (ascending)
remove_time_descending_balanced = []  # Removal from balanced AVL tree (descending)
remove_time_random_balanced = []  # Removal from balanced AVL tree (random)

# Measure time for insertion and removal in binary tree.
insert_time_ascending_binary.append(timer.measure_time(data_ascending, binary_tree, "insert"))
insert_time_descending_binary.append(timer.measure_time(data_descending, binary_tree, "insert"))
insert_time_random_binary.append(timer.measure_time(data_random, binary_tree, "insert"))

remove_time_ascending_binary.append(timer.measure_time(data_ascending, binary_tree, "remove"))
remove_time_descending_binary.append(timer.measure_time(data_descending, binary_tree, "remove"))
remove_time_random_binary.append(timer.measure_time(data_random, binary_tree, "remove"))

# Measure time for insertion and removal in balanced tree.
insert_time_ascending_balanced.append(timer.measure_time(data_ascending, balanced_tree, "insert"))
insert_time_descending_balanced.append(timer.measure_time(data_descending, balanced_tree, "insert"))
insert_time_random_balanced.append(timer.measure_time(data_random, balanced_tree, "insert"))

remove_time_ascending_balanced.append(timer.measure_time(data_ascending, balanced_tree, "remove"))
remove_time_descending_balanced.append(timer.measure_time(data_descending, balanced_tree, "remove"))
remove_time_random_balanced.append(timer.measure_time(data_random, balanced_tree, "remove"))

# Plot 1: Insertion into the unbalanced binary tree (ascending, descending, random)
plt.figure(figsize=(10, 6))
plt.plot(data_ascending, insert_time_ascending_binary, label="Binary Tree (Ascending)", marker='o', markersize=3)
plt.plot(data_descending, insert_time_descending_binary, label="Binary Tree (Descending)", marker='x', markersize=3)
plt.plot(data_random, insert_time_random_binary, label="Binary Tree (Random)", marker='s', markersize=3)
plt.title("Insertion in Unbalanced Binary Tree")
plt.xlabel("Number of Elements")
plt.ylabel("Time (s)")
plt.legend()
plt.grid(True)

# Plot 2: Removal from the unbalanced binary tree.
plt.figure(figsize=(10, 6))
plt.plot(data_ascending, remove_time_ascending_binary, label="Binary Tree (Ascending)", marker='o', markersize=3)
plt.plot(data_descending, remove_time_descending_binary, label="Binary Tree (Descending)", marker='x', markersize=3)
plt.plot(data_random, remove_time_random_binary, label="Binary Tree (Random)", marker='s', markersize=3)
plt.title("Removal in Unbalanced Binary Tree")
plt.xlabel("Number of Elements")
plt.ylabel("Time (s)")
plt.legend()
plt.grid(True)

# Plot 3: Insertion into the balanced AVL tree.
plt.figure(figsize=(10, 6))
plt.plot(data_ascending, insert_time_ascending_balanced, label="Balanced Tree (Ascending)", marker='o', markersize=3)
plt.plot(data_descending, insert_time_descending_balanced, label="Balanced Tree (Descending)", marker='x', markersize=3)
plt.plot(data_random, insert_time_random_balanced, label="Balanced Tree (Random)", marker='s', markersize=3)
plt.title("Insertion in Balanced AVL Tree")
plt.xlabel("Number of Elements")
plt.ylabel("Time (s)")
plt.legend()
plt.grid(True)

# Plot 4: Removal from the balanced AVL tree.
plt.figure(figsize=(10, 6))
plt.plot(data_ascending, remove_time_ascending_balanced, label="Balanced Tree (Ascending)", marker='o', markersize=3)
plt.plot(data_descending, remove_time_descending_balanced, label="Balanced Tree (Descending)", marker='x', markersize=3)
plt.plot(data_random, remove_time_random_balanced, label="Balanced Tree (Random)", marker='s', markersize=3)
plt.title("Removal in Balanced AVL Tree")
plt.xlabel("Number of Elements")
plt.ylabel("Time (s)")
plt.legend()
plt.grid(True)

# Show the plots.
plt.show()
