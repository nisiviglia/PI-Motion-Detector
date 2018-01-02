#include "gtest/gtest.h"
#include "../include/logger.hpp"
#include <string>
#include <boost/filesystem.hpp> 

//Global
std::string FP = "test_logs/";

//A weak test to confirm the logger can create the folder.
//If thats not good enough you can check the test log by hand.
TEST(logger_test, create_log){
    
    //delete old folder
	boost::filesystem::remove_all(FP); 

    logger log(FP);
    log.fatal("fatal message");
    log.error("this is a test error message");
    log.warning("A warning msg");
    log.info("info message");
	
	bool log_folder_exits = boost::filesystem::is_directory(FP);
    EXPECT_TRUE(log_folder_exits);

}
