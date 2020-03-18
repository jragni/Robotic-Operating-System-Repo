#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "sensor_msgs/LaserScan.h"

// Global Variables
double x;
double y;
double ranges[360];
double intensities[360];

void OdomCallback(const nav_msgs::Odometry::ConstPtr& msg){
    x = msg -> pose.pose.position.x;
    y = msg -> pose.pose.position.y;

    //ROS_INFO("x: %f. y:%f", x, y);
}

void LaserScanCallback(const sensor_msgs::LaserScan::ConstPtr& msg){
    for(int i = 0; i<360;i++){
        ranges[i] = msg ->ranges[i];
        intensities[i] = msg -> intensities[i];
    }
    // for(int i=0; i<360;i++){
    //     ROS_INFO("angle: %d ,range %f",i, ranges[i]);
    // }

    
}

int main(int argc, char** argv){
    // initialize ROS
    ros::init(argc, argv, "Location");

    // Odometry Node
    ros::NodeHandle odometryNode;  //odometry Node
    ros::Subscriber odom_sub = odometryNode.subscribe("odom", 10, OdomCallback);
    // Laser Scan Node;
    ros::NodeHandle laserScanNode;
    ros::Subscriber laser_sub = laserScanNode.subscribe("scan",10,LaserScanCallback);

    ros::spin();
    return 0;
}