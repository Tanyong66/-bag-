
#include <sensor_msgs/Image.h>
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <vector>
#include<iostream>
#include <fstream>
#include<string>
#include <sstream>
#include <stdio.h>
using namespace std;
vector<double> image_times;
vector<cv::Mat> images;
vector<double> imu_times;
vector<double> a_x;
vector<double> a_y;
vector<double> a_z;
vector<double> w_x;
vector<double> w_y;
vector<double> w_z;

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
int i=0;
void imageCallback(const sensor_msgs::ImageConstPtr &img_msg)
{

	cv_bridge::CvImageConstPtr ptr;
   ptr = cv_bridge::toCvCopy(img_msg, img_msg->encoding);
   cv::Mat show_img = ptr->image;

string str1,image_path;
stringstream ss1;
ss1 << i;
ss1 >> str1;
i++;
image_path=IMAGE_PATH + str1 + ".png";
cv::imwrite(image_path,show_img);
}




int main(int argc, char **argv)
{
    //if ( argc != 2 )
   // {
   //     cout<<"usage: no path of  .yaml "<<endl;
   //     return 1;
   // }
   yaml=argv[1];
// 初始化ROS节点
    ros::init(argc, argv, "image_subscriber");

    // 创建节点句柄
    ros::NodeHandle n;
    
	readParameters(n);

cout<<"IMAGE_PATH   "<< yaml<<endl;

    // 创建一个Subscriber，订阅名为/turtle1/pose的topic，注册回调函数poseCallback
    ros::Subscriber image_sub = n.subscribe(IMAGE_TOPIC, 5000, imageCallback);

    // 循环等待回调函数

    ros::spin();


    return 0;
}
