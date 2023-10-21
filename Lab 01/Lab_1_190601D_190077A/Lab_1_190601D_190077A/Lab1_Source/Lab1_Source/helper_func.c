#include "helper_func.h"

void shuffle(int *array, int n) {
    // Fisher-Yates shuffle algorithm
    srand(time(0));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}
