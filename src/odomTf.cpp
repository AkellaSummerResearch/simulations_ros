#include <ros/ros.h>
#include <iostream>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/PositionTarget.h>
#include <unistd.h>
#include <geometry_msgs/Pose.h>
#include <mavros_msgs/CommandTOL.h>
#include <nav_msgs/Odometry.h>
#include <cmath>
#include <tf/transform_broadcaster.h>

using namespace std;

nav_msgs::Odometry odom;

void odom_cb(const nav_msgs::Odometry::ConstPtr& msg)
{
	odom = *msg;
	ROS_INFO("x: %f y: %f x: %f", odom.pose.pose.position.x, odom.pose.pose.position.y, odom.pose.pose.position.z);
	//out << odom << endl;
	geometry_msgs::Pose pose1 =  odom.pose.pose;
	
	static tf::TransformBroadcaster br;
	tf::Transform transform;
	transform.setOrigin( tf::Vector3(pose1->x, pose1->y, 0.0) );
	tf::Quaternion q;
	q.setRPY(0, 0, pose1->theta);
	transform.setRotation(q);
	br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", "odomtransform"));
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "odomTf");
	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe<nav_msgs::Odometry>("/mavros/local_position/odom", 1, odom_cb);
	while(ros::ok())
	{
		ros::spinOnce();
	}
	return 0;
}






