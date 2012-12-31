/* perms.h
 *
 *
 */

#include "perms.h"



BOOL next_permutation(uint8_t *first, uint8_t *last)
{
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
         
         iter_swap(i, j);
         reverse(ii, last);
         
         return TRUE;
      }
      if (i == first)
      {
         reverse(first, last);
         return FALSE;
       }
   }
}

// b points to element to swap with a.
void iter_swap(uint8_t *a, uint8_t *b)
{
  uint8_t tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

// b points one element beyond the last element be reversing
void reverse(uint8_t *a, uint8_t *b)
{
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
