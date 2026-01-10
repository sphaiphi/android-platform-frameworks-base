# GeofenceHardwareMonitorEvent - Reverse Engineering Documentation

## Executive Summary
`GeofenceHardwareMonitorEvent` wraps details about a change in the monitoring system's status. It includes the type (GPS/Fused), the new status (Available/Unavailable), source technologies, and the last known location.

## Architecture Overview
- **Pattern**: Value Object / Event Object.
- **Inheritance**: Implements `android.os.Parcelable`.

## Data Model
| Field | Type | Description |
|---|---|---|
| `mMonitoringType` | `int` | Type of monitor (GPS/Fused). |
| `mMonitoringStatus` | `int` | Status (Available/Unavailable). |
| `mSourceTechnologies` | `int` | Bitmap of sources (GNSS, Wifi, etc.). |
| `mLocation` | `Location` | Last known location. |

## Java-to-C++ Translation Guide
- **Data Structure**: Simple struct.
- **Location**: Use the C++ equivalent of `android.location.Location`.

## Questions for C++ Team
- None.
