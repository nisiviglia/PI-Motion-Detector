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
/// @file pi_motion_detector.cpp
/// @brief A motion detector with logging and smtp support
/// @author Nicholas Siviglia
/// @version 1.0
/// @date 2018-04-25

#include "../include/alarm.hpp"

int main(int argc, char **argv){
    
    if(argc > 1){
        class alarm al(argv[1]);
        al.run();
    }
    else{
        class alarm al;
        al.run();
    }
     
    return 0;
}
