#include <iostream>
#include <cmath>

using namespace std;
int main() {
	int N = 0;
	cin >> N;
	int i = 1; // i - сколько разрядов
	int approximation = 0;
	while(approximation + 9*i*pow(10, (i-1)) < N) {
		approximation += 9*i*pow(10, i-1);
		i += 1;
	}
	int remainder = N - approximation - 1; // сколько цифр осталось до N
	int num = pow(10, i-1) + remainder / i;
	int digit_index = remainder % i;
	string tmp = to_string(num);
	cout << tmp[digit_index] << endl;
	cout << "num: " << num << endl;
	return 0;
}
