#include "unity.h"
#include <string.h>
#include "CRC.h"

void test_CRC_Check(void)
{
	char array[] = "mHOlA7B";
	char array2[] = {'m','H','O', 'l', 'A', '7', 'B'};
	TEST_ASSERT(CRC_Check(array, strlen(array))); //strlen(array) = sizeof(array)-1 (null character)
	TEST_ASSERT(CRC_Check(array2, sizeof(array2)));
	array[6] = 'C';
	TEST_ASSERT_FALSE(CRC_Check(array, strlen(array)));
}

void test_CRC_Calc(void)
{
	char array[] = "mHOlAXX";
	TEST_ASSERT(array[5] == 'X' && array[6] == 'X');
	CRC_Calc(array, strlen(array));
	TEST_ASSERT(array[5] == '7' && array[6] == 'B');
}
