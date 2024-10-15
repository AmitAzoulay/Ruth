/*includes*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kallsyms.h>
#include "changePagesPermission.h"


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

static int __init example_init(void)
{
    kallsyms_lookup_func = (void*) kallsyms_lookup_addr;
    sys_call_table = (unsigned long*)(*kallsyms_lookup_func)("sys_call_table");
    

    int rw_res = modify_to_rw_permissions((unsigned long)sys_call_table);
    printk(KERN_INFO "Changed to RW!  %d\n", rw_res);
    int ro_res = modify_to_ro_permissions((unsigned long)sys_call_table);
    printk(KERN_INFO "Changed to RO!  %d\n", ro_res);   
    return 0;
}

static void __exit example_exit(void)
{
    printk(KERN_INFO "Goodbye, world!\n");
}

module_init(example_init);
module_exit(example_exit);

