#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

// chama o arquivo: gcc main.c maxtrix.c -o programa
//./programa

int main()
{
  Matrix *matrixA = NULL;
  Matrix *matrixB = NULL;

  printf("Informe a matriz A:\n");
  matrixA = matrix_create();

  printf("Matriz A:\n");
  matrix_print(matrixA);

  printf("Informe a matriz B:\n");
  matrixB = matrix_create();

  printf("Matriz B:\n");
  matrix_print(matrixB);

  Matrix *sumMatrix = matrix_add(matrixA, matrixB);
  printf("Soma das matrizes A e B:\n");
  matrix_print(sumMatrix);

  Matrix *productMatrix = matrix_multiply(matrixA, matrixB);
  printf("Produto das matrizes A e B:\n");
  matrix_print(productMatrix);

  Matrix *transposeMatrixA = matrix_transpose(matrixA);
  printf("Transposta da matriz A:\n");
  matrix_print(transposeMatrixA);

  // Liberação da memória alocada para as matrizes
  matrix_destroy(matrixA);
  matrix_destroy(matrixB);
  matrix_destroy(sumMatrix);
  matrix_destroy(productMatrix);
  matrix_destroy(transposeMatrixA);

  return 0;
}
