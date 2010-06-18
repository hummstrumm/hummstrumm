#include "cpuid.h"

int
main(int argc, char **argv)
{
  cpuid(0x00000001);
  return getBits(registers.d,26,1);
}
