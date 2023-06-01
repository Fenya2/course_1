/*
  2. Реализовать программу поиска корня квадратного уравнения на отрезке методом деления отрезка пополам с точностью 1•10^(-3). На вход даются три коэффициента квадратного уравнения (a•x^2+b•x+c=0) и две координаты концов (L, R).  Если данным методом корень найти невозможно, то вывести соответствующее сообщение. 
*/

//CHECKED

#include <iostream>
#include <cmath>

using namespace std;

double sqrfunc(double a, double b, double c, double x){
	
	return a*pow(x,2) + b*x + c; 
}

int main() {
	const double e = 0.000000001;
	
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
		cout << "incorrect input." << endl;
		return 0;
	}
	
	if(sqrfunc(A,B,C,L) * sqrfunc(A,B,C,R) > 0 ) {
			cout << "can't find roots on this slice.'" << endl;
	}
	
	bool is_increasing = true;
	
	if(sqrfunc(A,B,C,L) > 0 && sqrfunc(A,B,C,R) < 0){
		is_increasing = false;
	}
	cout << "--------------------" << endl;
	cout << "is_increasing: " << is_increasing << endl;
	
	double mid_of_LR = (L+R)/2;
	while(R-L > e) {
		//~ cout << L << "; " << R << " d: " << abs(R-L) << endl;
		if(is_increasing) {
			if(sqrfunc(A,B,C,mid_of_LR) < 0) L = mid_of_LR;
			else R = mid_of_LR;	
		} else {
			if(sqrfunc(A,B,C,mid_of_LR) > 0) L = mid_of_LR;
			else R = mid_of_LR;
		}./
		cout << L << ":" << sqrfunc(A,B,C,L) << "	" << R << ":" << sqrfunc(A,B,C,R) << endl;
		mid_of_LR = (L+R)/2;
	}
	cout << min(L,R) << endl;
	return 0;
}
