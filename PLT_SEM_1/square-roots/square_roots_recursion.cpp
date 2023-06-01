#include <iostream>
#include <cmath>

using namespace std;

double sqrfunc(double a, double b, double c, double x)
{
  return a*pow(x,2) + b*x + c; 
}

double get_root(double a, double b, double c, double l, double r, double eps)
{
  if(abs(r-l) < eps)
    return min(l,r);
  
  if(sqrfunc(a,b,c,l) * sqrfunc(a,b,c,(l+r)/2) > 0)
    return get_root(a, b, c, (l+r)/2, r, eps);
  else
    return get_root(a, b, c, l, (l+r)/2, eps);
}

int main()
{
  const double eps = 0.000001;
  double A; 
  double B;
  double C;
  double L; 
  double R; 

  cout << "A: "; cin >> A;
  if (A == 0) {
    cout << "incorrect input. A must be not zero." << endl;
    return 0;
  }
  cout << "B: "; cin >> B;
  cout << "C: "; cin >> C;

  double D = pow(B, 2) - 4*A*C;
  if(D < 0) {
    cout << "No roots." << endl;
    return 0;
  }

  cout << "L:  "; cin >> L;
  cout << "R:  "; cin >> R;

  if(L >= R) {
    cout << "TypeError. incorrect input." << endl;
    return 0;
  }

  if(sqrfunc(A,B,C,L) * sqrfunc(A,B,C,R) > 0 )
    cout << "Can't find roots on this slice.'" << endl;

  
  //cout << sqrfunc(A,B,C,L) << endl;
  cout << get_root(A,B,C,L,R,eps) << endl;
  return 0;
}
