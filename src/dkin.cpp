#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/JointState.h>
#include <visualization_msgs/Marker.h>
#include <math.h>



ros::Publisher pub; 



using namespace std;

double const PI=M_PI;
double 		d1,a2,a3,a4;

void msgReceived(const sensor_msgs::JointState & msg)
{
	geometry_msgs::PoseStamped 	poseStamped;

	double theta,sqr;
	double theta1=msg.position[0];
	double theta2=msg.position[1];
	double theta3=msg.position[2];

	theta=theta2+theta3;
	sqr=sqrt(2)/2;

	poseStamped.header.frame_id="base_link";
	poseStamped.header.stamp = ros::Time::now();

	poseStamped.pose.position.x= (cos(theta1)*(a3*cos(theta2 + theta3) + a2*sin(theta2) + sqr*a4*cos(theta2 + theta3) - sqr*a4*sin(theta2 + theta3)));
	poseStamped.pose.position.y=(sin(theta1)*(a3*cos(theta2 + theta3) + a2*sin(theta2) + sqr*a4*cos(theta2 + theta3) - sqr*a4*sin(theta2 + theta3)));
	poseStamped.pose.position.z=d1 - a3*sin(theta2 + theta3) + a2*cos(theta2) - (sqr*a4*cos(theta2 + theta3)) - (sqr*a4*sin(theta2 + theta3));
	
	poseStamped.pose.orientation.x=0;
	poseStamped.pose.orientation.y=0;
	poseStamped.pose.orientation.z=0;
	poseStamped.pose.orientation.w=0; 


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
