---
layout: idea
title: Quiet Mail
description: A private email-like service
category: Crypto
tags: [anonymity, privacy, ZKPoK]
author: Michael Z. Lee
email: mzlee@cs.utexas.edu
---

# Goal

We want to name someone without disclosing them publicly.  How?

1. How does the sender know how to "address" the receiver?

   A shared secret?  

2. How does the receiver accept the "email"?

   Random authentication?  Only download once?

3. How does the receiver know when there is a new "email"?

   An accumulator?  A randomly generated name?

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

Hiding the sender:

1. k-anonymity -- when a user sends a message, it is automatically
   mixed with k - 1 other users.
   1. Collect k messages from different public keys, mix the messages:
      1 real message, k-1 empty messages.
   2. Broadcast the message to k people.
   
2. What if my sender is not among the receivers (i.e. not among the
   k-1 other clients?)
   1. Messages are available to every user.
   2. What if we add a client requirement - check your messages every day?
      1. Change users' message identifier everyday.
	  2. How do you set the identifier?

Sender authentication:

1. A signature is included in the encrypted message.
  Basically, encrypt and MAC.

2. 

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
