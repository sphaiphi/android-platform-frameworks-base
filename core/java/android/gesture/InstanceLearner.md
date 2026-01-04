# InstanceLearner - Reverse Engineering Documentation

## Executive Summary
`InstanceLearner` is a specific implementation of `Learner` that uses nearest-neighbor-like logic to classify gestures.

## Algorithm
- **Classify**:
  1.  Iterates through all stored `Instance`s.
  2.  Computes distance (Cosine or Euclidean) between the input vector and each stored instance.
  3.  Calculates a score (weight) = `1 / distance`.
  4.  Aggregates scores by label (Nearest Neighbor).
  5.  Returns a sorted list of `Prediction`s.

## Java-to-C++ Translation Guide
- **Sorting**: Use `std::sort` with a custom comparator.
- **Data Structures**: `TreeMap` used for score aggregation (can use `std::map`).

## Source Reference
Defined in `InstanceLearner.java`.
