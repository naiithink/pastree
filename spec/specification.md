# Directory Exchange Protocol (DXP) Specification

Status: Draft
Author: Potsawat Thinkanwatthana
Created at: 2024-02-04
Modified at: 2024-02-04

## Abstract

The Directory Exchange Protocol (DXP) is a stateless application-level protocol
for reading, exchanging, and forming directory trees. This document describes
the overall architecture of DXP. In this definition are core protocol elements
and the "dxp" Uniform Resource Identifier (URI) schemes.

## Copyright Notice

```
MIT License

Copyright (c) 2024 Potsawat Thinkanwatthana

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## Introduction

### Purpose

The Directory Exchange Protocol (DXP) is a stateless, application-level,
request/response protocol that enables exchanging of directory tree structure
information through the Internet. Data is transfered in the format that allows
the receiver to replicate the source directory while preserving its relative
metadata and contents. Reading the source directory tree is done top-down
without following extra-tree soft links.

## Terminology and Core Concepts

### Eng and Chang

The source directory tree is called "Eng". The target directory tree is called
"Chang". This is to distinguish the term "source" as in "source address"
from the term "source" as in "source directory", avoiding ambiguilty.

### Cookie

DXP is a stateless protocol that uses "cookie" to remember stateful information
namely connection information...

### Token

...

### Connections, Senders, and Receivers

DXP is a protocol that operates over a reliable transport- or session-layer
"connection".

A DXP "sender" is a program that establishes a connection to the receiver
for the purpose of sending one or more DXP requests. A DXP "receiver" is a program
that accepts connections in order to process DXP requests by sending DXP
responses.
...

### Tidbits

DXP is a stateless request/response protocol for exchanging "tidbits" across
a connection. The terms "sender" and "recipient" refer to any implementation
that sends or receives a given tidbit, respectively.
...

### User Agents

...

### Example Tidbit Exchange

The following illustrates a typical DXP tidbit exchange for a PLUCK request
on the URI "dxp://example.com/usr/local/lib/ldxp":

sender request:

```
PLUCK /usr/local/lib/ldxp
DXP-sender: 1.0.0
Token: sometoken
Host: example.com

```

receiver response:

```
0 OK
DXP-receiver: 1.0.0
Token: sometoken
Date: 2024-02-04T19:50:00+07:00
Job-ID: 2024-02-04-12345
Content-Type: inode/directory

