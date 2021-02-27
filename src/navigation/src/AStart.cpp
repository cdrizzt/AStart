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
#define WEIGHT_STEP_SIZE    (0.4)

/* Function -----------------------------------------------------------------*/
_AStart::_AStart(ros::NodeHandle n)
{
    pub_mapShow = n.advertise<nav_msgs::OccupancyGrid>("mapShow",1,true);
}

void _AStart::SetNodeMap(nav_msgs::OccupancyGrid map)
{
    mapReal = map;  //缓存地图
    mapShow = map;
    mapNode.clear();

    _GridPoint2D::SetSize(map.info.width,map.info.height);
    _GridPoint2D::SetOrigin(-map.info.origin.position.x/0.03,-map.info.origin.position.y/0.03);
    
    //设置障碍节点地图
    for(int i=0;i<map.data.size();i++){
        if(map.data[i]<49){
            mapNode.push_back(_Node(i,0,false,false));
            mapShow.data[i] = 0;    //debug
        }else{
            mapNode.push_back(_Node(i,0,true,false));
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
                //float grade = weight / (sqrt(float(pow(x,2))+float(pow(y,2))) * stepSize);
                float dis = sqrt(float(pow(x,2))+float(pow(y,2)));
                if(dis<stepDis-1)
                {
                    float grade = (stepDis-dis) * stepSize;
                    if(grade > mapNode[number].GetWeight())
                    {
                        mapNode[number].SetWeight(grade);
                        mapShow.data[number] = -(grade*8);
                        
                    }
                }
            }
        }
    }
}

void _AStart::SetGoalPoint(geometry_msgs::PoseStamped goal)
{
    ROS_INFO("x %f y %f",goal.pose.position.x,goal.pose.position.y);
    int goalX = goal.pose.position.x/0.03;
    int goalY = goal.pose.position.y/0.03;

    goalPoint = _Node(goalX,goalY);
    ROS_INFO("goal x%d y%d",goalPoint.point.x,goalPoint.point.y);

    Task();

    mapShow.header.stamp=ros::Time::now();
    pub_mapShow.publish(mapShow);
}

bool _AStart::Task(void)
{
    ROS_INFO("start");
    mapNodeCache = mapNode;

    //清空起始点与目标点附近的障碍信息
    CleanPointAround(mapNodeCache,goalPoint,10);
    CleanPointAround(mapNodeCache,startPoint,20);

    struct cmp //小顶堆  数值小的在前面
    {
        bool operator()(_Node *left,_Node *right)
        {
            return (left->GetSumCost() > right->GetSumCost());
        }
    };
    
    std::priority_queue<_Node *,std::vector<_Node*>,cmp> seachQueue;
    seachQueue.push(&mapNodeCache[startPoint.GetNumber()]);
    mapNodeCache[startPoint.GetNumber()].SetVisited(true);

    _GridPoint2D v1(-1,-1),v2(-1,0),v3(-1,1),\
                 v4(0,-1) ,         v5(0,1),\
                 v6(1,-1) ,v7(1,0) ,v8(1,1);

    std::vector<_Node>motion = {
                                _Node(v2,1),
                                _Node(v4,1),
                                _Node(v5,1),
                                _Node(v7,1),
                                _Node(v3,sqrt(2)),
                                _Node(v1,sqrt(2)),
                                _Node(v6,sqrt(2)),
                                _Node(v8,sqrt(2)),
                                };

    _Node *successGoalPoint = nullptr;

    while(!seachQueue.empty())
    {
        _Node& curPointer = *seachQueue.top();       //获取堆顶指针
        seachQueue.pop();

        if(curPointer==goalPoint){                  //已经搜索到目标点
            successGoalPoint = &curPointer;
            break;
        }

        for(int i=0;i<8;i++)                        //计算当前遍历点的附近8个点代价
        {   
            _Node pose = curPointer;             //暂存当前指针
            pose += motion[i];                   //获取当前需要计算的指针

            _Node tmpNode = mapNodeCache[pose.GetNumber()];
            tmpNode.SetDisFromStart(pose.GetDisFromStart()+1*tmpNode.GetWeight());
    
            if(tmpNode.CanVisited())
            {
                //计算权值
                float cost = 0*tmpNode.GetWeight() + tmpNode.GetDisFromStart() + 0.4*tmpNode.point.GetDisFromPoint(goalPoint.point);

                //写入权值
                tmpNode.SetSumCost(cost);
                tmpNode.SetVisited(true);
                tmpNode.SetParent(&curPointer);
                
                _Node& pointer = mapNodeCache[tmpNode.GetNumber()];
             
                pointer = tmpNode;

                mapShow.data[tmpNode.GetNumber()] = 101;   
                seachQueue.push(&pointer);
            }
        }
        mapShow.header.stamp=ros::Time::now();
        pub_mapShow.publish(mapShow);
    }

    while(successGoalPoint!=nullptr){
        mapShow.data[successGoalPoint->GetNumber()]=-120;
        successGoalPoint = successGoalPoint->GetParent();
    }

    ROS_INFO("end");
    mapShow.header.stamp=ros::Time::now();
    pub_mapShow.publish(mapShow);

}

void _AStart::CleanPointAround(std::vector<_Node>& map,_Node point,int step)
{
     for(int x=-step;x<=step;x++){
        for(int y=-step;y<=step;y++){
            int number = _GridPoint2D(point.point.x+x,point.point.y+y).GetNumber();
            if((sqrt(float(pow(x,2))+float(pow(y,2))))<step){
                map[number].SetWeight(0);
                map[number].SetObstacle(false);
                mapShow.data[number] = 0;
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