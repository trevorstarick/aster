mkdir lib/
mkdir bin/
gcc -DGLEW_NO_GLU -O2 -Wall -W -Iinclude  -DGLEW_BUILD -o src/glew.o -c src/glew.c
gcc -shared -Wl,-soname,libglew32.dll -Wl,--out-implib,lib/libglew32.dll.a    -o lib/glew32.dll src/glew.o -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32

# Create library file: lib/libglew32.dll.a
ar cr lib/libglew32.a src/glew.o

# Create pkg-config file (optional if you just want a lib)
sed \
                -e "s|@prefix@|/usr|g" \
                -e "s|@libdir@|/usr/lib|g" \
                -e "s|@exec_prefix@|/usr/bin|g" \
                -e "s|@includedir@|/usr/include/GL|g" \
                -e "s|@version@|1.6.0|g" \
                -e "s|@cflags@||g" \
                -e "s|@libname@|GLEW|g" \
                < glew.pc.in > glew.pc

gcc -DGLEW_NO_GLU -DGLEW_MX -O2 -Wall -W -Iinclude  -DGLEW_BUILD -o src/glew.mx.o -c src/glew.c
gcc -shared -Wl,-soname,libglew32mx.dll -Wl,--out-implib,lib/libglew32mx.dll.a -o lib/glew32mx.dll src/glew.mx.o -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32

# Create library file: lib/libglew32mx.dll.a
ar cr lib/libglew32mx.a src/glew.mx.o

# Create pkg-config file (optional if you just want a lib)
sed \
                -e "s|@prefix@|/usr|g" \
                -e "s|@libdir@|/usr/lib|g" \
                -e "s|@exec_prefix@|/usr/bin|g" \
                -e "s|@includedir@|/usr/include/GL|g" \
                -e "s|@version@|1.6.0|g" \
                -e "s|@cflags@|-DGLEW_MX|g" \
                -e "s|@libname@|GLEWmx|g" \
                < glew.pc.in > glewmx.pc

# Make the glew visualinfo program. Skip this if you want just the lib
gcc -c -O2 -Wall -W -Iinclude  -o src/glewinfo.o src/glewinfo.c
gcc -O2 -Wall -W -Iinclude  -o bin/glewinfo.exe src/glewinfo.o -Llib  -lglew32 -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32
gcc -c -O2 -Wall -W -Iinclude  -o src/visualinfo.o src/visualinfo.c
gcc -O2 -Wall -W -Iinclude  -o bin/visualinfo.exe src/visualinfo.o -Llib  -lglew32 -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32