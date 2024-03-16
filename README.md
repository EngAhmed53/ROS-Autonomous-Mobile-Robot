# Autonomous Navigation Mobile Robot

## Table of Contents

1. [Introduction](#introduction)
2. [Demo](#demo)
3. [Motivations](#motivations)
4. [Roadmap](#roadmap)
5. [Design](#design)
6. [Source Code](#source-code)
7. [License](#license)

## Introduction
This project is based on the Udacity Home Service Robot project, serving as the final project of the Udacity Robotics Nanodegree.

## Demo
Check out the robot demo on this YouTube video.

## Motivations
I embarked on this project for several reasons:
1. To apply the knowledge I gained to real hardware.
2. To enhance my understanding of ROS (Robot Operating System).
3. To observe the robot's behavior in real-world scenarios.

## Roadmap
To complete this project, I divided it into the following steps:
1. Set up Raspberry Pi.
2. Establish SSH connection with Raspberry Pi.
3. Run RPLidar on Raspberry Pi and visualize data on the computer side.
4. Study motor control commands reception on Arduino from Raspberry Pi.
5. Prepare motors on Arduino, control them, and receive encoder readings from each motor.
6. Implement motor speed control using a PID controller.
7. Configure control nodes on Raspberry Pi.
8. Test control nodes using keyboard input.
9. Design and build the robot chassis.
10. Apply necessary changes to mapping nodes.
11. Test map generation for the environment.
12. Implement required changes for navigation nodes.
13. Test robot's autonomous navigation.
14. Enhancements and fixes.

## Design
The robot is a differential drive robot with two wheels at the back and a caster wheel at the front.
The robot's base consists of three layers made from wooden material, separated by 45mm spacers. Each layer accommodates various components:
1. The bottom layer contains motors, an Arduino UNO board, an L298N motor driver, and a breadboard for component interconnection.
2. The middle layer houses the Raspberry Pi 3 Model B and an XL4015 5A Step Down Module to power the Raspberry Pi.
3. The upper layer hosts the RPLidar and the Raspberry Pi Camera v1.

The robot incorporates three sensors:
1. Motor encoders
2. RPLidar
3. Camera

## Source Code
The source code of the project is divided into three parts:
1. [The robot side](/Robot-Local): Primarily operates on a Raspberry Pi 3 running Ubuntu 20.04 (without desktop) with ROS Noetic [download link](https://learn.ubiquityrobotics.com/noetic_pi_image_downloads).
2. [The remote machine side](/Remote-Machine): Also runs on a desktop computer with Ubuntu 20.04 with ROS Noetic.
3. [The Arduino side](https://github.com/EngAhmed53/ROS-Arduino-Bridge): This section manages motor speed based on commands from the Raspberry Pi.

## License
This project is licensed under the [MIT License](LICENSE).
