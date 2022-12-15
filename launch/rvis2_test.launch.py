# Copyright 2022
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Authors: Mayank Sharma, Joshua Gomez, Anukriti Singh
import os

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.conditions import IfCondition, UnlessCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import Command, LaunchConfiguration, PythonExpression
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from ament_index_python import get_package_share_directory
from launch.actions import TimerAction


def generate_launch_description():

  # Set the path to different files and folders.
  Delivery_Bot_dir = FindPackageShare(package='Delivery_Bot').find('Delivery_Bot')
  rviz_file_name = 'tb3_cartographer.rviz'
  #rviz_file_name = 'tb3_gazebo.rviz' 
  default_rviz_config_path = os.path.join(Delivery_Bot_dir, 'rviz', rviz_file_name)

  rviz_config_file = LaunchConfiguration('rviz_config_file')

  declare_rviz_config_file_cmd = DeclareLaunchArgument(
    name='rviz_config_file',
    default_value=default_rviz_config_path)

  # RVIS2
  start_rviz_cmd = Node(
    package='rviz2',
    executable='rviz2',
    name='rviz2',
    output='screen',
    arguments=['-d', rviz_config_file])

  ld = LaunchDescription()
 
  ld.add_action(declare_rviz_config_file_cmd)
 
  ld.add_action(start_rviz_cmd)

  return ld
