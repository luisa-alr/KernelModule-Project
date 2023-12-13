//Luisa Rosa
//Operation Systems Final Project - 12/14/2023
//Program to get familiar with Linux Kernel programming.

#include <linux/init.h>
#include <linux/module.h>

//We declare some module metadata using the MODULE_DESCRIPTION , MODULE_AUTHOR , and MODULE_LICENSE macros. These aren't strictly necessary, but just like a README , it is good practice to include them.
MODULE_AUTHOR("Luisa Rosa");
MODULE_DESCRIPTION("Once the module is initialized or exited, the functions will use printk to print a message to the Linux kernel log.");
MODULE_LICENSE("GPL"); //this module uses a free license
 
//function that will print "Hello, Professor" when module is initialized.
static int hello_init(void) {
    printk(KERN_ALERT "Hello, Professor\n");
    return 0;
}

//function that will print "Goodbye, Professor" when module is exited.
static void hello_exit(void) {
    printk(KERN_ALERT "Goodbye, Professor\n");
}
 
module_init(hello_init); 
module_exit(hello_exit);