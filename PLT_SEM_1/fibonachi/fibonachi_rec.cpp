#define Matrix     vector <vector<int>>
#include <iostream>
#include <vector>

using namespace std;

Matrix multiplyMatrices(const Matrix matrix1, const Matrix matrix2)
{
  Matrix res = {
                {0,0},
                {0,0}
                };
  
  res[0][0] = matrix1[0][0]*matrix2[0][0] + matrix1[0][1]*matrix2[1][0];
  res[0][1] = matrix1[0][0]*matrix2[0][1] + matrix1[0][1]*matrix2[1][1];
  res[1][0] = matrix1[1][0]*matrix2[0][0] + matrix1[1][1]*matrix2[1][0];
  res[1][1] = matrix1[1][0]*matrix2[0][1] + matrix1[1][1]*matrix2[1][1];
  return res;
}

Matrix powerMatrix(Matrix matrix, int n)
{
  if(n == 0)
  {
    Matrix e = {
                {1,0},
                {0,1}
                };
    return e;
  }
  
  if(n % 2 == 1)
  {
    Matrix tmp = multiplyMatrices(matrix, powerMatrix(matrix, n-1));
    return tmp;
  }
  else
  {
    Matrix b = powerMatrix(matrix, n/2);
    return multiplyMatrices(b,b);
  }
} 

int main()
{
  Matrix q_matrix = {
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
  Matrix res = powerMatrix(q_matrix, n - 1);
  cout << res[0][1] << endl;
}
