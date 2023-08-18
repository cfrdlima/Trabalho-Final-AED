#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

Matrix *matrix_create()
{
  // Criacao da Matriz
}

void matrix_destroy(Matrix *m)
{
  // Destruicao da Matriz
}

void matrix_print(Matrix *m)
{
  // Print da Matriz
}

Matrix *matrix_add(Matrix *m, Matrix *n)
{
  // Soma das Matrizes
}

Matrix *matrix_multiply(Matrix *m, Matrix *n)
{
  // Multiplicacao das Matrizes
}

Matrix *matrix_transpose(Matrix *m)
{
  // Transpose da Matriz
}

float matrix_getelem(Matrix *m, int x, int y)
{
  // Pega Elemento da Matriz
}

void matrix_setelem(Matrix *m, int x, int y, float elem)
{
  // Set Elemento da Matriz
}

int main()
{
  /* Inicializacao da aplicacao ... */
  Matrix *A = matrix_create();
  matrix_print(A);

  Matrix *B = matrix_create();
  matrix_print(B);

  Matrix *C = matrix_add(A, B);
  matrix_print(C);
  matrix_destroy(C);

  C = matrix_multiply(A, B);
  matrix_print(C);
  matrix_destroy(C);

  C = matrix_transpose(A);
  matrix_print(C);
  matrix_destroy(C);

  matrix_destroy(A);
  matrix_destroy(B);
  return 0;
}
