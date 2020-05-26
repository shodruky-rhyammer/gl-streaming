## Setup streaming environment
### Server setup
- Compile Server using Android Studio.
- Install server APK.
- Enter server port and client address, or leave empty for default values.

### Client setup
```
# Set $PATH_TO_STREAMINGLIB
PATH_TO_STREAMINGLIB=/anywhere/you/want

cd /path/to/android-gl-streaming/gl_client

# Make the client
make

cp libGLESv2.so.2 $PATH_TO_STREAMINGLIB

cd $PATH_TO_STREAMINGLIB

ln -s libGLESv2.so.2 libEGL.so.1

export LD_LIBRARY_PATH=$PATH_TO_STREAMINGLIB:$LD_LIBRARY_PATH
```

## Variables on compile
- (Server) `GL_DEBUG`: enable debug log write to `/sdard/mthr_log.txt`. Disabled by default.
