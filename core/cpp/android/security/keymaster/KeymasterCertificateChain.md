# KeymasterCertificateChain - Reverse Engineering Documentation

## Executive Summary
Container for a chain of X.509 certificates (byte arrays) returned by Keymaster.

## Data Model
*   `mCertificates`: `List<byte[]>`.

## Java-to-C++ Translation Guide
*   `std::vector<std::vector<uint8_t>>`.
