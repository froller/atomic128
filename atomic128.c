#include <stdint.h>

#define NAME_OF_SYNC_LOCK_TEST_AND_SET    __xync_lock_test_and_set_16
#define NAME_OF_SYNC_VAL_COMPARE_AND_SWAP __xync_val_compare_and_swap_16

__int128 NAME_OF_SYNC_LOCK_TEST_AND_SET(volatile __int128 *subject, __int128 set)
{
    __int128 orig;
    __asm
    {
        push  rbx

        // Loading value of set  into RCX:RBX
        mov   rcx, qword ptr [set + 8]
        mov   rbx, qword ptr [set + 0]
        
RETRY:  pause
START:  lock cmpxchg16b xmmword ptr [rdi]
        jnz   RETRY
        
        mov   qword ptr [orig + 8], rdx
        mov   qword ptr [orig + 0], rax
        
        pop rbx
    }
    return orig; 
}

__int128 NAME_OF_SYNC_VAL_COMPARE_AND_SWAP(volatile __int128 *subject, __int128 compare, __int128 swap)
{
    __int128 orig;
    __asm
    {
        push  rbx;
        
        // Loading value of test into RDX:RAX
        mov   rdx, qword ptr [compare + 8]
        mov   rax, qword ptr [compare + 0]
        
        // Loading value of set  into RCX:RBX
        mov   rcx, qword ptr [swap + 8]
        mov   rbx, qword ptr [swap + 0]

        // Trying to swap
        lock cmpxchg16b [rdi]

        // Returning initial value
        mov   qword ptr [orig + 8], rdx
        mov   qword ptr [orig + 0], rax
        
        pop rbx
    }
    return orig;
}
