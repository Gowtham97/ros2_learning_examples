from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, EnvironmentVariable

from launch_ros.actions import Node

def generate_launch_description():
    node_prefix_launch_argument = DeclareLaunchArgument("node_prefix", default_value=[EnvironmentVariable("USER"),"_"],
                                                        description="prefix for node")
    
    fixed_broadcaster_node = Node(package="turtle_tf2_py",executable="fixed_frame_tf2_broadcaster",
                                  name=[LaunchConfiguration("node_prefix"),"fixed_broadcaster"])
    
    return LaunchDescription([
        node_prefix_launch_argument,
        fixed_broadcaster_node
    ])