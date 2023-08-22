#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include "matrix.h"

struct matrix
{
  struct matrix *right;
  struct matrix *below;
  int line;
  int column;
  float info;
};

typedef struct matrix Matrix;

Matrix *createNode(int row, int col, float value)
{
  Matrix *newNode = (Matrix *)malloc(sizeof(Matrix));
  newNode->right = NULL;
  newNode->below = NULL;
  newNode->line = row;
  newNode->column = col;
  newNode->info = value;
  return newNode;
}

void addNode(Matrix **head, int row, int col, float value)
{
  Matrix *newNode = createNode(row, col, value);

  if (*head == NULL)
  {
    *head = newNode;
  }
  else
  {
    Matrix *currentRow = *head;
    while (currentRow->below != NULL && currentRow->below->line <= row)
    {
      currentRow = currentRow->below;
    }

    Matrix *currentColumn = currentRow;
    while (currentColumn->right != NULL && currentColumn->right->column <= col)
    {
      currentColumn = currentColumn->right;
    }

    newNode->below = currentColumn->below;
    currentColumn->below = newNode;

    newNode->right = currentRow->right;
    currentRow->right = newNode;
  }
}

Matrix *matrix_create()
{
  int numRows, numCols;
  printf("Digite o tamanho da Matrix: ");
  scanf("%d %d", &numRows, &numCols);
  printf("\nTamanho: Linhas: [%d]\nColunas: [%d]\n\n", numRows, numCols);
  printf("Agora preencha o conteudo da Matrix: ");

  Matrix *sparseMatrix = NULL;

  int row, col;
  float value;
  while (scanf("%d %d %f", &row, &col, &value) == 3)
  {
    if (value == 0.0)
    {
      break; // Marcador de fim de matriz
    }
    addNode(&sparseMatrix, row, col, value);
  }

  return sparseMatrix;
}

void matrix_destroy(Matrix *m)
{
  while (m != NULL)
  {
    Matrix *currentRow = m;
    while (currentRow->right != NULL)
    {
      Matrix *temp = currentRow;
      currentRow = currentRow->right;
      free(temp);
    }
    Matrix *temp = currentRow;
    m = m->below;
    free(temp);
  }
}

void matrix_print(Matrix *m)
{
  Matrix *currentRow = m;

  while (currentRow != NULL)
  {
    Matrix *currentColumn = currentRow;
    while (currentColumn != NULL)
    {
      printf("%d %d %.1f\n", currentColumn->line, currentColumn->column, currentColumn->info);
      currentColumn = currentColumn->right;
    }
    currentRow = currentRow->below;
  }
}

Matrix *matrix_add(Matrix *m, Matrix *n)
{
  if (m == NULL || n == NULL)
  {
    return NULL; // Verificação de entradas inválidas
  }

  Matrix *result = NULL;
  Matrix *currentM = m;
  Matrix *currentN = n;

  while (currentM != NULL && currentN != NULL)
  {
    if (currentM->line == currentN->line && currentM->column == currentN->column)
    {
      float sum = currentM->info + currentN->info;
      if (sum != 0.0)
      {
        addNode(&result, currentM->line, currentM->column, sum);
      }
      currentM = currentM->right;
      currentN = currentN->right;
    }
    else if (currentM->line < currentN->line || (currentM->line == currentN->line && currentM->column < currentN->column))
    {
      addNode(&result, currentM->line, currentM->column, currentM->info);
      currentM = currentM->right;
    }
    else
    {
      addNode(&result, currentN->line, currentN->column, currentN->info);
      currentN = currentN->right;
    }
  }

  while (currentM != NULL)
  {
    addNode(&result, currentM->line, currentM->column, currentM->info);
    currentM = currentM->right;
  }

  while (currentN != NULL)
  {
    addNode(&result, currentN->line, currentN->column, currentN->info);
    currentN = currentN->right;
  }

  return result;
}

Matrix *matrix_multiply(Matrix *m, Matrix *n)
{
  if (m == NULL || n == NULL)
  {
    return NULL; // Verificação de entradas inválidas
  }

  Matrix *result = NULL;
  Matrix *currentM = m;

  while (currentM != NULL)
  {
    Matrix *currentN = n;
    while (currentN != NULL)
    {
      if (currentM->column == currentN->line)
      {
        float product = currentM->info * currentN->info;
        addNode(&result, currentM->line, currentN->column, product);
      }
      currentN = currentN->below;
    }
    currentM = currentM->below;
  }

  return result;
}

Matrix *matrix_transpose(Matrix *m)
{
  if (m == NULL)
  {
    return NULL; // Verificação de entrada inválida
  }

  Matrix *result = NULL;
  Matrix *current = m;

  while (current != NULL)
  {
    addNode(&result, current->column, current->line, current->info);
    current = current->right;
  }

  return result;
}

float matrix_getelem(Matrix *m, int x, int y)
{
  if (m == NULL)
  {
    return 0.0; // Retorna 0 se a matriz for nula
  }

  Matrix *current = m;
  while (current != NULL)
  {
    if (current->line == x && current->column == y)
    {
      return current->info; // Retorna o valor do elemento encontrado
    }
    current = current->right;
  }

  return 0.0; // Retorna 0 se o elemento não for encontrado
}

void matrix_setelem(Matrix *m, int x, int y, float elem)
{
  if (m == NULL)
  {
    return; // Retorna se a matriz for nula
  }

  Matrix *current = m;
  while (current != NULL)
  {
    if (current->line == x && current->column == y)
    {
      current->info = elem; // Atualiza o valor do elemento encontrado
      return;
    }
    current = current->right;
  }

  // Se o elemento não foi encontrado, adicione-o com o valor elem
  if (elem != 0.0)
  {
    addNode(&m, x, y, elem);
  }
}