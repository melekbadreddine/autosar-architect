/******************************************************************************
 * @file
 *
 * @ingroup SwcLceMaster
 *
 * Definition of the Swc for the SwcLceMaster.
 *
 * @author Abderrahmen Hammami
 *****************************************************************************/

#include "Rte_Type.h"

namespace lce
{
	namespace lceMaster
	{
		/**
		 * The SwcLceMaster Softwarecomponent is responsable to decide if exterior light functions shall be activated or not based on different inputs from the software component SwcLceComManager
		 */
		class SwcLceMaster
		{

		public:
			IComLight_Ctrl_Inputs_CTR_FN_DR_Type ctrFnDrF;
			IComLight_Ctrl_Inputs_CTR_FN_PAR_Type ctrFnParF;
			IComLight_Ctrl_Inputs_CTR_FN_POS_Type ctrFnPosF;
			IComLight_Ctrl_Inputs_CTR_FN_DR_Type ctrFnDrR;
			IComLight_Ctrl_Inputs_CTR_FN_PAR_Type ctrFnParR;
			IComLight_Ctrl_Inputs_CTR_FN_POS_Type ctrFnPosR;

			SwcLceMaster();

			static SwcLceMaster& getInstance();

			/**
			* reinit the isntance
			*/
			void reinit();

			/**
			* init the instance
			*/
			void init();

			/**
			* run the 10ms cyclic loop
			*/
			void run10ms();
		};
	}
}
