# SegmentFinder - Reverse Engineering Documentation

## Executive Summary
Abstract class defining text segment boundaries (start/end). Subclasses include `GraphemeClusterSegmentFinder` and `WordSegmentFinder`.

## API Reference
- **`previousStartBoundary(int offset)`**
- **`previousEndBoundary(int offset)`**
- **`nextStartBoundary(int offset)`**
- **`nextEndBoundary(int offset)`**

## Java-to-C++ Translation Guide
- **Iterators**: Abstract interface for text segmentation iterators.
