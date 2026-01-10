# IpConnectivityLog.java - Reverse Engineering Documentation

## Executive Summary
`IpConnectivityLog` is a client-side wrapper for logging networking events to the `IIpConnectivityMetrics` service. It handles service retrieval and object parceling.

## Architecture Overview
- **Type**: Service Client / Logger
- **Package**: `android.net.metrics`
- **Service**: `connmetrics` (`IIpConnectivityMetrics`).

## Functionality
-   `log(Event)`: Wraps the specific event (like `DnsEvent` or `ApfProgramEvent`) into a `ConnectivityMetricsEvent` parcelable and sends it to the service.
-   `logDefaultNetworkEvent(...)`: Logs default network changes.

## Java-to-C++ Translation Guide
-   This is the "Producer" side. In C++, you would likely write to a different logging backend (e.g., StatsD) directly, as `connmetrics` is being deprecated in favor of StatsD.
