import sys
import time
import random
import matplotlib.pyplot as plt

# Function to insert elements into a balanced tree
def insert_balanced(root, value):
    if root is None:
        return Node(value)
    if value < root.value:
        root.left = insert_balanced(root.left, value)
    elif value > root.value:
        root.right = insert_balanced(root.right, value)
    return root

# Function to insert elements into an unbalanced tree
def insert_unbalanced(root, value):
    if root is None:
        return Node(value)
    if random.random() < 0.5:
        root.left = insert_unbalanced(root.left, value)
    else:
        root.right = insert_unbalanced(root.right, value)
    return root

def find_min(root):
    current = root
    while current.left is not None:
        current = current.left
    return current

# Function to remove a node in order (balanced tree)
def remove_in_order(root, value):
    if root is None:
        return root
    if value < root.value:
        root.left = remove_in_order(root.left, value)
    elif value > root.value:
        root.right = remove_in_order(root.right, value)
    else:
        if root.left is None:
            temp = root.right
            root = None
            return temp
        elif root.right is None:
            temp = root.left
            root = None
            return temp
        temp = find_min(root.right)
        root.value = temp.value
        root.right = remove_in_order(root.right, temp.value)
    return root

# Function to measure time for insertion and removal
def measure_time(action, n, operation):
    root = None
    times = []

    for i in range(1, n + 1):
        value = random.randint(1, 1000)
        start_time = time.perf_counter()
        
        if operation == "insert":
            root = action(root, value)
        elif operation == "remove":
            root = remove_in_order(root, value)

        end_time = time.perf_counter()
        execution_time = (end_time - start_time) * 1e9  # Convert to nanoseconds
        times.append(execution_time)

    return times

# Class to represent a binary tree node
class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

# Main function
if __name__ == "__main__":
    n = 1000000  # Number of elements to insert or remove
    random.seed(42)

    # Measure insertion time for balanced and unbalanced trees
    insert_times_balanced = measure_time(insert_balanced, n, "insert")
    insert_times_unbalanced = measure_time(insert_unbalanced, n, "insert")

    # Measure removal time for balanced and unbalanced trees (in-order)
    remove_times_balanced_in_order = measure_time(lambda root, value: remove_in_order(root, value), n, "remove")
    remove_times_unbalanced_in_order = measure_time(lambda root, value: remove_in_order(root, value), n, "remove")

    # Measure removal time for balanced and unbalanced trees (pre-order)
    remove_times_balanced_pre_order = measure_time(lambda root, value: insert_balanced(root, value), n, "remove")
    remove_times_unbalanced_pre_order = measure_time(lambda root, value: insert_unbalanced(root, value), n, "remove")

    # Measure removal time for balanced and unbalanced trees (post-order)
    remove_times_balanced_post_order = measure_time(lambda root, value: insert_balanced(root, value), n, "remove")
    remove_times_unbalanced_post_order = measure_time(lambda root, value: insert_unbalanced(root, value), n, "remove")

    # Create normalized times for better visualization
    max_time_insert = max(insert_times_balanced + insert_times_unbalanced)

    max_time_remove_in_order = max(remove_times_balanced_in_order + remove_times_unbalanced_in_order)
    max_time_remove_pre_order = max(remove_times_balanced_pre_order + remove_times_unbalanced_pre_order)
    max_time_remove_post_order = max(remove_times_balanced_post_order + remove_times_unbalanced_post_order)

    normalized_insert_times_balanced = [t / max_time_insert for t in insert_times_balanced]
    normalized_insert_times_unbalanced = [t / max_time_insert for t in insert_times_unbalanced]

    normalized_remove_times_balanced_in_order = [t / max_time_remove_in_order for t in remove_times_balanced_in_order]
    normalized_remove_times_unbalanced_in_order = [t / max_time_remove_in_order for t in remove_times_unbalanced_in_order]

    normalized_remove_times_balanced_pre_order = [t / max_time_remove_pre_order for t in remove_times_balanced_pre_order]
    normalized_remove_times_unbalanced_pre_order = [t / max_time_remove_pre_order for t in remove_times_unbalanced_pre_order]

    normalized_remove_times_balanced_post_order = [t / max_time_remove_post_order for t in remove_times_balanced_post_order]
    normalized_remove_times_unbalanced_post_order = [t / max_time_remove_post_order for t in remove_times_unbalanced_post_order]

    # Plot a scatter plot for insertion time
    plt.figure(1)
    plt.scatter(range(1, n + 1), normalized_insert_times_balanced, label="Balanced Tree (Insert)", s=10)
    plt.scatter(range(1, n + 1), normalized_insert_times_unbalanced, label="Unbalanced Tree (Insert)", s=10)
    plt.ylabel("Normalized Time")
    plt.xlabel("Number of Elements")
    plt.title("Insertion Time (Normalized Scatter Plot)")
    #plt.ylim(0, 0.6)  # Set the y-axis range
    plt.legend()
    plt.grid(True)

    # Plot a scatter plot for removal time (in-order)
    plt.figure(2)
    plt.scatter(range(1, n + 1), normalized_remove_times_balanced_in_order, label="Balanced Tree (Remove - In-Order)", s=10)
    plt.scatter(range(1, n + 1), normalized_remove_times_unbalanced_in_order, label="Unbalanced Tree (Remove - In-Order)", s=10)
    plt.ylabel("Normalized Time")
    plt.xlabel("Number of Elements")
    plt.title("Removal Time (In-Order) (Normalized Scatter Plot)")
    #plt.ylim(0, 0.3)  # Set the y-axis range
    plt.legend()
    plt.grid(True)

    # Plot a scatter plot for removal time (pre-order)
    plt.figure(3)
    plt.scatter(range(1, n + 1), normalized_remove_times_balanced_pre_order, label="Balanced Tree (Remove - Pre-Order)", s=10)
    plt.scatter(range(1, n + 1), normalized_remove_times_unbalanced_pre_order, label="Unbalanced Tree (Remove - Pre-Order)", s=10)
    plt.ylabel("Normalized Time")
    plt.xlabel("Number of Elements")
    plt.title("Removal Time (Pre-Order) (Normalized Scatter Plot)")
    #plt.ylim(0, 0.3)  # Set the y-axis range
    plt.legend()
    plt.grid(True)

    # Plot a scatter plot for removal time (post-order)
    plt.figure(4)
    plt.scatter(range(1, n + 1), normalized_remove_times_balanced_post_order, label="Balanced Tree (Remove - Post-Order)", s=10)
    plt.scatter(range(1, n + 1), normalized_remove_times_unbalanced_post_order, label="Unbalanced Tree (Remove - Post-Order)", s=10)
    plt.ylabel("Normalized Time")
    plt.xlabel("Number of Elements")
    plt.title("Removal Time (Post-Order) (Normalized Scatter Plot)")
    #plt.ylim(0, 0.3)  # Set the y-axis range
    plt.legend()
    plt.grid(True)

    # Show all plots
    plt.show()

# Exit the program successfully
sys.exit(0)
