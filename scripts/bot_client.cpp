#include "ros/ros.h"
// #include "slam/"
#include <cstdlib>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "bot_client");
    ros::NodeHandle n;
    ros::ServiceClient client= n.serviceClient<slam::fetchsensor>("fetch_sensor");
    slam::fetchsensor srv;
    srv.request.a = atoll(argv[1]);

    if (client.call(srv))
    {
        srv.response()
    }
    else
    {
        ROS_ERROR("Failed to call service add_two_ints");
        return 1;
    }
    return 0;



}