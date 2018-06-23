#include "../include/queens.h"
#include<stdio.h>
#include<stdlib.h>

int solve(int row, int col, Cell **table, int size)
{
  int i,j;
  //check the column positions above this position
  for( i = 0; i < size; i++)
    if(table[i][col].figure == 'Q')
      return 1;

  //check upper right diagonal
  for( i = row,j = col; i >= 0 && j >= 0; i--, j--)
    if(table[i][j].figure == 'Q')
      return 1;

  for( i = row,j = col; i < size && j < size; i++, j++)
    if(table[i][j].figure == 'Q')
      return 1;

  //check upper left diagonal
  for( i = row,j = col; i >= 0 && j < size; i--, j++)
    if(table[i][j].figure == 'Q')
      return 1;

  for( i = row,j = col; j >= 0 && i < size; i++, j--)
    if(table[i][j].figure == 'Q')
      return 1;

  return 0;
}

int require(int cur_row, Cell **table, int size)
{
  if(cur_row == size)
    return 1;
  for(int i = 0; i < size; i++)
    if(!solve(cur_row, i, table, size)){
      table[cur_row][i].figure = 'Q';

      if(!require(cur_row + 1, table, size))
        table[cur_row][i].figure = 'E';
      else
        return 1;
    }
  return 0;
}

void place_queens(Cell **table, int size)
{
  require(1, table, size);
}

