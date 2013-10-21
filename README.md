gl-streaming
============

Streaming opengl commands over network

A simple,lightweight and low latency framework suitable for embedded systems. (no X server needed)

* gl_client : client framework and sample program

  The client system does not need to have any GPU and heavy X server. Without GPU, opengl programs can be run on any system !

* gl_server : server framework

  gl_server is optimized for Raspberry Pi for now. Therefore, the client system can use opengl es 2.0.

Quickstart
----------

connect RPi and the client system with a ethernet cable. (straight cable is ok)

connect RPi to a display with HDMI cable. (yes, RPi do it)

copy the gl_server directory to RPi.

    cd gl_server
    
    (edit IP address in main.c for now ;-))
    
    make
    
    ./gl_server

copy the gl_client directory to any computer.

    cd gl_client
    
    (edit IP address in main.c for now ;-))

    make
    
    ./gl_client

