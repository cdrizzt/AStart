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
#define WEIGHT_START        (10.0)
#define WEIGHT_STEP_SIZE    (1.0)

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
            mapNode.push_back(_Node(i,0,false));
            mapShow.data[i] = 0;    //debug
        }else{
            mapNode.push_back(_Node(i,0,true));
            mapShow.data[i] = -1;   //debug
        }
    }

    for(int i=0;i<mapNode.size();i++){
        if(mapNode[i].IsObstacle()){
            SetObsWeight(WEIGHT_START,WEIGHT_STEP_SIZE,i);
        }
    }
   
    mapShow.header.stamp=ros::Time::now();
    pub_mapShow.publish(mapShow);
}

void _AStart::SetObsWeight(float weight,float stepSize,int pose)
{
    int step = weight / stepSize;
    float stepDis =  weight / stepSize;

    _GridPoint2D origin(pose);

    for(int x=-step;x<=step;x++){
        for(int y=-step;y<=step;y++){
            int number = _GridPoint2D(origin.x+x,origin.y+y).GetNumber();
            if(mapNode[number].IsObstacle()==false)
            {
                float grade = weight / (sqrt(float(pow(x,2))+float(pow(y,2))) * stepSize);
                if(grade > mapNode[number].GetWeight())
                {
                    mapNode[number].SetWeight(grade);
                    mapShow.data[number] = -(grade*12);
                }
            }
        }
    }
}
#if 0
//bfs参考
void _AStart::SetObsWeight(float weight,float setpSize,int pose)
{
    std::queue<_Node *> nodeList;
    std::queue<_Node *> nodeVistsedList;

    nodeList.push(&mapNode[pose]);
    nodeVistsedList.push(&mapNode[pose]);

    //设置膨胀方向
    std::vector<_Node> motion = {_Node(1,1) ,_Node(1,0) ,_Node(1,-1),
                                 _Node(0,1) ,            _Node(0,-1),
                                 _Node(-1,1),_Node(-1,0),_Node(-1,-1)};

    while(weight>0)
    {
        int circuCnt = nodeList.size();
        for(int cnt = circuCnt;cnt>0;cnt--)
        {
            _Node *origin = nodeList.front();
            ROS_INFO("x %d y%d",origin->point.x,origin->point.y);
            origin->SetVisited(true);
            nodeList.pop();

            for(int i=0;i<8;i++)
            {
                _Node pointer=*origin;
                pointer+=motion[i]; //
                int number = pointer.GetNumber();
                if(mapNode[number].GetVisited()==false)
                {
                    nodeList.push(&mapNode[number]);
                }
                
                if(mapNode[number].IsObstacle()==false)
                {
                    if(mapNode[number].GetWeight()<weight){
                        mapNode[number].SetWeight(weight);
                        mapShow.data[number] = -80 ;   //debug
                    }
                }
            }
        }

        weight -= setpSize;
    }

}
#endif