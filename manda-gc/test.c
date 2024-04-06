#include <stdio.h>
#include <stdlib.h>

typedef struct s_node {
    void *data;
    struct s_node *next;
} t_node;

t_node* init_gc() {
    return NULL; // Initialize the garbage collector (linked list) as empty
}

void* gc_malloc(t_node **gc, size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    t_node *node = (t_node*)malloc(sizeof(t_node));
    if (node == NULL) {
        perror("Failed to allocate memory for garbage collector node");
        exit(EXIT_FAILURE);
    }
    node->data = ptr;
    node->next = *gc;
    *gc = node;
    return ptr;
}

void gc_free(t_node **gc)
{
    t_node *current = *gc;
    while (current != NULL)
    {
        t_node *temp = current;
        current = current->next;
        free(temp->data); // Free the memory
        free(temp);       // Free the node
    }
    *gc = NULL; // Set the garbage collector to NULL after freeing
}

int main() {
    t_node *gc = init_gc();
    
    // Allocate memory using gc_malloc
    int *ptr1 = (int*)gc_malloc(&gc, sizeof(int));
    *ptr1 = 10;
    printf("*ptr1: %d\n", *ptr1);
    
    // Allocate memory using gc_malloc
    int *ptr2 = (int*)gc_malloc(&gc, sizeof(int));
    *ptr2 = 20;
    printf("*ptr2: %d\n", *ptr2);
    
    // Deallocate memory
    gc_free(&gc);
    
    return 0;
}
