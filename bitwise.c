#include <stdio.h>
#include <string.h>


/* Fun with magic coincidences.
 *
 * Based on the way fprintf handles strings, we can use a single string for
 * every kind of thing we want to print, in power of two lengths.
 *
 * For a single integer, "%u" length == 2
 * For fizz or buzz, "fizz" or "buzz" length == 4
 * For fizzbuzz, length == 8
 *
 * Even better, we can set up a string so the starts of our format are at
 * powers of 2
 *
 * "fizzbuzz%u"
 *  0   4   8
 *
 * The clever thing to do when we see powers of 2 is to try to shoehorn bitwise
 * operators into our trials.
 */

#define DIV5(x) ((x & 2) >> 1)
#define DIV3(x) (x & 1)
int main(int argc, char **argv) {

  char fmts[] = "FizzBuzz%u";
  char fmt[9]; /* 9 for max length + NUL */

  unsigned int i;
  for( i = 1; i <= 100; i++ ) {

    /* Define mask/flags for storing divisibility */
    unsigned int mask = 0;

    /* Create bitmask of the form 000000ab
       a - divisible by 5
       b - divisible by 3 */
    mask |= !(i%5) << 1;
    mask |= !(i%3);


    // Default start is 8
    unsigned int start =
      // Shift down 1 if div5
      (8 >> DIV5(mask))
      // Shift down another 4 if div3 */
      >> ( DIV3(mask) << 2);

    // Default length is 2
    // Shift up by one for each bit set
    unsigned int length = (2 << (DIV3(mask))) << DIV5(mask);
      // Shift up by 1 for each bit set


    strncpy(fmt,&fmts[start],length);
    fmt[length] = '\0';

    printf(fmt,i);

    printf("\n");
  }
  return 0;
}
