---
title: Larrabee Benchmarking Notes
author: Michael Z. Lee
email: mzlee@cs.utexas.edu
---

* Interrupts
** Message Signalled Interrupts
** Host to LRB
** LRB to Host
* Local LRB
** mov 24, %eax; syscall
   958 cycles
** getuid
   966 cycles
   + On habals:
     about 370 (364 min, 430 max)
** Local Cache and Memory Access

* Data Transfer
** Things that affect the data transfer
   The memory allocation
   There and back
** In Memory File
   
** Multi Round
   
** Loss Ends
   Ugh...failed file open => early quit with no message.
