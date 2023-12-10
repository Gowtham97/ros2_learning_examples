from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    listener_node = Node(
        package="cpp_pubsub",
        executable="listener",
        name="cpp_subscriber_node"
    )

    return LaunchDescription([
        listener_node
    ])