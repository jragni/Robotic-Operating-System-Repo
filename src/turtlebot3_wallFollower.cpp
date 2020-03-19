#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include <vector>
// Global Variables
double x;
double y;
double ranges[360];
double intensities[360];
double rightDistance;
double leftDistance;
double frontDistance;
double backDistance;
double right;
double left;
double back;
double front;
double PI = 3.14159;

void OdomCallback(const nav_msgs::Odometry::ConstPtr& msg){
    x = msg -> pose.pose.position.x;
    y = msg -> pose.pose.position.y;

    //ROS_INFO("x: %f. y:%f", x, y);
}

double setDefaultDistance(double dist){
    if(dist > 3){
        dist = 3.02;
    }
    return dist; 
}

void laserScan(const sensor_msgs::LaserScan::ConstPtr& msg){
    for(int i = 0; i<360;i++){
        ranges[i] = msg ->ranges[i];
        intensities[i] = msg -> intensities[i];
    }
    
    rightDistance = ranges[270];  
    leftDistance = ranges[90]; 
    frontDistance = ranges[0];  
    backDistance = ranges[180];
    right = setDefaultDistance(rightDistance);
    left = setDefaultDistance(leftDistance);
    front = setDefaultDistance(frontDistance);
    back = setDefaultDistance(backDistance);
    // ROS_INFO("front %f: left: %f right: %f back: %f",frontDistance,leftDistance,rightDistance,backDistance);

}




int main(int argc, char** argv){
    // initialize ROS
    ros::init(argc, argv, "Location");

    // Velocity Node
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel",1000);
    ros::Rate loop_rate(10);
    geometry_msgs::Twist VEL;
    // Odometry Node
    ros::NodeHandle odometryNode;  //odometry Node
    ros::Subscriber odom_sub = odometryNode.subscribe("odom", 10, OdomCallback);
    // Laser Scan Node;
    ros::NodeHandle laserScanNode;
    ros::Subscriber laser_sub = laserScanNode.subscribe("scan",10,laserScan);
    while(ros::ok()){

        if(front > 0.22){
            VEL.linear.x = .2;
        }
        else{
            VEL.linear.x = 0;
            VEL.angular.z = PI/12;
            ros::Duration(6).sleep();
            
        }
        pub.publish(VEL);

        ros::spinOnce();
        loop_rate.sleep();


    }

    return 0;
}