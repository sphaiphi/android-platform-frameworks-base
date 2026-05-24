# RecoveryCertPath - Reverse Engineering Documentation

## Executive Summary
Wrapper around a `CertPath` (certificate chain) for Parceling. Uses "PkiPath" encoding.

## Data Model
*   `mEncodedCertPath` (byte[]).

## Java-to-C++ Translation Guide
*   It's just a byte array containing the encoded cert path. C++ side needs to parse the PkiPath format (ASN.1).
