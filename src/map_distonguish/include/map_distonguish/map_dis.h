/* 
    @version : 2021.2.18
    @file    : map_dis
    @brief   : 地图类
    @author  : cdrizzt
    @email   : 530102839@qq.com
*/
#ifndef _MAP_DIS_H
#define _MAP_DIS_H
/* Includes ------------------------------------------------------------------*/
#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"

/* Class ---------------------------------------------------------------------*/
class _MapDis{
public:
    _MapDis(ros::NodeHandle n);
    bool LoadMap(const std::string &address);     //读取地图
    void MapPublish(void);                        //地图发布
    void MapGetPointer(int num,int *x,int *y);
    void DrawPointer(int x,int y,float dis,nav_msgs::OccupancyGrid &map_cache);
private:
    ros::Publisher pub_map;
    nav_msgs::OccupancyGrid map;
};

#endif
