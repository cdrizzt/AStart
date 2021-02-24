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
#include "Node.h"
#include "nav_msgs/OccupancyGrid.h"


#include <queue>
#include <vector>
/* Class ---------------------------------------------------------------------*/
class _AStart{

public:
    _AStart(ros::NodeHandle n);
    //task
    bool Task();     //a* 运行任务 true->成功找到路径  false->不可达
    void CleanStartAround(void);    //清除起始点附近的障碍
    void GetNodeMap(void);          //获取节点地图  遍历障碍
    void SetNodeMapWeight(void);    //设置权值地图  离障碍物越近的权值越低
    bool AStart(void);              //开始搜索路径

    void WriteMap(nav_msgs::OccupancyGrid msg);
private:
    nav_msgs::OccupancyGrid map;    //ros地图
};


#endif
