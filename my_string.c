/**
 * @file my_string.c
 * @author YOUR NAME HERE
 * @brief Your implementation of these famous 3 string.h library functions!
 *
 * NOTE: NO ARRAY NOTATION IS ALLOWED IN THIS FILE
 *
 * @date 2021-06-xx
 */

// DO NOT MODIFY THE INCLUDE(s) LIST
#include <stddef.h>
#include "hw7.h"

/**
 * @brief Calculate the length of a string
 *
 * @param s a constant C string
 * @return size_t the number of characters in the passed in string
 */
size_t my_strlen(const char *s)
{
  /* Note about UNUSED_PARAM
   *
   * UNUSED_PARAM is used to avoid compiler warnings and errors regarding unused function
   * parameters prior to implementing the function. Once you begin implementing this
   * function, you can delete the UNUSED_PARAM lines.
   */
 const char *e=s;
 while(*e!='\0')e++;
 return e-s;

}

/**
 * @brief Compare two strings
 *
 * @param s1 First string to be compared
 * @param s2 Second string to be compared
 * @param n First (at most) n bytes to be compared
 * @return int "less than, equal to, or greater than zero if s1 (or the first n
 * bytes thereof) is found, respectively, to be less than, to match, or be
 * greater than s2"
 */
int my_strncmp(const char *s1, const char *s2, size_t n)
{
  /* Note about UNUSED_PARAM
   *
   * UNUSED_PARAM is used to avoid compiler warnings and errors regarding unused function
   * parameters prior to implementing the function. Once you begin implementing this
   * function, you can delete the UNUSED_PARAM lines.
   */
   size_t cntr = 1;

    /* go on until at least one is finished or we reached n-1 (-1 because we
       do the last comparison in the following if */
    while ((*s1 != '\0') && (*s2 != '\0') && (cntr < n)) {
	    if (*s1 > *s2)
	      return 1;
	    else if (*s1 < *s2)
	      return -1;
	    else {			/*go to the next if equal */
	      s1++;
	      s2++;
	      cntr++;
	}
    }

    /* the handling is the same */
    if (*s1 == *s2)
	    return 0;
    else if (*s1 > *s2)
	    return 1;
    else if (*s1 < *s2)
	    return -1;
  else return -1;
}

/**
 * @brief Copy a string
 *
 * @param dest The destination buffer
 * @param src The source to copy from
 * @param n maximum number of bytes to copy
 * @return char* a pointer same as dest
 */
char *my_strncpy(char *dest, const char *src, size_t n)
{
  /* Note about UNUSED_PARAM
   *
   * UNUSED_PARAM is used to avoid compiler warnings and errors regarding unused function
   * parameters prior to implementing the function. Once you begin implementing this
   * function, you can delete the UNUSED_PARAM lines.
   */
   char *temp = dest;
   while ((*dest++ = *src++) && (--n));
   for (; n-- ; *dest++ = '\0')
  ;
  
   return temp;

}
