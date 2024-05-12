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

//convert to global
LaserScan laser;
Image     img;
Imu       inertia;



void lidarCallback(const sensor_msgs::LaserScan::ConstPtr& msgl)
{
    laser   = msgl;
}

void imuCallback(const sensor_msgs::Imu::ConstPtr& msgi)
{
    inertia = msgi;
}

void cameraCallback(const sensor_msgs::Image::ConstPtr& msgc)
{
    img     = msgc;
}

// void encoderCallback()
// {
// pko   
// }


bool master_sensor(slam::FetchSensor::Request &req,
                   slam::FetchSensor::Response &res)
{
    res.laser   = laser;
    res.img     = img;
    res.inertia = inertia;
    return true;
}


int main()
{
    ros::init(argc, argv, "bot_server");
    ros::NodeHandle sen_ser;

    // subscriber part
    //ros::Subscriber sub_command = no.subscribe("/cmd_vel",100, commandCallback);
    ros::Subscriber sub_lidar   = sen_ser.subscribe("/slam_bot/laser/scan",100, lidarCallback);
    ros::Subscriber sub_imu     = sen_ser.subscribe("/imu",100, imuCallback);
    ros::Subscriber sub_camera  = sen_ser.subscribe("/slam_bot/camera/image_raw",100, cameraCallback);
    ros::Subscriber sub_encoder = sen_ser.subscribe("",100, encoderCallback);

    // service part
    ros::ServiceServer service  = sen_ser.advertiseService("fetch_sensor", master_sensor);
    ros::spin();

    return 0;

}
