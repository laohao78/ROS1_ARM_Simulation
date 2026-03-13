#!/usr/bin/env python3

import rospy
import subprocess
import time
from gazebo_msgs.msg import ModelStates

def wait_for_model(model_name, timeout=10):
    rospy.init_node('wait_for_model', anonymous=True)
    start = time.time()
    rospy.loginfo(f"Waiting for model '{model_name}' to appear in Gazebo...")
    while not rospy.is_shutdown() and (time.time() - start) < timeout:
        try:
            msg = rospy.wait_for_message('/gazebo/model_states', ModelStates, timeout=1.0)
            if model_name in msg.name:
                rospy.loginfo(f"Model '{model_name}' found!")
                return True
        except:
            pass
    rospy.logwarn(f"Timeout waiting for model '{model_name}'")
    return False

def spawn_model(file_path, model_name, args=""):
    cmd = ["rosrun", "gazebo_ros", "spawn_model", "-file", file_path, "-model", model_name] + args.split()
    rospy.loginfo(f"Spawning {model_name}: {' '.join(cmd)}")
    subprocess.run(cmd)

if __name__ == '__main__':
    robot_sim_path = subprocess.getoutput('rospack find robot_sim')

    # 1. Spawn table
    spawn_model(
        f"{robot_sim_path}/grasp/urdf/table_marble/model.sdf",
        "table",
        "-sdf -x 0.0 -y 1.13 -z 0.0"
    )

    # 2. Wait for table
    if not wait_for_model("table", timeout=5):
        rospy.logerr("Failed to detect table! Aborting.")
        exit(1)

    # 3. Spawn other objects
    time.sleep(0.5)
    spawn_model(f"{robot_sim_path}/grasp/urdf/block.sdf", "box", "-sdf -x -0.13 -y 0.75 -z 1.2 -Y 2.2")
    spawn_model(f"{robot_sim_path}/grasp/urdf/coke_can/model.sdf", "coke", "-sdf -x -0.22 -y 0.88 -z 1.1 -R 1.57 -Y -0.3665")
    spawn_model(f"{robot_sim_path}/grasp/urdf/dropbox.urdf", "dropbox", "-urdf -x -0.5 -y 0.25 -z 1.1 -Y 1.57")
    spawn_model(f"{robot_sim_path}/grasp/urdf/banana.sdf", "banana", "-sdf -x -0.1 -y 0.65 -z 1.1 -R 1.57 -Y 2.2")

    rospy.loginfo("All objects spawned!")