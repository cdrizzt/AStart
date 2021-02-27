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
_Node::_Node(int num,int cost,bool obs,bool visited)
{
    point = _GridPoint2D(num);
    weight = cost;
    isObstacle = obs;
    isVisited = visited;
    parent = nullptr;
}

_Node::_Node(int x,int y)
{
    point = _GridPoint2D(x,y);
}

_Node::_Node(_GridPoint2D pointInput,float cost)
{
    point = pointInput;
    disFromStart = cost;
}

bool _Node::CanVisited(void)
{
    return (!isVisited&&!isObstacle);
}

bool _Node::IsObstacle(void)
{
    return (isObstacle);
}

_Node* _Node::GetParent(void)
{
    return parent;
}

float _Node::GetWeight(void)
{
    return weight;
}

float _Node::GetDisFromStart(void)
{
    return disFromStart;
}

bool _Node::IsVisited(void)
{
    return isVisited;
}

void _Node::SetObstacle(bool obs)
{
    isObstacle = obs;
}

float _Node::GetSumCost(void)
{
    return sumCost;
}

bool _Node::operator==(const _Node& rhs)
{
    return (point == rhs.point);
}

_Node& _Node::operator+=(_Node rhs)
{
    point += rhs.point;
    disFromStart += rhs.disFromStart;
    return *this;
}

void _Node::SetDisFromStart(float dis)
{
    disFromStart = dis;
}

void _Node::SetWeight(float weight_)
{
    weight = weight_;
}

void _Node::SetVisited(bool visited_)
{
    isVisited = visited_;
}

void _Node::SetParent(_Node *Node)
{
    parent = Node;
}

void _Node::SetSumCost(float cost)
{
    sumCost = cost;
}

int _Node::GetNumber(void)
{
    return (point.GetNumber());
}

