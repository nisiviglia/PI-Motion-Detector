#include "gtest/gtest.h"
#include <string>
#include <cstdio>

#include "../include/alarm.hpp"

// This will test if you're getting a stable reading from the sensor.
// Be sure to not move or otherwise interfere with the sensor while this
// test is being carried out.
TEST(alarm, generate_config_file){
    
    std::string test_config = "./pda_test.cfg";
    std::remove(test_config.c_str());
    class alarm al(test_config);
   
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    ASSERT_EXIT( al.run(), ::testing::ExitedWithCode(-1), "config file not found. config generated.");

    std::remove(test_config.c_str());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
