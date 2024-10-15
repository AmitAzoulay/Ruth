/*includes*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kallsyms.h>
#include "changePagesPermission.h"


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ruth");
MODULE_VERSION("0.01");

static unsigned long syscall_table_address = 0;
module_param(syscall_table_address, ulong, 0);

static int __init example_init(void)
{
    unsigned long *syscall_table = (unsigned long*)syscall_table_address;

    modify_to_rw_permissions((unsigned long)syscall_table);
    printk(KERN_INFO "Changed to RW!\n");
    modify_to_ro_permissions((unsigned long)syscall_table);
    printk(KERN_INFO "Changed to RO!\n");
    return 0;
}

static void __exit example_exit(void)
{
    printk(KERN_INFO "Goodbye, world!\n");
}

module_init(example_init);
module_exit(example_exit);

