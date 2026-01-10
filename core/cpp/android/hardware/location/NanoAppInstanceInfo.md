# NanoAppInstanceInfo - Reverse Engineering Documentation

## Executive Summary
`NanoAppInstanceInfo` is a deprecated class describing a running instance of a nanoapp. Replaced by `NanoAppState`.

## Architecture Overview
- **Status**: **DEPRECATED**.
- **Role**: Legacy status object.

## Data Model
- `mHandle`, `mAppId`, `mAppVersion`, `mContexthubId`.

## Java-to-C++ Translation Guide
- **Replacement**: Use `NanoAppState`.

## Questions for C++ Team
- None.
