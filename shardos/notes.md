---
layout: idea
title: "ShardOS"
description: "Sharding OS services on demand"
category: "OS"
tags: ["distributed systems", "shared memory"]
author: "Michael Z. Lee"
email: "mzlee@cs.utexas.edu"
---

# COMET is cool.  Actually, that's basically the idea in my head.  But
# do it without using dalvik.  Do it bare metal in the Linux kernel.  Is
# that even reasonable?

# Also: http://research.microsoft.com/en-us/projects/homeos/ :(

## MongoDB is auto sharding

* Introduction
  More and more home users have multiple computers: a computer in
  every person's pocket, a laptop for work, a desktop for home, a game
  console in the living room.  The idea of mobile device offload to
  save energy and improve performance is not new [], but the co-location
  of so many devices on the same unified network is.

  This work aims to bridge the gap between the old goal of offloading
  computaiton for power or performance gain, with the new assumptions
  of tight coupling of devices on a reliable and fast network.  Recent
  work [] has shown that the distributed shared memory model provides
  a way to efficiently offload finer grained computation: they were
  able to split multi-threaded applications between the client (an
  Android phone) and a server.  However, one of the key components in
  their system is the assumption of a runtime system.  This is
  critical for efficient data and code sharing due to the access
  constraints imposed by the runtime.  In fact, this even allows
  transparent migration of threads of a multi-threaded program, a
  first of its kind.  But they also admit native code, code written in
  a less type-safe language such as C or C++, is largely
  unapproachable.  To allow native code offloading, the functions had
  to be manually inspected and annotated.

  Instead of trying to tackle the difficult problem of transparent
  migration of threads between different end-points, we try to bring
  transparent resources to user applications.  One might wonder how
  such resources can be considered transparent, but what we are trying
  to create is an operating system (OS) level abstraction over
  multiple machines.  Just as non-uniform memory access systems expect
  multiple cores and disparate access to memory, so to can ShardOS
  provide non-uniform processor access (NUPA).  

  Non-uniform processor access provides more computational power in a
  semi-distrbuted fashion.  There is a tight coupling between the
  operating systems, but a loose coupling of the resources.  When two
  machines are not connected, both behave as normal; however,
  connecting the two systems then allows transparent sharing of
  resources.  In particular, it allows one machine to add processes to
  the scheduler or the other machine.  It does so without the failure
  model of a normal distributed system.  This is because in a home
  setting, the probability of repeated hardware or network failures is
  much smaller.

* Contributions
  Is distributed scheduling of related programs interesting?

  Example applications.
  - GIMP filter offload: open a large image on one machine, execute a
    series of computationally intensive filters, return results (and
    intermediate results after each filter).  This might be a
    multi-threaded thing which could make this really really hard...
  - Sharded Apache (or nginx?) server.  Not really a home desktop
    app...But having one master synchonizing different requests across
    twice as many resources could have some performance benefit.
  - Sharded MySQL (or other database) without the need to run a
    special version.  Large joins and what not over data split between
    the two machines.  Not even sure this is a valid file format.
  - Some kind of game?  Maybe run the AI on a separate machine?

* Related Work
  - COMET and code offload.
  - Manycore operating systems (Barrelfish, Helios, Cell operating systems)
  - Distributed Shared Memory (or does an RPC interface make more sense?)
    - Over infiniband, 1 Gbps ehternet, Wi-Fi
  - Distributed operating systems, grid operating systems, scientic
    computing and distributed systems
