#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a task
typedef struct {
    char description[100];
} Task;

// Function to dynamically allocate a new task
Task* allocateTask(const char* description) {
    Task* task = (Task*)malloc(sizeof(Task));
    if (task != NULL) {
        strncpy(task->description, description, sizeof(task->description) - 1);
        task->description[sizeof(task->description) - 1] = '\0'; // Ensure the string is terminated correctly
    }
    return task;
}

// Function to free the memory of a task
void freeTask(Task* task) {
    free(task);
}

// Function to add a task to the list
void addTask(Task*** list, int* size, int* capacity) {
    char description[100];
    printf("Enter task description: ");
    scanf(" %[^\n]", description);

    if (*size == *capacity) {
        // Resize the list if necessary
        *capacity *= 2;
        *list = (Task**)realloc(*list, *capacity * sizeof(Task*));
        if (*list == NULL) {
            printf("Error allocating memory.\n");
            exit(1);
        }
    }

    Task* newTask = allocateTask(description);
    if (newTask != NULL) {
        (*list)[*size] = newTask;
        (*size)++;
        printf("Task added successfully.\n");
    } else {
        printf("Error adding the task.\n");
    }
}

// Function to remove a task from the list
void removeTask(Task*** list, int* size) {
    if (*size == 0) {
        printf("The task list is empty.\n");
    } else {
        printf("Tasks:\n");
        for (int i = 0; i < *size; i++) {
            printf("%d. %s\n", i + 1, (*list)[i]->description);
        }

        int index;
        printf("Enter the task number to remove: ");
        scanf("%d", &index);

        if (index >= 1 && index <= *size) {
            freeTask((*list)[index - 1]);
            for (int i = index - 1; i < *size - 1; i++) {
                (*list)[i] = (*list)[i + 1];
            }
            (*size)--;
            printf("Task removed successfully.\n");
        } else {
            printf("Invalid index.\n");
        }
    }
}

// Function to view the task list
void viewTasks(Task*** list, int* size) {
    if (*size == 0) {
        printf("The task list is empty.\n");
    } else {
        printf("Tasks:\n");
        for (int i = 0; i < *size; i++) {
            printf("%d. %s\n", i + 1, (*list)[i]->description);
        }
    }
}

int main() {
    int choice;
    int capacity = 10; // Initial capacity of the list
    int size = 0;     // Current size of the list
    Task** list = (Task**)malloc(capacity * sizeof(Task*));

    if (list == NULL) {
        printf("Error allocating memory.\n");
        return 1;
    }

    printf("Welcome to the Task Manager!\n");

    while (1) {
        printf("---------------------------\n");
        printf("\t Menu \n");
        printf("---------------------------\n");
        printf("0. Quit\n");
        printf("...........................\n");
        printf("1. Add task\n");
        printf("2. Remove task\n");
        printf("3. View task list\n");
        printf("---------------------------\n");
        printf("\nChoose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                // Exit the program
                // Free allocated memory
                for (int i = 0; i < size; i++) {
                    freeTask(list[i]);
                }
                free(list);
                return 0;
            case 1:
                addTask(&list, &size, &capacity);
                break;
            case 2:
                removeTask(&list, &size);
                break;
            case 3:
                viewTasks(&list, &size);
                break;
            default:
                printf("Invalid option.\n");
                break;
        }
    }
}
