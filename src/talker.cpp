#include "ros/ros.h"
#include "std_msgs/String.h"

int main(int argc, char **argv){
    ros::init(argc,argv,"talker");  // initialize node

    ros::NodeHandle n;  // creates a handle for node
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter",1000);
    ros::Rate loop_rate(10);
    


    return 0;
}