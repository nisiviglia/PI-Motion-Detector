#ifndef LV_MAXSONAR
#define LV_MAXSONAR 

#include <string>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>

//! API for the LV-MaxSonar sensor.
/*! 
  Remember to disable tty console via 'sudo raspi-config'.

  Example usage: <br> 
    
       lv_maxsonar sensor; 

       int test_distance = sensor.read_distance();

       std::cout << test_distance << std::endl;

*/

class lv_maxsonar{

    public:
        lv_maxsonar();

        ~lv_maxsonar();

        int read_distance();

    private:
        boost::asio::io_service io;

        boost::asio::serial_port serial;

        //This is the alias for the tty RX on raspberry pi 
        std::string serial_loc = "/dev/serial0";

        unsigned int baud_rate = 9600;
};

#endif
