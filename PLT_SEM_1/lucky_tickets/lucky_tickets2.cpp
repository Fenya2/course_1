#include <iostream>
#include <string>
using namespace std;

//Next lucky ticket когда слева больше, справа меньше

string next(int n1, int n2, int n3, int n4, int n5, int n6, int r)
{
    int a1, a2, a3, a4, a5, a6;
    a1 = n1;
    a2 = n2;
    a3 = n3;
    a4 = n4;
    a5 = n5;
    a6 = n6;

    if ((9 - n6) >= r) {
        a6 = n6 + r;
        r = 0;
    }
    else{
        a6 = 9;
        r -= (9 - n6);
    }

    if ((r != 0) && (9 - n5) >= r) {
        a5 = n5 + r;
        r = 0;
    }
    else if ((9 - n5) < r) {
        a5 = 9;
        r -= (9 - n5);
    }

    if ((r != 0) && (9 - n4) >= r) {
        a4 = n4 + r;
        r = 0;
    }
    else if ((9 - n4) < r) {
        a4 = 9;
        r -= (9 - n4);
    }
    return to_string(a1*100000 + a2*10000+a3*1000+a4*100+a5*10+a6);
}

//previous когда слева меньше, справа больше

string previous(int n1, int n2, int n3, int n4, int n5, int n6, int r)
{
    int a1, a2, a3, a4, a5, a6;
    a1 = n1;
    a2 = n2;
    a3 = n3;
    a4 = n4;
    a5 = n5;
    a6 = n6;

    if (n6 >= r) {
        a6 = n6 - r;
        r = 0;
    }
    else if (n6 < r) {
        a6 = 0;
        r -= n6;
    }

    if ((r != 0) && (n5 >= r)) {
        a5 = n5 - r;
        r = 0;
    }
    else if (n5 < r) {
        a5 = 0;
        r -= n5;
    }

    if ((r != 0) && (n4 >= r)) {
        a4 = n4 - r;
        r = 0;
    }
    else if (n4 < r) {
        a4 = 0;
        r -= n4;
    }
    return to_string(a1*100000 + a2*10000+a3*1000+a4*100+a5*10+a6);
    ;
}

//next когда справа больше, слева меньше и нужно менять левую часть, например 123999

string supernext(int n1, int n2, int n3, int n4, int n5, int n6)
{
    int a1, a2, a3, a4, a5, a6;
    a1 = n1;
    a2 = n2;
    a3 = n3;
    a4 = n4;
    a5 = n5;
    a6 = n6;

    if (a3 < 9) {
        a3 += 1;
    }
    else {
        if (a2 < 9) {
            a2 += 1;
            a3 = 0;
        }
        else {
            if (a1 < 9) {
                a3 = 0;
                a2 = 0;
                a1 += 1;
            }
        }
    }
    a4 = 0;
    a5 = 0;
    a6 = 0;

    return next(a1, a2, a3, a4, a5, a6, a1 + a2 + a3);
}

//previous когда справа меньше, слева больше и нужно менять левую часть, например 123000

string superprevious(int n1, int n2, int n3, int n4, int n5, int n6)
{
    int a1, a2, a3, a4, a5, a6;
    a1 = n1;
    a2 = n2;
    a3 = n3;
    a4 = n4;
    a5 = n5;
    a6 = n6;

    if (a3 > 0) {
        a3 -= 1;
    }
    else {
        if (a2 > 0) {
            a2 -= 1;
            a3 = 9;
        }
        else {
            if (a1 > 0) {
                a3 = 9;
                a2 = 9;
                a1 -= 1;
            }
        }
    }
    a4 = 9;
    a5 = 9;
    a6 = 9;

    return previous(a1, a2, a3, a4, a5, a6, 9 * 3 - a1 - a2 - a3);
}

//main

