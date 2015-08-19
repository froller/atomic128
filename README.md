# atomic128
128-bit atomic operation funcs missing from clang 3.5.0

Inspired by a bug found in clang 3.5.0 during my work on "Divinity: Original Sin"

__int128 __sync_lock_test_and_set_16(volatile __int128 *, __int128)
__int128 __sync_val_compare_and_swap_16(volatile __int128 *, __int128, __int128)
