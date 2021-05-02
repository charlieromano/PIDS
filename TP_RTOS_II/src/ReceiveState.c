/*=====ReceiveState===========================================================
 
 /*=============================================================================
 * Copyright (c) 2020, David Broin <davidmbroin@gmail.com>
 * All rights reserved.
 * License: mit (see LICENSE.txt)
 * Date: 2020/07/17
 *===========================================================================*/

#include "ReceiveState.h"

ReceiveStatePtr createReceiveState(const uint8_t *name, ReceiveStateAction receiveStateAction)
{
	ReceiveStatePtr receiveState = malloc(sizeof *receiveState);
	if (NULL != receiveState)
	{
		/* Bind the initial strategy supplied by the client. */
		receiveState->execute = receiveStateAction;
		/* Initialize the other attributes of the receiveState here. */
		receiveState->stateHasChanged = true;
	}
	return receiveState;
}

void ChangeState(ReceiveStatePtr me, ReceiveStateAction receiveStateAction)
{
		me->execute = receiveStateAction;
		me->stateHasChanged = true;
}