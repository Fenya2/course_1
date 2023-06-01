//CHECKED
#include <iostream>
#include <cmath>

using namespace std;
int main() {
	const double e = 0.000000001;
	
	double A[2];
	double B[2];
	double C[2];
	double D[2];

	cout << "A: X Y = ";
	cin >> A[0] >> A[1];
	
	cout << "B: X Y = ";
	cin >> B[0] >> B[1];

	cout << "C: X Y = ";
	cin >> C[0] >> C[1];

	double sqrAB = pow(B[0]-A[0],2) + pow(B[1]-A[1],2);
	double sqrBC = pow(B[0]-C[0],2) + pow(B[1]-C[1],2);
	double sqrCA = pow(C[0]-A[0],2) + pow(C[1]-A[1],2);

	if(abs(sqrAB - (sqrBC + sqrCA)) < e){
		cout << "right triangle" << endl;
		double vec_CA[2];
		vec_CA[0] = A[0] - C[0];
		vec_CA[1] = A[1] - C[1];
		
		double vec_CB[2];
		vec_CB[0] = B[0] - C[0];
		vec_CB[1] = B[1] - C[1];
		
		double vec_CAplusvec_CB[2];
		vec_CAplusvec_CB[0] = vec_CA[0]+vec_CB[0];
		vec_CAplusvec_CB[1] = vec_CA[1]+vec_CB[1];
		
		D[0] = C[0] + vec_CAplusvec_CB[0];
		D[1] = C[1] + vec_CAplusvec_CB[1];
		cout << "D: " << D[0] << " " << D[1] << endl;

	} else if (abs(sqrBC - (sqrAB + sqrCA)) < e) {
		cout << "right triangle" << endl;
		double vec_AB[2];
		vec_AB[0] = B[0] - A[0];
		vec_AB[1] = B[1] - A[1];
		
		double vec_AC[2];
		vec_AC[0] = C[0] - A[0];
		vec_AC[1] = C[1] - A[1];
		
		double vec_ABplusvec_AC[2];
		vec_ABplusvec_AC[0] = vec_AB[0]+vec_AC[0];
		vec_ABplusvec_AC[1] = vec_AB[1]+vec_AC[1];
		
		D[0] = A[0] + vec_ABplusvec_AC[0];
		D[1] = A[1] + vec_ABplusvec_AC[1];
		cout << "D: " << D[0] << " " << D[1] << endl;
		
	} else if (abs(sqrCA - (sqrAB + sqrBC)) < e) {
		cout << "right triangle" << endl;
		double vec_BC[2];
		vec_BC[0] = C[0] - B[0];
		vec_BC[1] = C[1] - B[1];
		
		double vec_BA[2];
		vec_BA[0] = A[0] - B[0];
		vec_BA[1] = A[1] - B[1];
		
		double vec_BCplusvec_BA[2];
		vec_BCplusvec_BA[0] = vec_BC[0]+vec_BA[0];
		vec_BCplusvec_BA[1] = vec_BC[1]+vec_BA[1];
		
		D[0] = B[0] + vec_BCplusvec_BA[0];
		D[1] = B[1] + vec_BCplusvec_BA[1];
		cout << "D: " << D[0] << " " << D[1] << endl;

	} else {
		cout << "not right triangle" << endl;
	}
	return 0;
}

