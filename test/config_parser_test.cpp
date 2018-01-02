#include "gtest/gtest.h"
#include "../include/config_parser.hpp"
#include "./smtp_settings.hpp"
#include <boost/filesystem.hpp> 

//Global 
std::string FN = "test_config.ini";

// Make sure that a new config file will be generated
// if one is not found.
TEST(config_parser_test, generate_new_config){

    //delete old folder
	boost::filesystem::remove(FN); 

    //since no config file exits it will be generated
    config_parser config(FN);

    //check if file now exists
    bool exists = boost::filesystem::exists(FN);
    ASSERT_TRUE(exists);
}

// Test that you receive the right values from the config.
TEST(config_parser_test, get_value_from_config){

    //delete old folder
	boost::filesystem::remove(FN); 

    //since no config file exits it will be generated
    config_parser config(FN);

    //get server name and port from config
    std::string server = config.get_str("SMTP.server");
    EXPECT_EQ(server, "smtp.example.com");
    int port = config.get_int("SMTP.port");
    EXPECT_EQ(port, 587); 
}

// Test that the config parser can handle invalid input.
TEST(config_parser_test, get_invalid_value_from_config){

    //delete old folder
	boost::filesystem::remove(FN); 

    //since no config file exits it will be generated
    config_parser config(FN);
    
    //get invalid string from config file
    std::string string = config.get_str("INVALID.string");
    EXPECT_EQ(string, "");

    //get invalid int from config file
    int integer = config.get_int("INVALID.int");
    EXPECT_EQ(integer, -1); 
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
