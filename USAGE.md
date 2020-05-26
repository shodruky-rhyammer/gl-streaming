## Setup streaming environment
### Server setup
- Compile Server using Android Studio.
- Install server APK.

### Client setup
```
# Set $PATH_TO_STREAMINGLIB
PATH_TO_STREAMINGLIB=/anywhere/you/want

cd /path/to/android-gl-streaming/gl_client

# Make the client
make

cp libGLESv2.so.2 $PATH_TO_STREAMINGLIB

# Copy GL4ES into
cp /path/to/gl4es/build/lib/libGL.so.1 $PATH_TO_STREAMINGLIB

cd $PATH_TO_STREAMINGLIB

ln -s libGLESv2.so.2 libEGL.so.1

# Override system libGLESv2.so.2, libEGL.so.1 and libGL.so.1
export LD_LIBRARY_PATH=$PATH_TO_STREAMINGLIB:$LD_LIBRARY_PATH
```

## Launch streaming!
### Launch server
- Do as title: Launch server.
- Enter server port and client address, or leave empty for default values.

### Launch client
- Test: run `es2_info, es2gears, es2tri, glxinfo, glxgears, glxdemo or glxheads`
- Run an OpenGL Native Program or Java Program.

## Variables on compile
- (Server) `GL_DEBUG`: enable debug log write to `/sdard/mthr_log.txt`. Disabled by default.
