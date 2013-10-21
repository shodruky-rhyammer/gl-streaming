# gl-streaming

Streaming opengl commands over network

A fast, simple, lightweight and low latency framework suitable for embedded systems. (no X server needed)

![gl-streaming summary](https://raw.github.com/shodruky-rhyammer/gl-streaming/master/www/gl-streaming_small.png)

* gl_client : client framework and sample program

  The client system does not need to have any GPU and heavy X server. Without GPU, opengl programs can be run on any system !

* gl_server : server framework

  gl_server is optimized for Raspberry Pi for now. Therefore, the client system can use opengl es 2.0.

## Demo Video

[Demo Video](http://youtu.be/6S-Epb6m6mI)

## Quick start

connect RPi and the client system with a ethernet cable. (straight cable is ok)

connect RPi to a display with HDMI cable. (yes, RPi do it)

copy the gl_server directory to RPi.

``cd gl_server``
    
(edit IP address in main.c for now ;-) set_server_address() for RPi's address, set_client_address() for the client system's address.)
    
``make``
    
``./gl_server``

copy the gl_client directory to any computer.

``cd gl_client``
    
(edit IP address in main.c. ALERT!! set_server_address() for the client system's address, set_client_address() for RPi's address.)

``make``
    
``./gl_client``

## Licence

BSD 3-Clause licence (except other's source code)

(c) Shodruky Rhyammer
since Oct 21, 2013
