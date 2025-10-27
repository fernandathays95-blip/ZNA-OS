# ZNA-OS Dalvik IR Tool

This directory contains the Dalvik Intermediate Representation (IR) tool
for ZNA-OS, inspired by Android's dex analysis utilities.

## Files

- **dalvik.cc**: Main executable, constructs sample IR and prints statistics.
- **dalvik.h**: Core IR structure definitions.
- **dalvik_utils.h**: Utility functions for printing and managing IR.
- **LICENSE**: Apache 2.0 license.
- **README.md**: This file.

## Purpose

This tool provides an internal way to monitor and log ZNA-OS Dalvik IR data:
- Strings
- Types
- Protos
- Fields
- Methods
- Annotations

It is designed for system developers to test IR creation without external `.dex` files.

## Usage

Compile and run:

```bash
g++ dalvik.cc -o dalvik_tool
./dalvik_tool
