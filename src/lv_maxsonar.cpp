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
/// @file lv_maxsonar.cpp
/// @brief API for lv_maxsonar sensor.
/// @author Nicholas Siviglia
/// @version 1.0
/// @date 2018-04-08

#include "../include/lv_maxsonar.hpp"

/// @brief Constructor that initilizes the io and serial port aswell as sets the baud rate.
lv_maxsonar::lv_maxsonar() : io(), serial(io){
    
    serial.open(serial_loc);

    serial.set_option( boost::asio::serial_port_base::baud_rate(baud_rate) );
}

/// @brief Closes the serial connection.
lv_maxsonar::~lv_maxsonar(){
    
    serial.close();
}

/// @brief Reads the disatance from the lv_maxsonar sensor
///
/// @return Integer from 6-255. Zero is returned on error.
int lv_maxsonar::read_distance(){
    
    //Read line from serial port.
    //The documents for the lv_maxsonar sensor's serial output tells us that
    //we'll receive a 'R' followed by three integers
    //and end with a carriage return.
    char ch = ' ';
    std::string line = "";

    while(true){
        
        boost::asio::read(serial, boost::asio::buffer(&ch, 1));
        
        if(ch == '\r' && line.length() > 0){
            break;
        }

        else if( line[0] == 'R' ){
            line += ch;
        }

        else if(ch == 'R'){
            line += ch;
        }
    }

    //If its a valid reading, convert to int
    int distance = 0;
    if(line[0] == 'R'){
        
        distance = std::stoi( line.substr(1) );
    }

    return distance;
}


