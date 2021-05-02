#include "../vendor/unity/src/unity.h"
#include "package.h"
#include "CRC.h"
#include <stdio.h>
#include <string.h>

static package mypackage;

void setUp(void)
{
    char mysom = '(';
    char myeom = ')';
    package_ctor(&mypackage, mysom, myeom);
}

void tearDown(void)
{
    uint8_t i;
    printf("printing one item at a time like UART: ");

    putchar(mypackage.som);
    for (i = 0; i < mypackage.msg_l; i++)
    {
        putchar(mypackage.msg[i]);
    }
    putchar(mypackage.crcH);
    putchar(mypackage.crcL);
    putchar(mypackage.eom);
    printf("\r\n");
}

void test_addElement(void)
{
    package_addElement(&mypackage, '1');
    package_addElement(&mypackage, '2');
    TEST_ASSERT_EQUAL_CHAR('1', mypackage.msg[0]);
    TEST_ASSERT_EQUAL_CHAR('2', mypackage.msg[1]);
    TEST_ASSERT_EQUAL_CHAR(END_STRING, mypackage.msg[2]);
    TEST_ASSERT_EQUAL_INT(2, mypackage.msg_l);
}

void test_addElement_full_message(void)
{
    uint8_t i;
    for (i = 0; i < MSG_LENGTH; i++)
    {
        TEST_ASSERT(package_addElement(&mypackage, '1') == true);
    }
    TEST_ASSERT(package_addElement(&mypackage, '2') == false);
}

void test_addString(void)
{
    char msg[] = "HOLA";
    package_addString(&mypackage, msg, strlen(msg));
    TEST_ASSERT_EQUAL_CHAR_ARRAY(mypackage.msg, "HOLA", strlen("HOLA"));
}

void test_package_check_valid_msg(void)
{
    char msg[] = "mHOlA7B";
    package_addString(&mypackage, msg, strlen(msg));
    TEST_ASSERT(package_check(&mypackage) == true);
}

void test_package_check_empty_msg(void)
{
    TEST_ASSERT(package_check(&mypackage) == false);
}

void test_package_check_invalid_msg(void)
{
    char msg[] = "mHOlAF5";
    package_addString(&mypackage, msg, strlen(msg));
    TEST_ASSERT(package_check(&mypackage) == false);
}

void test_package_memory_violation(void)
{
    char msg[MSG_LENGTH];
    uint16_t length;
    for (length = 0; length < MSG_LENGTH; length++)
    {
        msg[length] = 'F';
    }
    TEST_ASSERT(package_addString(&mypackage, msg, strlen(msg) + 1) == false);
}

void test_package_calc(void)
{
    char msg[] = "mHOlA--";
    package_addString(&mypackage, msg, strlen(msg));
    package_calc(&mypackage);
    TEST_ASSERT_EQUAL_CHAR(mypackage.crcH, '7');
    TEST_ASSERT_EQUAL_CHAR(mypackage.crcL, 'B');
}

void test_package_PeekElement(void)
{
    uint8_t i;
    char msg[] = "lol--";
    char c;
    package_addString(&mypackage, msg, strlen(msg));
    package_calc(&mypackage);

    do
    {
        c = package_PeekElement(&mypackage);
        putchar(c);
    } while (c != mypackage.eom && c != END_STRING);
    printf("\r\n");
}