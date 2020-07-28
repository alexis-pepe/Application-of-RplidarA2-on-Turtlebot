#include <iostream>
#include <cmath>
#include <vector>
#include "math.h"
#include <list>
#include <string>
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include <fstream>
#define RAD2DEG(x) ((x)*180./M_PI)

using namespace message_filters;
using namespace std;

void scanCallback1(const sensor_msgs::LaserScan::ConstPtr& scan1)
{
    std::vector<double> laser_x;
    std::vector<double> laser_y;
    double pr;
    int count1 = scan1->scan_time / scan1->time_increment;
    for(int i = 0; i < count1; i++){

      float pt = RAD2DEG(scan1->angle_min + scan1->angle_increment * i);
      pr = scan1->ranges[i];

        if(isnormal(pt)&&isnormal(pr))
        {
            
	laser_x.push_back( pt );
	laser_y.push_back( pr );

	ROS_INFO(": [%f, %f]", pt, pr);
        }
      }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "rplidar_c");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("/scan_filtered",100, scanCallback1);
    ros::spin();

    return 0;

}

   
