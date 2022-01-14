/**
 * @file package.c
 * @author Luciano Francisco Vittori (lucianovittori99@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-07-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "package.h"
#include "CRC.h"

#define MSG_EMPTY 0x00
#define CRC_EMPTY 'X'
#define CURSOR_DEFAULT -1

bool package_ctor(package *const me, char som_set, char eom_set)
{
    if (NULL == me)
    {
        return false;
    }
    else
    {
        me->som = som_set;
        me->msg[0] = END_STRING;
        me->msg_l = MSG_EMPTY;
        me->msg_cursor = CURSOR_DEFAULT;
        me->crcH = CRC_EMPTY;
        me->crcL = CRC_EMPTY;
        me->eom = eom_set;
        return true;
    }
}

bool package_clear(package *const me)
{
    if (NULL == me)
    {
        return false;
    }
    else
    {
        me->msg[0] = END_STRING;
        me->msg_l = MSG_EMPTY;
        me->msg_cursor = CURSOR_DEFAULT;
        me->crcH = CRC_EMPTY;
        me->crcL = CRC_EMPTY;
        return true;
    }
}

bool package_dtor(package *const me)
{
    if (NULL == me)
    {
        return false;
    }
    else
    {
        free(me->msg);
        return true;
    }
}

bool package_addElement(package *const me, char element)
{
    if ((NULL == me))
    {
        return false;
    }
    else if (me->msg_l < MSG_LENGTH)
    {
        me->msg[me->msg_l] = element;
        me->msg_l++;
        return true;
    }
    else
    {
        return false;
    }
}

char package_PeekElement(package *const me)
{
    char element = END_STRING;
    if (me->msg_cursor <= (me->msg_l + CRC_SIZE))
    {
        if (me->msg_cursor == CURSOR_DEFAULT)
        {
            element = me->som;
        }
        else if (me->msg_cursor < me->msg_l)
        {
            element = me->msg[me->msg_cursor];
        }
        else if (me->msg_cursor == me->msg_l)
        {
            element = me->crcH;
        }
        else if (me->msg_cursor == (me->msg_l + 1))
        {
            element = me->crcL;
        }
        else if (me->msg_cursor == (me->msg_l + CRC_SIZE))
        {
            element = me->eom;
        }
        else
        {
            element = END_STRING;
        }
        me->msg_cursor++;
    }
    return element;
}

bool package_addString(package *const me, char *const string, uint8_t string_length)
{
    uint8_t i;
    uint8_t element_added = 0;

    if ((NULL == me) || (string_length > MSG_LENGTH))
    {
        return false;
    }

    for (i = 0; i < string_length; i++)
    {
        element_added += package_addElement(me, string[i]);
    }
    if (element_added == me->msg_l)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool package_check(package *const me)
{
    if (CRC_Check(me->msg, me->msg_l))
    {
        me->crcH = me->msg[me->msg_l - CRC_SIZE];
        me->crcL = me->msg[me->msg_l - CRC_SIZE + 1];
        return true;
    }
    else
    {
        return false;
    }
}

bool package_calc(package *const me)
{
    if (CRC_Calc(me->msg, me->msg_l))
    {
        me->crcH = me->msg[me->msg_l - CRC_SIZE];
        me->crcL = me->msg[me->msg_l - CRC_SIZE + 1];
        me->msg[me->msg_l - CRC_SIZE] = END_STRING;
        me->msg_l -= CRC_SIZE; //Discard CRC from the original message.
        return true;
    }
    else
    {
        return false;
    }
}
