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

Tasks
===

1. How does the `vmcs` compare between Dune and KVM?
   The version is the same.  I don't know about the rest of it yet.
   Let's print out the entire `vmcs` to check.

2. Can we just allocate and attach a new VCPU to the queue of
   schedulable VCPU's?

3. How does `vmx_launch` (Dune) compare to `vmx_vcpu_run` (KVM)?

4. 
