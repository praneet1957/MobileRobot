#include "ros/ros.h"
// #include "slam/"
#include <cstdlib>
#include "std_msgs/String.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Point.h"
#include "sensor_msgs/LaserScan"
#include "sensor_msgs/Image"
#include "sensor_msgs/Imu"



LaserScan laser;
Image     img;
Imu       inertia;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "bot_client");
    ros::NodeHandle n;
    ros::ServiceClient client= n.serviceClient<slam::FetchSensor>("fetch_sensor");
    slam::FetchSensor srv;
    srv.request.a = atoll(argv[1]);

    if (client.call(srv))
    {
        laser  = srv.response.laser;
        img    = srv.response.img;
        inertia= srv.response.inertia;
    }
    else
    {
        ROS_ERROR("Failed to call service add_two_ints");
        return 1;
    }
    return 0;

}