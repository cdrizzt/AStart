/* 
    @version : 2021.2.18
    @file    : map_dis_node
    @brief   : 地图处理节点
    @author  : cdrizzt
    @email   : 530102839@qq.com
*/
/* Includes ------------------------------------------------------------------*/
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "map_dis.h"
/* Funciton ------------------------------------------------------------------*/
/**
  * @brief  main
  * @note	main
  * @param  None
  * @retval None
*/
int main(int argc, char **argv)
{
    ros::init(argc,argv,"map_dis_node");  //创建节点

    ros::NodeHandle n;  //创建句柄

    ros::Rate loop_rate(10000);

    ROS_INFO("start");

    _MapDis map(n);
    map.LoadMap("/home/nick/map_test/map");
  
    while(ros::ok())
    {      
      map.MapPublish();
      ros::spinOnce();
      loop_rate.sleep();
    } 

    return 0;
}

