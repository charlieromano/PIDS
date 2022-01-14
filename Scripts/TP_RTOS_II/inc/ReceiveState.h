/*=============================================================================
 * Copyright (c) 2020, David Broin <davidmbroin@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Date: 2020/07/17
 *===========================================================================*/

#ifndef _RECEIVESTATE_H_
#define _RECEIVESTATE_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef void (*ReceiveStateAction)(void *object, uint8_t receivedChar);

struct ReceiveState
{
	const char *name;
	ReceiveStateAction execute;
	bool stateHasChanged;
};

typedef struct ReceiveState *ReceiveStatePtr;

/* Create a ReceiveState and return a handle to it. */
ReceiveStatePtr createReceiveState(const uint8_t *name, ReceiveStateAction receiveStateAction);

void ChangeState(ReceiveStatePtr me, ReceiveStateAction receiveStateAction);


#endif /* _RECEIVESTATE_H_ */
