#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    __int128 zero = 0;
    __int128 one  = 1;
    __int128 few  = 128;
    __int128 much = ((__int128)1 << 64) + ((__int128)1 << 63);
    __int128 res[4];
    __int128 zlo  = few;
    res[0] = __sync_lock_test_and_set_16(&zlo, much);
    res[1] = zlo;
    res[2] = __sync_lock_test_and_set_16(&zlo, zero);
    res[3] = zlo;
    for (unsigned char i = 0; i < 4; i++)
        printf("%lu\n", res[i]);
    int rv = 0;
    rv |= (res[0] != few ) && (1 << 0);
    rv |= (res[1] != much) && (1 << 1);
    rv |= (res[2] != much) && (1 << 2);
    rv |= (res[3] != zero) && (1 << 3);
    return rv;
}
