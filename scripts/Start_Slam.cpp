#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>
// #include <string>

using namespace std;


int main()
{
	string algo;
	cout<<"The SLAM algorithm to be used"<<"\n";
	cin >> algo;

	string algo_list[4] = {"EKF","UKF","EIF","GraphSlam"};

	for(int i=0; i<4; i++){
		string algo_name = algo_list[i];
		if (algo==algo_name)
    	{
    		cout<<algo_name;
    	}
    	cout<<algo_name<<'\n';
	}
    

 	return 0;


}
