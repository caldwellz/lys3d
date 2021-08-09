# Lys3D

An experiment in indie 3D game engine design. The current plan is to implement a lightweight GLES2 backend that falls back to regular OpenGL 2.0+ when needed, while also leaving open the possibility of other backend options (Vulkan, etc.) in the future.

### Requirements

At the moment, Lys3D uses the Meson build system and depends on SDL2, SDL2_image, PhysFS, and your platform's OpenGL / GLES libraries (although it uses its own GL headers).  
On Debian-based systems (including Ubuntu), usually this means you just need to have a C++ compiler of your choice installed (clang or g++) and then from the project directory, run:
```
sudo apt install meson libsdl2-dev libsdl2-image-dev libphysfs-dev
meson build
cd build
ninja install
```

### What's with the name?

Lys means 'light' and is also the abbreviated symbol for 'light years'. The terrible pun behind this is that Lys3D intends to provide dynamic lighting (among other things) to the applications built upon it, particularly the space-themed game(s) it is primarily being built for.

