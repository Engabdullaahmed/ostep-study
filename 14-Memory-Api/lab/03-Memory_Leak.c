
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = malloc(10 * sizeof(int));

    if (ptr == NULL) {
        return 1;
    }

    ptr[0] = 100;

    // Forgot to free(ptr)

    return 0;
}