int main() {
    int ticket;
    cout << "Ticket: "; cin >> ticket;

    int n1, n2, n3, n4, n5, n6;
    n1 = ticket / 100000;
    n2 = (ticket % 100000) / 10000;
    n3 = (ticket % 10000) / 1000;
    n4 = (ticket % 1000) / 100;
    n5 = (ticket % 100) / 10;
    n6 = ticket % 10;

    int s1 = n1 + n2 + n3;
    int s2 = n4 + n5 + n6;
    int r = abs(s1 - s2);
    int raz = r;

    int b1, b2, b3, b4, b5, b6;
    b1 = n1;
    b2 = n2;
    b3 = n3;
    b4 = n4;
    b5 = n5;
    b6 = n6;

    if (s1 == s2) {
        cout << "Your ticket is lucky!!!" << endl;
        return 0;
    }
    if (s1 > s2) {
        cout << "Next lucky ticket: " << next(n1, n2, n3, n4, n5, n6, raz) << endl;
        r -= (9 - b6);
        b6 = 9;
        if (b5 > 0) {
            r += 1;
            b5 -= 1;
            if (r > 0) {
                r -= (9 - b5);
                b5 = 9;
                if (b4 > 0) {
                    r += 1;
                    b4 -= 1;
                    if (r < 0) {
                        cout << "Previous lucky ticket: " << previous(b1, b2, b3, b4, b5, b6, abs(r)) << endl;
                    }
                    else if (r > 0) {
                        cout << "Previous lucky ticket: " << superprevious(b1, b2, b3, b4, b5, b6) << endl;
                    }
                    else {
                        cout << "Previous lucky ticket: " << b1 * 100000 + b2 * 10000 + b3 * 1000 + b4 * 100 + b5 * 10 + b6 << endl;
                    }
                }
                else {
                    cout << "Previous lucky ticket: " << superprevious(b1, b2, b3, b4, b5, b6) << endl;
                }
            }
            else if (r == 0) {
                cout << "Previous lucky ticket: " << b1 * 100000 + b2 * 10000 + b3 * 1000 + b4 * 100 + b5 * 10 + b6 << endl;
            }
            else {
                cout << "Previous lucky ticket: " << previous(b1, b2, b3, b4, b5, b6, abs(r)) << endl;
            }
        }
        else {
            r -= (9 - b5);
            b5 = 9;
            if (b4 > 0) {
                r += 1;
                b4 -= 1;
                if (r < 0) {
                    cout << "Previous lucky ticket: " << previous(b1, b2, b3, b4, b5, b6, abs(r)) << endl;
                }
                else if (r > 0) {
                    cout << "Previous lucky ticket: " << superprevious(b1, b2, b3, b4, b5, b6) << endl;
                }
                else if (r == 0) {
                    cout << "Previous lucky ticket: " << b1 * 100000 + b2 * 10000 + b3 * 1000 + b4 * 100 + b5 * 10 + b6 << endl;
                }
            }
            else {
                cout << "Previous lucky ticket: " << superprevious(b1, b2, b3, b4, b5, b6) << endl;
            }
        }
    }
    else if (s1 < s2) {
        r -= b6;
        b6 = 0;
        if (b5 < 9) {
            r += 1;
            b5 += 1;
            if (r > 0) {
                r -= b5;
                b5 = 0;
                if (b4 < 9) {
                    r += 1;
                    b4 += 1;
                    if (r < 0) {
                        cout << "Next lucky ticket: " << next(b1, b2, b3, b4, b5, b6, abs(r)) << endl;
                    }
                    else if (r == 0) {
                        cout << "Next lucky ticket: " << b1 * 100000 + b2 * 10000 + b3 * 1000 + b4 * 100 + b5 * 10 + b6 << endl;
                    }
                    else if (r > 0) {
                        cout << "Next lucky ticket: " << supernext(b1, b2, b3, b4, b5, b6) << endl;
                    }
                }
                else {
                    cout << "Next lucky ticket: " << supernext(b1, b2, b3, b4, b5, b6) << endl;
                }
            }
            else if (r == 0) {
                cout << "Next lucky ticket: " << b1 * 100000 + b2 * 10000 + b3 * 1000 + b4 * 100 + b5 * 10 + b6 << endl;
            }
            else if (r < 0) {
                cout << "Next lucky ticket: " << next(b1, b2, b3, b4, b5, b6, abs(r)) << endl;
            }
        }
        else {
            if (b4 < 9) {
                r -= b5;
                b5 = 0;
                r += 1;
                b4 += 1;
                if (r > 0) {
                    cout << "Next lucky ticket: " << supernext(b1, b2, b3, b4, b5, b6) << endl;
                }
                else if (r < 0) {
                    cout << "Next lucky ticket: " << next(b1, b2, b3, b4, b5, b6, abs(r)) << endl;
                }
                else if (r == 0) {
                    cout << "Next lucky ticket: " << b1 * 100000 + b2 * 10000 + b3 * 1000 + b4 * 100 + b5 * 10 + b6 << endl;
                }
            }
            else {
                cout << "Next lucky ticket: " << supernext(b1, b2, b3, b4, b5, b6) << endl;
            }
        }
        cout << "Previous lucky ticket: " << previous(n1, n2, n3, n4, n5, n6, raz) << endl;
    }
}
