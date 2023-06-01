#include <iostream>
#include <cmath>

using namespace std;

int (*extentTwo(int n, int (*arr)[2]))[2] {
    while (n != 0) {
        int a00 = arr[0][0], a01 = arr[0][1], a10 = arr[1][0], a11 = arr[1][1];
        arr[0][0] = a00 * a00 + a01 * a10;
        arr[0][1] = a00 * a01 + a01 * a11;
        arr[1][0] = a10 * a00 + a11 * a10;
        arr[1][1] = a10 * a01 + a11 * a11;
        n--;
    }
    return arr;
}

int (*mult(int (*m1)[2], int (*m2)[2]))[2] {
    int a00 = m2[0][0], a01 = m2[0][1], a10 = m2[1][0], a11 = m2[1][1];
    m2[0][0] = m1[0][0] * a00 + m1[1][0] * a01;
    m2[0][1] = m1[0][1] * a00 + m1[1][1] * a01;
    m2[1][0] = m1[0][0] * a10 + m1[1][0] * a11;
    m2[1][1] = m1[0][1] * a10 + m1[1][1] * a11;
    return m2;
}

int (*fib(int n))[2] {
    int ext2 = (int) log2(n);
    int arr[2][2] = {{1, 1},
                     {1, 0}};
    if (ext2 == log2(n))
        return extentTwo(ext2, arr);
    int (*MatrixExt1)[2] = extentTwo(ext2, arr);
    return mult(fib(n-pow(2,ext2)), MatrixExt1);
}

int main() {
    int n; cin >> n;
    cout << fib(n)[1][1];
}
