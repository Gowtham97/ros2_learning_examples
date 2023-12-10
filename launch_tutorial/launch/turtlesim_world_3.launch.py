from os.path import join as JoinPath

from ament_index_python.packages import get_package_share_directory as GetPackPath

from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    config = JoinPath(GetPackPath("launch_tutorial"),"config","turtlesim.yaml")

    turtlesim_node = Node(package="turtlesim",executable="turtlesim_node",name="sim",
                          namespace="turtlesim3",parameters=[config])

    return LaunchDescription([
        turtlesim_node
    ])