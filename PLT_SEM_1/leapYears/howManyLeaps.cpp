//CHECKED

#include <iostream>
using namespace std;
int main() {
    int y1,y2,lty1,lty2;
    cin >> y1;
    cin >> y2;
    lty1 = (y1-1) / 4 + y1 / 400 - y1 / 100;
    lty2 = y2 / 4 + y2 / 400 - y2 / 100;
    cout << lty2 - lty1 << endl;
    return 0;
}
