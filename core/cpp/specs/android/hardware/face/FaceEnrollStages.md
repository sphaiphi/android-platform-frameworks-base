# FaceEnrollStages - Reverse Engineering Documentation

## Executive Summary
`FaceEnrollStages` defines constants representing the different stages of the face enrollment process. This is a utility class for constants only.

## Architecture Overview
- **Type**: Constant Definition Class.
- **Usage**: Used by `FaceEnrollFrame`.

## Constants (FaceEnrollStage)
- `UNKNOWN` (0)
- `FIRST_FRAME_RECEIVED` (1)
- `WAITING_FOR_CENTERING` (2)
- `HOLD_STILL_IN_CENTER` (3)
- `ENROLLING_MOVEMENT_1` (4)
- `ENROLLING_MOVEMENT_2` (5)
- `ENROLLMENT_FINISHED` (6)

## Java-to-C++ Translation Guide
- **Enum**: Map these constants to a C++ `enum class`.

