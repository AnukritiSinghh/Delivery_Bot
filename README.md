# Delivery_Bot
## A service bot delivering food in restaurant using ROS2 

[![Build Status](https://github.com/AnukritiSinghh/Delivery_Bot/actions/workflows/build_and_coveralls.yml/badge.svg)](https://github.com/AnukritiSinghh/Delivery_Bot/actions/workflows/build_and_coveralls.yml)
[![Coverage Status](https://coveralls.io/repos/github/AnukritiSinghh/Delivery_Bot/badge.svg?branch=master)](https://coveralls.io/github/AnukritiSinghh/Delivery_Bot?branch=master

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

## Team
For phase 1:
1) Anukriti Singh (driver) 
2) Joshua Arup Gomes (navigator)  
3) Mayank Sharma (design keeper)
For phase 2:
1) Anukriti Singh (navigator)
2) Joshua Arup Gomes (driver)
3) Mayank Sharma (design keeper)

## Overview

In the foodservice industry it has become incedibly challenging to deliver food and beverages seamlessly and efficiently, every day. Humans tend to get distracted and tired, they also need break and holidays. However, this all can be avoided by using the state of the art technology. With delivery robots, the orders can be delivered to the custromors with precision and effeciency. We are using ros2 turtlebot to achieve this task. 

## Deliverables
* Project: Project is search and deliver robot for restaruant dining
* Overview of prosposed work
* UML and activity diagrams
* Developer-level documentation

## Screenshot Capture 
In results folder as !!!!!!!!!!Rvis_Gazebo_Driver_capture.png!!!!!!!!!
## Dependencies with licenses
* Apache 2 License
* ROS Humble/Foxy 
* Turtlebot2 
* Gazebo 
* GTest

## Development Process
Following the Agile Iterative Process for Development, we switch roles of driver, navigator and design keeper. 
* Product backlog, iteration backlog and worklog:  [here](https://docs.google.com/spreadsheets/d/1dZ-y45_AL5Mc8_DbIJrSJJ0H6H_2HLId_zzahEZlHxE/edit#gid=2139171243) 
* Sprint planning: [here](https://docs.google.com/document/d/1f-xjoKFd7hRqJ0oETVylUt3rAWTCG6LZAqg9HKFyrsw/edit)

## Enviroment

## Static Code analysis
* Cppcheck results can be found [here]()
* Cpplint results can be found [here]()

## Installation



may not require but if any issues is run into do the following !!!required dependencies!!!??????

---
In your workspace src folder(EX: /ros_ws/src) download the final tag (Phase 3)  

After downloading the repo onto the source folder, build it and launch the turtlebot3 into our custom test world
```
colcon build
. install/setup.bash 
export TURTLEBOT3_MODEL=burger
ros2 launch Delivery_Bot obstacle_course.launch.py
```
To spawn at a specific point, such as (0,0), enter the following command
```
ros2 launch Delivery_Bot obstacle_course.launch.py x_pose:=0 y_pose:=0
````
---
To run RVIS2 and the cartographer

```
#In a new terminal in your workspace
. install/setup.bash 
export TURTLEBOT3_MODEL=burger
ros2 launch Delivery_Bot cartographer.launch.py \
use_sim_time:=True
```
---
To run the obstacle avoidance program
```
#In a new terminal in your workspace
. install/setup.bash 
export TURTLEBOT3_MODEL=burger
ros2 launch Delivery_Bot  hamburger_walker.launch.py
```
To enable a ROSbag recording
```
ros2 launch Delivery_Bot  hamburger_walker.launch.py enable_recording:=True
```
---
The Hamburger is now moving around the world, creating a map   
To save the map, enter the following command map
```
ros2 run nav2_map_server map_saver_cli -f obstacle_sample_map
```
---
Using the created map, the user now can use RVIS to set the desired endpoint of a turtlebot, assuming a complete map is taken

```
#Close all terminals and spawn in the Hamburger back into gazebo
colcon build
. install/setup.bash 
export TURTLEBOT3_MODEL=burger
ros2 launch Delivery_Bot obstacle_course.launch.py
```
Run Rvis with the map 

```
#In a new terminal in your workspace
. install/setup.bash 
export TURTLEBOT3_MODEL=burger
ros2 launch Delivery_Bot cartographer.launch.py\
use_sim_time:=true map:=maps/"you map name".yaml
```

The user can denote the end and start point for the Hamburger in RVIS 



## Known issues
--
!!!!!!!!!!!!!!!!
could not make own rvis launch file, had issues finding turtlebot3_lds_2d.lua,
reliant on turtlbot source code 
--
colcon build --packages-select hamburger_cartographer 
this sample map is create from purely the autonomous driving 
although incomplete, this map is created automatically 
of course, one could manually controll the turtle bot to move it around and record a more accurate
downside, a robot might be forever stuck in a room
future development

if for some reason RVIS doesnt accept the recorded map enter the following 
```
ros2 launch turtlebot3_navigation2 \
navigation2.launch.py \
use_sim_time:=true map:=maps/"you map name".yaml
```
