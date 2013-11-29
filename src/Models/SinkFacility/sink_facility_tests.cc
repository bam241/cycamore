// sink_facility_tests.cc
#include <gtest/gtest.h>

#include "sink_facility_tests.h"

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void SinkFacilityTest::SetUp() {
  InitParameters();
  SetUpSinkFacility();
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void SinkFacilityTest::TearDown() {
  delete src_facility;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void SinkFacilityTest::InitParameters() {
  commod_ = "incommod";
  // commod_market = new MockMarket(tc_.get());
  // commod_market->SetCommodity(commod_);
  // cyclus::MarketModel::RegisterMarket(commod_market);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void SinkFacilityTest::SetUpSinkFacility() {
  using cycamore::SinkFacility;
  src_facility = new SinkFacility(tc_.get());
  src_facility->AddCommodity(commod_);
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
TEST_F(SinkFacilityTest, InitialState) {
  int time = 1;
  EXPECT_DOUBLE_EQ(0.0, src_facility->InventorySize());
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
TEST_F(SinkFacilityTest, clone) {
  using cycamore::SinkFacility;
  SinkFacility* cloned_fac = dynamic_cast<cycamore::SinkFacility*>
                             (src_facility->Clone());

  EXPECT_EQ(src_facility->capacity(), cloned_fac->capacity());
  EXPECT_EQ(src_facility->MaxInventorySize(), cloned_fac->MaxInventorySize());

  delete cloned_fac;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
TEST_F(SinkFacilityTest, Print) {
  EXPECT_NO_THROW(std::string s = src_facility->str());
}

// //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// TEST_F(SinkFacilityTest, ReceiveMessage) {
//   cyclus::Message::Ptr msg = cyclus::Message::Ptr(new cyclus::Message(
//                                                     src_facility));
//   EXPECT_NO_THROW(src_facility->ReceiveMessage(msg));
// }

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
TEST_F(SinkFacilityTest, Tick) {
  int time = 1;
  EXPECT_DOUBLE_EQ(0.0, src_facility->InventorySize());
  EXPECT_NO_THROW(src_facility->HandleTick(time));
  EXPECT_DOUBLE_EQ(0.0, src_facility->InventorySize());
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
TEST_F(SinkFacilityTest, Tock) {
  int time = 1;
  EXPECT_DOUBLE_EQ(0.0, src_facility->InventorySize());
  EXPECT_NO_THROW(src_facility->HandleTock(time));
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
cyclus::Model* SinkFacilityModelConstructor(cyclus::Context* ctx) {
  using cycamore::SinkFacility;
  return dynamic_cast<cyclus::Model*>(new SinkFacility(ctx));
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
cyclus::FacilityModel* SinkFacilityConstructor(cyclus::Context* ctx) {
  using cycamore::SinkFacility;
  return dynamic_cast<cyclus::FacilityModel*>(new SinkFacility(ctx));
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
INSTANTIATE_TEST_CASE_P(SinkFac, FacilityModelTests,
                        Values(&SinkFacilityConstructor));
INSTANTIATE_TEST_CASE_P(SinkFac, ModelTests,
                        Values(&SinkFacilityModelConstructor));

