/******************************************************************************
 * @file Rte_SwcComManager.cpp
 *
 * @ingroup SwcComManager
 *
 * brief Rte entry points
 *
 * @author Abderrahmen Hammami
 *****************************************************************************/
#include "Rte_SwcLceComManager.h"
#include "../include/SwcLceComManager.h"

using namespace lce::lceComManager;

extern "C"
{

	void RTERunnable_SwcLceComManager_Init()
	{
		SwcLceComManager::getInstance().init();
	}


	void RTERunnable_SwcLceComManager_RunComMngr_10msTask()
	{
		SwcLceComManager::getInstance().run10ms();
	}

}
