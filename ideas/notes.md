---
layout: idea
title: "Ideas"
description: "Assorted ideas"
category: "ideas"
tags: ["ideas"]
author: "Michael Z. Lee"
email: "mzlee@cs.utexas.edu"
---

Anti-ROP
===

  Is it possible to cut off code disclosure?  Some kind of system that
  prevents data from being executed and code from being read except by
  the execution.  And if so, does this help anything?

  An extra bit in the page tables that marks pages data-read and
  code-read.  What do byte disclosures look like?

Zero Knowledge proof of correct execution
===

  A program could be decomposed and the operations could form a zero
  knowledge proof of correct execution without leaking the input
  data.  We would probably only want to target execution (i.e. PALs)
  because syscalls are hard.

Detecting click fraud
===

  Something like anon-pass to generate tokens and submit.
  You look like a new random person?

  Look at detecting click-fraud using crypto?  Basically looks for
  someone who has submitted the same token too many times.

Use DUNE for something fun
===

  Seems like it could be fun.

Look at cryptographic accumulators
===

  Why do they take 40KB, that kind of sucks...Can we cut that in half?

Do a translation from a target group to a general EC group
===

  That seems like it could do some interesting things.  Maybe even in
  the crypto world?  Probably in the crypto-systems world.

  Something else that would be interesting is the efficient
  computation of a bijection from one prime-order group to another.
  What does that entail and how could you possibly approach it?

Language tranalation:
===

  Translated Java bytecode (or DEX) into JavaScript.  Why?  More
  efficient, cross platform execution in a browser.  No more Java
  applet, just run in in JS.
  - Frabrise already showed it was possible to execute x86 in JS,
    can we do a more direct translation?
  - Could it be possible to run Android apps in a browser? That'd be
    cool.

  Whoa, this kind of showed up as a paper in ASPLOS 2014...

JavaScript record and replay
===

  Is there some kind of computational offload that can happen here?
  Basically, a "beefy" server plays the JavaScript and records the
  highlights.  This is translated to something that can be replayed
  with less computation on the client machine.
  - Take the model Kindle Fire has, and make it more general.  Screw
    privacy..
  - How do you handle user interaction?
  - How do you handle side effects?
  - Can you offload your own home desktop for this task?

ShardOS
===
(for Sharded Operating System or Shared Application Resource
and Data Operating System) or LANOS (for LAN Operating System or Local
Area Network Operating System)

  - Homes are connected.  There has been a shift in computing where
    more and more systems are online or connected over a
    local-area-network.  However, resources are still split.
    - The resources can and should be outsourced to other computing
      devices on the local network.
    - This is different from single-host computing:
      More than one physical host.
    - This is different from multi-processor computing:
      Compute and memory resource can be shared, slower resources
      (network and disk) are not directly shared.
    - This is different from grid-computing:
      This is ad hoc computational offload, not concerted special
      purpose computing.
    - This is different from distributed systems/cloud computing:
      We assume no failures and controlled network partitions (all
      entities know when a "partition" will happen).
  - The basic setup is a more powerful desktop (or in our case, server
    class and referred to as "desktop") machine and a less powerful
    desktop or laptop machine (referred to as "laptop").
  - The desktop is an always or usually on machine connected to a high
    speed network.  We will want to test this over wi-fi, lan (1gpbs),
    and infiniband (if possible).  Networking capabilities are the key
    to how the kernel makes a cost comparison to offload computation
    or not.
  - Example applications for offload:
    - GIMP and any heavy compute filters.  This could potentially save
      battery though would have to contend with a radio.  The tradeoff
      could be somewhere between cost of data transfer and power cost
      of filter.
    - Shared filesystem access.  The desktop filesystems are locally
      represented.  Files are streamed on-demand and locally cached if
      necessary (music or movie streaming).
    - Remote system administration.  The desktop is still a
      stand-alone system (with kernel modification and integration).
      Instead of navigating the filesystem remotely (ala a mounted
      sshfs), executables are run on the desktop and only results are
      sent back (ala ssh).
    - Sharded apache server.  Computation can be split between two
      machines transparently while looking like a single host.  No
      need for a load balancer, the master thread/process handles that
      automatically by dispatching to the process pool.

Process Fork and Join
===

  Serializing a process to pause and restart has been shown to be
  possible.  The necessary services will need to be copied and will
  need to be established on top of an interface that is fairly
  hardware agnostic.  Keeping a small in-memory file-system, normal
  application services and a way to simply translate a small interface
  into the necessary changes on the hardware should allow applications
  to pause, save to disk, migrate, and many other services that were
  primarily reserved for virtual machines.

  However, something that was probably previously impossible is the
  ability to fork and merge running applications.  In the most general
  sense, any long running program must have a loop waiting for a
  resource or performing repeated computation.  The idea of program
  checkpoints has been around for a long (enough) time and restoring
  system state to an earlier version is certainly possible.  However,
  what would be more interesting is automatically identifying the main
  loop, synchronizing any transient state, and reconciling the
  persistent changes to merge a previously forked program.

Implemenation
---

   I should be able to checkpoint a program from a kernel module or
   virtual machine.  Furthermore, implementing an in memory filesystem
   seems perfectly reasonable as just buffers in a flat namespace.
   Transient versus persistent program state changes could then be
   changes in "memory" versus changes on the "file system".

   The trick in getting the underlying operating system to resume the
   serialized program state.  It would have to be a specialized
   loader.  Things like input, output, and cached buffers may pose a
   problem as two different programs would be reading from different
   things.  This could all just be discarded upon serialization.

