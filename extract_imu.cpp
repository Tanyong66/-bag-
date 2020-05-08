#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <vector>
#include <fstream>
#include<iostream>
#include<string>
#include <opencv2/opencv.hpp>
using namespace std;
string yaml;
string IMAGE_TOPIC;
string IMU_TOPIC;
string TIME_PATH;
string IMAGE_PATH;
string IMU_PATH;


void readParameters(ros::NodeHandle &n)
{
    std::string config_file;
    config_file = yaml;
    cv::FileStorage fsSettings(config_file, cv::FileStorage::READ);
    if(!fsSettings.isOpened())
    {
        std::cerr << "ERROR: Wrong path to settings" << std::endl;
    }


    fsSettings["image_topic"] >> IMAGE_TOPIC;
    fsSettings["imu_topic"] >> IMU_TOPIC;
  fsSettings["time_path"] >> TIME_PATH;  
  fsSettings["image_path"] >> IMAGE_PATH;
fsSettings["imu_path"] >> IMU_PATH;
    fsSettings.release();

}


void imu_callback(const sensor_msgs::ImuConstPtr &imu_msg)
{   

  ofstream p;
p.open(IMU_PATH+"data.csv",ios::out|ios::app); 
p << std::setprecision(15);
    double time = imu_msg->header.stamp.toSec();

     	double a_x=imu_msg->linear_acceleration.x;
  	double a_y=imu_msg->linear_acceleration.y;
  	double a_z=imu_msg->linear_acceleration.z;
	double w_x=imu_msg->angular_velocity.x;
	double w_y=imu_msg->angular_velocity.y;
	double w_z=imu_msg->angular_velocity.z;
p<<time<<" "<<w_x<<" "<<w_y<<" "<<w_z<<" "
		<<a_x<<" "<<a_y<<" "<<a_z<<'\n';

}



int main(int argc, char **argv)
{
   yaml=argv[1];
// 初始化ROS节点
    ros::init(argc, argv, "imu_subscriber");

    // 创建节点句柄
    ros::NodeHandle n;
    
	readParameters(n);

cout<<"yaml   "<< yaml<<endl;

ros::Subscriber sub_imu = n.subscribe(IMU_TOPIC, 2000, imu_callback);
    // 循环等待回调函数

    ros::spin();


    return 0;
}
