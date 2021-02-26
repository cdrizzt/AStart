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
#include "math.h"


/* Class ---------------------------------------------------------------------*/
class _GridPoint2D
{
public:
    int x;      //栅格
    int y;
    static int width;    //宽度 x
    static int height;   //高度 y
    typedef struct{
        int x;
        int y;
    }_point;
    
    static _point origin;

    _GridPoint2D(void){
        x = 0;y = 0;
    };
    _GridPoint2D(int num){
        num = num < 0 ? 0 : num;
        num = num >  (width)*(height)-1 ? (width)*(height)-1 : num;

        x = -num % width + origin.x;
        y = -num / width + origin.y;
    };
    _GridPoint2D(int x_,int y_){
        y_ = (-y_ + origin.y < 0) ? origin.y : y_;
        y_ = (-y_ + origin.y > height) ? origin.y-height : y_;

        x_ = (-x_ + origin.x < 0) ? origin.x : x_;
        x_ = (-x_ + origin.x > width) ? origin.x-height : x_;

        x = x_;
        y = y_;
    };
    static void SetOrigin(int x_,int y_){
        origin.x = x_;
        origin.y = y_;
        ROS_INFO("origin x %d y %d",origin.x,origin.y);
    };
    static void SetOrigin(int num){
        origin.x = num % width;
        origin.y = num / width;
        ROS_INFO("origin x %d y %d",origin.x,origin.y);
    };
    static void SetSize(int width_,int height_){
        width = width_;
        height = height_;
        ROS_INFO("width %d height %d",width,height);
    };

    bool operator==(const _GridPoint2D& rhs){
        return ((x==rhs.x&&y==rhs.y));
    };
    _GridPoint2D& operator+=(_GridPoint2D rhs){
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
    int GetNumber(void){
        if(width*height==0){
            return 0;
        }
        int yInData = -y + origin.y;
        int xInData = -x + origin.x;

        if(yInData<0){ yInData = 0;}
        else if(yInData>height){ yInData = height;}
    
        if(xInData<0){ xInData = 0;}
        else if(xInData>width){ xInData = width;}

        return (yInData*width + xInData);
    }
};

class _Node
{
public:
    _Node(){};    //设置坐标
    _Node(int num,int cost,bool obs);    //设置坐标
    _Node(int x,int y);    //设置坐标
    bool CanVisited(void);      //未被遍历的
    bool IsObstacle(void);
    _Node* GetParent(void);     //返回父节点
    float GetSumCost(void);     //获取总代价
    float GetWeight(void);      //获取权值
    bool GetVisited(void);      //是否被查阅
        
    bool operator==(const _Node& rhs);
    _Node& operator+=(_Node rhs);

    void SetWeight(float weight_);      //设置权值
    void SetVisited(bool visited);      //设置已被遍历
    void SetParent(_Node *Node);        //设置父节点
    void SetSumCost(_GridPoint2D goal,float startDis);      //计算当前总代价
    
    int GetNumber(void);
    _GridPoint2D point; //地图坐标(栅格)
private:
    
    _Node *parent;      //父节点

    bool isVisited;     //已路过
    bool isObstacle;    //障碍物
    
    float weight;       //点的权值  距离障碍物递减
    float disFromStart; //走过的步数
    float sumCost;      //总代价 = 点的权值(距离障碍物的距离) + 走过的步数 + 距离终点的直线距离
};


#endif

