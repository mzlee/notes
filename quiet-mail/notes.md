---
layout: idea
title: Quiet Mail
description: A private email-like service
category: Crypto
tags: [anonymity, privacy, ZKPoK]
author: Michael Z. Lee
email: mzlee@cs.utexas.edu
---

# How do you make an untraceable email?

## What is private?

Not leaking the data and the metadata.
The data is easy, symmetric key encryption.
The metadata is harder:

1. Timestamp: can't do anything about this

2. Originating IP: can't do anything about this

3. The sending address: sure, just don't include it.
How does the sender respond to the message?
A rendezvous point that is established by in the initial message.
  
4. The receiving address: this would be the killer app.
   1. Encrypt the message with a random symmetric key.
   2. Encrypt the symmetric key with a public key.

# What does this look like?

No idea, but here are some potential pieces...

## Email server accessible over a Tor hidden service.

This ensures people are using Tor.  I guess instead this could be a
normal service and just let people be linked by IP.  Leave it up to
them to figure it out.

## Service keeps a directory of current addresses.

Should the server be the directory service?

# As a service, what will I see?

* An IP address
* A timestamp
* A blob of data
* When and how the blob of data moves
