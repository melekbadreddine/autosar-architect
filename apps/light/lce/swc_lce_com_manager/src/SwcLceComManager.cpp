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
#include "../include/SwcLceComManager.h"
#include "Rte_SwcLceComManager.h"

namespace lce
{
	namespace lceComManager
	{
		SwcLceComManager::SwcLceComManager()

		{

		}

		SwcLceComManager& SwcLceComManager::getInstance()
		{
			static SwcLceComManager _instance;
			return _instance;
		}

		void SwcLceComManager::reinit()
		{
			new (this) SwcLceComManager();
		}

		void SwcLceComManager::init()
		{
			reinit();
		}

		void SwcLceComManager::init()
		{
			reinit();
		}
		void SwcLceComManager::run10ms()
		{
			// develop code of this function
			readInputs();
			writeOutputs();
		}
		void SwcLceComManager::readInputs()
		{
			// develop code of this function: read all inputs RTE Read ()
			Rte_Read_SwcLceComManager_comBrightness_Rain_Sensor_ST_RB_LIN(&stRbLin);
			Rte_Read_SwcLceComManager_comLight_Ctrl_Inputs_ST_LP_LIN(&stLpLin);			
		}
		void SwcLceComManager::writeOutputs()
		{
			// develop code of this function: we will call RTE Write to be consumed by SwcLceMaster
			rte_wri
			// develop code of this function: we will call RTE Write to be consumed by External ECUs RTE Write CTR_FN_DR
		}
	}
}