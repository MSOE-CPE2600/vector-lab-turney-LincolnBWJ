/*
 * Lincoln Jiang
 * 10/15/2025
 * vector.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

#define INITIAL_CAPACITY 4

void storage_init(VectorStorage *storage) {
    storage->data = (Vector*) malloc(INITIAL_CAPACITY * sizeof(Vector));
    storage->size = 0;
    storage->capacity = INITIAL_CAPACITY;
    
    if (storage->data == NULL) {
        printf("FATAL: Memory allocation failed!\n");
        exit(1);
    }
}

void storage_add_vector(VectorStorage *storage, Vector v) {
    if (storage->size >= storage->capacity) {
        int new_capacity = storage->capacity * 2;
        Vector* new_data = (Vector*) realloc(storage->data, new_capacity * sizeof(Vector));
        
        if (new_data == NULL) {
            printf("ERROR: Memory reallocation failed!\n");
            return;
        }
        
        storage->data = new_data;
        storage->capacity = new_capacity;
    }
    
    storage->data[storage->size] = v;
    storage->size++;
}

void storage_print_all(const VectorStorage *storage) {
    printf("--- Stored Vectors (%d) ---\n", storage->size);
    int i = 0;
    while (i < storage->size) {
        Vector v = storage->data[i];
        printf("  %c: (%.2f, %.2f, %.2f)\n", v.name, v.x, v.y, v.z);
        i++;
    }
    printf("---------------------------\n");
}

void storage_clear(VectorStorage *storage) {
    free(storage->data);
    storage_init(storage);
    printf("All vectors cleared.\n");
}

void storage_free(VectorStorage *storage) {
    if (storage->data != NULL) {
        free(storage->data);
        storage->data = NULL;
    }
    storage->size = 0;
    storage->capacity = 0;
}

int load_vectors_from_csv(VectorStorage *storage, const char* filename) {
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("Error: Could not open file '%s'.\n", filename);
        return 0;
    }
    
    char line_buffer[100];
    int line_num = 0;
    
    while (fgets(line_buffer, sizeof(line_buffer), file) != NULL) {
        line_num++;
        
        if (line_buffer[0] == '\n' || line_buffer[0] == '\r') {
            continue;
        }

        Vector temp;
        int items = sscanf(line_buffer, " %c,%f,%f,%f", &temp.name, &temp.x, &temp.y, &temp.z);
        
        if (items == 4) {
            storage_add_vector(storage, temp);
        } else {
            printf("Warning: Skipping malformed line %d in file.\n", line_num);
        }
    }
    
    fclose(file);
    printf("Successfully loaded vectors from '%s'.\n", filename);
    return 1;
}

int save_vectors_to_csv(const VectorStorage *storage, const char* filename) {
    FILE *file = fopen(filename, "w");
    
    if (file == NULL) {
        printf("Error: Could not open file '%s' to save.\n", filename);
        return 0;
    }
    
    int i = 0;
    while (i < storage->size) {
        Vector v = storage->data[i];
        fprintf(file, "%c,%.2f,%.2f,%.2f\n", v.name, v.x, v.y, v.z);
        i++;
    }
    
    fclose(file);
    printf("Saved %d vectors to '%s'.\n", storage->size, filename);
    return 1;
}