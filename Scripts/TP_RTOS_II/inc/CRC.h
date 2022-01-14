/**
 * @file CRC.h
 * @author Luciano Francisco Vittori (lucianovittori99@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-07-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef PROGRAMS_CRC_TEST_INC_C2_CRC_H_
#define PROGRAMS_CRC_TEST_INC_C2_CRC_H_

#include <stdbool.h>
#include <stdint.h>

#define CRC_SIZE 2

/**
 * message = char array
 * array = DATA+CRC
 * @example mHOlA7B
 */

/**
 * @brief validate CRC.
 * Receive a message and validate CRC.
 * @note CRC are the last 2 character.
 * @param message
 * @param message_length
 * @return true: CRC correct.false: CRC incorrect.
 */
bool CRC_Check(char *message, uint8_t message_length);

/**
 * @brief add CRC.
 * Receive a message and add the correct CRC.
 * @note CRC is added in ASCII.
 * @param message
 * @param message_length
 * @return true: when finish.
 */
bool CRC_Calc(char *message, uint8_t message_length);

#endif /* PROGRAMS_CRC_TEST_INC_C2_CRC_H_ */
