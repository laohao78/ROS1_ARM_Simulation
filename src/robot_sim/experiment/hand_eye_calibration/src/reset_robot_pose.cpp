#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <control_msgs/GripperCommandAction.h>
#include <control_msgs/GripperCommandGoal.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <gazebo_msgs/ModelState.h>
#include <geometry_msgs/Pose.h>
#include <gazebo_msgs/SetModelState.h>

// ✅ 如果坚持用 tf（不推荐），必须包含这个头文件
#include <tf/LinearMath/Quaternion.h>

#define pi 3.1415926
#define max_velocity 1
#define max_acceleration 1

void go_home(void)
{
    moveit::planning_interface::MoveGroupInterface group("manipulator");
    robot_state::RobotState current_state(*group.getCurrentState());
    current_state.setToDefaultValues(current_state.getJointModelGroup("manipulator"), "yixiuge_home");
    group.setJointValueTarget(current_state);

    moveit::planning_interface::MoveGroupInterface::Plan my_plan;
    bool success = (group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
    if (success)
        group.execute(my_plan);
}

void move(float x, float y, float z, float roll, float pitch, float yaw)
{
    moveit::planning_interface::MoveGroupInterface group("manipulator");

    geometry_msgs::Pose target_pose;
    tf::Quaternion Q;

    roll = roll / 180.0 * pi;
    pitch = pitch / 180.0 * pi;
    yaw = yaw / 180.0 * pi;
    Q.setRPY(roll, pitch, yaw);
    target_pose.orientation.x = Q.getX();
    target_pose.orientation.y = Q.getY();
    target_pose.orientation.z = Q.getZ();
    target_pose.orientation.w = Q.getW();

    target_pose.position.x = x;
    target_pose.position.y = y;
    target_pose.position.z = z;

    group.setPoseTarget(target_pose);
    group.setMaxVelocityScalingFactor(max_velocity);
    group.setMaxAccelerationScalingFactor(max_acceleration);

    // ✅ 关键修复：MoveGroupInterface::Plan （不是 MoveGroup::Plan）
    moveit::planning_interface::MoveGroupInterface::Plan my_plan;
    bool success = (group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);

    ROS_INFO("Visualizing plan 1 (pose goal) %s", success ? "SUCCESS" : "FAILED");

    if (success)
        group.execute(my_plan);
}

void grasp(float angle)
{
    moveit::planning_interface::MoveGroupInterface gripper_group("gripper");

    std::vector<double> rbq_joint_values;
    const robot_state::JointModelGroup* joint_model_group =
        gripper_group.getCurrentState()->getJointModelGroup(gripper_group.getName());
    gripper_group.getCurrentState()->copyJointGroupPositions(joint_model_group, rbq_joint_values);

    if (rbq_joint_values.size() >= 6) {
        rbq_joint_values[0] = 0;
        rbq_joint_values[1] = 0;
        rbq_joint_values[2] = 0.8f - angle;
        rbq_joint_values[3] = 0;
        rbq_joint_values[4] = 0;
        rbq_joint_values[5] = 0;
    }

    gripper_group.setJointValueTarget(rbq_joint_values);
    gripper_group.setMaxVelocityScalingFactor(max_velocity);
    gripper_group.setMaxAccelerationScalingFactor(max_acceleration);

    moveit::planning_interface::MoveGroupInterface::Plan gripper_plan;
    bool grasp_flag = (gripper_group.plan(gripper_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
    if (grasp_flag)
        gripper_group.execute(gripper_plan);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "movo_moveit");
    ros::NodeHandle node_handle;
    ros::AsyncSpinner spinner(1);
    spinner.start();

    go_home();
    move(-0.143, 0.589, 1.75, 0, 0, 0);
    grasp(0.6);
    grasp(0.8);

    ros::shutdown();
    return 0;
}