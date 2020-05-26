# gl-streaming

Streaming opengl commands over network

A fast, simple, lightweight and low latency framework suitable for embedded systems. (no X server needed)

> Original image
> ![gl-streaming summary](https://raw.github.com/shodruky-rhyammer/gl-streaming/master/www/gl-streaming_small.png)

![sample-screenshot](https://github.com/khanhduytran0/gl-streaming/raw/master/www/Screenshot_2020-05-19-09-42-24.png)

* gl_client : client framework and sample program
 
  The client system may not need to have any GPU and heavy X server. Even without GPU, opengl programs can be run on any system !
  
  (X Server may be required by some programs).

  Copied from @mittorn fork and do my attempt to run on GL4ES.

* gl_server : server framework
 
  gl_server is optimized for Android for now. Therefore, the client system can use opengl es 2.0.

* android_gl_server : Android demo port app.

## Demo Video (RPi original video)

[Demo Video1](https://youtu.be/6S-Epb6m6mI)

[Demo Video2](https://youtu.be/y0eRwrwetcA)

## Demo Video (Android port)

[Demo Video](https://youtu.be/uwM9uxLHH1M)

## TODO implement
- [ ] glGetActiveUniform
- [ ] glGetError
- [ ] glGetIntegerv
- [ ] glGetFloatv
- [ ] glReadPixels
- [ ] glGetProgramiv
- [x] glGetShaderiv
- [ ] glGetString
- [x] glTexSubImage2D

## Notes
- Current minimum SDK level is set to 21 (Android 5) but it may work on older Android devices by some modify.
- Default port of server: 18145, client: 18146.

## Known issue (Android)
- Rotate screen (change orientation) or put app to background cause app to spawn huge memory usage in a short time.

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
