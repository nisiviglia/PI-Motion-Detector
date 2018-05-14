#ifndef ALARM
#define ALARM 

#include <string>
#include "./config_parser.hpp"
#include "./logger.hpp"
#include "./motion_detector.hpp"
#include "./smtp_client.hpp"

//! An Alarm that sends an email (sms) and logs to log file when motion is detected.
/*! 
  Example usage: 
        
*/

class alarm {
    
    public:

        alarm();

        alarm(std::string config_file_path);

        void run();

    private:
        std::string config_file_path = "pda_config.cfg"; 

        config_parser config;

        logger log;

        smtp_client smtp;

        motion_detector motion;
};

#endif
