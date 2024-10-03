#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "some_heap.h"

unsigned long long rand_between(unsigned long long min, unsigned long long max) {
    unsigned long long range = max - min;
    return min + (rand() % range);
}

void test_heap(void) {
    heap_t *heap = heap_create(200);
    FILE *output = fopen("heap_output.txt", "w");

    if (!output) {
        printf("Error opening file!\n");
        return;
    }

    for (heap_key_t ix = 0; ix < 20; ix++) {
        heap_key_t key = rand_between(0, 1000);
        heap_insert(heap, key, (heap_value_t)key);
        fprintf(output, "Inserted %llu\n", key);
        heap_print(heap);
    }

    for (int ix = 0; ix < 10; ix++) {
        heap_key_t key = (heap_key_t)heap_remove_min(heap);
        fprintf(output, "Removed %llu\n", key);
        heap_print(heap);
    }

    fclose(output);
    heap_free(heap);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    test_heap();
    return 0;
}
