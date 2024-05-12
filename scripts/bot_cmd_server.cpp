#include "ros/ros.h"
// #include "slam/" include h file

// will combine server and subscriber
#include "std_msgs/String.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Point.h"
#include "sensor_msgs/LaserScan"
#include "sensor_msgs/Image"
#include "sensor_msgs/Imu"
#include "geometry_msgs/Twist"

//convert to global
Twist cmd_vel;


void commandCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
    cmd_vel   = msg;
}

bool master_command(slam::FetchCommand::Request &req,slam::FetchSensor::Response &res)
{
    res.u = cmd_vel.linear.x;
    res.v = cmd_vel.angular.z;
    return true;
}


int main()
{
    ros::init(argc, argv, "bot_server");
    ros::NodeHandle cmd_ser;

    // subscriber part
    ros::Subscriber sub_command = cmd_ser.subscribe("/cmd_vel",100, commandCallback);
    
    // service part
    ros::ServiceServer service  = cmd_ser.advertiseService("fetch_command", master_command);
    ros::spin();

    return 0;
}
