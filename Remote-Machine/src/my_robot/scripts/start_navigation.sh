#!/bin/sh

remote_server="ubuntu@192.168.99.86"

xterm -hold -e "ssh $remote_server -t '
    source ../../etc/ubiquity/env.sh;
    cd catkin_ws/;
    source devel/setup.bash;
    roslaunch robot_control diff_controller.launch --wait;'
" &


# xterm -hold -e "ssh $remote_server -t '
#     source ../../etc/ubiquity/env.sh;
#     cd catkin_ws/;
#     source devel/setup.bash;
#     rosrun teleop_twist_keyboard teleop_twist_keyboard.py --wait;'
# " &

xterm -hold -e "ssh $remote_server -t '
    source ../../etc/ubiquity/env.sh;
    cd catkin_ws/;
    source devel/setup.bash;
    roslaunch my_robot robot_description.launch --wait;'
" &

xterm -hold -e "ssh $remote_server -t '
    source ../../etc/ubiquity/env.sh;
    cd catkin_ws/;
    source devel/setup.bash;
    roslaunch rplidar_ros rplidar_a1.launch --wait;'
" &

sleep 3 &

xterm -hold -e "source ~/.bashrc; source devel/setup.bash; roslaunch my_robot amcl.launch;" &

sleep 3 &

xterm -hold -e "source ~/.bashrc; source devel/setup.bash; roslaunch my_robot view_navigation.launch;"
