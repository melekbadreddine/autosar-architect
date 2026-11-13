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
			// develop code of this function: read the control signals produced by SwcLceComManager
			Rte_Read_SwcLceMaster_comCTR_EL_F_CTR_FN_DR(&ctrFnDrF);
			Rte_Read_SwcLceMaster_comCTR_EL_F_CTR_FN_POS(&ctrFnPosF);
			Rte_Read_SwcLceMaster_comCTR_EL_F_CTR_FN_PAR(&ctrFnParF);
			Rte_Read_SwcLceMaster_comCTR_EL_R_CTR_FN_DR(&ctrFnDrR);
			Rte_Read_SwcLceMaster_comCTR_EL_R_CTR_FN_POS(&ctrFnPosR);
			Rte_Read_SwcLceMaster_comCTR_EL_R_CTR_FN_PAR(&ctrFnParR);
		}
	}
}