/* 
 * Lincoln Jiang
 * 10/1/2025
 * vector_calc.c
*/

#include <stdio.h>
#include <string.h>

#define MAX_VECTORS 10

/* define structure */
typedef struct {
    char name[10];
    double x;
    double y;
    double z;
    int used;
} vect;

/* global array */
vect store[MAX_VECTORS];

/* basic vector functions */
vect add(vect a, vect b)
{
    vect returnval;
    returnval.x = a.x + b.x;
    returnval.y = a.y + b.y;
    returnval.z = a.z + b.z;
    returnval.used = 1;
    return returnval;
}

vect sub(vect a, vect b)
{
    vect returnval;
    returnval.x = a.x - b.x;
    returnval.y = a.y - b.y;
    returnval.z = a.z - b.z;
    returnval.used = 1;
    return returnval;
}

vect scalar(vect a, double s)
{
    vect returnval;
    returnval.x = a.x * s;
    returnval.y = a.y * s;
    returnval.z = a.z * s;
    returnval.used = 1;
    return returnval;
}

/* store control */
void clear_store()
{
    int i = 0;
    for (i = 0; i < MAX_VECTORS; i = i + 1) {
        store[i].used = 0;
    }
    printf("All vectors cleared.\n");
}

int find_vector(const char *name)
{
    int i = 0;
    for (i = 0; i < MAX_VECTORS; i = i + 1) {
        if (store[i].used && strcmp(store[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int add_vector(const char *name, double x, double y, double z)
{
    int index = find_vector(name);
    if (index >= 0) {
        store[index].x = x;
        store[index].y = y;
        store[index].z = z;
        return index;
    }

    int i = 0;
    for (i = 0; i < MAX_VECTORS; i = i + 1) {
        if (!store[i].used) {
            strcpy(store[i].name, name);
            store[i].x = x;
            store[i].y = y;
            store[i].z = z;
            store[i].used = 1;
            return i;
        }
    }
    printf("No space to add new vector.\n");
    return -1;
}

void list_vectors()
{
    int found = 0;
    int i = 0;
    for (i = 0; i < MAX_VECTORS; i = i + 1) {
        if (store[i].used) {
            printf("%s = %.2f %.2f %.2f\n",
                   store[i].name, store[i].x, store[i].y, store[i].z);
            found = 1;
        }
    }
    if (found == 0) {
        printf("No vectors stored.\n");
    }
}

/* main */
int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "-h") == 0) {
        printf("Usage: ./vector_calc\n");
        printf("An interactive vector calculator.\n");
        printf("Commands: quit, list, clear, help.\n");
        printf("Assignment: a = 1 2 3\n");
        printf("Operations: c = a + b | d = a * 2 | a + d\n");
        return 0;
    }

    char input[100];
    printf("Welcome to simple vector calculator - LincolnBWJ\n");
    printf("Commands: list, clear, quit, help\n");
    printf("Use form: a = 1 2 3 | c = a + b | d = a * 2\n");

    while (1) {
        printf("minimat> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            return 0;
        }

        /* remove newline */
        int len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        /* command */
         if (strcmp(input, "quit") == 0) {
            printf("Goodbye!\n");
            return 0;
        }
        if (strcmp(input, "help") == 0) {
            printf("Commands:\n");
            printf("  name = x y z      define vector\n");
            printf("  result = a + b    add\n");
            printf("  result = a - b    subtract\n");
            printf("  result = a * n    scalar multiply\n");
            printf("  list              show all vectors\n");
            printf("  clear             remove all vectors\n");
            printf("  quit              exit\n");
            continue;
        }
        if (strcmp(input, "clear") == 0) {
            clear_store();
            continue;
        }
        if (strcmp(input, "list") == 0) {
            list_vectors();
            continue;
        }

        /* declare parsing vars ONCE per-iteration */
        char name[10];
        char v1[10];
        char v2[10];
        char sign;
        double x, y, z, num;

        /* case 1: a = 1 2 3 */
        if (sscanf(input, "%s = %lf %lf %lf", name, &x, &y, &z) == 4) {
            add_vector(name, x, y, z);
            printf("%s = %.2f %.2f %.2f\n", name, x, y, z);
            continue;
        }

        /* case 3: result = a * num */
        if (sscanf(input, "%s = %s * %lf", name, v1, &num) == 3) {
            int i1 = find_vector(v1);
            if (i1 < 0) {
                printf("Vector not found.\n");
                continue;
            }
            vect result = scalar(store[i1], num);
            add_vector(name, result.x, result.y, result.z);
            printf("%s = %.2f %.2f %.2f\n", name, result.x, result.y, result.z);
            continue;
        }

        /* case 3b: result = num * a */
        if (sscanf(input, "%s = %lf * %s", name, &num, v1) == 3) {
            int i1 = find_vector(v1);
            if (i1 < 0) {
                printf("Vector not found.\n");
                continue;
            }
            vect result = scalar(store[i1], num);
            add_vector(name, result.x, result.y, result.z);
            printf("%s = %.2f %.2f %.2f\n", name, result.x, result.y, result.z);
            continue;
        }

        /* case 2: result = a + b or a - b */
        if (sscanf(input, "%s = %s %c %s", name, v1, &sign, v2) == 4) {
            int i1 = find_vector(v1);
            int i2 = find_vector(v2);
            if (i1 < 0 || i2 < 0) {
                printf("Vector not found.\n");
                continue;
            }

            vect result;
            if (sign == '+') {
                result = add(store[i1], store[i2]);
            } else if (sign == '-') {
                result = sub(store[i1], store[i2]);
            } else {
                printf("Unknown operator.\n");
                continue;
            }

            add_vector(name, result.x, result.y, result.z);
            printf("%s = %.2f %.2f %.2f\n", name, result.x, result.y, result.z);
            continue;
        }

        /* case 6: a * 2 */
        if (sscanf(input, "%s * %lf", v1, &num) == 2) {
            int i1 = find_vector(v1);
            if (i1 < 0) {
                printf("Vector not found.\n");
                continue;
            }
            vect result = scalar(store[i1], num);
            add_vector("ans", result.x, result.y, result.z);
            printf("ans = %.2f %.2f %.2f\n", result.x, result.y, result.z);
            continue;
        }
        /* case 6b: 2 * a */
        if (sscanf(input, "%lf * %s", &num, v1) == 2) {
            int i1 = find_vector(v1);
            if (i1 < 0) {
                printf("Vector not found.\n");
                continue;
            }
            vect result = scalar(store[i1], num);
            add_vector("ans", result.x, result.y, result.z);
            printf("ans = %.2f %.2f %.2f\n", result.x, result.y, result.z);
            continue;
        }

        /* case 4: a + b */
        if (sscanf(input, "%s %c %s", v1, &sign, v2) == 3) {
            int i1 = find_vector(v1);
            int i2 = find_vector(v2);
            if (i1 < 0 || i2 < 0) {
                printf("Vector not found.\n");
                continue;
            }

            vect result;
            if (sign == '+' || sign == '-') {
                 if (sign == '+') {
                    result = add(store[i1], store[i2]);
                } else { 
                    result = sub(store[i1], store[i2]);
                }
                add_vector("ans", result.x, result.y, result.z);
                printf("ans = %.2f %.2f %.2f\n", result.x, result.y, result.z);
                continue;
            }
        }

        /* case 5: display single vector by name */
        // Check if the input is a single word that is a stored vector
        char extra[100]; // buffer to check for extra input
        if (sscanf(input, "%s %s", v1, extra) == 1) {
            int i = find_vector(v1);
            if (i >= 0) {
                printf("%s = %.2f %.2f %.2f\n",
                       store[i].name, store[i].x, store[i].y, store[i].z);
                continue;
            }
        }

        printf("Invalid command. Type 'help' for info.\n");
    }
}
