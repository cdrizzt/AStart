/* 
    @version : 2021.2.23
    @file    : Node
    @brief   : a* 路径搜索
    @author  : cdrizzt
    @email   : 530102839@qq.com
*/

/* Includes -----------------------------------------------------------------*/
#include "AStart.h"

/* Define -------------------------------------------------------------------*/
#define WEIGHT_START        (5.0)
#define WEIGHT_STEP_SIZE    (5.0)

/* Function -----------------------------------------------------------------*/
_AStart::_AStart(ros::NodeHandle n)
{
    pub_mapShow = n.advertise<nav_msgs::OccupancyGrid>("mapShow",1,true);
}

void _AStart::SetNodeMap(nav_msgs::OccupancyGrid map)
{
    mapReal = map;  //缓存地图
    mapShow = map;

    _GridPoint2D::SetSize(map.info.width,map.info.height);
    _GridPoint2D::SetOrigin(map.info.width/2,map.info.height/2);
    
    //设置障碍节点地图
    for(int i=0;i<map.data.size();i++){
        if(map.data[i]<49){
            mapShow.data[i] = 0;
            mapNode.push_back(_Node(i,0,false));
        }else{
            mapShow.data[i] = -1;
            mapNode.push_back(_Node(i,0,true));
        }
    }

    startPoint = _Node(-10,10);
    mapShow.data[startPoint.GetNumber()]=-100;

    ROS_INFO("start num %d",startPoint.GetNumber());
    ROS_INFO("x %d y %d",startPoint.point.x,startPoint.point.y);
    

    //添加权值
    for(int i=0;i<mapNode.size();i++){
        if(mapNode[i].CanVisited()){
            //SetObsWeight(WEIGHT_START,WEIGHT_STEP_SIZE,i);
        }
    }


    mapShow.header.stamp=ros::Time::now();
    pub_mapShow.publish(mapShow);
}
void _AStart::SetObsWeight(float weight,float setpSize,int pose)
{
    std::queue<_Node *> nodeList;
    nodeList.push(&mapNode[pose]);
    
    std::vector<_Node> motion = {_Node(1,1) ,_Node(1,0) ,_Node(1,-1),
                                 _Node(0,1) ,            _Node(0,-1),
                                 _Node(-1,1),_Node(-1,0),_Node(-1,-1)};

    while(weight>0)
    {

    }
}