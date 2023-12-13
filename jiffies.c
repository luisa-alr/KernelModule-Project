//Luisa Rosa
//Operation Systems Final Project - 12/14/2023
//A simple kernel module that prints the current value of the kernel’s jiffies (the number of ticks that have occurred since the system booted).

#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/module.h>

MODULE_AUTHOR("Luisa Rosa");
MODULE_DESCRIPTION("A simple kernel module that prints the current value of the kernel’s jiffies (the number of ticks that have occurred since the system booted).");
MODULE_LICENSE("GPL");

//variable to store the start time (jiffies) of the module
unsigned long start;

//initialize the starting jiffies variable that holds the current number of jiffies when module is initialized
static int simple_init(void) {
    start = jiffies;
    printk(KERN_ALERT "Module is initialized\n");
    return 0;
}

//end: save final number of jiffies when module is finished
//elapsed: total number of jiffies that occurred from start to end
static void simple_exit(void) {
    unsigned long end = jiffies;
    printk(KERN_ALERT "Module is finished\n");
    unsigned long elapsed = end - start;

    //print number of jiffies 
    printk(KERN_ALERT "Jiffies at start time: %lu\n", start);
    printk(KERN_ALERT "Jiffies at end time: %lu\n", end);
    printk(KERN_ALERT "Jiffies total elapsed time: %lu\n", elapsed);
}

module_init(simple_init);
module_exit(simple_exit);