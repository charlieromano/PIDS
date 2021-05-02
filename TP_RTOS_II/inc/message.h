/**
 * @file message.h
 * @author Luciano Francisco Vittori (lucianovittori99@gmail.com)
 * @brief edit string
 * @version 0.1
 * @date 2020-07-18
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef PROGRAMS_TP_RTOS_II_INC_MESSAGE_H_
#define PROGRAMS_TP_RTOS_II_INC_MESSAGE_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief convert string to upper case
 * 
 * @param msg 
 * @param msg_l 
 * @return true when successful
 * @return false if message contain space, alphabetic characters,
 * 					null pointer or 0 size.
 */
bool message_uppercase(char *msg, uint8_t msg_l);

/**
 * @brief convert string to lower case
 * 
 * @param msg 
 * @param msg_l 
 * @return true when successful
 * @return false if message contain space, alphabetic characters,
 * 					null pointer or 0 size.
 */
bool message_lowercase(char *msg, uint8_t msg_l);



#endif /* PROGRAMS_TP_RTOS_II_INC_MESSAGE_H_ */
