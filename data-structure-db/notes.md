---
layout: idea
title: "A query interface for opaque datatypes"
description: "Applications store data in many different formats,
              including some proprietary data formats.  This makes it
              difficult for a user to understand what data an
              application has as well as difficult to understand the
              data being generated.  We propose to use static program
              analysis, binary analysis, dynamic runtime analysis,
              and/or reverse engineering to extract the program
              interfaces inherently present and provides users the
              ability to analyze and query the data."
category: "Program Analysis, "
tags: ["Program Analysis"]
author: "Michael Z. Lee"
email: "mzlee@cs.utexas.edu"
---

1. See if applications have some kind of centralized data stores.

2. See if there are well defined entry points to get and set data.

3. See if it is possible to extract or piggy back off of applications
   to query over data stores.

   One way is to hook a debugger to a running program and provide a
   translation layer between the requested queries and the provided
   functions.

4. See if there are one-way interfaces (i.e., query and reverse
   engineer logs based on the log generation code).

   Use the logging interfaces and provided variables to extract
   information about the resulting logs.
