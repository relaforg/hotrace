#include <stdint.h>
#include <unistd.h>

const size_t fnv_offset = 0xcbf29ce484222325;
const size_t fnv_prime = 0x100000001b3;

size_t	fnz1_hash(const char* str)
{
	size_t	hash;

	hash = fnv_offset;
	while (*str && *str != '\n')
	{
		hash *= fnv_prime;
		hash ^= *str;
		str++;
	}
	return (hash); 
}
__asm__ volatile (
        "vpxor %%ymm0, %%ymm0, %%ymm0\n\t" // Set YMM0 to zero
        "1:\n\t"
        "vmovdqa (%1), %%ymm1\n\t"         // Load 32 bytes (Aligned)
        "vpcmpeqb %%ymm0, %%ymm1, %%ymm1\n\t" // Compare bytes to zero
        "vpmovmskb %%ymm1, %0\n\t"         // Extract 32-bit mask
        "test %0, %0\n\t"                  // Check if mask is non-zero
        "jnz 2f\n\t"                       // If found, jump to end
        "add $32, %1\n\t"                  // Else, increment pointer by 32
        "jmp 1b\n\t"                       // Repeat
        "2:\n\t"
        : "=r" (mask), "+r" (ptr)          // Outputs
        :                                  // Inputs
        : "ymm0", "ymm1", "cc", "memory"   // Clobbered registers
    );
size_t	fast_strlen(const char* str)
{
	const char		*ptr = str;
	const uint64_t	*word;
	uint64_t		has_zero;
	uint64_t		chunk;

	while ((uintptr_t)ptr & 7) 
	{
		if (*ptr == '\0')
			return ptr - str;
		ptr++;
	}
	word = (uint64_t*) ptr;
	while (1)
	{
		chunk = *word;
		has_zero = (chunk - 0x0101010101010101ULL)
	}
}
