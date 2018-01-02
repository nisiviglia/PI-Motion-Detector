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
/// @file config_parser.cpp
/// @brief An ini config file parser.
/// @author Nicholas Siviglia
/// @version 1.0
/// @date 2017-12-30

#include "../include/config_parser.hpp"
#include <fstream>
#include <iostream>
#include <boost/property_tree/ini_parser.hpp>

/// @brief Opens the config file. If it doesn't exist then it's generated.
///
/// @param filename The full path to the configuration file.
config_parser::config_parser(std::string filename) : filename(filename){
    
    // Check if config file exits and generate one if it doesn't
    std::ifstream f(filename.c_str());
    if(f.good())
        f.close();
    else
        generate_config_file();
    
    // Parse the ini file into the property tree.
    try{
        boost::property_tree::read_ini(this->filename, this->tree);
    }
    catch(std::exception e){
        std::cout << "error, malformed config file." << std::endl; 
        std::terminate();
    }
}

/// @brief Gets a string value from from the config file.
///
/// @param path The section and key of the value wanted.
/// This is given in the format of "section.key" .<br>
///
/// Example of config file: <br>
///     `[SMTP]` <br>
///     `server=smtp.example.com` <br>
///
/// Example of path string: <br>
///     `"SMTP.server"` <br>
///
/// Key returned <br>
///    `"smtp.example.com"`
///
/// @return String
std::string config_parser::get_str(std::string path){

    std::string return_value = "";

    // Get value from ptree and return it if it exists
    boost::optional<std::string> opt = tree.get_optional<std::string>(path);
    if(opt){
        return_value = *opt;         
    }
    
    return return_value;
}

/// @brief Gets an int value from from the config file.
///
/// @param path The section and key of the value wanted.
/// This is given in the format of "section.key" .<br>
///
/// Example of config file: <br>
///     `[SMTP]` <br>
///     `port=587` <br>
///
/// Example of path string: <br>
///     `"SMTP.port"` <br>
///
/// Key returned <br>
///     `587`
///
///
/// @return Int
int config_parser::get_int(std::string path){
    int return_value = -1;

    // Get value from ptree and return it if it exists
    boost::optional<int> opt = tree.get_optional<int>(path);
    if(opt){
        return_value = *opt;         
    }
    
    return return_value;
}

/// @brief Generates a generic config file at the location 
/// supplied to the constructor.
///
/// @return False for success.
bool config_parser::generate_config_file(){
    
    // Open filename
    std::ofstream os (this->filename);
    if(!os.is_open()){
        return true; 
    }
    
    // Insert config values into file
    //      Header
    os << "; Configuration file for pi-door-alarm\n";
    os << "; \n";
    os << "\n";
    
    //      SMTP settings
    os << "\n";
    os << "[SMTP]\n";
    os << "server=smtp.example.com\n";
    os << "port=587\n";
    os << "username=username\n";
    os << "password=password\n";
    os << "connection_timeout_seconds=30\n";
    
    //      email settings
    os << "\n";
    os << "[EMAIL]\n";
    os << "from_address=from@example.com\n";
    os << "to_address=to@example.com\n";
    os << "subject=\"Example email subject\"\n";
    os << "message=\"Example email message\"\n";

    //      Logger settings
    os << "\n";
    os << "[LOG]\n"; 
    os << "log_folder=/var/log/pi-door-alarm/\n";

    //      Footer
    os << "\n";
    os << "\n";

    // Close file
    os.close();
    
    return 0;
}

