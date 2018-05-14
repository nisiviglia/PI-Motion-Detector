# Pi Motion Detector
This uses a Rasperry Pi Zero W combined with a LV-MaxSonar-EZ0 to monitor a door or other area and notify you via email/text when motion is detected.

## Build Instructions
```bash
mkdir build
cd build
cmake ..
make piMotionDetector
./bin/piMotionDetector //this will generate a config file named pmd.cfg. Fill it out.
./bin/piMotionDetector
```
## Required Hardware
### Rasperry PI Zero W
Any model will do. A wireless enabled pi may be helpful to some people. I'll be using the pi zero w.
### LV-MxxSonar-EZ0
* [DataSheet](https://www.pololu.com/file/0J68/LV-MaxSonar-EZ0-Datasheet.pdf)

## Required Libraries
* boost (1.62)
* googletest (1.8.0)

## Rasperry Pi Configuration

## Hardware Configuration




