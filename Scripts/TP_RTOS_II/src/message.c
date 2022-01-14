/**
 * @file message.c
 * @author Luciano Francisco Vittori (lucianovittori99@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-07-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "message.h"

#define LOWER_TO_UPPER_OFFSET 32
#define SPACE 32
#define NULL_POINTER 0


bool message_uppercase(char *msg, uint8_t msg_l)
{
    uint8_t i;

    if ((NULL_POINTER == msg) || msg_l == 0)
    {
        return false;
    }

    for (i = 0; i < msg_l; i++)
    {
        if ((msg[i] >= 'A') && (msg[i] <= 'Z'))
        {
            //msg[i] = msg[i] + 32;
        }
        else if ((msg[i] >= 'a') && (msg[i] <= 'z'))
        {
            msg[i] -= LOWER_TO_UPPER_OFFSET;
        }
        else if (msg[i] != SPACE)
        {
            return false;
        }
    }
    return true;
}

bool message_lowercase(char *msg, uint8_t msg_l)
{
    uint8_t i;

    if ((NULL_POINTER == msg) || msg_l == 0)
    {
        return false;
    }

    for (i = 0; i < msg_l; i++)
    {
        if ((msg[i] >= 'A') && (msg[i] <= 'Z'))
        {
            msg[i] += LOWER_TO_UPPER_OFFSET;
        }
        else if ((msg[i] >= 'a') && (msg[i] <= 'z'))
        {
            //msg[i] -= LOWER_TO_UPPER_OFFSET;
        }
        else if (msg[i] != SPACE)
        {
            return false;
        }
    }
    return true;
}
