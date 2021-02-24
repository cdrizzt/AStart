/* 
    @version : 2021.2.23
    @file    : AStart Node
    @brief   : a* 节点
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
/* Struct --------------------------------------------------------------------*/
typedef struct _GridPoint2D{
    int x;
    int y;
}_GridPoint2D;

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
    void SetNodeMap(void);              //设置node地图
    //variate
    ros::Publisher pub_route;       //路径发布
    ros::Subscriber sub_map;        //地图接收

private:

};


#endif
