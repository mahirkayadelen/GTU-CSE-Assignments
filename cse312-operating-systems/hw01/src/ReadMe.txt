Mehmet Mahir Kayadelen -- Operating System Project

This project is for building a custom operating system mahirOS.

Usage
Setting Up VirtualBox
Open VirtualBox.
Create a new virtual machine:
Name: mahirOS 

!Name is important for expected results in makefile!

To build and run the project, use the following command and wait 5 seconds to executing:
make

Stopping the Operating System
To stop the operating system running in VirtualBox, use:
make close


Commands

make           # Builds the project and generates the ISO file and runs the OS.
make mykernel.iso # Creates the ISO file from the kernel binary.
make run       # Runs the operating system in VirtualBox.
make close     # Stops the running operating system in VirtualBox.
make install   # Installs the kernel to the boot directory.
make clean     # Cleans the build files.