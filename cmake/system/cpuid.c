#include "cpuid.h"

unsigned
getBits(unsigned x, int p, int n)
{
  if (((p+1-n) >= sizeof(unsigned) * CHAR_BIT) ||
      (p+1-n) < 0)
  {
    // error condition
    //fprintf(stderr, "getBits undefined behavior\n");
    exit(1);
  }
  // The expression x >> (p+1-n) moves the desired
  // field to the right end of the word. ~0 is all
  // 1-bits; shifting it left n bit positions with
  // ~0 << n places zeros in the rightmost n bits;
  // complementing that with ~ makes a mask with
  // ones in the rightmost n bits.
  return (x >> (p+1-n)) & ~(~0 << n);
}

void
cpuid(const unsigned int cpuidOp)
{
  unsigned highest_acceptable_eax_value =  0x80000000;

  bzero(&registers,sizeof(struct sRegisters));
  if (highest_acceptable_eax_value >= cpuidOp)
  {
    #ifdef HUMMSTRUMM_PLATFORM_WIN
      #ifdef HUMMSTRUMM_ARCHITECTURE_32
        exit(0);
      #elif HUMMSTRUMM_ARCHITECTURE_64
        exit(0); 
      #else
        exit(0);
      #endif
    #elif HUMMSTRUMM_PLATFORM_GNULINUX
      #ifdef HUMMSTRUMM_ARCHITECTURE_32
        asm volatile
        (
          "pushl %%ebx\n\t"
          "cpuid\n\t"
          "movl %%eax, %0\n\t"
          "movl %%ebx, %1\n\t"
          "movl %%edx, %2\n\t"
          "movl %%ecx, %3\n\t"
          "popl %%ebx\n\t"
          : "=m"(registers.a),
            "=m"(registers.b),
            "=m"(registers.d),
            "=m"(registers.c)
          : "a"(cpuidOp)      
        );
      #elif HUMMSTRUMM_ARCHITECTURE_64
        asm volatile
        (
          "pushq %%rbx\n\t"
          "cpuid\n\t"
          "movq %%rax, %0\n\t"
          "movq %%rbx, %1\n\t"
          "movq %%rcx, %2\n\t"
          "movq %%rdx, %3\n\t"
          "popq %%rbx\n\t"
          : "=m"(registers.a),
            "=m"(registers.b),
            "=m"(registers.c),
          "=m"(registers.d)
          : "a"(cpuidOp)      
        );
      #else
        exit(0);
      #endif
    #else
      exit(0);
    #endif
  }
  else
    exit(0);
}
