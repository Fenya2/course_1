#include <iostream>

using namespace std;

void showTest(char *test)
{
  cout << test[0] << endl;
}

int main()
{
  for(int i = 48; i <= 57; i++)
  {
    cout << (char) i << endl;
  }
}
