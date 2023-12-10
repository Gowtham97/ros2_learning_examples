#! /usr/bin/env python3

import os
import launch_ros
import xacro
import yaml
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
from launch_ros.actions import Node
from launch.launch_description_sources import PythonLaunchDescriptionSource

def generate_launch_description():
  
    # Using the standard Gazebo launch file
    pkg_gazebo_ros = get_package_share_directory('gazebo_ros')
    pkg_share = get_package_share_directory('test_gazebo_sensor_plugin')
    default_model_path = os.path.join(pkg_share, 'urdf/sensor.xacro')

    # Gazebo Server
    gzserver_launch_file = os.path.join(pkg_gazebo_ros, 'launch', 'gzserver.launch.py')
    world_file = os.path.join(get_package_share_directory(
        'test_gazebo_sensor_plugin'), 'worlds', 'test.world')
    gzserver_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(gzserver_launch_file), launch_arguments={
            'world': world_file, 'verbose': 'verbose'}.items())

    # Gazebo Client
    gzclient_launch_file = os.path.join(pkg_gazebo_ros, 'launch', 'gzclient.launch.py')
    gzclient_launch = IncludeLaunchDescription(PythonLaunchDescriptionSource(gzclient_launch_file))
        
    # Generate sonar model
    doc = xacro.process_file(default_model_path)
    robot_desc = doc.toprettyxml(indent='  ')
    sonar_state_publisher_node = launch_ros.actions.Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        parameters=[{'robot_description': robot_desc}])
    
    # Spawn sonar model
    spawn_entity = launch_ros.actions.Node(
    	package='gazebo_ros', 
    	executable='spawn_entity.py',
      arguments=["-entity", "test_plugin", '-topic', 'robot_description'],
      output='screen'
    )
    
    return LaunchDescription([
        DeclareLaunchArgument(name="gui", default_value="true"),
        DeclareLaunchArgument(name="paused", default_value="false"),
        DeclareLaunchArgument(name="manager", default_value="true"),
        DeclareLaunchArgument('use_sim_time',
                              default_value='false',
                              description='Use simulation (Gazebo) clock if true'),
        DeclareLaunchArgument(name='model', default_value=default_model_path),
        DeclareLaunchArgument(name='verbose', default_value="true"),
        gzserver_launch, 
        gzclient_launch, 
        sonar_state_publisher_node,
        spawn_entity
        ])
