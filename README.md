# Luisa Rosa
# Operation Systems Final Project - 12/14/2023

---

## Reasoning → Option #3: Write a Linux Kernel Module

* In the Linux environment, the kernel's features can be dynamically expanded during runtime. This means I can add functionality through the Linux kernel using modules while the Operation System runs. A piece of code added to the kernel is called a module.

---

## Designing the Kernel module in C:
* The Kernel is responsible for maintaining all the essential abstractions of the operating system, including such things as virtual memory and process.
* Pieces of the code can be loaded and unloaded into the kernel upon demand.
* My module creates a pseudo-file (named proc/jiffies) to allow users to obtain the current value of the kernel’s jiffies global variable.
* The variables are set to zero during system startup.
* The Linux kernel keeps track of the number of time interrupts.
* This value is stored in the jiffies variable declared in the file.

---

## Proc File System:
+ (proc):
    * Proc is a virtual file system created on the fly when it boots and is dissolved at the time of system shutdown. A proc file system is a virtual file system that exists in RAM.
    * Obtains information about the kernel and changes specific parameters at runtime (sys ctl)
    * Used to trace a process system call, receive signals, and incur machine faults.

+ (jiffies):
    * Holds the number of ticks that have occurred since the system booted.
    * There are HZ jiffies in a second. HZ is the number of clock ticks (jiffies) in one second.
    * All variables in the code are declared as unsigned long, which is the data type of Jiffies.

---

## THE PROJECT:
Because I was unfamiliar with kernel programming, my project ended up having three “levels”.

1) The first level (hello_basics.c) is a simple program to familiarize myself with Linux Kernel programming. When creating a Linux module, it is good practice to add metadata information to the files using the MODULE_DESCRIPTION, MODULE_AUTHOR, and MODULE_LICENSE macros. Basically, what this program does is print "Hello, Professor" into the kernel once the module is initialized. When the module is exited, the program will print out “Goodbye, Professor” to the kernel.

2) In the second level (jiffies.c), I learned how to develop the previous program further. This program now prints the current value of the kernel’s jiffies (the number of ticks that have occurred since the system booted). First, we initialize the starting jiffies variable that holds the current number of jiffies when the module is initialized. When the module is exited, the final number of jiffies is saved in the variable end, and the total number of jiffies that occurred from start to end is saved on the variable elapsed. These variables are finally printed out into the kernel, and I can see the number of jiffies at the start-time end-time and how many jiffies happened before the module exited.

3) The third level (seconds.c) has a program that creates a kernel module that interacts with the /proc file system in Linux. The module calculates and reports elapsed kernel jiffies in seconds. Similarly to level 2, when the module is initialized, we save the number of jiffies in a variable and create a proc/seconds file. This means that another three functions are called. First, proc_sec_fops initializes the file operations for the /proc/seconds file and calls the following function proc_sec_pen. This function maps the /proc file read function to the file name. Finally, using the start variable and HZ, the show_sec function prints into the proc file how many seconds have elapsed since the start time. The proc/seconds file entries are removed when the module is exited.

---
