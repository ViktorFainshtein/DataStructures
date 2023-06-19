#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__
#include <stddef.h>  /* __uint64_t */
#include <stdint.h>  /* __uint64_t */

typedef __uint64_t bit_array_t;

/* description: set all bits to 1 
   params: bit_array_t 
   return value: bit_array_t ba
   undefined behavior: in case of invalid element type */ 	
bit_array_t BitArraySetAll(bit_array_t ba);

/* description: set all bits to 0 
   params: bit_array_t 
   return value: bit_array_t
   undefined behavior: in case of invalid element type */ 
bit_array_t BitArrayResetAll(bit_array_t ba);

/* description: set a bit to 1 in recived index
   params: bit_array_t and an index
   return value: bit_array_t
   undefined behavior: in case of invalid element type or index out of bounds */ 
bit_array_t BitArraySetOn(bit_array_t ba, __uint64_t index);

/* description: set a bit to 0 in recived index
   params: bit_array_t and an index
   return value: bit_array_t
   undefined behavior: in case of invalid element type or index out of bounds */ 
bit_array_t BitArraySetOff(bit_array_t ba, __uint64_t index);

/* description: set a bit to 1 or 0 via recived set in place of index
   params: bit_array_t , set, and an index
   return value: bit_array_t
   undefined behavior: in case of invalid element type, index out of bounds or invalid char */ 
bit_array_t BitArraySetBit(bit_array_t ba, char set, __uint64_t index);

/* description: mirror the bits of the recived bit_array_t
   params: bit_array_t 
   return value: bit_array_t
   undefined behavior: in case of invalid element type */ 
bit_array_t BitArrayMirror(bit_array_t ba);

/* description: rotate the bit_array_t right num times
   params: bit_array_t and num
   return value: bit_array_t
   undefined behavior: in case of invalid element type */ 
bit_array_t BitArrayRotateRight(bit_array_t ba, __uint64_t num);

/* description: rotate the bit_array_t left num times
   params: bit_array_t and num
   return value: bit_array_t
   undefined behavior: in case of invalid element type */ 
bit_array_t BitArrayRotateLeft(bit_array_t ba, __uint64_t num);

/* description: flip the bits in a bit array
   params: bit_array_t
   return value: bit_array_t
   undefined behavior: in case of invalid element type */ 
bit_array_t BitArrayFlip(bit_array_t ba);

/* description: count the number of on bits
   params: bit_array_t
   return value: bit_array_t
   undefined behavior: in case of invalid element type */ 
__uint64_t BitArrayCountOn(bit_array_t ba);

/* description: count the number of off bits
   params: bit_array_t
   return value: bit_array_t
   undefined behavior: in case of invalid element type */ 
__uint64_t BitArrayCountOff(bit_array_t ba);

/* description: return the value of an index bit
   params: bit_array_t and index
   return value: __uint64_t
   undefined behavior: in case of invalid element type or index out of bounds */ 
__uint64_t BitArrayGetVal(bit_array_t ba, __uint64_t index);

/* description: convert a bit array to string
   params: bit_array_t, pointer to string
   return value: pointer to string
   undefined behavior: in case of invalid element type, buffer not big enough */
char *BitArrayToString(bit_array_t ba, char *str);

/* description: flips the bit in a bit array specified by the index
   params: bit_array_t, index
   return value: bit_array_t
   undefined behavior: in case of invalid element type */ 
bit_array_t BitArrayFlipBit(bit_array_t ba, __uint64_t index);



#endif
