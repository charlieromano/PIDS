/**
 * @file package.h
 * @author Luciano Francisco Vittori (lucianovittori99@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-07-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef PROGRAMS_TP_RTOS_II_INC_PACKAGE_H_
#define PROGRAMS_TP_RTOS_II_INC_PACKAGE_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define MSG_LENGTH 100 //!< block memory size
#define CRC_LENGTH 2  //!< 2 ASCII character
#define SOM_LENGTH 1
#define EOM_LENGTH 1
#define NO_MSG_LENGTH (SOM_LENGTH + CRC_LENGTH + EOM_LENGTH)
#define END_STRING '\0' //!< Null character.

/**
 * @brief package class
 */

/**
 * package struct.
 */
typedef struct
{
	char som;			  //!< Start of message character.
	char msg[MSG_LENGTH]; //!< Message.
	char crcH;			  //!< ASCII CRC. F for 0xFA number.
	char crcL;			  //!< ASCII CRC. A for 0xFA number.
	char eom;			  //!< End of message character.
	uint8_t msg_l;		  //!< Message length.
	int8_t msg_cursor;	  //!< Actual position in message (for READ)
} package;

/**
 * @brief package constructor
 * 
 * @param me 
 * @param som_set 
 * @param eom_set 
 * @return true  object created.
 * @return false null pointer
 */
bool package_ctor(package *const me, char som_set, char eom_set);

/**
 * @brief Function to reset message field.
 * 
 * @param me 
 * @return true 
 * @return false 
 */
bool package_clear(package *const me);

/**
 * @brief add element
 * This function increment message size automatic.
 * @param me 
 * @param element 
 * @return true if was successful
 * @return false for error (NULL pointer or message is full)
 */
bool package_addElement(package *const me, char element);

/**
 * @brief Function to read one element at once.
 * Function to automatically read one element at once including SOM, MSG, CRC and EOM.
 * @param me 
 * @return char 
 */
char package_PeekElement(package *const me);

/**
 * @brief Add a string to package
 * 
 * @param me 
 * @param string 
 * @param string_length 
 * @return true 
 * @return false (NULL pointer or string_length is greater than MSG_LENGTH)
 */
bool package_addString(package *const me, char *const string, uint8_t string_length);

/**
 * @brief No more element will be add.
 * This function validate CRC with last two character and complete CRC field if is correct.
 * @param me 
 * @return true if CRC was correct.
 * @return false if not.
 */
bool package_check(package *const me);

/**
 * @brief prepare package to be send.
 * This function add a correct CRC in a CRC field.
 * @note The last two character change to null value for discard from the message field.
 * @param me 
 * @return true 
 * @return false 
 */
bool package_calc(package *const me);

#endif /* PROGRAMS_TP_RTOS_II_INC_PACKAGE_H_ */
