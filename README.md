# Trabalho-Final-AED

DESCRIÇÃO
Matrizes esparsas são matrizes nas quais a maioria das posições são preenchidas por zeros.
Existem muitas situações onde encontramos esse tipo de matrizes, por exemplo, em Aprendizado de
Máquina e simulações da realidade com o uso de equações da física como aerodinâmica e
termodinâmica. Veja os seus usos em:
https://www.youtube.com/results?search_query=sparse+matrix

Para estas matrizes, podemos economizar um espaço significativo de memória se apenas os termos
diferentes de zero forem armazenados, pois elas podem ser gigantescas, porém só uma pequena
porcentagem delas é diferente de zero. Por exemplo, imagine que as colunas e linhas são todas as
pessoas do planeta e marcamos com 1 a linha e coluna onde as duas pessoas se conhecem.
As operações usuais sobre estas matrizes (somar, multiplicar, inverter, pivotar) também podem ser
feitas em tempo muito menor se não armazenarmos as posições que contém zeros.

# Dada a representação acima, o trabalho consiste em desenvolver um TAD cuja interface em C é especificada abaixo:

Matrix* matrix_create( void ): lê de stdin os elementos diferentes de zero de uma matriz e monta
a estrutura especificada acima. A entrada consiste dos valores de m e n (número de linhas e de
colunas da matriz) seguidos de triplas (i, j, valor) para os elementos diferentes de zero da matriz.
Por exemplo, para a matriz da Figura 1, a entrada seria:
4 4
1 1 50.0
2 1 10.0
2 3 20.0
4 1 −30.0
4 3 −60.0
4 4 5.0
.
Para facilitar a leitura de stdin, pode-se usar um marcador especial de fim de matriz após a última
tripla (por exemplo, “.” ou “0”).

void matrix_destroy( Matrix* m ): devolve todas as células da matriz m para a área de memória
disponível.

void matrix_print( Matrix* m ): imprime a matriz m para stdout no mesmo formato usado por
matrix_create().

Matrix* matrix_add( Matrix* m, Matrix* n ): recebe como parâmetros as matrizes m e n,
retornando a soma das mesmas (a estrutura da matriz retornada deve ser alocada dinamicamente
pela própria operação).

Matrix* matrix_multiply( Matrix* m, Matrix* n ): recebe como parâmetros as matrizes m e n,
retornando a multiplicação das mesmas (a estrutura da matriz retornada deve ser alocada
dinamicamente pela própria operação).

Matrix* matrix_transpose( Matrix* m ): recebe como parâmetro a matriz m, retornando mT – a
transposta de m (a estrutura da matriz retornada deve ser alocada dinamicamente pela própria
operação).

float matrix_getelem( Matrix* m, int x, int y ): retorna o valor do elemento (x, y) da matriz m.

void matrix_setelem( Matrix* m, int x, int y, float elem ): atribui ao elemento (x, y) da matriz m
o valor elem.

# TESTES
1) A resolução deve ser testada com o seguinte programa:
#include "matrix.h"
  int main( void ) {
  /* Inicializacao da aplicacao ... */
  Matrix *A = matrix_create();
  matrix_print( A );
  Matrix *B = matrix_create();
  matrix_print( B );
  Matrix *C = matrix_add( A, B );
  matrix_print( C );
  matrix_destroy( C );
  C = matrix_multiply( A, B );
  matrix_print( C );
  matrix_destroy( C );
  C = matrix_transpose( A );
  matrix_print( C );
  matrix_destroy( C );
  matrix_destroy( A );
  matrix_destroy( B );
  return 0;
}
