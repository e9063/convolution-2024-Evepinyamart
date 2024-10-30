#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void convolve_sequential(int *A, int NA, int *F, int NF, int *R)
{
  for (int i = 0; i <= NA - NF; i++)
  {
    int sum = 0;
    for (int j = 0; j < NF; j++)
    {
      sum += A[i + j] * F[NF - 1 - j]; // Reverse F for convolution
    }
    R[i] = sum;
  }
}

int main()
{
  int NA, NF;
  scanf("%d %d", &NA, &NF);

  int *A = malloc(NA * sizeof(int));
  int *F = malloc(NF * sizeof(int));
  int *R = malloc((NA - NF + 1) * sizeof(int));

  for (int i = 0; i < NA; i++)
    scanf("%d", &A[i]);
  for (int i = 0; i < NF; i++)
    scanf("%d", &F[i]);

  // Start timing
  clock_t start = clock();

  // Perform convolution
  convolve_sequential(A, NA, F, NF, R);

  // End timing
  clock_t end = clock();
  double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Sequential Execution Time: %f seconds\n", time_taken);

  for (int i = 0; i < NA - NF + 1; i++)
    printf("%d\n", R[i]);

  free(A);
  free(F);
  free(R);
  return 0;
}
