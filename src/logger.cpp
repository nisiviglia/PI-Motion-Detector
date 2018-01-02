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
/// @file logger.cpp
/// @brief A simple logger.
/// @author Nicholas Siviglia
/// @version 1.0
/// @date 2017-12-30

#define BOOST_LOG_DYN_LINK 1

#include "../include/logger.hpp"
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

/// @brief A simple logger. <br>
///
/// Logs are stored in a folder and are rotated. <br>
/// Log entries are formatted as: <br> 
///     `[TimeStamp][Severity]: [Message]` <br>
///
/// @param folder_path Path to where the log folder will be stored (ex. /var/log/pi-door-alarm/).
logger::logger(std::string folder_path) : folder_path(folder_path){

	logging::register_simple_formatter_factory<
        boost::log::trivial::severity_level, char>("Severity");
    
    logging::add_common_attributes();

    logging::add_file_log(
        keywords::target = this->folder_path, 
            keywords::file_name = "%y%m%d_%3N.log",
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::scan_method = sinks::file::scan_matching,
		keywords::format = "[%TimeStamp%][%Severity%]: %Message%");   
    
	logging::core::get()->set_filter(
		logging::trivial::severity >= logging::trivial::info);
}

/// @brief Log a message with the severity level of info.
///
/// @param msg The message to be stored.
void logger::info(std::string msg){

    BOOST_LOG_TRIVIAL(info) << msg;
}

/// @brief Log a message with the severity level of warning.
///
/// @param msg The message to be stored.
void logger::warning(std::string msg){
    
    BOOST_LOG_TRIVIAL(warning) << msg;
}

/// @brief Log a message with the severity level of error. 
///
/// @param msg The message to be stored.
void logger::error(std::string msg){
    
    BOOST_LOG_TRIVIAL(error) << msg;
}

/// @brief Log a message with the severity level of fatal.
///
/// @param msg The message to be stored.
void logger::fatal(std::string msg){
    
    BOOST_LOG_TRIVIAL(fatal) << msg;
}
