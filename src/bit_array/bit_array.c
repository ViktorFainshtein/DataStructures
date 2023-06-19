#include "bit_array.h"
#include <assert.h>	/* assert */
#include <stdint.h>	/* __uint64_t */

bit_array_t BitArraySetAll(bit_array_t ba)
{
	ba = ~(ba & 0);

	return ba;
}

bit_array_t BitArrayResetAll(bit_array_t ba)
{
	ba = 0;

	return ba;
}

bit_array_t BitArraySetOn(bit_array_t ba, uint64_t index)
{
	bit_array_t bit = 1;
	bit <<= index;

	return (ba | bit);
}

bit_array_t BitArraySetOff(bit_array_t ba, uint64_t index)
{
	bit_array_t bit = 1;
	bit <<= index;
	bit = ~bit;
	
	return (ba & bit);
}

bit_array_t BitArraySetBit(bit_array_t ba, char set, uint64_t index)
{	
	ba = BitArraySetOff(ba, index);
	ba = ba | (set << index);

	return ba;
}
/*
bit_array_t BitArrayMirror(bit_array_t ba)					MIRROR A NUMBER VIA ROTATION
{
	bit_array_t mirror = 0;
	uint64_t len = 0;

	while(ba)
	{
		mirror <<= 1;
		mirror |= (ba&1);
		ba >>= 1;
		++len;
	}

	mirror = BitArrayRotateRight(mirror, len);

	return mirror;
}
*/
/*
bit_array_t BitArrayMirror(bit_array_t ba)					MIRROR A NUMBER VIA SWAPS
{
	ba = ((ba & 0x55555555) << 1 | (ba & 0xAAAAAAAA) >> 1);		
	ba = ((ba & 0x33333333) << 2 | (ba & 0xCCCCCCCC) >> 2);		
	ba = ((ba & 0x0F0F0F0F) << 4 | (ba & 0xF0F0F0F0) >> 4);
	ba = ((ba & 0xFF00FF00) << 8 | (ba & 0x00FF00FF) >> 8);
	ba = ((ba & 0xFFFF0000) << 16 | (ba & 0x0000FFFF) >> 16);
	ba = ((ba & 0xFFFFFFFF) << 32 | (ba & 0xFFFFFFFF) >> 32);
		
	return ba;
}
*/

bit_array_t BitArrayMirror(bit_array_t ba)					/* MIRROR A NUMNER VIA LUT */
{
	unsigned char LUT[257]={0};
	bit_array_t temp = ba;
	unsigned char swap = 0;
	
	while(temp)								/*init the LUT - will run 64/8 times*/
	{
		swap = temp & 0xff;
		swap = ((swap & 0x55) << 1 | (swap & 0xAA) >> 1);		/*swap between every bit for each pair of bits*/
		swap = ((swap & 0x33) << 2 | (swap & 0xCC) >> 2);		/*swap between every pair of bits for every 4 adjecent bits*/
		swap = ((swap & 0x0f) << 4 | (swap & 0xf0) >> 4);		/*swap between every 4 bits for every 8 adjecent bit*/
		LUT[temp & 0xff] = swap;					/*save swaped value in nible index*/
		temp >>= 8;
	}
	
	temp |= LUT[ba & 0xff];
	temp <<= 8;
	temp |= LUT[(ba>>=8) & 0xff];
	temp <<= 8;
	temp |= LUT[(ba>>=16) & 0xff];
	temp <<= 8;
	temp |= LUT[(ba>>=24) & 0xff];
	temp <<= 8;
	temp |= LUT[(ba>>=32) & 0xff];
	temp <<= 8;
	temp |= LUT[(ba>>=40) & 0xff];
	temp <<= 8;
	temp |= LUT[(ba>>=48) & 0xff];
	temp <<= 8;
	temp |= LUT[(ba>>=56) & 0xff];
	
	return temp;
}

bit_array_t BitArrayRotateRight(bit_array_t ba, uint64_t num)
{
	bit_array_t shift = 0;
	num %= (sizeof(bit_array_t)*8);
	shift = ba << ((sizeof(bit_array_t)*8) - num);
	ba >>= num;

	return (ba | shift);
}

bit_array_t BitArrayRotateLeft(bit_array_t ba, uint64_t num)
{
	bit_array_t shift = 0;
	num %= (sizeof(bit_array_t)*8);
	shift = ba >> ((sizeof(bit_array_t)*8) - num);
	ba <<= num;

	return (ba | shift);
}

bit_array_t BitArrayFlip(bit_array_t ba)
{
	return ~ba;
}

bit_array_t BitArrayFlipBit(bit_array_t ba, uint64_t index)
{
	bit_array_t flip = 1;
	flip <<= index;

	return (ba ^ flip);
}
/*
uint64_t BitArrayCountOn(bit_array_t ba)									count via loop that run as the number of 1 bits in the number
{
	uint64_t count = 0;
	while(ba)
	{
		ba &= (ba -1);
		++count;
	}
	return count;
}
*/

uint64_t BitArrayCountOn(bit_array_t ba)
{
	unsigned char LUT[257]={0};
	bit_array_t temp = ba;
	unsigned char count = 0;
	
	while(temp)											/*init the LUT - will run 64/8 times*/
	{
		count = ((temp & 1)) + ((temp>>1) & 1) + ((temp>>2) & 1) + ((temp>>3) & 1) + 		/*add the bits that are 1 in a nible*/
			((temp>>4) & 1) + ((temp>>5) & 1) + ((temp>>6) & 1) + ((temp>>7) & 1);
		LUT[temp & 0xff] = count;								/*save counted on bits in nible index*/
		temp >>= 8;
	}
	
	temp += LUT[ba & 0xff];
	temp += LUT[(ba>>8) & 0xff];
	temp += LUT[(ba>>16) & 0xff];
	temp += LUT[(ba>>24) & 0xff];
	temp += LUT[(ba>>32) & 0xff];
	temp += LUT[(ba>>40) & 0xff];
	temp += LUT[(ba>>48) & 0xff];
	temp += LUT[(ba>>56) & 0xff];
	
	return temp;

}

uint64_t BitArrayCountOff(bit_array_t ba)
{
	return BitArrayCountOn(~ba);
}

uint64_t BitArrayGetVal(bit_array_t ba, uint64_t index)
{
	return ((ba >> index) & 1);
}
/*
char *BitArrayToString(bit_array_t ba, char *str)
{
	uint64_t end = 0, start = 0;
	char swap = 0;
	
	assert(str);
	
	while(ba)
	{
		*(str + end) = (ba & 1) +'0';
		ba >>= 1;
		++end;
	}

	while(end>start)
	{
		swap = *(str + start);
		*(str + start) = *(str + end - 1);
		*(str + end - 1) = swap;
		--end;
		++start;
	}
	
	return str;
}
*/
char *BitArrayToString(bit_array_t ba, char *str)
{
	uint64_t end = sizeof(ba)*8;

	assert(str);
	
	*(str + end) = '\0';
	--end;
	
	while(end)
	{
		*(str + end) = (ba & 1) +'0';
		ba >>= 1;
		--end;
	}
	
	*(str + end) = (ba & 1) +'0';
	
	return str;
}










