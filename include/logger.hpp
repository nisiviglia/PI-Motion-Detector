#ifndef PI_DOOR_ALARM_LOGGER
#define PI_DOOR_ALARM_LOGGER

#include<string>

//! A simple logger.
/*! 
  Example usage to create a log folder and add an entry:

       logger log("test_logs/"); 
       
       log.info("this is a test message");

 Example of the log entry:

       [2017-12-30 08:11:13.225028][info]: this is a test message 

*/
class logger{

    public:

        logger(std::string filename);

        void info(std::string msg);

        void warning(std::string msg);

        void error(std::string msg);

        void fatal(std::string msg);

    private:

        std::string folder_path;
};

#endif
