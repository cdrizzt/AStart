/* 
    @version : 2021.2.23
    @file    : Node
    @brief   : a* 路径搜索
    @author  : cdrizzt
    @email   : 530102839@qq.com
*/
#ifndef _ASTART_H
#define _ASTART_H
/* Includes ------------------------------------------------------------------*/
#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"


#include <queue>
#include <vector>
/* Class ---------------------------------------------------------------------*/
class _AStartNode{
public:

private:
    _GridPoint2D mapPoint;  //地图坐标
    _AStartNode *parent;    //父节点  用于路径回朔

};
class _AStart{

public:
    //function
    bool Task(void);                    //AStart任务
    void CleanStartPointerAround(void); //清空起点附近障碍物
    
    //variate
    ros::Publisher pub_route;       //路径发布
    ros::Subscriber sub_map;        //地图接收

private:

};


#endif
