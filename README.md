# Streaming Video Over UDP
**Experimenting with OpenCV
~~~~~~~~~~~~~~~~~~~~~~~~
Ubuntu 15.04 (Vivid Vervet)
OpenCV v3.0
g++ v4.9.2
make v4.0 

Motivation:
~~~~~~~~~~~
Was bitten by a c++ bug on labor day and felt the need to learn about sockets and play with opencv.

![alt tag](https://github.com/Andymic/Streaming-Video-Over-UDP/kitkat.gif)

Instructions:
~~~~~~~~~~~~
1-Grab a video and change 'vid_path' in kitkat.cc to point to video file
2-Update 'PROJECT_PATH' in makefile to your local directory **update to point to the opencv libs as well
3-cd in the core directory
4-Use 'make K' to build 
5-Do './K server' in one terminal to spin up server
6-Do './K client' to spin up the client in a different terminal
