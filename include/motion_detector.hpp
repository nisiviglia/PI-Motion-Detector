#ifndef MOTION_DETECTOR
#define MOTION_DETECTOR

#include <string>
#include <vector>
#include "../include/lv_maxsonar.hpp"

//! A motion detector that uses the lv_maxsomar sensor to detect motion.
/*! 
  Example usage: 
        
        motion_detector md;

        md.set_detector_distance();
        
        if( md.detect.motion() ){
            
            std::cout << motion detected << std::endl;
        }
*/

class motion_detector : public lv_maxsonar{

    public:
        motion_detector();

        void set_detector_distance();
        
        float get_detector_distance();
        
        void set_detector_sensitivity(float in);

        bool detect_motion();

        std::vector<int> &get_sensor_buffer();

    private:

        float detector_distance = 0;

        int buffer_size = 20;
        
        float sensitivity = .02;

        std::vector<int> sensor_buffer;
};

#endif
