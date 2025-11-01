/*
 * Lincoln Jiang
 * 10/15/2025
 * vector.h
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>

typedef struct {
    char name;
    float x;
    float y;
    float z;
} Vector;

typedef struct {
    Vector* data;
    int size;
    int capacity;
} VectorStorage;

void storage_init(VectorStorage *storage);

void storage_add_vector(VectorStorage *storage, Vector v);

void storage_print_all(const VectorStorage *storage);

void storage_clear(VectorStorage *storage);

void storage_free(VectorStorage *storage);

int load_vectors_from_csv(VectorStorage *storage, const char* filename);

int save_vectors_to_csv(const VectorStorage *storage, const char* filename);

#endif