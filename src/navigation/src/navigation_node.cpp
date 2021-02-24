/* 
    @version : 2021.2.18
    @file    : navigation_node
    @brief   : 导航节点
    @author  : cdrizzt
    @email   : 530102839@qq.com
*/
/* Includes ------------------------------------------------------------------*/
#include "ros/ros.h"
#include "std_msgs/String.h"
/* Funciton ------------------------------------------------------------------*/
/**
  * @brief  main
  * @note	main
  * @param  None
  * @retval None
*/
int main(int argc, char **argv)
{
    ros::init(argc,argv,"navigaiton_node");  //创建节点

    ros::NodeHandle n;  //创建句柄
    ROS_INFO("start");

    
    
    while(ros::ok())
    {
      ros::spinOnce();
    } 

    return 0;
}