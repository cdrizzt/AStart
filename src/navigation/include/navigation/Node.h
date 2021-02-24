/* 
    @version : 2021.2.23
    @file    : Node
    @brief   : 节点类
    @author  : cdrizzt
    @email   : 530102839@qq.com
*/

#ifndef _NODE_H
#define _NODE_H
/* Includes ------------------------------------------------------------------*/
#include "ros/ros.h"
#incldue "math.h"
/* Class ---------------------------------------------------------------------*/
class _GridPoint2D{
    int x;      //栅格
    int y;

    bool operator==(const _GridPoint2D& rhs){
        return ((x==rhs.x&&y==rhs.y));
    };
    _GridPoint2D& operator+(_GridPoint2D rhs){
        x+=rhs.x;
        y+=rhs.y;
        return *this;
    }
    _GridPoint2D& operator=(_GridPoint2D rhs){
        x=rhs.x;
        y=rhs.y;
        return *this;
    }
    float GetDisFromPoint(_GridPoint2D rhs){
        return (sqrt(pow(x-rhs.x,2)+pow(y-rhs.y,2)));
    }
};
class _Node{
public:
    _Node(int num,int cost);    //设置坐标
    _Node(int num,bool obs);    //设置坐标
    int GetNumber(void);        //获取指针
    bool CanVisited(void);      //未被遍历的
    _Node *GetParent(void);     //返回父节点
    float GetSumCost(void);     //获取总代价   依据总代价  优先遍历
    
    void SetWeight(float data);      //设置权值
    void SetParent(_Node *Node);     //设置父节点
    void SetSumCost(_GridPoint2D goal,flaot startDis);      //计算当前总代价

    bool operator==(const _Node& rhs);
    _Node& operator+=(_Node rhs);
    _Node& operator=(_Node rhs);
    //static
    static void SetMapSize(int size_x,int size_y);  //设置地图大小
private:
    _GridPoint2D mapPoint;  //位于地图的坐标
    _Node *parent;      //父节点  用于路径回朔

    float weight;       //点的权值  距离障碍物递减
    float disFromStart; //走过的步数
    float sumCost;      //总代价 = 点的权值(距离障碍物的距离) + 走过的步数 + 距离终点的直线距离

    bool isVisited;     //已路过
    bool isObstacle;    //障碍物

    static int width;   //宽度
    static int hight    //高度
    static _GridPoint2D 
    int number;         //地图指针
};


#endif

