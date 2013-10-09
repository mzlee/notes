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

Direction One: 
===
Don't trust your operating system, don't trust the VMM underneath it either

Direction Two:
===
Nested or not, it's kind of the same
   
How does this work?  We have an application that can handle its own
page table and pagefaults.  We have a guest OS which handles a lot of
system calls we don't care about.  We have the hypervisor which
allocates the memory we need for the inky-dune process.
