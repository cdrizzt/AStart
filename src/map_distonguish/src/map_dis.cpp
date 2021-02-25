/* 
    @version : 2021.2.18
    @file    : map_dis_node
    @brief   : 地图处理节点
    @author  : cdrizzt
    @email   : 530102839@qq.com
*/
/* Includes ------------------------------------------------------------------*/
#include "map_dis.h"
#include "stb_image.h"

/* Define --------------------------------------------------------------------*/


/* Funciton ------------------------------------------------------------------*/
_MapDis::_MapDis(ros::NodeHandle n)
{
    pub_map = n.advertise<nav_msgs::OccupancyGrid>("map_dis",1, true);
    
    map.header.frame_id="map";
    map.header.seq=1000;
    map.header.stamp=ros::Time::now();

    map.info.resolution = 0.03; //分辨率 3cm一格;

    map.data.clear();           //清空地图
}

void _MapDis::MapGetPointer(int num,int *x,int *y)
{
    *x = num/map.info.width;
    *y = num%map.info.width;
}

void _MapDis::DrawPointer(int x,int y,float R,nav_msgs::OccupancyGrid &map_cache)
{
    int dis = (int)(R/0.03);
    int startX = x-dis;
    int startY = y-dis; 

    startX = startX<0 ? 0:startX;
    startY = startY<0 ? 0:startY;

    int endX = x+dis;
    int endY = y+dis;
    endX = endX>map_cache.info.height-1 ? map_cache.info.height-1:endX;
    endY = endY>map_cache.info.width-1 ? map_cache.info.width-1:endY;

    for(int i=startX;i<=endX;i++){
        for(int j=startY;j<=endY;j++){
            if(sqrt(float(pow(i-x,2))+float(pow(j-y,2)))<R/0.03)
            {
                map_cache.data[i*map_cache.info.width+j]=101;
            }
        }
    }
}

bool _MapDis::LoadMap(const std::string &address)
{
    ROS_INFO("load map from png");
    std::string file = address + ".png";

    if (access(file.c_str(), F_OK) != 0){
        ROS_INFO("load fail");
        return false;
    }

    int w,h,n;
    const uint8_t *data = stbi_load(file.c_str(), &w, &h, &n, 0);
    
    map.info.width = w;        //宽
    map.info.height = h;       //高

    map.info.origin.position.x = -(float(w/2))*0.03;
    map.info.origin.position.y = -(float(h/2))*0.03;

    ROS_INFO("w:%d h:%d n:%d",w,h,n);
    ROS_INFO("origin x %f,origin y %f",map.info.origin.position.x,map.info.origin.position.y);
    
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            uint8_t dataFromPng = data[i*w+j];
            int8_t result = dataFromPng;
            if(dataFromPng>127){
                float tmp = ((float)(dataFromPng - 0x7f)/127.0)*50.0;
                result = (int8_t)tmp;
            }else{
                float tmp= (1.0-(float)(dataFromPng)/127.0)*50+50;
                result = (int8_t)tmp;
            }

            map.data.push_back(result);
        }
    }

    ROS_INFO("finish size %d",map.data.size());

    //膨胀地图
    nav_msgs::OccupancyGrid map_cache = map;
    for(int i=0;i<map.data.size();i++)
    {
        if(map.data[i]>50)
        {
            int x=0,y=0;
            MapGetPointer(i,&x,&y);   //获取坐标
            DrawPointer(x,y,0.25,map_cache);        
        }
    }
    map = map_cache;
    map.header.stamp=ros::Time::now();
    pub_map.publish(map);
}

void _MapDis::MapPublish(void)
{
    map.header.stamp=ros::Time::now();
    pub_map.publish(map);
}