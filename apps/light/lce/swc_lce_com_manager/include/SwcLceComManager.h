/******************************************************************************
 * @file
 *
 * @ingroup SwcLceComManager
 *
 * Definition of the Swc for the LceComManager layer.
 *
 * @author Abderrahmen Hammami
 *****************************************************************************/

namespace lce
{
	namespace lceComManager
	{
		/**
		 * The LceComManager Softwarecomponent is responsable to receive data from External ECUs or from internal SWCs and forward it to the appropriate SWCs ( SWcLceMaster )
		 */
		class SwcLceComManager
		{

		public:
			IComBrightness_Rain_Sensor_ST_RB_LIN_Type stRbLin;
			IComLight_Ctrl_Inputs_ST_LP_LIN_Type stLpLin;
			IComLight_Ctrl_Inputs_CTR_FN_DR_Type ctrFnDr;
			IComLight_Ctrl_Inputs_CTR_FN_PAR_Type ctrFnPar;
			IComLight_Ctrl_Inputs_CTR_FN_POS_Type ctrFnPos;

			SwcLceComManager();

			static SwcLceComManager& getInstance();

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

			/**
			* read the inputs from external ECUs or from internal SWCs
			*/
			void readInputs();

			/**
			* write the outputs to external ECUs or to internal SWCs
			*/
			void writeOutputs();
		};
	}
}