#!/bin/sh

remote_server="ubuntu@192.168.32.86"

xterm -e "bash -c '
    ssh $remote_server -t \"
    sleep 5;
    cd catkin_ws;
    source devel/setup.bash
    roscore
    bash -i\"
'"