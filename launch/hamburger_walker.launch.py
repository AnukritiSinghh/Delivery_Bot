
# Copyright 2022
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Authors: Mayank Sharma, Joshua Gomez, Anukriti Singh


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


        DeclareLaunchArgument(
            'enable_recording',
            default_value='False'
        ),

        Node(
            package='Delivery_Bot',
            executable='hamburger_drive',
            name='hamburger_drive'
        ),

        ExecuteProcess(
        condition=IfCondition(enable_recording),
        cmd=[
            'ros2', 'bag', 'record', '-o walker_bag', '-a'
        ],
        shell=True
        )

    ])
