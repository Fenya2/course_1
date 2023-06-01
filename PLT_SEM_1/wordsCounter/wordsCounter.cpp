// подсчет количества слов
//#define comma_ascii_code 44
//#define dot_ascii_code 46
#define ascii_code_0 48
#define ascii_code_9 57
#define max_text_length 10000


#include <iostream>
#include <fstream>
#include <string>
 
using namespace std;

int is_good_word(char *word, int size)
{  
  int digit_cnt = 0;
  int dot_cnt = 0;
  int comma_cnt = 0;
  
  for(int i = 0; i < size; i++)
  {
    if( (int)word[i] >= ascii_code_0 && (int)word[i] <= ascii_code_9 )
      digit_cnt++;
    
    if(word[i] == '.' && word[i-1] == '.')
      return 1;
    if(word[i] == ',' && word[i-1] == ',')
      return 1;
    
    if(word[i] == '.')
      dot_cnt++;
    if(word[i] == ',')
      comma_cnt++;
  }
  
  if(digit_cnt == size && size != 0)
    return 0;
  if(digit_cnt == size-1 && dot_cnt == 1)
    return 0;
  if(digit_cnt == size-1 && comma_cnt == 1)
    return 0;
  return 1;
}

int main()
{
  ifstream input_file;
  char text[max_text_length];
  
  input_file.open("input.txt");
  if(!input_file.is_open())
  {
    cout << "error. Can't open file 'input.txt'" << endl;
    return 0;
  }
  int text_size = 0;
  for(int i = 0; i < max_text_length; i++)
  {
    text[i] = input_file.get();
    text_size++;
  }
  input_file.close();
    
  int good_word_counter = 0;
  int word_start_idx = 0;
  int word_end_idx = 0;
  for(int i = 0; i < text_size; i++)
  {
    if(text[i] == ' ' || text[i] == '\n') // добавить перенос строки?
    {
      word_end_idx = i-1;
      good_word_counter += is_good_word(text+word_start_idx, word_end_idx-word_start_idx+1);
      word_start_idx = i+1;
    }
  }
  cout << good_word_counter << endl;
  return 0;
}
