# Lab 2: The Stack
### 100 Points
### Name: 

**Objective:** Create a stack

This is the beginning of a multi-lab project to create aspects of your own operating system entirely within userspace. We will begin with creating the capacity to manage memory. In this lab we will create a stack space, in the next lab we will create heap space. For these labs, you should modify **this readme** file so I have an in project identifier. 

Your stack needs the capacity to:
+ Allocate data of arbitrary size
+ Retain the size of the data allocated
+ Implement all of the methods defined in `ACMemory.h`
+ Correctly run all tests in `MemoryTests.h`


You may add additional structs, methods, and macros in your `ACMemory.c` file if necessary; *however*, you **CANNOT** modify `struct OS_Memory` or add additional global variables to retain data. If you have any questions, please contact me.

