#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uint8_t;
typedef unsigned char BOOL;

#define TRUE (0xff)
#define FALSE (0x00)

BOOL next_permutation(uint8_t *first, uint8_t *last);
void iter_swap(uint8_t *a, uint8_t *b);
void reverse(uint8_t *a, uint8_t *b);


int main(int argc, uint8_t *argv[])
{  
  uint8_t i = 0;
  int count = 0;
  const uint8_t MAX_N = 6;
  uint8_t test[MAX_N+2];         // appending '.' and '\0' to end of test[]
  
  // initialize test[] for fixed n (used by some of the tests below)
  uint8_t n = 3;
  for(i=0; i<=n; i++)
  {
    test[i] = i + 0x30;      // convert to ascii
  }
  test[i] = '.';
  test[i+1] = '\0';

  
  /*
  printf("Original: %s\n", test);
  iter_swap(test, test+n);
  printf("  result: %s\n", test);
  */

  /*
  printf("Original: %s\n", test);
  reverse(test, test+n);
  printf("Reversed: %s\n", test);
  */
  
  /*
  printf("                       Permutation: %s\n\n", test);
  next_permutation(test, test + n);
  printf("                       Permutation: %s\n\n", test);
  next_permutation(test, test + n);
  printf("                       Permutation: %s\n\n", test);
  next_permutation(test, test + n);
  printf("                       Permutation: %s\n\n", test);
  */

  ///*
  printf("Testing permuations...\n\n");
  do { 
    //printf("                       Permutation: ");
	printf("%s\n", test);
	//printf("\n");
  } while (next_permutation(test, test + n));   // second arg points one past last element
                                                // (not last element)
  printf("\n");
  //*/

  ///*
  // re-initialize test[] for variable n
  for(i=0; i<=MAX_N; i++)
  {
    test[i] = i + 0x30;      // convert to ascii
  }
  test[i] = '.';
  test[i+1] = '\0';

  // count number of permutations for n=1..MAX_N
  printf("Counting permuations...\n\n");
  for(n = 1; n <= MAX_N; n++)
  {
    count = 0;
	do
	{
	  count++;
	}while( next_permutation(test, test + n) );
	printf("n=%d: %d\n", n, count);
  }
  printf("\n");
  //*/

  exit(EXIT_SUCCESS);
}


// last points one past the last element in test
BOOL next_permutation(uint8_t *first, uint8_t *last)
{
  //printf("In next_perm(%c,%c)\n",*first,*last);

  uint8_t *i = last - 1;;
  if( first == last )    // check for n=0
    return FALSE;
  if( first == i )       // check for n=1
    return FALSE;

  for(;;)
  {
    uint8_t *ii = i--;
    if (*i < *ii)
	{
      uint8_t *j = last;
      while( !(*i < *--j) ) ;
	  
	  //printf("  Swapping %c,%c:\n", *i, *j);
	  iter_swap(i, j);
	  //printf("    result: %s\n", first);
	  
      //printf("  Reversing %c,%c:\n", *ii, *last);
	  reverse(ii, last);
	  //printf("    result: %s\n", first);
	  
      return TRUE;
    }
    if (i == first)
	{
	  //printf("  Final reverse %c,%c:\n", *ii, *last);
      reverse(first, last);
	  //printf("  result: %s\n", first);

      return FALSE;
    }
  }
}

// b points to element to swap with a.
void iter_swap(uint8_t *a, uint8_t *b)
{
  //printf("    In swp(%c,%c)\n",*a,*b);

  uint8_t tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

// b points one element beyond the last element be reversing
void reverse(uint8_t *a, uint8_t *b)
{
  //printf("    In rev(%c,%c)\n",*a,*b);

  b--;                // point b to element to begin reversing

  if (a < b)
  {
    while(a < b)
      iter_swap(a++, b--);
  }
  else
  {
    while(b < a)
      iter_swap(b++, a--);
  }
}
