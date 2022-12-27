// #include "gmock/gmock.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "test_appfacade.cpp"
#include "test_changecommand.cpp"
#include "test_configurationparser.cpp"
#include "test_directory.cpp"
#include "test_filepicker.cpp"
#include "test_logger.cpp"
#include "test_strategycontext.cpp"
#include "test_uniformstrategy.cpp"
#include "test_weightedstrategy.cpp"

// TODO: this is probably not the best way to run the tests... consider
// refactoring.

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
