/*
 * K - num of bots we should use
 * rateSum(N)/N=X
 * => rateSum(N) = XN (1)
 * 
 * (rateSum(N)+k)/(N+K) <= Y
 * => from(1):
 * XN/(N+K) <= Y
 * XN <= YN+YK
 * YK >= XN-YN
 * K >= (XN-YN)/Y
 * =>
 * |-------------------|
 * | K = [(XN-YN)/Y]+1 |
 * |-------------------|
 *
*/

#include <iostream>
using namespace std;
int main() {
	const double e = 0.000000001;
	
	float X = 0;
	float Y = 0;
	int N = 0;
	int K = 0;
	
	cout << "X:"; cin >> X;
	cout << "Y:"; cin >> Y;
	cout << "N:"; cin >> N;
	
	if(X == Y) {
		cout << 0 << endl;
		return 0;
	} else if (	== 0) {
		cout << "error." << endl;
		return 0;		
	}	
	
	X = X + 0.5 - e;
	Y = Y + 0.5 - e;

	K = ((N*(X-Y))/Y)/1 + 1;
	cout << K << endl;
	return 0;
}
