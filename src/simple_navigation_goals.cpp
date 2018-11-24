#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <iostream>
#include <array>

float map_resolution = 0.05;
int pixel_x = 480;
int pixel_y = 512;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
	
      int x = pixel_x * map_resolution;
      int y = pixel_y * map_resolution;
 
      int size_x = x/2.2;
      int size_y = y/2;

      int x_pos[50] = {0, size_x, size_x, -size_x, -size_x, size_x, size_x, -size_x, -size_x, size_x, size_x, -size_x, -size_x, size_x, size_x, -size_x, -size_x, size_x, size_x, -size_x, -size_x, size_x, size_x, -size_x, -size_x}; 
      int y_pos[50] = {0, 0, -1, -1, -2, -2, -3, -3, -4, -4, -5, -5, -6, -6, -7, -7, -8, -8, -9, -9, -10, -10, -11, -11, -12, -12, 12, 12, 11, 10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 0};
      int z_pos[50] = {0, -1, 1, -1, 0, -1, 1, -1, 0, -1, 1, -1, 0,-1, 1, -1, 0, -1, 1, -1, 0, -1, 1, -1, 0, -1, 1, -1, 0, -1, 1, -1, 0, -1, 1, -1, 0, -1, 1, -1, 0, -1, 1, -1, 0, -1, 1, -1, 0, -1};
      int w_pos[50] = {1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1};

      int lenght0f_Array = sizeof(x_pos) / sizeof(x_pos[0]);

      int main(int argc, char** argv){

	ros::init(argc, argv, "simple_navigation_goals");
	
        //tell the action client that we want to spin a thread by default
        MoveBaseClient ac("move_base", true);

        //wait for the action server to come up
        while(!ac.waitForServer(ros::Duration(1.0))){
           ROS_INFO("Waiting for the move_base action server to come up");
        }

        move_base_msgs::MoveBaseGoal goal;

        goal.target_pose.header.frame_id = "/map";
        goal.target_pose.header.stamp = ros::Time::now();
        for( int i = 0; i < lenght0f_Array; i = i + 1 ) {
		
          goal.target_pose.pose.position.x = x_pos[i];
          goal.target_pose.pose.position.y = y_pos[i];
          goal.target_pose.pose.orientation.w = w_pos[i];
	  goal.target_pose.pose.orientation.z = z_pos[i];
            ROS_INFO("Sending goal");
	    ROS_INFO("Posicion %d%d%d%d", x_pos[i],y_pos[i], z_pos[i], w_pos[i]);
          ac.sendGoal(goal);

          ac.waitForResult();

         if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
            ROS_INFO("Goal aceptado, moviendose" );
	else
            ROS_INFO("Error, goal inaceptable");
         }


      return 0;
}

