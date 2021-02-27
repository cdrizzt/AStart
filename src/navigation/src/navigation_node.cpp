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
#include "nav_msgs/OccupancyGrid.h"
#include "AStart.h"
/* Class ---------------------------------------------------------------------*/
_AStart *aStart;

/* Funciton ------------------------------------------------------------------*/
/**
  * @brief  scanCallBack
  * @note	数据回调
  * @param  None
  * @retval None
*/
void mapCallBack(const nav_msgs::OccupancyGrid::ConstPtr msg)
{
    aStart->SetNodeMap(*msg);
}

void SetGoalPoint(geometry_msgs::PoseStampedPtr ptrGoal)
{
  aStart->SetGoalPoint(*ptrGoal);
}
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

    ros::Rate loop_rate(1);
    aStart = new _AStart(n);

    ros::Subscriber sub_map  = n.subscribe("/map_dis",1,&mapCallBack);    
    ros::Subscriber sub_goal = n.subscribe("/move_base_simple/goal",10,&SetGoalPoint);   
    
    while(ros::ok())
    {
        ROS_INFO("live");
        ros::spinOnce();
        loop_rate.sleep();
    } 

    return 0;
}