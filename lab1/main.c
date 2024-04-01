#include <stdio.h>
#include <stdlib.h>

void allocArray(int ***p, int m, int n)
{
    // Assignment memory to create 2-D array
    int **temp = (int **)malloc(m * sizeof(int *));
    if (temp == NULL){
        printf("Memory allocation failed \n");
        exit(1);
    }

    int *data = (int *) malloc(m * n * sizeof(int));
    if (data == NULL) {
        printf("Memory allocation failed \n");
        free(temp);
        exit(1);
    }

    // Make sure 2-D array refer to continuous memory space
    for(int i = 0; i < m; i++) {
        temp[i] = data + i * n; // Corrected the memory offset here
    }
    *p = temp;
}

int main()
{
  int **array;
  int j, k;
  allocArray(&array, 5, 10);

  // Assigning values and printing memory address
  for(j = 0; j < 5; j++) {
    for(k = 0; k < 10; k++) {
       array[j][k] = j * 10 + k;
    }
  }
  // Fixed the loop for printing the addresses outside the assignment loop
  for(j = 0; j < 5; j++) {
    for(k = 0; k < 10; k++) {
        printf("%p ", &(array[j][k]));
    }
    printf("\n");
  }

  // Release allocated memory
  free(array[0]);
  free(array);
  return 0;
}
