// Copyright (C) 
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
// 
/// @file alarm.cpp
/// @brief sends a message via smtp when motion is detected.
/// @author Nicholas Siviglia
/// @version 1.0
/// @date 2018-04-09

#include "../include/alarm.hpp"
#include <future>
#include <ctime>
#include <chrono>
#include <thread>

/// @brief Basic constructor
alarm::alarm() : 
    config(this->config_file_path),
    log( config.get_str("LOG.log_folder") ),
    smtp(config.get_str("SMTP.server"),
        config.get_int("SMTP.port"),
        config.get_str("SMTP.username"),
        config.get_str("SMTP.password")),
    motion(){
    
        motion.set_detector_sensitivity( config.get_float("MOTION.sensitivity") );
    }

/// @brief Constructer that takes in the config file path.
///
/// @param config_file_path full path to the config file.
alarm::alarm(std::string path) :
    config(path),
    log( config.get_str("LOG.log_folder") ),
    smtp(config.get_str("SMTP.server"),
        config.get_int("SMTP.port"),
        config.get_str("SMTP.username"),
        config.get_str("SMTP.password")),
    motion(){
    
        motion.set_detector_sensitivity( config.get_float("MOTION.sensitivity") );
    }

/// @brief Start the system and continusly scan for motion. When motion is detected send a message, log it, and timeout.
void alarm::run(){
    
    using system_clock = std::chrono::system_clock;

    //Init log file and send startup message
    log.info("System Started");
    log.info("Sending startup message");

    auto current_time = system_clock::to_time_t(system_clock::now());
    std::string msg = "System started.\n";
    msg += std::ctime(&current_time);
    bool rc_smtp = false;
    rc_smtp = smtp.send(
            config.get_str("EMAIL.from_address"),
            config.get_str("EMAIL.to_address"),
            config.get_str("EMAIL.subject"),
            msg
            );
    
    //Check if message was successfully sent
    if(rc_smtp == true){
        log.info("Startup message sent");
        log.info("System engaged, detecting motion");
    }
    else{
        log.fatal("Startup message failed");
        log.fatal(smtp.get_connection_output());
        exit(-1);
    }

    //Loop looking for motion. 
    //if there is: send message, log event, timeout
    while(true){
        if(motion.detect_motion() == true){

            //Send message
            log.warning("Motion detected");
            log.info("Sending message");
            current_time = system_clock::to_time_t(system_clock::now());
            msg = config.get_str("EMAIL.message") + "\n" + std::ctime(&current_time);
            rc_smtp = smtp.send(
                    config.get_str("EMAIL.from_address"),
                    config.get_str("EMAIL.to_address"),
                    config.get_str("EMAIL.subject"),
                    msg
                    );
            
            //Check if message was successfully sent
            if(rc_smtp == true){
                log.info("Motion detected message sent");
            }
            else{
                log.error("Motion detected message failed");  
                log.error(smtp.get_connection_output());
            } 
            
            //Time out
            log.info("Timeout");
            int time_in_milli = 1000 * config.get_int("MOTION.sleep_in_sec");
            std::this_thread::sleep_for(std::chrono::milliseconds(time_in_milli));

            //Reset
            log.info("System reset");
            motion.set_detector_distance();

        }//END if 
    
    }//END while
}
