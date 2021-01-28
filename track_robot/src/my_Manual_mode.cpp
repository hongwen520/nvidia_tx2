#include "ros/ros.h"
#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <iostream> 
#include "conio.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Float64.h"
#include <dynamixel_workbench_msgs/JointCommand.h>

#define PI 3.14

int vv1 = 1000, vv2 = 1000, y = 0;
int act;       
float topp = 0, bottomm = -20;       

int main(int argc, char **argv)
{

    printf("|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|\n");
    printf("|---------------Keyboard Command Manual----------------|\n");
    printf("|------------------------------------------------------|\n");
    printf("|--------------------Robot control---------------------|\n");
    printf("|    ↑ : robot forward     |      ↓ : robot back       |\n");
    printf("|    → : robot right       |      ← : robot left       |\n");
    printf("|    space : robot stop    |                           |\n");
    printf("|------------------------------------------------------|\n");
    printf("|---------------------Foot control---------------------|\n");
    printf("|      a : forefoot up     |     z : forefoot down     |\n");
    printf("|      s : hindfoot up     |     x : hindfoot down     |\n");
    printf("|------------------------------------------------------|\n");
    printf("|--------------------Speed control---------------------|\n");
    printf("|   f : normal speed (1000) |  r : reset speed (350)   |\n");
    printf("|   u : add speed (+500)    |  y : reduce speed (-500) |\n");
    printf("|   e : exit the system     |                          |\n");
    printf("|------------------------------------------------------|\n");
    printf("|-------------------Camera control---------------------|\n");
    printf("|   o : camera turn up    |    l : camera turn down    |\n");
    printf("|   p : camera turn right |    i : camera turn left    |\n");
    printf("|   9 : camera return     |                            |\n");
    printf("|______________________________________________________|\n");

	ros::init(argc, argv, "Manual_mode");
  	ros::NodeHandle n;
	ros::Publisher pub1 = n.advertise<std_msgs::Int32MultiArray>("robot_speed", 100);
	ros::Publisher pub2 = n.advertise<std_msgs::Int32MultiArray>("leg_speed", 100);
	ros::Publisher pub3 = n.advertise<std_msgs::Int32MultiArray>("robot_MA", 100);
	ros::Publisher pub4 = n.advertise<std_msgs::Int32MultiArray>("leg_MA", 100);
	ros::Publisher pub5 = n.advertise<std_msgs::Int32MultiArray>("robot_HO", 100);
	ros::Publisher pub6 = n.advertise<std_msgs::Int32MultiArray>("robot_VA", 100);

	ros::Publisher pub7 = n.advertise<std_msgs::Int32>("robot_motion", 100);
	ros::Publisher pub8 = n.advertise<std_msgs::Int32>("leg_motion", 100);

	ros::Publisher pub9 = n.advertise<std_msgs::Int32MultiArray>("leg_HO", 100);
	ros::Publisher pub10 = n.advertise<std_msgs::Int32MultiArray>("leg_VA", 100);
	ros::Publisher pub11 = n.advertise<std_msgs::Int32MultiArray>("robot_MR", 100);

	ros::Publisher pub12 = n.advertise<std_msgs::Float64>("head_top", 100);
	ros::Publisher pub13 = n.advertise<std_msgs::Float64>("head_bottom", 100);

	ros::ServiceClient joint_command_client = n.serviceClient<dynamixel_workbench_msgs::JointCommand>("joint_command");
		
	ros::Rate loop_rate(100);
    
    while(ros::ok())
	{
		std_msgs::Int32MultiArray robot_speed, leg_speed, robot_MA, leg_MA, robot_HO, robot_VA, robot_MR, leg_HO, leg_VA;
		std_msgs::Int32 robot_motion, leg_motion;
		std_msgs::Float64 head_top, head_bottom;
		dynamixel_workbench_msgs::JointCommand joint_command;

		robot_speed.data.clear();
		leg_speed.data.clear();
		robot_MA.data.clear();
		leg_MA.data.clear();
		robot_HO.data.clear();
		robot_VA.data.clear();
		robot_MR.data.clear();

        y = getch();      // ASCII keyboard

        if(y == 32)       //"space"
            {
                int rm = 0;
                robot_motion.data = rm;
                pub7.publish(robot_motion);
                ros::spinOnce();
            }
        else if(y == 65)      //"↑"
            {
                int rm = 1;
                robot_motion.data = rm;
                pub7.publish(robot_motion);
                ros::spinOnce();
            }
        else if(y == 66)      //"↓"
            {
                int rm = 2;
                robot_motion.data = rm;
                pub7.publish(robot_motion);
                ros::spinOnce();
            }
        else if(y == 68)      //"←"
            {
                int rm = 3;
                robot_motion.data = rm;
                pub7.publish(robot_motion);
                ros::spinOnce();
            }
        else if(y == 67)      //"→"
            {
                int rm = 4;
                robot_motion.data = rm;
                pub7.publish(robot_motion);
                ros::spinOnce();
            }
        else if(y == 97 || y == 65) //"A"
            {  
                int lm = 1;
                leg_motion.data = lm;
                pub8.publish(leg_motion);
                ros::spinOnce();
            }
        else if(y == 122 || y == 90)//Z
            {  
                int lm = 2;
                leg_motion.data = lm;
                pub8.publish(leg_motion);
                ros::spinOnce();
            }
        else if(y == 83 || y == 115)//S
            {
                int lm = 3;
                leg_motion.data = lm;
                pub8.publish(leg_motion);
                ros::spinOnce();
            }
        else if(y == 120 || y == 88)//X
            {
                int lm = 4;
                leg_motion.data = lm;
                pub8.publish(leg_motion);
                ros::spinOnce();   
            }
    //-------------------------------------------------------
        else if(y == 114 || y == 82)//R reset speed
            {
                int rs[2];//robot_speed
                int ls[2];//leg_speed
                rs[0]=350;
                rs[1]=350;
                ls[0]=1000;
                ls[1]=1000;

                for (int i = 0; i < 2; i++)
                {
                    robot_speed.data.push_back(rs[i]);
                    leg_speed.data.push_back(ls[i]);
                }

                pub1.publish(robot_speed);
                pub2.publish(leg_speed);
                ros::spinOnce();
                vv1=350;
                vv2=350;
            }

        else if(y == 102 || y == 70)//F fast speed
            {
                int rs[2];//robot_speed
                int ls[2];//leg_speed
                rs[0]=1000;
                rs[1]=1000;
                ls[0]=1000;
                ls[1]=1000;

                for (int i = 0; i < 2; i++)
                {
                    robot_speed.data.push_back(rs[i]);
                    leg_speed.data.push_back(ls[i]);
                }

                pub1.publish(robot_speed);
                pub2.publish(leg_speed);         
                ros::spinOnce();
                vv1=1000;
                vv2=1000;
            }
        else if(y == 85 || y == 117)//U add speed
            {
                if(vv1<30000)
                    vv1+=500;
                if(vv2<30000)
                    vv2+=500;
                
                    int rs[2];//robot_speed
                    
                    rs[0]=vv1;
                    rs[1]=vv2;

                    for (int i = 0; i < 2; i++)
                    {
                        robot_speed.data.push_back(rs[i]);
                    }
                    pub1.publish(robot_speed); 
                    ros::spinOnce();

                    if (act == 1)
                    {
                        int rm=1;//robot_motion
                        robot_motion.data=rm;
                        pub7.publish(robot_motion);
                        ros::spinOnce();
                    }		
                    else if (act == 2)
                    {
                        int rm=2;//robot_motion
                        robot_motion.data=rm;
                        pub7.publish(robot_motion);
                        ros::spinOnce();
                    }
                    else if (act == 3)
                    {
                        int rm=3;//robot_motion
                        robot_motion.data=rm;
                        pub7.publish(robot_motion);
                        ros::spinOnce();
                    }
                    else if (act == 4)
                    {
                        int rm=4;//robot_motion
                        robot_motion.data=rm;
                        pub7.publish(robot_motion);
                        ros::spinOnce();
                    }
                    else if (act == 0)
                    {						
                        int rm=0;//robot_motion
                        robot_motion.data=rm;
                        pub7.publish(robot_motion);
                        ros::spinOnce();
                    }

            }
            else if (y == 121)//y slow down
            {
                if (vv1>1000)
                    vv1 -= 500;
                if (vv2>1000)
                    vv2 -= 500;
    //------------------------------------------			
                //bodyJOGvel(vv1, vv2);
                int rs[2];//robot_speed  
                rs[0]=vv1;
                rs[1]=vv2;
                for (int i = 0; i < 2; i++)
                {
                    robot_speed.data.push_back(rs[i]);
                }
                pub1.publish(robot_speed);             
                ros::spinOnce();
    //------------------------------------------		
                    
                    if (act == 1)
                    {
                        int rm=1;//robot_motion
                        robot_motion.data=rm;
                        pub7.publish(robot_motion);
                        ros::spinOnce();
                    }		
                    else if (act == 2)
                    {
                        int rm=2;//robot_motion
                        robot_motion.data=rm;
                        pub7.publish(robot_motion);
                        ros::spinOnce();
                    }
                    else if (act == 3)
                    {
                        int rm=3;//robot_motion
                        robot_motion.data=rm;
                        pub7.publish(robot_motion);
                        ros::spinOnce();
                    }
                    else if (act == 4)
                    {
                        int rm=4;//robot_motion
                        robot_motion.data=rm;
                        pub7.publish(robot_motion);
                        ros::spinOnce();
                    }
                    else if (act == 0)
                    {						
                        int rm=0;//robot_motion
                        robot_motion.data=rm;
                        pub7.publish(robot_motion);
                        ros::spinOnce();
                    }
            }

        else if(y == 101 || y == 69)//E end for break
        {
            break;
        }

        else if(y == 106)// J
            {
                int l_MA[2];//leg_MA
                    
                l_MA[0]=-26000;
                l_MA[1]=-27000;
                for (int i = 0; i < 2; i++)
                {
                    leg_MA.data.push_back(l_MA[i]);
                }
                pub4.publish(leg_MA);    
                ros::spinOnce();          

        }
        

            else if(y == 57)//9	xtion return home
            {
                bottomm=-1;topp=0;
                joint_command.request.unit = "rad";
                joint_command.request.id = 1;
                joint_command.request.goal_position = bottomm*PI/180;
                joint_command_client.call(joint_command);
                joint_command.request.unit = "rad";
                joint_command.request.id = 2;
                joint_command.request.goal_position = topp*PI/180;
                joint_command_client.call(joint_command);
                ros::spinOnce();
            }
            else if(y == 105)//i	xtion turn left
            {	
                bottomm=bottomm+10;
                joint_command.request.unit = "rad";
                joint_command.request.id = 1;
                joint_command.request.goal_position = bottomm*PI/180;
                joint_command_client.call(joint_command);
                joint_command.request.unit = "rad";
                joint_command.request.id = 2;
                joint_command.request.goal_position = topp*PI/180;
                joint_command_client.call(joint_command);
                ros::spinOnce();
            }
            else if(y == 112)//p	xtion turn right
            {	
                bottomm=bottomm-10;
                joint_command.request.unit = "rad";
                joint_command.request.id = 1;
                joint_command.request.goal_position = bottomm*PI/180;
                joint_command_client.call(joint_command);
                joint_command.request.unit = "rad";
                joint_command.request.id = 2;
                joint_command.request.goal_position = topp*PI/180;
                joint_command_client.call(joint_command);
                ros::spinOnce();
            }
            else if(y == 111)//o	xtion turn up
            {
                topp=topp-10;
                joint_command.request.unit = "rad";
                joint_command.request.id = 1;
                joint_command.request.goal_position = bottomm*PI/180;
                joint_command_client.call(joint_command);
                joint_command.request.unit = "rad";
                joint_command.request.id = 2;
                joint_command.request.goal_position = topp*PI/180;
                joint_command_client.call(joint_command);
                ros::spinOnce();
            }
            else if(y == 108)//l	xtion turn down
            {
                topp=topp+10;
                joint_command.request.unit = "rad";
                joint_command.request.id = 1;
                joint_command.request.goal_position = bottomm*PI/180;
                joint_command.request.unit = "rad";
                joint_command.request.id = 2;
                joint_command.request.goal_position = topp*PI/180;
                joint_command_client.call(joint_command);
                ros::spinOnce();
            }
            printf("\rRobot Speed = %d, Camera pose top = %f, Camera pose bottom = %f",vv1,topp,bottomm);
            fflush(stdout);
            
            loop_rate.sleep();
            
        }

	return 0;
}