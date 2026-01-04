# WebViewLibraryLoader - Reverse Engineering Documentation

## Executive Summary
`WebViewLibraryLoader` handles the complex low-level details of loading the WebView's native library (`.so`). This involves dealing with 32-bit/64-bit compatibility, reserving address space in the Zygote, and creating RELRO (Relocation Read-Only) files for memory sharing.

## Detailed Functionality
*   **RELRO Sharing**: Spawns a child process (`RelroFileCreator`) to load the library and dump the RELRO section to a file. This file is then memory-mapped by all apps using WebView to save RAM.
*   **`loadNativeLibrary`**: Loads the library using the prepared RELRO file.
*   **`reserveAddressSpaceInZygote`**: Reserves virtual memory address space to ensure the library can be loaded at the same address in all processes (required for RELRO sharing).

## Java-to-C++ Translation Guide
*   **Linker Logic**: This interacts deeply with the Android dynamic linker (`linker`).
