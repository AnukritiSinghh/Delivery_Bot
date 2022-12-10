from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument, ExecuteProcess, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch.conditions import IfCondition

from ament_index_python.packages import get_package_share_directory

import os

def generate_launch_description():
    
    enable_recording = LaunchConfiguration('enable_recording')

    return LaunchDescription([

        IncludeLaunchDescription(
            PythonLaunchDescriptionSource([os.path.join(
            get_package_share_directory('turtlebot3_gazebo'), 'launch'),
            '/turtlebot3_world.launch.py'])
        ),

        DeclareLaunchArgument(
            'enable_recording',
            default_value='True'
        ),

        Node(
            package='turtlebot3_walker',
            executable='walker',
            name='walker'
        ),

        ExecuteProcess(
        condition=IfCondition(enable_recording),
        cmd=[
            'ros2', 'bag', 'record', '-o walker_bag', '-a', '-x /camera.+' 
        ],
        shell=True
        )

    ])
