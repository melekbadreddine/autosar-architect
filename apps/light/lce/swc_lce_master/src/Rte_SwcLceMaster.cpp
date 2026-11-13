/******************************************************************************
 * @file Rte_SwcLceMaster.cpp
 *
 * @ingroup SwcLceMaster
 *
 * brief Rte entry points
 *
 * @author Abderrahmen Hammami
 *****************************************************************************/
#include "Rte_SwcLceMaster.h"
#include "../include/SwcLceMaster.h"

using namespace lce::lceMaster;

extern "C"
{

	void RTERunnable_SwcLceMaster_Init()
	{
		SwcLceMaster::getInstance().init();
	}


	void RTERunnable_SwcLceMaster_RunComMngr_10msTask()
	{
		SwcLceMaster::getInstance().run10ms();
	}

}
