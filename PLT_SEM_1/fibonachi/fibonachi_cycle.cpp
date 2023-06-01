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
    while (n)
    {
        if(n % 2 == 1)
        { 
            multiplyQMatrices(m, res, res);
            n--;
        }
        else
        {
            multiplyQMatrices(m, m, m);
            n /= 2;
        }
    }
    return;
}

int main()
{
  int result[2][2] = {
                  {1,0},
                  {0,1}
                  };
                  
  int matrix[2][2] = {
                  {1,1},
                  {1,0}
                  };
                  
  int n;
  cout << "n: "; cin >> n;
  
  if(n < 1)
  {
    cout << "TypeError." << endl;
    return -1;
  }
  power_Qmatrix(matrix, n-1, result);
  
  cout << "====" << endl;
  for(int i = 0; i < 2; i++)
  {
    for(int j = 0; j < 2; j++)
      cout << result[i][j] << " ";
    cout << endl;
  }
  cout << "====" << endl;
  cout << "======> " << result[0][1] << endl;
}
