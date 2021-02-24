/* 
    @version : 2021.2.23
    @file    : Node
    @brief   : 节点类
    @author  : cdrizzt
    @email   : 530102839@qq.com
*/

/* Includes ------------------------------------------------------------------*/
#include "Node.h"

_Node::_Node(int num,int cost)
{
    if(width==0||hight==0){
        while(1){ROS_INFO("nodeMap size 0"); sleep(1);}
    }

    mapPoint.x = (int)(num/width);
    mapPoint.y = (int)(num%width);
    weight = cost;

    isObstacle = false;
    isVisited = flase;
}

_Node::_Node(int num,bool obs)
{
    if(width==0||hight==0){
        while(1){ROS_INFO("nodeMap size 0"); sleep(1);}
    }

    mapPoint.x = (int)(num/width);
    mapPoint.y = (int)(num%width);
    isObstacle = obs;
}

void _Node::SetMapSize(int size_x,int size_y)
{
    width = size_x;
    hight = size_y;
}

bool _Node::operator==(const _Node& rhs)
{
    return (mapPoint == rhs.mapPoint);
}

_Node& _Node::operator+=(_Node rhs)
{
    mapPoint = (rhs.mapPoint + mapPoint);
    return *this;
}
_Node& _Node::operator=(_Node rhs)
{
    mapPoint = rhs.mapPoint;
    return *this;
}

int _Node::GetNumber(void)
{
    return ((mapPoint.x * width + mapPoint.y));
}

bool _Node::CanVisited(void)
{
    return (isVisited && isObstacle);
}

_Node _Node::*GetParent(void)
{
    return parent;
}

float _Node::GetSumCost(void)
{
    return sunCost;
}

void _Node::SetSumCost(_GridPoint2D goal,flaot startDis)
{
    disFromStart += startDis;
    sumCost = disFromStart + mapPoint.GetDisFromPoint(startDis) + weight;
}


