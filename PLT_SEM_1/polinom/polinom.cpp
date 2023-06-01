#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

int deg(string exp)
{
  int deg = 0;
  int cur_x = 0;
  int cur_op = 0;
  for(int i = 0; i <= exp.size(); ++i)
  {
    if(exp[i] == '+' || exp[i] == '-' || i == exp.size())
    {
      int power = stoi(exp.substr(cur_x+2, i - (cur_x + 2)));
      deg = max(deg, power);
      cur_op = i;
      continue;
    }
    else if(exp[i] == 'x')
      cur_x = i;
  }
  return deg;
}

int parce_exp(string exp, double* koefs)
{
  int cur_x = 0;
  int cur_op = 0;
  for(int i = 0; i <= exp.size(); ++i)
  {
    if(exp[i] == '+' || exp[i] == '-' || i == exp.size())
    {
      double koef = stod(exp.substr(cur_op, cur_x-cur_op-1));
      int power = stoi(exp.substr(cur_x+2, i - (cur_x + 2)));
      cout << koef << " " << power << endl;
      *(koefs+power) = koef;
      cur_op = i;
      continue;
    }
    else if(exp[i] == 'x')
      cur_x = i;
  }
  return 0;
}

double polinom_of(double* koefs, int m_deg, double x)
{
  double res = 0;
  for(int i = 0; i < m_deg; ++i)
    res += koefs[i]*pow(x,i);
  return res;
}

int main()
{

  string exp;
  double L;
  double R;
  double x;
  int m_deg;
  double delta;  

  cout << "exp: "; getline(cin, exp);
  if(exp.size() == 0)
  {
    cout << "Type error. polinom must be." << endl;
    return -1;
  }
  m_deg = deg(exp);
  m_deg++;
  
  double* koefs = new double[m_deg]{0};
  parce_exp(exp, koefs);

  cout << "L: "; cin >> L;
  cout << "R: "; cin >> R;
  if(L > R)
  {
    cout << "Type error. L must be less or equal R." << endl;
    return -1;
  }
  cout << "delta: "; cin >> delta;
  if(delta > R - L || delta <= 0)
  {
    cout << "Type error. delta must be positive and less or equal R - L." << endl;
    return -1;
  }
  
  ofstream output_file;
  output_file.open("out.txt");
  output_file << "x\ty" << endl; 
  for(L; L <= R+delta; L+=delta)
      output_file << L << "\t" << polinom_of(koefs, m_deg, L) << endl;
  output_file.close();
  delete [] koefs;
  return 0;
}
