from os.path import join as JoinPath

from ament_index_python.packages import get_package_share_directory as GetPackPath

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription,GroupAction
from launch.launch_description_sources import PythonLaunchDescriptionSource

from launch_ros.actions import PushRosNamespace

LAUNCH_DIR = JoinPath(GetPackPath("launch_tutorial"),"launch")

def form_include_launch_description(launch_file_name,launch_arguments={}):
    return IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            JoinPath(LAUNCH_DIR, launch_file_name)
        ]),
        launch_arguments=launch_arguments.items()
    )

def generate_launch_description():

    turtlesim_world_1 = form_include_launch_description("turtlesim_world_1.launch.py")

    turtlesim_world_2 = form_include_launch_description("turtlesim_world_2.launch.py")

    turtlesim_world_2_with_namespace = GroupAction(actions=[PushRosNamespace("turtlesim2"),turtlesim_world_2])

    broadcast_listener_nodes = form_include_launch_description("broadcaster_listener.launch.py",
                                                               {"target_frame": "carrot1"})

    mimic_node = form_include_launch_description("mimic.launch.py")

    fixed_frame_node = form_include_launch_description("fixed_broadcaster.launch.py")

    rviz_node = form_include_launch_description("turtlesim_rviz.launch.py")

    return LaunchDescription([
        turtlesim_world_1,
        turtlesim_world_2_with_namespace,
        broadcast_listener_nodes,
        mimic_node,
        fixed_frame_node,
        rviz_node
    ])