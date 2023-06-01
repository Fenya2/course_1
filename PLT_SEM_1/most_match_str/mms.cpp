#include <iostream>
#include <fstream>
#include <string>


using namespace std;

/*
int indexOf_using_bruteforce(char* str, int str_size, char* pattern, int pattern_size)
{  
  bool match;
  for(int i = 0; i < str_size - pattern_size + 1; ++i)
  {
    match = true;
    for(int j = 0; j < pattern_size; ++j)
    {
      if(str[i+j] == pattern[j])
        continue;
      else 
      {
        match = false;
        break;
      }
    }
    if(match)
      return i;
  }
  return -1;
}

int indexOf_using_BoyerMoore(char* str, int str_size, char* pattern, int pattern_size, char* N)
{
  for(int i = 0; i < 255; ++i)
    N[i] = -1;
  for(int i = 0; i < str_size; ++i)
    N[(int)str[i]] = i;
  bool match;
  
  for(int i = 0; i < str_size - pattern_size + 1;)
  {
    match = true;
    for(int j = pattern_size - 1; j >= 0; j--)
    {
      if(pattern[j] != str[j+i])
      {
        match = false;
        if(N[str[i+j]] == -1)
        {
            i += pattern_size;
            break;
        }
        i += max(pattern_size - (N[str[i+j]] + j), 1);
        break;
      }
    }
    if(match)
      return i;
  }
  return -1;
}

*/

int indexOf_using_hashes(char* str, int str_size, char* pattern, int pattern_size, int pattern_hash)
{
  int frag_hash = 0;
  bool match;
  for(int i = 0; i < pattern_size; ++i)
    frag_hash += (int) str[i];
  
  if(pattern_hash == frag_hash)
  {
    match = true;
    for(int i = 0; i < pattern_size; ++i)
    {
      if(str[i] != pattern[i])
      {
        match = false;
        break;
      }
    }
    if(match)
      return 0;
  }
  
  for(int i = 1; i < str_size - pattern_size + 1; ++i)
  {
    frag_hash = frag_hash + (int) str[i + pattern_size - 1] - (int) str[i - 1];
    if (pattern_hash == frag_hash) 
    {
        match = true;
        for (int j = 0; j < pattern_size; ++j)
        {
            if (str[i + j] != pattern[j])
            {
                match = false;
                break;
            }
        }
        if (match)
          return i;
    }
  }
  return -1;
}

int main(int argc, char *argv[])
{
  ifstream file;
  char* str1;
  char* str2;
  int str1_size;
  int str2_size;
  char N[255];
  
  
  
  file.open(argv[1]);
  if (!file.is_open())
  {
    cout << "can't open file 1." << endl;
		return 1;
	}
  
  file.seekg (0, file.end);
  str1_size = file.tellg();
  file.seekg (0, file.beg);
  str1 = new char[str1_size];
  file.read (str1, str1_size);
  
  file.close();
  
  file.open(argv[2]);
  if (!file.is_open())
  {
    cout << "file 'can't open file 2." << endl;
    delete[] str1;
		return 1;
	}
  
  file.seekg (0, file.end);
  str2_size = file.tellg();
  file.seekg (0, file.beg);
  str2 = new char[str2_size];
  file.read (str2, str2_size);
  
  file.close();

  if(str2_size > str1_size) // боо считаем, что первый текст по размеру больше
  {
    char* tmppnt;
    int tmpint;
    tmppnt = str1;
    tmpint = str1_size;
    str1 = str2;
    str1_size = str2_size;
    str2 = tmppnt;
    str2_size = tmpint;
  }
  
  
  char* pattern;
  int pattern_hash;
  int idx;
  for(int pattern_size = str2_size; pattern_size > 0; --pattern_size)
  {
    cout << (((float)str2_size-(float)pattern_size)/(float)str2_size) * 100 << "%" << endl;
    pattern_hash = 0;
    pattern = &str2[0];
    for(int i = 0; i < pattern_size; ++i)
      pattern_hash += (int) str2[i];
    
    idx = indexOf_using_hashes(str1, str1_size, pattern, pattern_size, pattern_hash);
    if(idx != -1)
    {
      cout <<"here "<< idx << endl;
      return 0;
    }

    for(int i = 1; i < str2_size - pattern_size + 1; ++i)
    {
      pattern = &str2[i];
      pattern_hash = pattern_hash + (int) str2[i + pattern_size - 1] - (int) str2[i - 1];
      int idx = indexOf_using_hashes(str1, str1_size, pattern, pattern_size, pattern_hash); 
      if(idx != -1)
      {
        for(int j = 0; j < pattern_size; j++)
          cout << str1[idx + j];
        cout << endl; 
        cout << "match: " << idx << endl;
        cout << "max_length: " << pattern_size << endl;
        
        delete[] str1;
        delete[] str2;
        return 0;
      }
    }
  }
  
  delete[] str1;
  delete[] str2;
  
  cout << "no matches." << endl;
  return 2;
}
