#include <stdio.h>	/* printf scanf */
#include "bit_array.h"

/* void TestSetAll();

void TestResetAll();

void TestSetBitOn();

void TestSetBitOff();

void TestMirror();

void TestRotateRight();

void TestRotateLeft();

void TestFlip();

void TestFlipBit();

void TestCountOn();

void TestCountOff();

void TestGetVal();

 */

int main()
{
/* 	__uint64_t select = 1;
	printf("MENU:\n");
	printf("1.TestSetAll\n");
	printf("2.TestResetAll\n");
	printf("3.TestSetBitOn\n");
	printf("4.TestSetBitOff\n");
	printf("5.TestMirror\n");
	printf("6.TestRotateRight\n");
	printf("7.TestRotateLeft\n");
	printf("8.TestFlip\n");
	printf("9.TestFlipBit\n");
	printf("10.TestCountOn\n");
	printf("11.TestCountOff\n");
	printf("12.TestGetVal\n");
	while(0!=select)
	{
		printf("Choose A Test Case(to exit enter 0): ");
		scanf("%lu", &select);
		
		switch (select)
		{
			case 1:
				TestSetAll();
				break;
			case 2:
				TestResetAll();
				break;
			case 3:
				TestSetBitOn();
				break;
			case 4:
				TestSetBitOff();
				break;
			case 5:
				TestMirror();
				break;
			case 6:
				TestRotateRight();
				break;
			case 7:
				TestRotateLeft();
				break;
			case 8:
				TestFlip();
				break;
			case 9:
				TestFlipBit();
				break;
			case 10:
				TestCountOn();
				break;
			case 11:
				TestCountOff();
				break;
			case 12:
				TestGetVal();
				break;
			default:
				select = 0;
				break;
		}
		
	} */
	
	return 0;
}
/* 
void TestSetAll()
{
	bit_array_t bit = 156;
	char str1[65] = {'0'};
	char str2[65] = {'0'};
	printf("Before SetAll: %s\n",BitArrayToString(bit,str1));
	bit = BitArraySetAll(bit);
	printf("After SetAll: %s\n",BitArrayToString(bit,str2));
}

void TestResetAll()
{
	bit_array_t bit = 156;
	char str1[65] = {'0'};
	char str2[65] = {'0'};
	printf("Before ResetAll: %s\n",BitArrayToString(bit,str1));
	bit = BitArrayResetAll(bit);
	printf("After ResetAll: %s\n",BitArrayToString(bit,str2));
}

void TestSetBitOn()
{
	bit_array_t bit = 156;
	char str1[65] = {'0'};
	char str2[65] = {'0'};
	printf("Before setting 1st bit on: %s\n",BitArrayToString(bit,str1));
	bit = BitArraySetOn(bit, 0);
	printf("After setting 1st bit on: %s\n",BitArrayToString(bit,str2));
}

void TestSetBitOff()
{
	bit_array_t bit = 156;
	char str1[65] = {'0'};
	char str2[65] = {'0'};
	printf("Before setting 7th bit off: %s\n",BitArrayToString(bit,str1));
	bit = BitArraySetOff(bit, 7);
	printf("After setting 7th bit off: %s\n",BitArrayToString(bit,str2));
}

void TestMirror()
{
	bit_array_t bit = 156;
	char str1[65] = {'0'};
	char str2[65] = {'0'};
	printf("Before mirroring the bits: %s\n",BitArrayToString(bit,str1));
	bit = BitArrayMirror(bit);
	printf("After mirroring the bits: %s\n",BitArrayToString(bit,str2));
}

void TestRotateRight()
{
	bit_array_t bit = 156;
	char str1[65] = {'0'};
	char str2[65] = {'0'};
	printf("Before rotating right: %s\n",BitArrayToString(bit,str1));
	bit = BitArrayRotateRight(bit, 2);
	printf("After rotating 2 bit right: %s\n",BitArrayToString(bit,str2));
}

void TestRotateLeft()
{
	bit_array_t bit = 156;
	char str1[65] = {'0'};
	char str2[65] = {'0'};
	printf("Before rotating left: %s\n",BitArrayToString(bit,str1));
	bit = BitArrayRotateLeft(bit, 2);
	printf("After rotating 2 bits left: %s\n",BitArrayToString(bit,str2));
}

void TestFlip()
{
	bit_array_t bit = 156;
	char str1[65] = {'0'};
	char str2[65] = {'0'};
	printf("Before fliping all bits: %s\n",BitArrayToString(bit,str1));
	bit = BitArrayFlip(bit);
	printf("After fliping all bits: %s\n",BitArrayToString(bit,str2));
}

void TestFlipBit()
{
	bit_array_t bit = 156;
	char str1[65] = {'0'};
	char str2[65] = {'0'};
	printf("Before fliping 1st bit: %s\n",BitArrayToString(bit,str1));
	bit = BitArrayFlipBit(bit, 0);
	printf("After fliping 1st bit: %s\n",BitArrayToString(bit,str2));
}

void TestCountOn()
{
	bit_array_t bit = 156;
	printf("Number of On bits in %ld is: %ld\n",bit,BitArrayCountOn(bit));
}

void TestCountOff()
{
	bit_array_t bit = 156;
	printf("Number of On bits in %ld is: %ld\n",bit,BitArrayCountOff(bit));
}

void TestGetVal()
{
	bit_array_t bit = 156;
	__uint64_t index = 7;
	printf("The bit in index %ld of %ld is %ld\n", index, bit,BitArrayGetVal(bit, index));
}
 */



















