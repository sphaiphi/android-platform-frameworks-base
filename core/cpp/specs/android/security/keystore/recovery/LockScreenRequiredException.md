# LockScreenRequiredException - Reverse Engineering Documentation

## Executive Summary
Exception thrown when trying to generate/recover keys but the user has no lock screen set (which is required for protection).

## Java-to-C++ Translation Guide
*   Map to error code `ERROR_INSECURE_USER`.
