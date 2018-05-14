#include "gtest/gtest.h"
#include <string>

#include "../include/motion_detector.hpp"

// this tests that the sensor can get a valid reading and 
// set the lock distance.
TEST(motion_detector, set_the_detector){

    motion_detector detector;

    detector.set_detector_distance();

    ASSERT_TRUE(detector.get_detector_distance() > 0);   
}

// This will test if you're getting a stable reading from the sensor.
// Be sure to not move or otherwise interfere with the sensor while this
// test is being carried out.
TEST(motion_detector, detect_no_motion){

    motion_detector detector;

    detector.set_detector_distance();

    ASSERT_FALSE( detector.detect_motion() );   
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
