# TexturedMesh - Reverse Engineering Documentation

## Executive Summary
`TexturedMesh` holds the geometry and texture data for a 3D object. It is a core component of the `CinematicEffectResponse`. To handle potentially large vertex/index arrays, it uses a Blob (mapped to Ashmem) for IPC transport.

## Architecture Overview
- **Package**: `android.app.wallpapereffectsgeneration`
- **Implements**: `Parcelable`
- **Role**: 3D Geometry Container.

## Detailed Functionality

### Data Storage
- **Texture**: A `Bitmap`.
- **Indices**: Array of integers defining primitives (e.g., triangles).
- **Vertices**: Array of floats defining point data (Position + UV).
- **Layouts**: Integer constants defining how to interpret the arrays (e.g., `VERTICES_LAYOUT_POSITION3_UV2` implies 5 floats per vertex: x, y, z, u, v).

### Optimized Serialization
**Purpose**: Avoid transaction limit errors (Binder 1MB limit) for complex meshes.
**Algorithm**:
1. **Write**:
   - Writes Layout types (ints).
   - Writes the Bitmap (TypedObject).
   - creates a temporary `Parcel` (`data`).
   - Writes `mIndices` (int array) and `mVertices` (float array) into `data`.
   - Marshalls `data` into a byte array (Blob).
   - Writes the Blob to the main Parcel. (The system handles large Blobs by passing a file descriptor to shared memory).
2. **Read**:
   - Reads Layouts and Bitmap.
   - Reads the Blob.
   - Unmarshalls the Blob into a new `Parcel`.
   - Reads the arrays from that parcel.

## Data Model

| Field | Type | Description |
|-------|------|-------------|
| `mBitmap` | `Bitmap` | Texture image. |
| `mIndices` | `int[]` | Index buffer. |
| `mVertices` | `float[]` | Vertex buffer (interleaved). |
| `mIndicesLayoutType` | `int` | Describes primitive topology. |
| `mVerticesLayoutType` | `int` | Describes vertex attribute layout. |

## Java-to-C++ Translation Guide

- **Blob Handling**: This is the most critical part.
  - Java: `Parcel.writeBlob()`.
  - C++: `Parcel::writeBlob()` (available in `binder/Parcel.h`).
  - The "Marshall/Unmarshall" nested parcel trick is a Java-specific way to serialize the arrays into a contiguous block.
  - **Correction for C++**: In C++, you might not need the nested `Parcel` if you can write the raw arrays directly to the Blob, OR you must replicate the nested Parcel structure if interoperating with Java.
  - **CRITICAL**: The Java code *marshalls a Parcel containing the arrays*. It does *not* just write the raw bytes of the arrays. The C++ code must read the blob, create a Parcel from the blob data, and then read the int array and float array from that temporary Parcel.

## Implementation Risks
- **Data Alignment**: Ensure float/int sizes are consistent.
- **Blob Compatibility**: If the C++ side writes a raw buffer but Java expects a marshalled Parcel inside the blob, deserialization will fail. The C++ side *must* serialize a Parcel into the blob if it acts as the sender (Service side), or parse a Parcel from the blob if it acts as the receiver (Client side, though usually this class is returned *from* service *to* client).

## Test Cases & Validation
- **Large Mesh Test**: Create a mesh > 1MB. Verify it passes through Binder without `TransactionTooLargeException`.

## Questions for C++ Team
- Does the C++ Binder API expose `unmarshall` (create parcel from data) publicly/easily? (Yes, `Parcel::setData`).
