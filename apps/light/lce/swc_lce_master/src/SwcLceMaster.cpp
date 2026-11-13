/******************************************************************************
 * @file SwcComManager.cpp
 *
 * @ingroup SwcComManager
 *
 * brief Main class for ComManager layer
 *
 * @author Abderrahmen Hammami
 *****************************************************************************/

#include <new>
#include "Rte_SwcLceMaster.h"
#include "../include/SwcLceMaster.h"

namespace lce
{
	namespace lceMaster
	{
		SwcLceMaster::SwcLceMaster()
		{

		}

		SwcLceMaster& SwcLceMaster::getInstance()
		{
			static SwcLceMaster _instance;
			return _instance;
		}

		void SwcLceMaster::reinit()
		{
			new (this) SwcLceMaster();
		}

		void SwcLceMaster::init()
		{
			reinit();
		}

		void SwcLceMaster::run10ms()
		{

		}
	}
}