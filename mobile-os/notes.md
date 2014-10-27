---
layout: idea
title: "Mobile OS File Systems"
description: "What do mobile file systems look like, and how do we fix them?"
category: "research"
tags: ["mobile", "os"]
author: "Michael Z. Lee"
email: "mzlee@cs.utexas.edu"
---

## Mobile OS Use Cases

* Games: usually wants access to a file system and binary files.

* Media Viewing:

* Media Editing:

* Web Browsing:

### What amount of sharing is necessary?

### Can applications become content providers?

Can we make arbitrary applications content providers?  Basically make
the application interpret its own data to be shared with other
applications.  Use that as a form of MAC where applications can
specify different types of data access policy.

Can we integrate different streams of content from varying
applications into a cohesive interface for consumers?  In other words,
multiple applications can serve and generate images, the gallery app
queries each application for its images and returns a consistent
interface.  In addition, each application can enforce its own policy
when a consumer app makes a request.

Can each application enforce its own policy when a consumer app
receives data?
