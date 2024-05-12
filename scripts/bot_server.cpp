#include "ros/ros.h"
// #include "slam/" include h file

// will combine server and subscriber
#include "std_msgs/String.h"

void lidarCallback()
{

}

void imuCallback()
{
    
}

void cameraCallback()
{
    
}

void encoderCallback()
{
    
}


int main()
{
    ros::init(argc, argv, "bot_server");
    ros::NodeHandle no;
    ros::Subscriber sub_lidar  = no.subscribe("",100, lidarCallback);
    ros::Subscriber sub_imu    = no.subscribe("", 100, imuCallback);
    ros::Subscriber sub_camera = no.subscribe(" ",100, cameraCallback);
    ros::Subscriber sub_encoder = no.subscribe(" ",100, encoderCallback);
    ros::spin();

    return 0;


}
