from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

from launch_ros.actions import Node

def generate_launch_description():

    target_frame_launch_argument = DeclareLaunchArgument("target_frame",default_value="turtle_1",
                                                         description="Target frame name")
    
    broadcaster_node_1 = Node(package="turtle_tf2_py", executable="turtle_tf2_broadcaster", name="broadcaster1",
                              parameters=[{"turtlename": "turtle1"}])
    
    broadcaster_node_2 = Node(package="turtle_tf2_py", executable="turtle_tf2_broadcaster", name="broadcaster2",
                              parameters=[{"turtlename" : "turtle2"}])
    
    listener_node = Node(package="turtle_tf2_py",executable="turtle_tf2_listener", name="listener",
                         parameters=[{"target_frame" : LaunchConfiguration("target_frame")}])
    
    return LaunchDescription([
        target_frame_launch_argument,
        broadcaster_node_1,
        broadcaster_node_2,
        listener_node
    ])