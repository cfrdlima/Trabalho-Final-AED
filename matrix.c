#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

struct matrix
{
  struct matrix *right;
  struct matrix *below;
  int line;
  int column;
  float info;
};

Matrix *criaNo(int linha, int col, float valor)
{
  Matrix *novoNo = (Matrix *)malloc(sizeof(Matrix));
  novoNo->right = NULL;
  novoNo->below = NULL;
  novoNo->line = linha;
  novoNo->column = col;
  novoNo->info = valor;
  return novoNo;
}

void matrix_setelem(Matrix *head, int linha, int col, float valor)
{
  Matrix *novoNo = criaNo(linha, col, valor);

  if (head == NULL)
  {
    head = novoNo;
  }
  else
  {
    Matrix *linhaAtual = head;
    while (linhaAtual->below != NULL && linhaAtual->below->line <= linha)
    {
      linhaAtual = linhaAtual->below;
    }

    Matrix *colunaAtual = linhaAtual;
    while (colunaAtual->right != NULL && colunaAtual->right->column <= col)
    {
      colunaAtual = colunaAtual->right;
    }

    novoNo->below = colunaAtual->below;
    colunaAtual->below = novoNo;

    novoNo->right = linhaAtual->right;
    linhaAtual->right = novoNo;
  }
}

Matrix *matrix_create()
{
  int numLinhas, numCols;
  printf("Digite o tamanho da Matrix:\n");
  scanf("%d %d", &numLinhas, &numCols);
  printf("Numero de Linhas: [%d]\nNumero de Colunas: [%d]\n", numLinhas, numCols);

  Matrix *sparseMatrix = NULL;

  int linha, col;
  float valor;
  while (scanf("%d %d %f", &linha, &col, &valor) == 3)
  {
    if (valor == 0.0)
    {
      break; // Marcador de fim de matriz
    }
    if (linha <= numLinhas && col <= numCols)
    {
      // Verifica se o elemento já existe na matriz
      float existingValue = matrix_getelem(sparseMatrix, linha, col);
      if (existingValue == 0.0)
      {
        matrix_setelem(&sparseMatrix, linha, col, valor);
      }
      else
      {
        printf("Elemento (%d, %d) já existe com valor %.1f\n", linha, col, existingValue);
      }
    }
    else
    {
      printf("Posição (%d, %d) fora dos limites da matriz %dx%d\n", linha, col, numLinhas, numCols);
    }
  }
  return sparseMatrix;
}

void matrix_destroy(Matrix *a)
{
  while (a != NULL)
  {
    Matrix *linhaAtual = a;
    while (linhaAtual->right != NULL)
    {
      Matrix *temp = linhaAtual;
      linhaAtual = linhaAtual->right;
      free(temp);
    }
    Matrix *temp = linhaAtual;
    a = a->below;
    free(temp);
  }
}

void matrix_print(Matrix *a)
{
  Matrix *linhaAtual = a;

  while (linhaAtual != NULL)
  {
    Matrix *colunaAtual = linhaAtual;
    while (colunaAtual != NULL)
    {
      if (colunaAtual->info != 0.0)
      {
        printf("%d  %d  %.1f\n", colunaAtual->line, colunaAtual->column, colunaAtual->info);
      }
      colunaAtual = colunaAtual->right;
    }
    linhaAtual = linhaAtual->below;

    printf("\n");
  }
}

