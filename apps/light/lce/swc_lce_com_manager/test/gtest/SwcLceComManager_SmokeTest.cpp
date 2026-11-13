/******************************************************************************
 * @file SwcLceComManager_SmokeTest.cpp
 *
 * @ingroup SwcLceComManager
 *
 * brief Smoke tests for the SwcLceComManager SWC using the generated
 *       test RTE (ArUnit gmock generator).
 *
 * @author Abderrahmen Hammami
 *****************************************************************************/

#include "gtest/gtest.h"
#include "SwcLceComManager_FixtureBase.h"
#include "SwcLceComManager.h"

/* Initialization runnable is defined in the SWC; it has no event in the
 * component model, hence the generated RTE header does not declare it. */
extern "C" void RTERunnable_SwcLceComManager_Init(void);

class SwcLceComManagerTest : public SwcLceComManager_FixtureBase
{
};

/**
 * After initialization and one 10ms cycle the ComManager shall read all
 * inputs from the RTE and forward the control signals to the external
 * ECUs (CTR_EL_F and CTR_EL_R messages).
 */
TEST_F(SwcLceComManagerTest, Run10msForwardsControlSignals)
{
    RTERunnable_SwcLceComManager_Init();

    lce::lceComManager::SwcLceComManager& swc =
        lce::lceComManager::SwcLceComManager::getInstance();
    swc.ctrFnDr = 1u;
    swc.ctrFnPos = 1u;
    swc.ctrFnPar = 1u;

    // one 10ms cycle
    run(10);

    EXPECT_EQ(1u, _rteBuffer.get_Rte_Write_SwcLceComManager_comCTR_EL_F_CTR_FN_DR_Buf());
    EXPECT_EQ(1u, _rteBuffer.get_Rte_Write_SwcLceComManager_comCTR_EL_F_CTR_FN_POS_Buf());
    EXPECT_EQ(1u, _rteBuffer.get_Rte_Write_SwcLceComManager_comCTR_EL_F_CTR_FN_PAR_Buf());
    EXPECT_EQ(1u, _rteBuffer.get_Rte_Write_SwcLceComManager_comCTR_EL_R_CTR_FN_DR_Buf());
    EXPECT_EQ(1u, _rteBuffer.get_Rte_Write_SwcLceComManager_comCTR_EL_R_CTR_FN_POS_Buf());
    EXPECT_EQ(1u, _rteBuffer.get_Rte_Write_SwcLceComManager_comCTR_EL_R_CTR_FN_PAR_Buf());
}

/**
 * The ComManager shall read the values provided by the RTE on its input
 * ports (LCU status, BRS status, vehicle state and motor speed).
 */
TEST_F(SwcLceComManagerTest, Run10msReadsInputs)
{
    using ::testing::_;
    using ::testing::DoAll;
    using ::testing::Return;
    using ::testing::SetArgPointee;

    ON_CALL(_mock_SwcLceComManager, Rte_Read_SwcLceComManager_comLight_Ctrl_Inputs_ST_LP_LIN(_))
        .WillByDefault(DoAll(SetArgPointee<0>(2u), Return(RTE_E_OK)));
    ON_CALL(_mock_SwcLceComManager, Rte_Read_SwcLceComManager_comBrightness_Rain_Sensor_ST_RB_LIN(_))
        .WillByDefault(DoAll(SetArgPointee<0>(3u), Return(RTE_E_OK)));
    ON_CALL(_mock_SwcLceComManager, Rte_Read_SwcLceComManager_comCar_State_VEH_ST(_))
        .WillByDefault(DoAll(SetArgPointee<0>(4u), Return(RTE_E_OK)));
    ON_CALL(_mock_SwcLceComManager, Rte_Read_SwcLceComManager_comMotor_Speed_Motor_Speed(_))
        .WillByDefault(DoAll(SetArgPointee<0>(100u), Return(RTE_E_OK)));

    RTERunnable_SwcLceComManager_Init();
    run(10);

    lce::lceComManager::SwcLceComManager& swc =
        lce::lceComManager::SwcLceComManager::getInstance();
    EXPECT_EQ(2u, swc.stLpLin);
    EXPECT_EQ(3u, swc.stRbLin);
    EXPECT_EQ(4u, swc.vehSt);
    EXPECT_EQ(100u, swc.motorSpeed);
}

/**
 * The 10ms timing event of the component model shall trigger the runnable
 * exactly every 10ms: not before the first period (t < 10ms) and twice
 * within a 20ms window after the first period (t = 10ms and t = 20ms).
 */
TEST_F(SwcLceComManagerTest, RunnableIsScheduledEvery10ms)
{
    using ::testing::_;

    RTERunnable_SwcLceComManager_Init();

    EXPECT_CALL(_mock_SwcLceComManager, Rte_Read_SwcLceComManager_comLight_Ctrl_Inputs_ST_LP_LIN(_)).Times(0);
    run(5); // before the first period: runnable must not be executed
    ::testing::Mock::VerifyAndClearExpectations(&_mock_SwcLceComManager);

    EXPECT_CALL(_mock_SwcLceComManager, Rte_Read_SwcLceComManager_comLight_Ctrl_Inputs_ST_LP_LIN(_)).Times(2);
    run(20); // executes at t = 10ms and t = 20ms
}
