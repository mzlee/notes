---
layout: idea
title: "Lacuna"
description: "Private mode for your operating system"
category: "OS"
tags: ["privacy", "systems hacking"]
author: "Michael Z. Lee"
email: "mzlee@cs.utexas.edu"
---

File system considerations
---

  We would like to be able to share data.  One way would be attach a
  drive that can be used to de-classify.  Not terrible as a first cut,
  but nicer things should exist.

  Another approach is to force user action to make the call.  For
  this, I want to modify libqt to allow file pass through.
** Qt Analysis
   User control flow:
   - open a QtFileDialog or a native file dialog
   - user chooses a file or number of files
   - QtFileDialog eventually returns a QString
     - Sub-class QString to QFileName (or mark a flag that can't
       normally be reached) and return that instead
   - The QString may eventually be passed into a QFile as a constructor
     - If QFileName is actually passed to the constructor, then open
       the underlying file (or at least set the proper flag)
     - By default, QFileName should be constant until we find an
       application where this doesn't work
   - QFile should, in the destructor or earlier, write-back changes to
     the underlying host file system through a set of hypercalls
     - We may be able to track the underlying changes and just pass
       this through
     - Or, we'll have a local copy that occasionally gets flushed to
       disk
     - If it's a local copy, it has to be protected from outside
       modification
** Other file system methods
   An encrypted drive seems like a reasonable way to hold persistant
   state.  We could use something like a hidden drive inside the root
   file system.
** Shared applications
   1. No sharing, you need to have duplicates and need to have
      manually force updates when necessary
   2. Host scraped, you need to have the host scrape the filesystem
      and pass these through into the guest.  The guest would obtain a
      local copy and its dependencies (somehow...)
   3. Shared disk, you need to have the applications copied into the
      disk image on the host.  The guest would then mount this drive.

   The general theme is a tradeoff between consistency and ease of
   setup.  The easiest thing to set up has no consistency.  The
   hardest thing to set up has the best (nfs) semantics.  The middle
   ground has some kind of consistency, but it's not clear what will
   happen if the host writes while the guest is reading.  If it's
   contained in the host application, that may be alright.

* What is an attack model?
** Forensic Deniability
   The "attacker" gets access to the system in some capacity
   (depending on strength of the attacker) and tries to determine
   whether or not a particular "action" was taken (where action could
   be loading a particular webpage, running an application, etc).

   The attacker wins if he can distinguish between two executions with
   one differing program.

   A harder problem would be to try to make some guarantee about a
   non-interference property.

* Where does data lie around?
  + Application Level
    - Swapped to disk
    - Memory Dump
    - Temporary Files
    - Dynamic Allocation
  + Kernel
    - Buffer Cache
    - Key Cache
    - DMA Buffers
  + General Data Structures
    - Circular queues
    - I/O buffers
    - Strings
** GUI Programs vs. Command Line
   There's an inherent difference due to the event loop in GUI
   programs [Garbage].  GUI event loops sit at the top of the stack
   and occansionally do work.  This results in a different access
   pattern and possibly leaked information on the stack.
** Specific Examples
*** Mozilla 1.0 [WSS]
    + Kernel random number generator
    + XFree86 event queue
    + Kernel socket Buffers
    + Mozilla strings
    + Kernel tty buffers
*** Apache and Perl [WSS]
    + Kernel packet buffers
    + Apache input buffers
    + Apache output buffer
    + Kernel pipe buffer
    + Perl file input buffer
    + Perl string buffers
*** Emacs [WSS]
    + Kernel random number generator
    + Global variable: kbd_buffer
    + Global variable: recent_keys
    + Lisp string in emacs
    + Stack
    + Three kernel buffers: a flip buffer, tty, and ipc to shell
      subprocess
*** Modern Browsers (Firefox 3.5) [Private Browse]
    + cert8.db: CA Certs, client certs, and settings
    + permissions.sqlite: site specific preferences
    + mimeTypes.rdf: Download actions for file types
    + SQlite databases - show an accessed timestamp
    + search.sqlite, search.json: Search Plugins
    + pluginreg.dat: Plugin registration
    + Browser extensions can also leak data
*** Databases (PostgreSQL, MySQL, IBM DB2, SQLite)
    + Not all operations properly remove data:
    + DELETE might not physically overwrite data
    + UPDATE might preserve the old value

* Terms from various papers
** Data Lifetime [WSS, Garbage]
   + Ideal Data Lifetime
   + Secure Deallocation Data Lifetime
   + Natural Data Lifetime
** Forensically Transparent System [Database]
   + "All data retained by the system should be accessible through a
      legitimate interface and it should not be possible to recover
      hidden data through inspection of system state." (Page 92)
** Slack Data
   Data that is not accessible through normal interfaces but can still
   be recovered for whatever purposes.
   + Database Slack
   + File System Slack

* Some (possibly relevant) papers
** Data Lifetime is a Systems Problem
   T. Garfinkel, et al.
   Stanford University
   2004 SIGOPS European Workshop
** Understanding Data Lifetime via Whole System Simulation [WSS]
   J. Chow, et al.
   Stanford University
   2004 USENIX Security Symposium
** Shredding Your Garbage: Reducing Data Lifetime Through Secure Deallocation [Garbage]
   J. Chow, et al.
   Stanford University
   2005 USENIX Security Symposium
** Threats to Privacy in the Forensic Analysis of Database Systems [Database]
   P. Stahlberg, et al.
   University of Massachusetts, Amherst
   2007 SIGMOD Internation Conference on Management of Data
** An Analysis of Private Browsing Modes in Modern Browsers
   G. Aggarwal, et al.
   Stanford University, CMU
   2010 USENIX Security Symposium
** LeakProber: A Framework for Profiling Sensitive Data Leakage Paths
   J. Yu, et al.
   Pennsylvania State University, University of Science and Technology, Wuhan China
   2011 ACM Conference on Data and Application Security and Privacy
