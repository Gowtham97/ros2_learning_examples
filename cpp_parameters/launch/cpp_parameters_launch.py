from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="cpp_parameters",
            executable="param_node",
            name="custom_param_node",
            output="screen",
            emulate_tty=True,
            parameters=[
                {"my_param" : "earth"}
            ]
        )
    ])