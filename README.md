# Overview
mirComp is a lightweight mir-based compositor. It was developed on an Ubuntu machine using C++, Bash scripting, CMake, and Neovim. 

# Installation, Building, and Running
## Additional Dependencies
- Weston: `sudo apt install weston`
- Qt's Wayland support: `sudo apt install qtwayland5`

# Setup
## Build Instructions
Run the bash script `./build.sh`
This will check for and install all dependencies and build the program.

## Run Instructions
Run the bash script `./run.sh`

# Program Usage
## Features
- Open Weston terminal with Ctrl + Alt + Shift + T
- Open the Help document with Ctrl + Alt + H
- Open Gnome Chess with Ctrl + Alt + C
- Open other programs from the Weston terminal 
- Close the compositor with Ctrl + Alt + Bksp

# Development Process
In my research on how to develop a compositor with Mir, I came across two examples that were extremely helpful to me in this project. The first was the article titled [Developing a Wayland Compositor Using Mir](https://mir-server.io/docs/developing-a-wayland-compositor-using-mir), which helped me learn the anatomy of a Wayland compositor and get a general template setup. From there, I moved on to experimenting with some more examples, and eventually found [Egmde](https://discourse.ubuntu.com/t/egmde-a-project-that-uses-mir/7129), which helped me learn how to introduce some more functionality into my compositor. I experimented around with the techniques I learned from Egmde, and implemented keyboard macros for opening a Weston terminal, opening up a user help document, playing a game of chess, and closing the compositor.

## Sources
- https://mir-server.io/docs/developing-a-wayland-compositor-using-mir
- https://discourse.ubuntu.com/t/egmde-a-project-that-uses-mir/7129
- https://mir-server.io/doc/index.html
