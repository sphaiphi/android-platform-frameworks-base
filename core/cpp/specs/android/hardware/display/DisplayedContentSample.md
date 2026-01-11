# DisplayedContentSample - Reverse Engineering Documentation

## Executive Summary
`DisplayedContentSample` holds histogram data collected from the display hardware. It represents color distribution statistics for a range of frames.

## Data Model
- `mNumFrames`: Count of frames sampled.
- `mSamplesComponent0/1/2/3`: `long[]`. Histograms for R, G, B, A (or other channels).

## Detailed Functionality
- **Histogram**: Buckets represent intensity values (0.0 to 1.0). The value in the bucket is a weighted count (pixels * milliseconds).

## Java-to-C++ Translation Guide
- Simple container class.
- **Enum**: `ColorComponent` (CHANNEL0..3).
