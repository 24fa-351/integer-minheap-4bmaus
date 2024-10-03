#include <stdio.h>
#include <stdlib.h>
#include "some_heap.h"

#define KEY_NOT_PRESENT -1

// Create a new heap
heap_t *heap_create(int capacity) {
    heap_t *heap = (heap_t *)malloc(sizeof(heap_t));
    heap->data = (heap_node_t *)malloc(sizeof(heap_node_t) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Free heap memory
void heap_free(heap_t *heap) {
    free(heap->data);
    free(heap);
}

// Get size of heap
unsigned int heap_size(heap_t *heap) { 
    return heap->size; 
}

// Get parent index
unsigned int heap_parent(unsigned int index) { 
    return (index - 1) / 2; 
}

// Get left child index
unsigned int heap_left_child(unsigned int index) { 
    return 2 * index + 1; 
}

// Get right child index
unsigned int heap_right_child(unsigned int index) { 
    return 2 * index + 2; 
}

// Get heap level
unsigned int heap_level(unsigned int index) {
    unsigned int level = 0;
    while (index > 0) {
        index = heap_parent(index);
        level++;
    }
    return level;
}

// Print the heap
void heap_print(heap_t *heap) {
    for (int ix = 0; ix < heap_size(heap); ix++) {
        printf("%3d - %3d : " HEAP_KEY_FORMAT "\n", heap_level(ix), ix, heap->data[ix].key);
    }
    printf("\n");
}

// Swap elements in heap
void heap_swap(heap_t *heap, int index1, int index2) {
    heap_node_t temp = heap->data[index1];
    heap->data[index1] = heap->data[index2];
    heap->data[index2] = temp;
}

// Bubble up to maintain min-heap property
void heap_bubble_up(heap_t *heap, int index) {
    while (index > 0 && heap->data[index].key < heap->data[heap_parent(index)].key) {
        heap_swap(heap, index, heap_parent(index));
        index = heap_parent(index);
    }
}

// Bubble down to maintain min-heap property
void heap_bubble_down(heap_t *heap, int index) {
    int left = heap_left_child(index);
    int right = heap_right_child(index);
    int smallest = index;

    if (left < heap_size(heap) && heap->data[left].key < heap->data[smallest].key) {
        smallest = left;
    }
    if (right < heap_size(heap) && heap->data[right].key < heap->data[smallest].key) {
        smallest = right;
    }

    if (smallest != index) {
        heap_swap(heap, index, smallest);
        heap_bubble_down(heap, smallest);
    }
}

// Insert into heap
void heap_insert(heap_t *heap, heap_key_t key, heap_value_t data) {
    if (heap_size(heap) == heap->capacity) {
        return;
    }

    heap->data[heap_size(heap)].key = key;
    heap->data[heap_size(heap)].value = data;
    heap->size++;

    heap_bubble_up(heap, heap_size(heap) - 1);
}

// Remove minimum element from heap
heap_value_t heap_remove_min(heap_t *heap) {
    if (heap_size(heap) == 0) {
        return NULL;
    }

    heap_value_t min = heap->data[0].value;
    heap->size--;

    // Move last element to root
    heap->data[0] = heap->data[heap_size(heap)];

    // Bubble it down
    heap_bubble_down(heap, 0);

    return min;
}

void heap_print_to_file(heap_t *heap, FILE *output) {
    for (int ix = 0; ix < heap_size(heap); ix++) {
        fprintf(output, "%3d - %3d : " HEAP_KEY_FORMAT "\n", heap_level(ix), ix, heap->data[ix].key);
    }
    fprintf(output, "\n");
}
