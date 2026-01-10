# Pin - Reverse Engineering Documentation

## Executive Summary
Represents a certificate pin (algorithm + digest).

## Data Model
*   `digestAlgorithm` (String): e.g., "SHA-256".
*   `digest` (byte[]).

## Java-to-C++ Translation Guide
*   Struct.
