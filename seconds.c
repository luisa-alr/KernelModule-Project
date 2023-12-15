//Luisa Rosa
//Operation Systems Final Project - 12/14/2023
//This file creates a kernel module that interacts with the /proc file system in Linux. The module calculates and reports elapsed kernel jiffies in seconds.

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/time.h>

#define PROC_FILENAME "seconds"

MODULE_AUTHOR("Luisa Rosa");
MODULE_DESCRIPTION("A simple kernel module that prints the current value of the kernel’s jiffies in seconds.");
MODULE_LICENSE("GPL");

//variable to store the start time (jiffies) of the module
unsigned long start;

//function that shows how many seconds have elapsed since start
static int show_sec(struct seq_file *m, void *v) {
    unsigned long elapsed = (jiffies - start) / HZ;
    seq_printf(m, "Elapsed Seconds: %lu\n", elapsed);
    return 0;
}

// This structure maps the /proc file read function to the file name
static int proc_sec_open(struct inode *inode, struct file *file) {
    return single_open(file, show_sec, NULL);
}

//function that initializes the file operations for the /proc/seconds file
static const struct proc_ops seconds_proc_fops = {
    .owner = THIS_MODULE,
    .open = seconds_proc_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release,
};

//initialize the starting jiffies variable that holds the current number of jiffies when module is initialized
static int __init seconds_init(void) {
    start = jiffies;
    //create proc/seconds file
    proc_create(PROC_FILENAME, 0, NULL, &seconds_proc_fops);
    return 0;
}

//remove proc/seconds file entries
static void seconds_exit(void) {
    remove_proc_entry(PROC_FILENAME, NULL);
}

module_init(seconds_init);
module_exit(seconds_exit);