Motivation
---

   Being able to pause and migrate a program is a powerful thing.
   Making it more platform agnostic is also useful because then a
   program can follow you around.  However, the ability to branch a
   long running program, merge, and otherwise version your changes
   while still in the program is something that is even beyond what
   migration could present.  One could open a document, send it to
   many collaborators, and have live merging within a legacy
   application.

   This would probably require program specific merge tools...

Attribute Based Encryption for ???
===

  It's an interesting idea for a crypto system, now how do we apply
  it?

Secure Signing and Update of Attested Code
===

  We would like to be able to update attested code from a remote
  location with some reasonable security guarantee.  How thin can we
  stretch the adverary model?

Stackable Virtual Machines
===

  Now that cloud visor exists, is there anything else that's
  interesting about stacking virtual machines?  Are there additional
  security guarantees one might be able to provide in the hypervisor
  layer?

The Four Rings to Secure Them All
===

  Your computer has four protection rings, but we're only commonly
  familiar with two of the rings: ring 0 and ring 3.  With the advent
  of new hardware and new technology, we have seen additional use and
  additional classifications such as ring -1 and -2.  But what of the
  ones in the middle?  Is there really nothing interesting between
  root and user?

  As an attempt to address this, we try to create a better seperation
  and compelling reason to include ring 1 and ring 2.  Recent work
  with library OS's showed that not only is it possible, but there are
  some compelling reasons to further separate the managing and
  multiplexing of resources from the user application itself.  To
  further this, I propose the use of four layers: hardware kernel,
  driver interface, OS interface, and user applications.  Creating
  several levels of separation and well defined interfaces at each
  level, we can get a better understanding of control flow.

  Hardware Kernel:
  + Deals with memory and CPU utilization
  + Keeps a page table per process and implements scheduling
  + Sets up and defines the interrupts and upcalls for higher level
    servicing
  + Implements only the basic services it needs to be able to set up
    the higher levels
    - Boot loader
    - Paging
    - Scheduling

  Driver Interface:
  + Deals with trying to standardize the different pieces of hardware
    into a single, conherent interface
  + Implements the services needed to interact with various IO devices
    - Block Devices
    - Network Driver
    - Keyboard, Mouse, Screen

  OS Library:
  + Implements the application API
    - POSIX
    - X11

  User Application:
  + The actual user application
  + Shouldn't need modification

Constraining the Interfaces
---

   A goal is to limit the number of transfer points and function calls
   needed.  Each layer below can copy the necessary entry points into
   the upper layer's memory space.  In some ways, this is just taking
   a bare metal VMM, putting a paravirtualized OS on top and further
   splitting the virtual drivers from the rest of the operating
   system.  However, the goal is not to have all of the capabilities
   of multi-processing in the upper levels of the operating system and
   putting the lower memory management solely in the hardware kernel.

*** Kernel
    Below:
    + Bare Metal
    Above:
    + Memory Allocation
    + Process Allocation
    + Time Slicing
    + Final Level of Mutual Exclusion

*** Driver
    Below:
    + Memory Reservation
    Above:
    + Input Streams
    + Output Streams
    + Mutual Exclusion

*** Library
    Below:
    + IO Streams
    Above:
    + Expected API (POSIX)

*** Application
    Below:
    * Expected API

** Implementation
   In theory, I could take a copy of Linux, libc, and windowing system
   and tear it into pieces to separate out the management from the
   services from the interface and finally application.  The OS
   interface can be a per-process instance (as some of it already is),
   and the drivers will sit aside almost like a micro kernel construction.

The Use, Misuse, and Abuse of Trusted Computing
===

  We would like to create a comprehensive view of the scope of
  trusted computing technology and how and where it is used in the
  real world.  To this end, we will collect different open and close
  source projects that use the Trusted Platform Module in some
  manner and test to see if they correctly implement and use the
  interface.  Finally, we see if it is possible to circumvent the use
  of the TPM by using an intentionally malicious implementation of a
  software TPM to see if it is possible to break or abuse people's
  assumption of trusted computing.

JavaScript Measurement Study
===

  What happens when you break up a browser's origin policy and only
  allow code from a given origin to access its own objects?  How much
  stuff does this break?

  What if you also taint objects with a principle upon use?  And how
  do you fix this once you understand what's broken?

  Just how many websites import other people's code?  How big is this
  trusted computing base?

Something bigger
---
   More than just a measurement study, can I make an interesting
   browser that splits the same-origin-policy in JavaScript.  Has this
   been done (AdSentry) or done well enough?

Three Party Computation
===

  How do you do three party computation when there is mutual distrust
  between all of the parties?  Is there some way to prove that this is
  or isn't possible (not quite on the level of FLP or the CAP
  theorem).

  Assumptions: One party (the bank) is trusted to do what is asked of
  it.  The other two parties are at odds with each other.

  The basic model is C, S, B:
      C <---> S
       \     /
        \   /
         \ /
          B
  The solution is to not allow non-hmac'd strings.  It's sort of
      alright to not hmac the user request so long as the server
      response is hmac'd.

Seccomp-BPF breaking
===

  BFP: (BSD Packet Filtering)
  http://blog.cr0.org/2012/09/introducing-chromes-next-generation.html

Address Space Randomization
===

  Is it possible to write an operating system extension and gcc
  extension to make it possible to randomize program text and data on
  a page level?

  Or possibly something like a user library that can use EPT to store
  offsets and translations for an underlying program.

  How bad is this from a performance perspective?

  Does this fix anything if the ROP also uses this address translation?

  Turns out the answers are: yes, yes, no.

Dune Kernel Modules
===

  What about putting kernel modules into Dune?
