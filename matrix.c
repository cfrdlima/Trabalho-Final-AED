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
  printf("Digite o tamanho da Matrix: \n");
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

    if (valor != 0.0)
    {
      matrix_setelem(sparseMatrix, linha, col, valor);
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
  }
}

Matrix *matrix_add(Matrix *a, Matrix *b)
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
      float sum = matrixA->info + matrixB->info;
      if (sum != 0.0)
      {
        matrix_setelem(resultado, matrixA->line, matrixA->column, sum);
      }
      matrixA = matrixA->right;
      matrixB = matrixB->right;
    }
    else if (matrixA->line < matrixB->line || (matrixA->line == matrixB->line && matrixA->column < matrixB->column))
    {
      matrix_setelem(resultado, matrixA->line, matrixA->column, matrixA->info);
      matrixA = matrixA->right;
    }
    else
    {
      matrix_setelem(resultado, matrixB->line, matrixB->column, matrixB->info);
      matrixB = matrixB->right;
    }
  }

  while (matrixA != NULL)
  {
    matrix_setelem(resultado, matrixA->line, matrixA->column, matrixA->info);
    matrixA = matrixA->right;
  }

  while (matrixB != NULL)
  {
    matrix_setelem(resultado, matrixB->line, matrixB->column, matrixB->info);
    matrixB = matrixB->right;
  }

  return resultado;
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
      float product = matrixA->info * matrixB->info;
      if (product != 0.0)
      {
        matrix_setelem(resultado, matrixA->line, matrixA->column, product);
      }
      matrixA = matrixA->right;
      matrixB = matrixB->right;
    }
    else if (matrixA->line < matrixB->line || (matrixA->line == matrixB->line && matrixA->column < matrixB->column))
    {
      matrix_setelem(resultado, matrixA->line, matrixA->column, matrixA->info);
      matrixA = matrixA->right;
    }
    else
    {
      matrix_setelem(resultado, matrixB->line, matrixB->column, matrixB->info);
      matrixB = matrixB->right;
    }
  }

  while (matrixA != NULL)
  {
    matrix_setelem(resultado, matrixA->line, matrixA->column, matrixA->info);
    matrixA = matrixA->right;
  }

  while (matrixB != NULL)
  {
    matrix_setelem(resultado, matrixB->line, matrixB->column, matrixB->info);
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
  if (a == NULL)
  {
    return 0.0; // Retorna 0 se a matriz for nula
  }

  Matrix *matrixAtual = a;
  while (matrixAtual != NULL)
  {
    if (matrixAtual->line == x && matrixAtual->column == y)
    {
      return matrixAtual->info; // Retorna o valor do elemento encontrado
    }
    matrixAtual = matrixAtual->right;
  }

  return 0.0; // Retorna 0 se o elemento não for encontrado
}