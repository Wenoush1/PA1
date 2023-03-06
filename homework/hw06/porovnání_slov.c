#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */

// Cleans all of the non-alphabetic chars from string taken in from input string
void string_clean(char ** input_str)
{
   
  //count is the number of characters in the input string
  int count = strlen( (*input_str));
  for (int i = 0; i < count; i++)
  {
    if (isalpha( (*input_str)[i]) == 0)
    {
      (*input_str)[i] = ' ';
    }
  }

}

//breaks up the long input string into a list of words
void breakup_into_list(char * input_a, char *** strings,int * amount_of_words)
{
  
  //token is the pointer for a character in a word
  char * token;
  (*strings) = NULL;
  (*amount_of_words) = 0;
  int array_length = 0;
  int word_length;
  token = strtok(input_a," ");
  while (token != NULL)
  {
    //this part checks if the amount of words in the list is less than the array length so it doesn't overflow
    //if the the amount is the same as the length it increases the size of the array 
    if ((*amount_of_words)>= array_length)
    {
      array_length = array_length * 2 + 4;
      (*strings) = (char **) realloc( (*strings), array_length*sizeof(char*));
    }
    // finds the amount bytes needed for the word
    word_length=(strlen(token)+1)*sizeof(token);
    (*strings)[(*amount_of_words)]=(char *) malloc(word_length);
    strcpy( (*strings)[(*amount_of_words)], token);
    (*amount_of_words)++;
    token = strtok(NULL," ");
  }
  
}

//creates a list of words, where each word is only once, from the input "strings"
void add_uniques(char *** strings, char *** unique_words,int amount_of_words,int * length_of_uniques)
{
  
  //is_in is used to find out if the word is in or not, if the word isn't in the list it gets added to the list 
  int is_in;
  (*length_of_uniques) = 0;
  int max_length = 0;
  (*unique_words) = NULL;
  int word_length;
  for (int i = 0; i < amount_of_words; i++)
  {
    is_in=0;
    for (int j = 0; j < (*length_of_uniques); j++)
    {
      if (strcasecmp( (*strings)[i], (*unique_words)[j])==0)
      {
        is_in = 1;
        break;
      }
      
    }
    if ( is_in == 0)
    {
      if ( (*length_of_uniques) >= max_length)
      {
        max_length = max_length*2 +4;
        (*unique_words) = (char **) realloc( (*unique_words), max_length * sizeof(char*));
      }
      //gets the amount of bytes needed for a word and dynamically allocates it to the index in the list 
      word_length =( strlen((*strings)[i])+1) * sizeof((*strings)[i]);
      (*unique_words)[(*length_of_uniques)] = (char *) malloc(word_length);
      //copies the word into the list
      strcpy( (*unique_words)[(*length_of_uniques)], (*strings)[i]);
      (*length_of_uniques)++;
    }        
  }

}

//compares the list of strings from the second input with the list of unique words from the first input
//returns 1 if contain the same words and 0 if they don't
int compare_words(char ** strings,char ** unique_words,int amount_of_words, int length_of_uniques)
{

  int is_in;
  
  for (int i = 0; i < amount_of_words; i++)
  {
    is_in=0;
    for (int j = 0; j < length_of_uniques; j++)
    {
      if ( strcasecmp( strings[i] ,unique_words[j]) == 0 )
      {
        is_in = 1 ;
      }
      
    }
    if ( is_in == 0 )
    {
      return 0;
    }
    
  }
  return 1;

}

// frees the memory allocated to array and all of it's contents 
void free_array(char *** strings, int length){
  for (int i = 0; i < length; i++)
  {
    free( (*strings)[i] );
  }
  free( (*strings) );
}

int sameWords ( const char * a, const char * b )
{
  
  char *input_a = (char *) malloc( (strlen(a)+1) * sizeof(char*) );
  char *input_b = (char *) malloc( (strlen(b)+1) * sizeof(char*) );
  char ** strings;
  char ** unique_words; 
  int amount_of_words,
  exit_code,
  length_of_uniques;
  strcpy( input_a, a );
  strcpy( input_b, b);
  string_clean( &input_a );
  string_clean( &input_b );
  breakup_into_list( input_a, &strings , &amount_of_words );
  add_uniques( &strings, &unique_words, amount_of_words, &length_of_uniques );
  free_array( &strings, amount_of_words);
  breakup_into_list( input_b, &strings, &amount_of_words );
  exit_code=compare_words( strings, unique_words, amount_of_words, length_of_uniques );
  free_array( &strings, amount_of_words );
  free_array( &unique_words, length_of_uniques );
  free( input_a );
  free( input_b );
  return exit_code;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  assert ( sameWords ( "Hello students.", "HELLO studEnts!" ) == 1 );
  assert ( sameWords ( " He said 'hello!'", "'Hello.' he   said." ) == 1 );
  assert ( sameWords ( "He said he would do it.", "IT said: 'He would do it.'" ) == 1 );
  assert ( sameWords ( " ", " " ) == 0 );
  assert ( sameWords ( " ", "a" ) == 0 );
  assert ( sameWords ( "a", " " ) == 0 );
  return 0;
}
#endif /* __PROGTEST__ */
