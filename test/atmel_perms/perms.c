/* perms.h
 *
 *
 */

#include "perms.h"



BOOL next_permutation(u08 *first, u08 *last)
{
   u08 *i = last - 1;;
   if( first == last )    // check for n=0
      return FALSE;
   if( first == i )       // check for n=1
      return FALSE;
      
   for(;;)
   {
      u08 *ii = i--;
      if (*i < *ii)
      {
         u08 *j = last;
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
void iter_swap(u08 *a, u08 *b)
{
  u08 tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

// b points one element beyond the last element be reversing
void reverse(u08 *a, u08 *b)
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
