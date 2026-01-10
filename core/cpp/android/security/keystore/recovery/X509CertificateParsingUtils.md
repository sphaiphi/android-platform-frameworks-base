# X509CertificateParsingUtils - Reverse Engineering Documentation

## Executive Summary
Utility class for decoding X.509 certificates from Base64 strings or byte arrays.

## Java-to-C++ Translation Guide
*   Use BoringSSL functions (`d2i_X509` or `PEM_read_bio_X509`).
