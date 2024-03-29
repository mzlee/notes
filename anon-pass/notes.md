---
layout: idea
title: "Anon-Pass"
description: "How to build an anonymous subscription service"
category: "Crypto"
tags: ["anonymity", "ZNPoK"]
author: "Michael Z. Lee"
email: "mzlee@cs.utexas.edu"
---

* Tasks
  + Reimplement in C
  + Implement it on smart card/Android device (if possible)
  + Look at OAuth
  + Implement on a router

* Schemes
** PRF + Interval Chain
   Pros:
   + Fast Keep alive (Client does one multiplication, Server does two
     pairings)
   Cons:
   - The initial setup is somewhat expensive.  Possibly log(T)
     exponentiations and log(T) pairings
   - It might not work

** Clones
   Pros:
   + Logon and keep alive are the same operation
   Cons:
   - The operations are not that cheap

** With Hash Chain
   Pros:
   + Hash Chains!
   + Client precomputes
   + Server does one hash (for normal case)
   Cons:
   - Don't remember why or how it worked..
   - It doesn't really work

* PRF + Interval Chain
** Construction
   There are two phases, the logon and the continuation.  Roughly,
   logon needs A to convince SP that $g^(a^t)$ was formed correctly
   without releasing $a$.  Continuation needs to make sure that SP
   gets the proper $g^(a^{t+1}).

*** Logon
    Need to convince SP of a(r+1) and 1/(ar)

    Commit to a solution, get a challenge, solve the challenge for the
    solution.  The key is constraining the possible solutions so that
    once A has commited, SP can challenge and A can only solve for one solution.

*** Continuation
    We want:
    * $<a(r+1), 1>$ is the increment
    * $<a^{t}, -ra^{t+1}>$ is the token
    * $<2, \frac{1}{ra}>$ is the decode

    Thus, the client proves that she may continue by sending
    $g^{<a^{t},-ra^{t+1}>}$ to the SP.  The SP does two pairings:
    + $e(g^{<a^{t}, -ra^{t+1}>}, g^{<2, \frac{1}{ra}>}$
    + $e(g^{<a^{t-1}, -ra^{t}>}, g^{<a(r+1), 1>})$
    
    This should result in $e(g,g)^{a^t}$ given that the pairing
    multiplication takes a dot product of the two vector components.

    How this is implemented, I have no idea...

* Modified Clones (really just the DY PRF)
** Construction
   Again, there are two phases, the logon and continuation.  This is a
   bit more fleshed out and a more straight forward (read, exisiting)
   for logon and may also be a faster continuation due to the lack of
   bilinear pairings

*** Logon
    I'm not sure how this works, but it's something like
    
    PK(a | g^{-1} Y_t^{a} = 1 and other stuff)

*** Continuation
    Given SP knows and believes Y_t is legitimate

    A: calculates Y_{t+1}, R_{t}, R_{t+1} --> SP

    SP: creates a random challenge, c --> A

    A: calculates s = r - ca --> SP

    SP: verifies (gY_t^{-t})^c Y_t^s and (gY_{t+1}^{-(t + 1)})^c Y_{t+1}^s
