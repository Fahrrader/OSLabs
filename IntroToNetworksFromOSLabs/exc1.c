#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <unistd.h>

struct Node 
{
    struct Node *next;
    int value;
};

struct Node* root = NULL;

int count;

int peek() {
    if (root == NULL) {
        printf("Error: stack is not initialized.\n");
        return 0;
    }

    if (count == 0) {
        printf("Error: stack is empty.\n");
        return 0;
    }

    printf("%d\n", root->value);
    return root->value;
}

void push(int data) {
    if (root == NULL) {
        printf("Error: stack is not initialized.\n");
        return;
    }

    if (count == 0) {
        root->value = data;
    } else {
        struct Node *next_node = malloc(sizeof(struct Node));
        next_node->value = data;
        next_node->next = root;
        root = next_node;
    }

    count++;
}

void pop() {
    if (root == NULL) {
        printf("Error: stack is not initialized.\n");
        return;
    }

    if (count == 0) {
        printf("Error: stack is empty.\n");
        return;
    }

    struct Node* top_node = root;

    int value = top_node->value;

    root = root->next;
    free(top_node);

    count--;
    printf("%d\n", value);
}

int empty() {
    if (root == NULL) {
        printf("Error: stack is not initialized.\n");
        return 1;
    }

    if (count == 0) {
        printf("Stack is empty\n");
    } else {
        printf("Stack is not empty\n");
    }

    return count == 0;
}

void display() {
    if (root == NULL) {
        printf("Error: stack is not initialized.\n");
        return;
    }

    if (count == 0) {
        printf("Stack is empty\n");
        return;
    }

    struct Node* current_node = root;

    while (current_node != NULL) {
        printf("%d\n", current_node->value);
        current_node = current_node->next;
    }
}

void create() {
    if (root != NULL) {
        while (count > 0) {
            pop();
        }
        free(root);
    }

    root = malloc(sizeof(struct Node));
    count = 0;
    printf("Stack successfully initialized\n");
}

void stack_size() {
    printf("%d elements\n", count);
}

void read_line(char* array, int size) {
    char c;
    for (int i = 0; i < size; i++) {
        scanf("%c", &c);
        array[i] = c;
        if (c == '\n') {
            array[i] = '\0';
            return;
        }
    }
}

int read_number(char* input) {
    int result = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] >= '0' && input[i] <= '9') {
            result *= 10;
            result += input[i] - '0';
        }
    }
    return result;
}

int main() {
    printf("Commands:\n
    	create -- initialize stack\npeek -- return the top element of the stack\n
    	push N -- push new integer number N on top of the stack (example: push 7)\npop -- pop the top element from the stack\n
    	empty -- check if the stack is empty\ndisplay -- print the stack\nstack_size -- print stack size\n");

    int pipes[2];

    if (pipe(pipes) == -1) {
        printf("Error: pipe creation failed.");
        return 1;
    }

    int pid = fork();

    if (pid > 0) {
        close(pipes[0]);
        while (1) {
            char input[128];
            read_line(input, 128);
            write(pipes[1], input, 128);
        }
    } else if (pid == 0) {
        close(pipes[1]);
        while (1) {
            char output[128];
            read(pipes[0], output, 128);
            if (strstr(output, "create")) {
                create();
            } else if (strstr(output, "peek")) {
                peek();
            } else if (strstr(output, "push")) {
                push(read_number(output));
            } else if (strstr(output, "pop")) {
                pop();
            } else if (strstr(output, "empty")) {
                empty();
            } else if (strstr(output, "display")) {
                display();
            } else if (strstr(output, "stack_size")) {
                stack_size();
            }
        }
    } else {
        printf("Error: failed to create child process.");
    }

    return 0;
}