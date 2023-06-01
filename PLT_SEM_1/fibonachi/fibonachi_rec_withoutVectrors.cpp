#include <iostream>

using namespace std;


void multiplyQMatrices(int (*matrix1)[2], int (*matrix2)[2], int (*result)[2])
{
  /*
   * |a0 a1|
   * |b0 b1|
   */
  int a0 = matrix1[0][0]*matrix2[0][0] + matrix1[0][1]*matrix2[1][0];
  int a1 = matrix1[0][0]*matrix2[0][1] + matrix1[0][1]*matrix2[1][1];
  int b0 = matrix1[1][0]*matrix2[0][0] + matrix1[1][1]*matrix2[1][0];
  int b1 = matrix1[1][0]*matrix2[0][1] + matrix1[1][1]*matrix2[1][1];
  
  result[0][0] = a0; result[0][1] = a1;
  result[1][0] = b0; result[1][1] = b1;
}

void power_Qmatrix(int m[][2], int n, int res[][2])
{
  
}

int main()
{
  
}
