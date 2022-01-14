/**
 * @file CRC.c
 * @author Luciano Francisco Vittori (lucianovittori99@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-07-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "CRC.h"

static uint8_t crc8_small_table[16] = {0x00, 0x07, 0x0e, 0x09, 0x1c, 0x1b,
									   0x12, 0x15, 0x38, 0x3f, 0x36, 0x31, 0x24, 0x23, 0x2a, 0x2d};

uint8_t crc8_init(void);
uint8_t crc8_calc(uint8_t val, void *buf, int cnt);

static char Hex_To_Ascii[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

bool CRC_Check(char *message, uint8_t message_length)
{
	volatile uint8_t crc;
	char crcH;
	char crcL;
	uint8_t i = 0;
	bool crc_ok = false;

	crc = crc8_init();
	crc = crc8_calc(crc, (void *)message, message_length - CRC_SIZE);

	crcH = Hex_To_Ascii[((crc & 0xF0) >> 4)];
	crcL = Hex_To_Ascii[(crc & 0x0F)];

	if (message[message_length - CRC_SIZE] == crcH)
	{
		if (message[message_length - CRC_SIZE + 1] == crcL)
		{
			crc_ok = true;
		}
	}

	return crc_ok;
}

bool CRC_Calc(char *message, uint8_t message_length)
{

	volatile uint8_t crc;
	char crcH;
	char crcL;
	uint8_t i = 0;
	bool crc_ready = false;

	crc = crc8_init();
	crc = crc8_calc(crc, (void *)message, message_length - CRC_SIZE);

	crcH = Hex_To_Ascii[((crc & 0xF0) >> 4)];
	crcL = Hex_To_Ascii[(crc & 0x0F)];

	message[message_length - CRC_SIZE] = crcH;
	message[message_length - CRC_SIZE + 1] = crcL;
	crc_ready = true;

	return crc_ready;
}

uint8_t crc8_init(void)
{
	return 0x00;
}

uint8_t crc8_calc(uint8_t val, void *buf, int cnt)
{
	int i;
	uint8_t *p = buf;

	for (i = 0; i < cnt; i++)
	{
		val ^= p[i];
		val = (val << 4) ^ crc8_small_table[val >> 4];
		val = (val << 4) ^ crc8_small_table[val >> 4];
	}
	return val;
}
