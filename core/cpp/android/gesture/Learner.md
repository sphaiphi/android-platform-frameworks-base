# Learner - Reverse Engineering Documentation

## Executive Summary
`Learner` is the abstract base class for gesture classifiers. It manages the collection of training `Instance`s.

## Architecture Overview
- **Storage**: `ArrayList<Instance>`.
- **Methods**: Add, get, and remove instances.
- **Abstract**: `classify` method.

## Java-to-C++ Translation Guide
- **Pattern**: Abstract Base Class.

## Source Reference
Defined in `Learner.java`.
