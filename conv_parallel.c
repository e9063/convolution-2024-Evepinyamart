#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void convolve_parallel(int *A, int NA, int *F, int NF, int *R)
{
#pragma omp parallel for
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

  // Set number of threads
  omp_set_num_threads(4); 

  // Start timing
  double start = omp_get_wtime();

  // Perform parallel convolution
  convolve_parallel(A, NA, F, NF, R);

  // End timing
  double end = omp_get_wtime();
  printf("Parallel Execution Time: %f seconds\n", end - start);

  for (int i = 0; i < NA - NF + 1; i++)
    printf("%d\n", R[i]);

  free(A);
  free(F);
  free(R);
  return 0;
}
