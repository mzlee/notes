---
layout: idea
title: "Quiet Mail"
description: "A private email-like service"
category: "Crypto"
tags: ["anonymity", "privacy", "ZKPoK"]
author: "Michael Z. Lee"
email: "mzlee@cs.utexas.edu"
---

How do you make an untraceable email?
=====================================

What do we want to prevent?
---------------------------

Leaking the data and the metadata.  The data is easy, symmetric key
encryption.  The metadata is harder:

# Timestamp:
  can't do anything about this

# Originating IP:
  can't do anything about this

# The sending address:
  sure, just don't include it.  How does the sender respond to the
  message?  A rendezvous point that is established by in the initial
  message.
  
# The receiving address
  This would be the killer app.

   # Encrypt the message with a random symmetric key.

   # Encrypt the symmetric key with a public key.

What does this look like?
=========================
No idea, but here are some potential pieces...

Email server accessible over a Tor hidden service.
---

This ensures people are using Tor.  I guess instead this could be a
normal service and just let people be linked by IP.  Leave it up to
them to figure it out.

Service keeps a directory of current addresses.
---

Should the server be the directory service?

As a service, what will I see?
===

* An IP address
* A timestamp
* A blob of data
* When and how the blob of data moves
