/*includes*/
#include <linux/mm.h>        
#include <linux/highmem.h>   

/**
 * modify_to_rw_permissions - Checks if virtual address is mapped and modifies PTE to RW.
 * @address - Virtual address to check amd modify.
 * 
 * This function check if virtual address is mapped in the page tables.
 * If it is, the function check if the has write permissions.
 * If it is'nt, the function modifies the PTE to RW permissions.
 * 
 * Return:
 * - 0 on success, indication the permissions were successfully changed to RW.
 * - 1 if the permissions were already RW, indication there was'nt modification.
 * - -1 if the address is'nt mapped in the page tables.  
 */
int modify_to_rw_permissions(unsigned long address)
{
    unsigned int level;    
    pte_t *pte;              
    pte = lookup_address(address, &level);

    if(pte)
    {
        if(pte->pte &~ _PAGE_RW)
        {
            pte->pte |= _PAGE_RW; // SET the RW bit.
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return -1;
    }

    return 0;

}

/**
 * modify_to_ro_permissions - Checks if virtual address is mapped and modifies PTE to RO.
 * @address - Virtual address to check amd modify.
 * 
 * This function check if virtual address is mapped in the page tables.
 * If it is, the function check if the has write permissions.
 * If it is'nt, the function modifies the PTE to RO permissions.
 * 
 * Return:
 * - 0 on success, indication the permissions were successfully changed to RO.
 * - 1 if the permissions were already RO, indication there was'nt modification.
 * - -1 if the address is'nt mapped in the page tables.  
 */
int modify_to_ro_permissions(unsigned long address)
{
    unsigned int level;    
    pte_t *pte;              

    pte = lookup_address(address, &level);

    if(pte)
    {
        if(pte->pte & _PAGE_RW)
        {
            pte->pte &= ~_PAGE_RW; // Clear the RW bit.
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return -1;
    }

    return 0;
}