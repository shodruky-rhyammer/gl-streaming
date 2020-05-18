# gl-streaming

Streaming opengl commands over network

A fast, simple, lightweight and low latency framework suitable for embedded systems. (no X server needed)

![gl-streaming summary](https://raw.github.com/shodruky-rhyammer/gl-streaming/master/www/gl-streaming_small.png)

* gl_client : client framework and sample program

  The client system does not need to have any GPU and heavy X server. Even without GPU, opengl programs can be run on any system !

* gl_server : server framework

  gl_server is optimized for Android for now. Therefore, the client system can use opengl es 2.0.

## Demo Video (RPi original video)

[Demo Video1](http://youtu.be/6S-Epb6m6mI)

[Demo Video2](http://youtu.be/y0eRwrwetcA)

## Note
Default port of server and client:
+ Server: 18145
+ Client: 18146

## Quick start

### Server

- Build android_gl_server use Android Studio or other similar to.
- Install android_gl_server apk to Android device or Emulator.
- Run it.

### Client

- copy the gl_client directory to any computer.

``cd gl_client``

``make``
    
``./sample1 -s 192.168.0.2:18145 -c 192.168.0.3:18146 -j /dev/input/js0``

``./sample2 -s 192.168.0.2:18145 -c 192.168.0.3:18146 -j /dev/input/js0``

(Usage: ./sampleX [-c my_ip_address:port] [-s server_ip_address:port] [-j joystick_device])

## License

BSD 3-Clause license (except other's source code)

about sample2 camel model:
original model from http://opengameart.org/content/camel
License:CC0 author: noway, sandsound
(Thanks for sharing!)

## Bookmarks
- [Parallella](http://www.parallella.org/)
- [Raspberry Pi](http://www.raspberrypi.org/)

## Special Thanks

Thank you very much for your interest and advices.

- noway @opengameart.org /
- sandsound @opengameart.org /
- GClements @OpenGL forum / 
- The Little Body @OpenGL forum / 
- Stephen A @OpenGL forum / 
- over9000 @Parallella forum / 
- LamsonNguyen @Parallella forum / 
- Gravis @Parallella forum / 
- svartalf @Parallella forum / 
- Raspberry Pi Foundation / 
- Adapteva / 

(c) Shodruky Rhyammer

since Oct 21, 2013
