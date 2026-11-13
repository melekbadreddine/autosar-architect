/******************************************************************************
 * @file
 *
 * @ingroup SwcLceMaster
 *
 * Definition of the Swc for the SwcLceMaster.
 *
 * @author Abderrahmen Hammami
 *****************************************************************************/

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
