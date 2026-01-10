# TriggerEventListener - Reverse Engineering Documentation

## Executive Summary
`TriggerEventListener` is the callback interface for receiving events from trigger-based sensors.

## Architecture Overview
Used with `SensorManager.requestTriggerSensor`. It is distinct from `SensorEventListener` because trigger sensors are one-shot and don't provide a continuous stream of data.

## Detailed Functionality

### `onTrigger(TriggerEvent event)`
**Purpose**: Called when the trigger condition is met.
**Lifecycle**: After this call, the listener is automatically unregistered for that sensor. To receive further triggers, the app must call `requestTriggerSensor` again.

## Java-to-C++ Translation Guide
- **Interface**: `abstract class TriggerEventListener` -> `class ITriggerEventListener`.
- **Method**: `virtual void onTrigger(const TriggerEvent& event) = 0;`.

## Implementation Risks
- Ensuring the "auto-disable" logic is correctly implemented in the manager layer to avoid extra IPC or interrupts.