data...
```

## Methods

| Method Name | Description                                              |
| :---------- | :------------------------------------------------------- |
| PLUCK       | Transfer a directory tree                                |
| PICK        | Get next directory tree node                             |
| PACK        | Transfer the Chang checksum caculated from tidbit stream |

...

## Response Status Codes

### Response Status Code Classes

| Status Code Range         | Classified As                                                                       |
| :------------------------ | :---------------------------------------------------------------------------------- |
| [0, 136] union [137, 999] | Operational errors (C standard library error numbers and DXP reserved status codes) |
| [1000, 1999]              | Request-response                                                                    |
| [2000, 2999]              | Information exchange                                                                |

### Predefined Response Status Codes

| Status Code | Status Name | Meaning                                    |
| ----------- | ----------- | ------------------------------------------ |
| 0           | OK          | The prior query processing status is fine. |
| [1, 136]    | -           | (C standard library error numbers)         |
| [137, 999]  | -           | (DXP reserved status codes)                |
| 1000        | READY       | Ready to process the request.              |
| 1001        | DECLINED    | The request is declined.                   |
| 2000        | DONE        | There are no more nodes to PICK.           |
| 2001        | MORE        | There is at least one more node to PICK.   |

Complemented with the standard C error numbers.

## DXP Connections

```
                                                                            DXP Sequence                                                                  
                                                                                                                                                          
                                        ┌─────────┐                              ┌────────────┐                                                           
                                        │ps:Sender│                              │ps:Recipient│                                                           
                                        └────┬────┘                              └─────┬──────┘                                                           
                                            ┌┴┐────┐                                   │                                                                  
                                            │ │    │ 1 Generate cookie and token       │                                                                  
                                            │ │<───┘                                   │                                                                  
                                            │ │                                        │                                                                  
                                            │ │      2 PLUCK <DIR_NAME>                ┌┴┐                                                                
                                            │ │      Token: <TOKEN>                    │ │                                                                
                                            │ │      [Request to transfer a tree       │ │                                                                
                                            │ │      rooted at <DIR_NAME>]             │ │                                                                
                                            │ │ ──────────────────────────────────────>│ │                                                                
                                            │ │                                        │ │                                                                
                                            │ │                                        │ │────┐                                                           
                                            │ │                                        │ │    │ 3 Remember token                                          
                                            │ │                                        │ │<───┘                                                           
                                            │ │                                        │ │                                                                
                                            │ │                                        │ │                                                                
          ╔══════╤══════════════════════════╪═╪════════════════════════════════════════╪═╪═══════════════════════════════════════════════════════════════╗
          ║ ALT  │  Recipient agrees to receive                                        │ │                                                               ║
          ╟──────┘                          │ │                                        │ │                                                               ║
          ║                                 │ │           4 1000 READY                 │ │                                                               ║
          ║                                 │ │           Token: <TOKEN>               │ │                                                               ║
          ║                                 │ │           [Ready to receive]           │ │                                                               ║
          ║                                 │ │ <─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ │ │                                                               ║
          ║                                 │ │                                        │ │                                                               ║
          ║                                 │ │────┐                                   │ │                                                               ║
          ║                                 │ │    │ 5 Verify then renew token         │ │                                                               ║
          ║                                 │ │<───┘                                   │ │                                                               ║
          ║                                 │ │                                        │ │                                                               ║
          ║                                 │ │           6 Cookie: <COOKIE>           │ │                                                               ║
          ║                                 │ │           Token: <TOKEN>               │ │                                                               ║
          ║                                 │ │           [Send cookie]                │ │                                                               ║
          ║                                 │ │ ──────────────────────────────────────>│ │                                                               ║
          ║                                 │ │                                        │ │                                                               ║
          ║                                 │ │                                        │ │────┐                                                          ║
          ║                                 │ │                                        │ │    │ 7 Remember cookie and update token                       ║
          ║                                 │ │                                        │ │<───┘                                                          ║
          ║                                 │ │                                        │ │                                                               ║
          ║                                 │ │                                        │ │                                                               ║
          ║         ╔═══════╤═══════════════╪═╪════════════════════════════════════════╪═╪═════════════════════════════════════════════════════╗         ║
          ║         ║ LOOP  │               │ │                                        │ │                                                     ║         ║
          ║         ╟───────┘               │ │                                        │ │                                                     ║         ║
          ║         ║                       │ │            8 PICK <COOKIE>             │ │                                                     ║         ║
          ║         ║                       │ │            Token: <TOKEN>              │ │                                                     ║         ║
          ║         ║                       │ │            [Get next node]             │ │                                                     ║         ║
          ║         ║                       │ │ <─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ │ │                                                     ║         ║
          ║         ║                       │ │                                        │ │                                                     ║         ║
          ║         ║                       │ │                                        │ │                                                     ║         ║
          ║         ║         ╔════════╤════╪═╪════════════════════════════════════════╪═╪══════════════╗                                      ║         ║
          ║         ║         ║ BREAK  │  Either cookie not found\nor cookie is INVALID│ │              ║                                      ║         ║
          ║         ║         ╟────────┘    │ │                                        │ │              ║                                      ║         ║
          ║         ║         ║             │ │         9 74 EBADMSG                   │ │              ║                                      ║         ║
          ║         ║         ║             │ │         [Refuse PICK request           │ │              ║                                      ║         ║
          ║         ║         ║             │ │         then close connection]         │ │              ║                                      ║         ║
          ║         ║         ║             │ │ ──────────────────────────────────────>│ │              ║                                      ║         ║
          ║         ║         ╚═════════════╪═╪════════════════════════════════════════╪═╪══════════════╝                                      ║         ║
          ║         ║                       │ │                                        │ │                                                     ║         ║
          ║         ║                       │ │────┐                                   │ │                                                     ║         ║
          ║         ║                       │ │    │ 10 Verify token                   │ │                                                     ║         ║
          ║         ║                       │ │<───┘                                   │ │                                                     ║         ║
          ║         ║                       │ │                                        │ │                                                     ║         ║
          ║         ║                       │ │────┐                                   │ │                                                     ║         ║
          ║         ║                       │ │    │ 11 Accumulate Eng checksum        │ │                                                     ║         ║
          ║         ║                       │ │<───┘                                   │ │                                                     ║         ║
          ║         ║                       │ │                                        │ │                                                     ║         ║
          ║         ║                       │ │────┐                                   │ │                                                     ║         ║
          ║         ║                       │ │    │ 12 Determine next node            │ │                                                     ║         ║
          ║         ║                       │ │<───┘                                   │ │                                                     ║         ║
          ║         ║                       │ │                                        │ │                                                     ║         ║
          ║         ║                       │ │                                        │ │                                                     ║         ║
          ║         ║         ╔════════╤════╪═╪════════════════════════════════════════╪═╪═══════════════════════════════════════════╗         ║         ║
          ║         ║         ║ BREAK  │  Next node does not exist                     │ │                                           ║         ║         ║
          ║         ║         ╟────────┘    │ │                                        │ │                                           ║         ║         ║
          ║         ║         ║             │ │     13 2000 DONE                       │ │                                           ║         ║         ║
          ║         ║         ║             │ │     DIGEST: <CHANG_DIGEST>             │ │                                           ║         ║         ║
          ║         ║         ║             │ │     [Send node and Chang checksum,     │ │                                           ║         ║         ║
          ║         ║         ║             │ │     then close connection]             │ │                                           ║         ║         ║
          ║         ║         ║             │ │ ──────────────────────────────────────>│ │                                           ║         ║         ║
          ║         ║         ║             │ │                                        │ │                                           ║         ║         ║
          ║         ║         ║             │ │                                        │ │────┐                                      ║         ║         ║
          ║         ║         ║             │ │                                        │ │    │ 14 Forget cookie and token           ║         ║         ║
          ║         ║         ║             │ │                                        │ │<───┘                                      ║         ║         ║
          ║         ║         ║             │ │                                        │ │                                           ║         ║         ║
          ║         ║         ║             │ │                                        │ │────┐                                      ║         ║         ║
          ║         ║         ║             │ │                                        │ │    │ 15 Accumulate Chang checksum         ║         ║         ║
          ║         ║         ║             │ │                                        │ │<───┘                                      ║         ║         ║
          ║         ║         ║             │ │                                        │ │                                           ║         ║         ║
          ║         ║         ║             │ │                                        │ │────┐                                      ║         ║         ║
          ║         ║         ║             │ │                                        │ │    │ 16 Compare Eng and Chang checksum    ║         ║         ║
          ║         ║         ║             │ │                                        │ │<───┘                                      ║         ║         ║
          ║         ║         ╚═════════════╪═╪════════════════════════════════════════╪═╪═══════════════════════════════════════════╝         ║         ║
          ║         ║                       │ │                                        │ │                                                     ║         ║
          ║         ║                       │ │────┐                                   │ │                                                     ║         ║
          ║         ║                       │ │    │ 17 Renew token                    │ │                                                     ║         ║
          ║         ║                       │ │<───┘                                   │ │                                                     ║         ║
          ║         ║                       │ │                                        │ │                                                     ║         ║
          ║         ║                       │ │ 18 2001 MORE                           │ │                                                     ║         ║
          ║         ║                       │ │ Token: <TOKEN>                         │ │                                                     ║         ║
          ║         ║                       │ │ [Send node and tell next node exists]  │ │                                                     ║         ║
          ║         ║                       │ │ ──────────────────────────────────────>│ │                                                     ║         ║
          ║         ║                       │ │                                        │ │                                                     ║         ║
          ║         ║                       │ │                                        │ │────┐                                                ║         ║
          ║         ║                       │ │                                        │ │    │ 19 Update token                                ║         ║
          ║         ║                       │ │                                        │ │<───┘                                                ║         ║
          ║         ║                       │ │                                        │ │                                                     ║         ║
          ║         ║                       │ │                                        │ │────┐                                                ║         ║
          ║         ║                       │ │                                        │ │    │ 20 Accumulate Chang checksum                   ║         ║
          ║         ║                       │ │                                        │ │<───┘                                                ║         ║
          ║         ╚═══════════════════════╪═╪════════════════════════════════════════╪═╪═════════════════════════════════════════════════════╝         ║
          ╠══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣
          ║ [Recipent declines to receive]   │                                         │                                                                 ║
          ║                                  │ 21 1001 DECLINED                        │                                                                 ║
          ║                                  │ Token: <TOKEN>                          │                                                                 ║
          ║                                  │ [Refuse request then close connection]  │                                                                 ║
          ║                                  │<─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─                                                                 ║
          ╚══════════════════════════════════╪═════════════════════════════════════════╪═════════════════════════════════════════════════════════════════╝
                                             │                                         │                                                                  
                                             │                                         │                                                                  
                                             │                                         │────┐                                                             
                                             │                                         │    │ 22 Terminate                                                
                                        ┌────┴────┐                              ┌─────┴<───┘                                                             
                                        │ps:Sender│                              │ps:Recipient│                                                           
                                        └─────────┘                              └────────────┘                                                           
```