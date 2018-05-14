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
/// @file motion_detector.cpp
/// @brief detects motion via lv_maxsonar.
/// @author Nicholas Siviglia
/// @version 1.0
/// @date 2018-04-09

#include <iostream>
#include <cmath>

#include "../include/motion_detector.hpp"

/// @brief Standard Constructor. Sets the Vector to the correct size.
motion_detector::motion_detector(){
    
    this->sensor_buffer.resize(this->buffer_size);
}

/// @brief Sets the lock distance by taking multiple samples and calculating their sum.
void motion_detector::set_detector_distance(){

    float sum = 0;

    for(int i=0; i < this->buffer_size; i++){
        this->sensor_buffer[i] = this->read_distance();
        sum += sensor_buffer[i];
    }

    this->detector_distance = sum / this->buffer_size;
}

/// @brief Returns the distance that the detector is locked onto.
///
/// @return float detector_distance.
float motion_detector::get_detector_distance(){
    
    return this->detector_distance;
}

/// @brief Sets the sensitivity to motion.
///
/// @param in float number from 1 being high to 0.01 being the lowest.
void motion_detector::set_detector_sensitivity(float in){
    
    this->sensitivity = in;
}

/// @brief Takes a sample and calculates the distance. If this does not exceed the sensitivity setting it returns false. 
///
/// @return bool.
bool motion_detector::detect_motion(){

    //Make sure the lock distance is a valid one.
    //As per the lv_maxsonar documentation, the sensor will report
    //anything closer than 6 inches as a distance of 6. Therefore a 
    //detector_distance of less than 6 is invalid.
    if(this->detector_distance < 6){
        this->set_detector_distance(); 
    }

    if(this->detector_distance < 6){
        std::cout << "error getting valid lock distance" << std::endl;
        exit(-1);
    }
    
    //Take sample and calculate sum
    float sum = 0.0;
    for(int i=0; i < buffer_size; i++){

        this->sensor_buffer[i] = this->read_distance();
        sum += sensor_buffer[i];
    }

    float sum_avg = sum / this->buffer_size;
    
    //Check for unacceptable difference
    if( (std::abs(detector_distance - sum_avg) / detector_distance) > sensitivity ){
        
        return true;
    }
    
    return false;
}

/// @brief This is a vector that keeps the values used in the last sensor sample.
///
/// @return a reference to the vector sensor_buffer
std::vector<int> &motion_detector::get_sensor_buffer(){

    return this->sensor_buffer; 
}
