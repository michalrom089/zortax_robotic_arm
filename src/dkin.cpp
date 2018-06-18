#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/JointState.h>
#include <visualization_msgs/Marker.h>
#include <math.h>
#include <tf/LinearMath/Matrix3x3.h>


ros::Publisher pub; 



using namespace std;

double const PI=M_PI;
double 		d1,a2,a3,a4;

void msgReceived(const sensor_msgs::JointState & msg)
{
	geometry_msgs::PoseStamped 	poseStamped;

	double theta_23,sqr,const_xy;
	double theta1=msg.position[0];
	double theta2=msg.position[1];
	double theta3=msg.position[2];
	tf::Matrix3x3 rot;
	tf::Quaternion quaternion;
	
	theta_23=theta2+theta3;
	sqr=sqrt(2)/2;
	const_xy=a3*sin(theta_23)+a2*sin(theta2)+sqr*a4*cos(theta_23)+sqr*a4*sin(theta_23);

	poseStamped.header.frame_id="base_link";
	poseStamped.header.stamp = ros::Time::now();

	
	const_xy=a2*sin(theta2)+a3*sin(theta_23)+a4*sin(theta_23+PI/4);
	poseStamped.pose.position.x= cos(theta1)*const_xy;
	poseStamped.pose.position.y= sin(theta1)*const_xy;
	poseStamped.pose.position.z=d1+a2*cos(theta2)+a3*cos(theta_23)+a4*cos(theta_23+PI/4);

	rot.setEulerYPR(theta1,theta2+theta3-PI/4,0);
	rot.getRotation(quaternion);

	poseStamped.pose.orientation.x=quaternion.getX();
	poseStamped.pose.orientation.y=quaternion.getY();
	poseStamped.pose.orientation.z=quaternion.getZ();
	poseStamped.pose.orientation.w=quaternion.getW(); 

	printf("T1: %f \t T2 : %f \t T3 : %f \n",theta1,theta2,theta3);


	pub.publish(poseStamped);
	
	
	
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "DKIN");
	ros::NodeHandle s; 
	ros::Rate 	loop_rate(30);
	

	pub = s.advertise<geometry_msgs::PoseStamped>("zortax_dkin",1);
	ros::Subscriber sub = s.subscribe("/joint_states", 100, msgReceived);

	s.param<double>("d1",d1,1);
    s.param<double>("a2",a2,1);
	s.param<double>("a3",a3,1);
	s.param<double>("a4",a4,1);

	 

	ros::spin();

	return 0;
}
