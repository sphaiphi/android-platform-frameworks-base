# GestureStore - Reverse Engineering Documentation

## Executive Summary
`GestureStore` is the core database and recognition engine. It stores named gestures and uses a `Learner` (classifier) to predict labels for new gestures.

## Architecture Overview
- **Storage**: `HashMap<String, ArrayList<Gesture>>` maps names to gesture examples.
- **Classifier**: Uses `InstanceLearner` for recognition.
- **Configuration**: Supports different sensitivity modes (Sequence Invariant/Sensitive, Orientation Invariant/Sensitive).

## Detailed Functionality

### File Format
Custom binary format:
1.  Version (Short)
2.  Entry Count (Int)
3.  Entries:
    - Name (UTF)
    - Gesture Count (Int)
    - Gestures (Serialized)

### Recognition (`recognize`)
1.  Converts the input `Gesture` into an `Instance` (feature vector).
2.  Delegates to `mClassifier.classify()`.

### Management
- `addGesture`, `removeGesture`, `getGestures`: CRUD operations on the store.

## Java-to-C++ Translation Guide
- **Data Structures**: Use `std::map<std::string, std::vector<Gesture>>`.
- **Streams**: Ensure binary compatibility with the Java serialization format if interoperability is required.

## Source Reference
Defined in `GestureStore.java`.
