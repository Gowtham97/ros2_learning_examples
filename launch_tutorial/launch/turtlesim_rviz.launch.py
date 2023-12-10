from os.path import join as JoinPath

from ament_index_python.packages import get_package_share_directory as GetPackPath

from launch import LaunchDescription

from launch_ros.actions import Node

def generate_launch_description():
    rviz_config = JoinPath(GetPackPath("turtle_tf2_py"),"rviz","turtle_rviz.rviz")

    rviz_node = Node(package="rviz2",executable="rviz2",name="rviz2", arguments=["-d", rviz_config])

    return LaunchDescription([
        rviz_node
    ])