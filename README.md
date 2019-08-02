# SSE-Vector-Functions
A pair of Extended ASM functions for C99, to perform pairwise vector multiplication and pairwise vector multiplication with additive reduction, using the XMMS registers and SSE instructions.

This is just a pair of utility functions intended to do SSE pairwise operations on 4-byte floating point numbers a little faster than
GCC's built-in behavior will do it.  They're written in GCC's extended ASM syntax, which will allow the compiler to select the registers of its choice and avoid clobbering any in the process.
