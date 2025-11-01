/*
 * Lincoln Jiang
 * 10/22/2025
 * main.c
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector.h"

VectorStorage my_vectors;

void cleanup_on_exit(void) {
    printf("Exiting program, freeing memory...\n");
    storage_free(&my_vectors);
}

int main() {
    storage_init(&my_vectors);
    atexit(cleanup_on_exit);
    
    char input_line[100];
    char command[20];
    char arg1[50]; 

    printf("Vector Calculator. Type commands or 'exit' to quit.\n");
    
    int program_is_running = 1;
    while (program_is_running) {
        printf("> ");
        fgets(input_line, sizeof(input_line), stdin);
        
        int parts_read = sscanf(input_line, "%s %s", command, arg1);
        
        if (parts_read <= 0) {
            continue;
        }
        
        if (strcmp(command, "exit") == 0) {
            program_is_running = 0;
        
        } else if (strcmp(command, "list") == 0) {
            storage_print_all(&my_vectors);
        
        } else if (strcmp(command, "clear") == 0) {
            storage_clear(&my_vectors);
        
        } else if (strcmp(command, "load") == 0) {
            if (parts_read < 2) {
                printf("Usage: load <filename>\n");
            } else {
                storage_clear(&my_vectors);
                load_vectors_from_csv(&my_vectors, arg1);
            }

        } else if (strcmp(command, "save") == 0) {
            if (parts_read < 2) {
                printf("Usage: save <filename>\n");
            } else {
                save_vectors_to_csv(&my_vectors, arg1);
            }

        } else if (strcmp(command, "add") == 0) {
            Vector v;
            int add_parts = sscanf(input_line, "%s %c %f %f %f", command, &v.name, &v.x, &v.y, &v.z);
            if (add_parts < 5) {
                printf("Usage: add <name> <x> <y> <z>\n");
            } else {
                storage_add_vector(&my_vectors, v);
                printf("Added vector %c.\n", v.name);
            }

        } else {
            printf("Unknown command: '%s'\n", command);
        }
    }
    
    return 0;
}