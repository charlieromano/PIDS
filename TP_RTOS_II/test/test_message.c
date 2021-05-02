#include "unity.h"
#include "message.h"
#include <string.h>

static char string[50];

void setUp(void)
{
    string[0] = '\0';
}

void tearDown(void)
{
    printf("%s, %ld characters\r\n", string, strlen(string));
}

void test_message_uppercase_correctos(void)
{
    /* Tiene que pasar y convertir aunque tenga espacios */
    strcpy(string, "prueba CON espacios");
    TEST_ASSERT(message_uppercase(string, strlen(string)) == true);
}

void test_message_uppercase_withoutCRC(void)
{
    /* Tiene que pasar y convertir aunque tenga espacios */
    strcpy(string, "mprobandoF3");
    TEST_ASSERT(message_uppercase(string, strlen(string)-2) == true);
}

void test_message_uppercase_incorrecto(void)
{
    strcpy(string, "prueba con numeros comO 5300");
    TEST_ASSERT(message_uppercase(string, strlen(string)) == false);
    /* Tiene que fallar por haber caracteres raros */
    strcpy(string, "prueba con cosas comO }[{ssf`");
    TEST_ASSERT(message_uppercase(string, strlen(string)) == false);
}

void test_message_lowercase_correctos(void)
{
    /* Tiene que pasar y convertir aunque tenga espacios */
    strcpy(string, "prueba CON espacios");
    TEST_ASSERT(message_lowercase(string, strlen(string)) == true);
}

void test_message_lowercase_incorrecto(void)
{
    strcpy(string, "prueba con numeros comO 5300");
    TEST_ASSERT(message_lowercase(string, strlen(string)) == false);
    /* Tiene que fallar por haber caracteres raros */
    strcpy(string, "prueba con cosas comO }[{ssf`");
    TEST_ASSERT(message_lowercase(string, strlen(string)) == false);
}