#include "gtest/gtest.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "../include/lv_maxsonar.hpp"

// Tests that the serial interface is not being used by the console.
// If this fails, run 'sudo raspi-config' and disable the console on
// the serial interface.
TEST(lv_maxsonar_test, is_serial0_accessible){

    std::string file_name = "is_serial0_accessible.txt";
    std::string command_str = "dmesg | grep -c \"console \\[ttyAMA0\\] enabled\" > " + file_name;
    
    std::system(command_str.c_str()); 
    
    std::ifstream fn;
    fn.open(file_name);
    ASSERT_TRUE(fn.is_open());
    
    std::string file_line;
    std::getline(fn, file_line);
    fn.close();
    std::remove( file_name.c_str() );
    ASSERT_TRUE( file_line.find("1") == std::string::npos );
}

// This appemts to read the distance from the sensor.
TEST(lv_maxsonar_test, read_distance){
   
   lv_maxsonar sensor; 

   int test_distance = sensor.read_distance();

   ASSERT_TRUE( test_distance != -1);
}




int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
