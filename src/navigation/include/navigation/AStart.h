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
    bool Task();        //a* 运行任务 true->成功找到路径  false->不可达
    void SetNodeMap(nav_msgs::OccupancyGrid map);  //设置权值地图

    void SetObsWeight(float weight,float setpSize,int pose);   //权值递减 线性递减
    
private:
    ros::Publisher pub_mapShow;
    nav_msgs::OccupancyGrid mapReal;    //真实地图
    nav_msgs::OccupancyGrid mapShow;    //权值显示地图

    std::vector<_Node> mapNode;         //节点地图
};


#endif
