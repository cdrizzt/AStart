/* 
    @version : 2021.2.23
    @file    : Node
    @brief   : a* 路径搜索
    @author  : cdrizzt
    @email   : 530102839@qq.com
*/

/* Includes ------------------------------------------------------------------*/
#include "AStart.h"

/* Function -----------------------------------------------------------------*/

_AStart::_AStart(ros::NodeHandle n)
{
    
}

void _AStart::WriteMap(nav_msgs::OccupancyGrid msg)
{
    map = msg;
}

/* Task Function -----------------------------------------------------------*/
//任务
bool _AStart::Task()
{

}