Matrix *matrix_add(Matrix *m, Matrix *n)
{
  if (m == NULL || n == NULL)
  {
    return NULL; // Verificação de entradas inválidas
  }

  Matrix *result = NULL;
  Matrix *matrixM = m;
  Matrix *matrixN = n;

  while (matrixM != NULL && matrixN != NULL)
  {
    if (matrixM->line == matrixN->line && matrixM->column == matrixN->column)
    {
      float sum = matrix_getelem(matrixM, matrixM->line, matrixM->column) +
                  matrix_getelem(matrixN, matrixN->line, matrixN->column);

      if (sum != 0.0)
      {
        matrix_setelem(&result, matrixM->line, matrixM->column, sum);
      }

      matrixM = matrixM->right;
      matrixN = matrixN->right;
    }
    else if (matrixM->line < matrixN->line ||
             (matrixM->line == matrixN->line && matrixM->column < matrixN->column))
    {
      matrix_setelem(&result, matrixM->line, matrixM->column, matrix_getelem(matrixM, matrixM->line, matrixM->column));
      matrixM = matrixM->right;
    }
    else
    {
      matrix_setelem(&result, matrixN->line, matrixN->column, matrix_getelem(matrixN, matrixN->line, matrixN->column));
      matrixN = matrixN->right;
    }
  }

  while (matrixM != NULL)
  {
    matrix_setelem(&result, matrixM->line, matrixM->column, matrix_getelem(matrixM, matrixM->line, matrixM->column));
    matrixM = matrixM->right;
  }

  while (matrixN != NULL)
  {
    matrix_setelem(&result, matrixN->line, matrixN->column, matrix_getelem(matrixN, matrixN->line, matrixN->column));
    matrixN = matrixN->right;
  }

  return result;
}

Matrix *matrix_multiply(Matrix *a, Matrix *b)
{
  if (a == NULL || b == NULL)
  {
    return NULL; // Verificação de entradas inválidas
  }

  Matrix *resultado = NULL;
  Matrix *matrixA = a;
  Matrix *matrixB = b;

  while (matrixA != NULL && matrixB != NULL)
  {
    if (matrixA->line == matrixB->line && matrixA->column == matrixB->column)
    {
      float product = matrix_getelem(a, matrixA->line, matrixA->column) * matrix_getelem(b, matrixB->line, matrixB->column);
      if (product != 0.0)
      {
        matrix_setelem(resultado, matrixA->line, matrixA->column, product);
      }
      matrixA = matrixA->right;
      matrixB = matrixB->right;
    }
    else if (matrixA->line < matrixB->line || (matrixA->line == matrixB->line && matrixA->column < matrixB->column))
    {
      matrix_setelem(resultado, matrixA->line, matrixA->column, matrix_getelem(a, matrixA->line, matrixA->column));
      matrixA = matrixA->right;
    }
    else
    {
      matrix_setelem(resultado, matrixB->line, matrixB->column, matrix_getelem(b, matrixB->line, matrixB->column));
      matrixB = matrixB->right;
    }
  }

  while (matrixA != NULL)
  {
    matrix_setelem(resultado, matrixA->line, matrixA->column, matrix_getelem(a, matrixA->line, matrixA->column));
    matrixA = matrixA->right;
  }

  while (matrixB != NULL)
  {
    matrix_setelem(resultado, matrixB->line, matrixB->column, matrix_getelem(b, matrixB->line, matrixB->column));
    matrixB = matrixB->right;
  }

  return resultado;
}

Matrix *matrix_transpose(Matrix *a)
{
  if (a == NULL)
  {
    return NULL; // Verificação de entrada inválida
  }

  Matrix *resultado = NULL;
  Matrix *matrixAtual = a;

  while (matrixAtual != NULL)
  {
    matrix_setelem(resultado, matrixAtual->column, matrixAtual->line, matrixAtual->info);
    matrixAtual = matrixAtual->right;
  }

  return resultado;
}

float matrix_getelem(Matrix *a, int x, int y)
{
  Matrix *linhaAtual = a;

  while (linhaAtual != NULL && linhaAtual->line < x)
  {
    linhaAtual = linhaAtual->below;
  }

  if (linhaAtual == NULL || linhaAtual->line != x)
  {
    return 0.0;
  }

  Matrix *colunaAtual = linhaAtual;

  while (colunaAtual != NULL && colunaAtual->column < y)
  {
    colunaAtual = colunaAtual->right;
  }

  if (colunaAtual == NULL || colunaAtual->column != y)
  {
    return 0.0;
  }

  return colunaAtual->info;
}
