---
layout: idea
title: "Inky Dune Visor (aka Dunk)"
description: "You don't trust your OS, but you do trust your VMM, part
3"
category: "Virtualization"
tags: ["untrusted os", "virtualization"]
author: "Michael Z. Lee"
email: "mzlee@cs.utexas.edu"
---

More Directions
===

Shared memory syscall polling.
Get `open`, fs syscalls working first.


Tasks
===

1. How does the `vmcs` compare between Dune and KVM?
   The version is the same.  I don't know about the rest of it yet.
   Let's print out the entire `vmcs` to check out the differences.

2. Can we just allocate and attach a new VCPU to some queue of
   schedulable VCPU's?

3. How does `vmx_launch` (Dune) compare to `vmx_vcpu_run` (KVM)?

4. How do the `vcpu`'s differ?

Ok, what am I doing?
===

There are a number of moving pieces, where am I and how is it going?

1. Guest OS - untrusted.  Runs as guest root.  Unmodified.
   Done - this part is easy.

2. Guest Stub - untrusted.  Runs as guest user. Makes vmcall to
   initialize the dunk process.  Makes vmcalls to switch into dunk
   process.
   Done - this part is easy.

3. Dunk Kernel Module - trusted.  Run as host root.  Handles vmcalls,
   vcpus, vmcs's, basically everything.
   WTF...how does this work?

   For now, let's just get something that 1) creates a new VCPU/VMCS
   (what else happens on create_vcpu).

4. Host Stub - trusted.  Runs as host user.  This is the first step
   for bootstrapping.  Hooks up the system calls and interrupt tables
   and boots the dunk process.  A part of the page table setup can
   come from dune.

5. Guest Loader - trusted.  Runs as guest root.  This is the second
   step for bootstrapping.  This opens, mmaps, and starts executing
   the dunk process.  This is likely parts of the the elf loader
   and dune sandbox.

6. Dunk process - trusted.  Runs as guest user.  This is the
   bootstrapped process we're trying to execute.  All of its system
   calls are transformmed into vmcalls which the kernel module
   handles.  This should be mostly transparent.

How does this work?
---

Starting from the guest VM.  Run the guest-stub program.  This
serializes arguments and makes a vmcall to create a new
vcpu/vmcs/other structures for the dunk process.  We really just want
to have a VCPU and associated vmcs but the easiest way to set this up
is with a new process (`vfork` and `exec`).  But we still want access
to the same `struct kvm` so it's properly associated.

Alternatives
---

Why not just run a host process with the trusted program?

Issue 1: This implies a full host OS.

Issue 2: This takes host resources (namely host CPU time).

Issue 3: Syscalls would need interposition to redirect from host to
         guest.

