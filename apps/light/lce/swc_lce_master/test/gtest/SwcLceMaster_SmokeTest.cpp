/******************************************************************************
 * @file SwcLceMaster_SmokeTest.cpp
 *
 * @ingroup SwcLceMaster
 *
 * brief Smoke tests for the SwcLceMaster SWC using the generated
 *       test RTE (ArUnit gmock generator).
 *
 * @author Abderrahmen Hammami
 *****************************************************************************/

#include "gtest/gtest.h"
#include "SwcLceMaster_FixtureBase.h"
#include "SwcLceMaster.h"

/* Initialization runnable is defined in the SWC; it has no event in the
 * component model, hence the generated RTE header does not declare it. */
extern "C" void RTERunnable_SwcLceMaster_Init(void);

class SwcLceMasterTest : public SwcLceMaster_FixtureBase
{
};

/**
 * After initialization and one 10ms cycle the Master shall have read the
 * control signals provided by the RTE on its input ports (CTR_EL_F and
 * CTR_EL_R messages produced by SwcLceComManager).
 */
TEST_F(SwcLceMasterTest, Run10msReadsControlSignals)
{
    using ::testing::_;
    using ::testing::DoAll;
    using ::testing::Return;
    using ::testing::SetArgPointee;

    ON_CALL(_mock_SwcLceMaster, Rte_Read_SwcLceMaster_comCTR_EL_F_CTR_FN_DR(_))
        .WillByDefault(DoAll(SetArgPointee<0>(1u), Return(RTE_E_OK)));
    ON_CALL(_mock_SwcLceMaster, Rte_Read_SwcLceMaster_comCTR_EL_F_CTR_FN_POS(_))
        .WillByDefault(DoAll(SetArgPointee<0>(2u), Return(RTE_E_OK)));
    ON_CALL(_mock_SwcLceMaster, Rte_Read_SwcLceMaster_comCTR_EL_F_CTR_FN_PAR(_))
        .WillByDefault(DoAll(SetArgPointee<0>(3u), Return(RTE_E_OK)));
    ON_CALL(_mock_SwcLceMaster, Rte_Read_SwcLceMaster_comCTR_EL_R_CTR_FN_DR(_))
        .WillByDefault(DoAll(SetArgPointee<0>(4u), Return(RTE_E_OK)));
    ON_CALL(_mock_SwcLceMaster, Rte_Read_SwcLceMaster_comCTR_EL_R_CTR_FN_POS(_))
        .WillByDefault(DoAll(SetArgPointee<0>(5u), Return(RTE_E_OK)));
    ON_CALL(_mock_SwcLceMaster, Rte_Read_SwcLceMaster_comCTR_EL_R_CTR_FN_PAR(_))
        .WillByDefault(DoAll(SetArgPointee<0>(6u), Return(RTE_E_OK)));

    RTERunnable_SwcLceMaster_Init();
    run(10);

    lce::lceMaster::SwcLceMaster& swc = lce::lceMaster::SwcLceMaster::getInstance();
    EXPECT_EQ(1u, swc.ctrFnDrF);
    EXPECT_EQ(2u, swc.ctrFnPosF);
    EXPECT_EQ(3u, swc.ctrFnParF);
    EXPECT_EQ(4u, swc.ctrFnDrR);
    EXPECT_EQ(5u, swc.ctrFnPosR);
    EXPECT_EQ(6u, swc.ctrFnParR);
}
