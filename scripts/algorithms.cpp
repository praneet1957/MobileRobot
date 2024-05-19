#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>
#include <vector>
#include "lidar_model.h"
#include "camera.h"
#include <map>
#include <math.h>
#include <matrix>
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Point.h"
#include "sensor_msgs/LaserScan"
#include "sensor_msgs/Image"
#include "sensor_msgs/Imu"
#include <cstdlib>
#include <ctime>

using namespace std

class Algorithm{
	Public:
		float T;
		float motion_model();
        float sensor_model();
		float jacob_motion_model();
		float jacob_sensor_model();
    

	Private:
		float lidar_model();
		float camera_model();
		float imu_model();
		float encoder_model();
}

// state space will be X = [x,y,theta ]

float Algorithm::motion_model(Bot &bot){
	bot.pos.x = bot.pos.x + bot.pose.vx*T;
	bot.pos.y = bot.pos.y + bot.pose.vy*T;
	bot.pos.theta = bot.pos.theta + bot.pos.w*T;
	bot.pos.vx = bot.command.v*cos(bot.pos.theta);
	bot.pos.vy = bot.command.v*sin(bot.pos.theta);
	bot.pos.w  = bot.command.v*tan(bot.command.steer)/bot.L;
    
    return 0;
    // Need to add noise

}

vector<float> Algorithm::sensor_model(Bot &bot){
	vector<float> Z;
	float* Xc, Xi, Xe, Xl;
	
	Xc = this-> camera_model(&bot);
	Xi = this-> imu_model(&bot);
	Xe = this-> encoder_model(&bot);
	Xl = this-> lidar_model(&bot);

	int len_Xc = *(&Xc + 1) - Xc;

	for (int i=0;i<len_Xc;i++)
	{
		Z.push_back(*(Xc+i));
	}

	int len_Xi = *(&Xi + 1) - Xi;

	for (int i=0;i<len_Xi;i++)
	{
		Z.push_back(*(Xi+i));
	}

	int len_Xe = *(&Xe + 1) - Xe;

	for (int i=0;i<len_Xe;i++)
	{
		Z.push_back(*(Xe+i));
	}

	int len_Xl = *(&Xl + 1) - Xl;

	for (int i=0;i<len_Xl;i++)
	{
		Z.push_back(*(Xl+i));
	}

	//should output the observation variables either h(x)
	return Z;
}


float Algorithm::camera_model(Bot &bot){
    float u,v;
	float res[];
	u = c1 + (1+k1*r)*fx*x/z;
	v = c2 + (1+k2*r)*fy*y/z;
	res = {u,v};
	return res; 
}

float Algorithm::imu_model(Bot &bot){
    float imu_sens[];
	float wz = bot.pos.w;
	float ax = (bot.pos.vx - bot.pos.prev.vx)/T;
	float ay = (bot.pos.vy - bot.pos.prev.vy)/T;
    imu_sens = {wz, ax, ay};
	return imu_sens;
}

float Algorithm::lidar_model(Bot &bot){
	float lid_val[];
	return lid_val = {x,y};
}

float Algorithm::jacob_motion_model(Bot &bot){
// need to hardcode the jacob model y = C_x
    float jacob_motion[];
	jacob_motion = {
					{ 1, 0, -bot.command.v*T*sin(bot.pos.theta), 0, 0, 0},
					{ 0, 1, bot.command.v*T*cos(bot.pos.theta), 0, 0, 0},
					{ 0, 0, 1, 0, 0, 0},
					{ 0, 0, -bot.command.v*T*sin(bot.pos.theta), 0, 0, 0},
					{ 0, 0, bot.command.v*T*cos(bot.pos.theta), 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0}
					}

	return jacob_motion
}



float Algorithm::jacob_sensor_model(Bot &bot){
// need to hardcode the sensor model
	float jacob_sensor[];
	jacob_sensor =  {
					{  };  //leaving for camera
					{  }; //leaving for camera
					{1, 0, 0, 0, 0, 0, 0},
					{0, 1, 0, 0, 0, 0, 0},
					{0, 0, 1, 0, 0, 0, 0},
					{0, 0, 0, 1, 0, 0, 0},
					{0, 0, 0, 0, 1, 0, 0},
					{0, 0, 0, 0, 0, 1, 0},
					{0, 0, 0, 0, 0, 0, 1}
	}
	return jacob_sensor;
}

