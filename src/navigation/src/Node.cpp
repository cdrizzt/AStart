/* 
    @version : 2021.2.23
    @file    : Node
    @brief   : 节点类
    @author  : cdrizzt
    @email   : 530102839@qq.com
*/

/* Includes ------------------------------------------------------------------*/
#include "Node.h"
int _GridPoint2D::width = 0;
int _GridPoint2D::height = 0;
_GridPoint2D::_point _GridPoint2D::origin={0};
/* Function -----------------------------------------------------------------*/
_Node::_Node(int num,int cost,bool obs)
{
    point = _GridPoint2D(num);
    weight = cost;
    isObstacle = obs;
}

_Node::_Node(int x,int y)
{
    point = _GridPoint2D(x,y);
}

bool _Node::CanVisited(void)
{
    return (isVisited&&isObstacle);
}

bool _Node::IsObstacle(void)
{
    return (isObstacle);
}

_Node* _Node::GetParent(void)
{

}

float _Node::GetSumCost(void)
{

}

bool _Node::operator==(const _Node& rhs)
{
    return (point == rhs.point);
}

_Node& _Node::operator+=(_Node rhs)
{
    point += rhs.point;
    return *this;
}



void _Node::SetWeight(float weight)
{

}

void _Node::SetParent(_Node *Node)
{

}

void _Node::SetSumCost(_GridPoint2D goal,float startDis)
{

}

int _Node::GetNumber(void)
{
    return (point.GetNumber());
}

