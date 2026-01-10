# SystemUpdatePolicy - Reverse Engineering Documentation

## 1. Executive Summary
`SystemUpdatePolicy` is a final, `Parcelable` class that encapsulates an Android device's policy for over-the-air (OTA) system updates. It allows a Device Policy Controller (DPC) (specifically a Device Owner or Profile Owner on an organization-owned device) to control when system updates are installed. The policy can be set to automatic installation, windowed installation (during a daily maintenance window), or postponement. Additionally, it supports "freeze periods," which are recurring annual windows where updates are completely blocked. The class includes methods for creating different policy types, retrieving configuration, and managing freeze periods, as well as XML serialization/deserialization for persistence.

## 2. Architecture Overview
`SystemUpdatePolicy` is a complex value object that combines several distinct update management strategies within a single entity. It centralizes rules for timing, deferral, and blocking of system updates. Its design incorporates helper classes like `FreezePeriod` for date-specific logic and an inner class `InstallationOption` to convey the current effective policy to system clients.

### Design Patterns
- **Value Object**: Represents an immutable policy configuration once built (though it has setters for freeze periods). Its internal state (`mPolicyType`, `mMaintenanceWindowStart`, `mMaintenanceWindowEnd`, `mFreezePeriods`) defines the policy.
- **Factory Methods**: Provides static `createAutomaticInstallPolicy()`, `createWindowedInstallPolicy()`, and `createPostponeInstallPolicy()` methods for easy, type-specific policy creation.
- **Composition**: Uses `ArrayList<FreezePeriod>` to manage multiple freeze periods, delegating date logic to the `FreezePeriod` class.
- **Nested Class (`InstallationOption`)**: Provides a structured way for internal system clients to query the effective update behavior at a given time.

## 3. Detailed Functionality

### Policy Types
- **`TYPE_INSTALL_AUTOMATIC` (1)**: Updates install immediately when available.
- **`TYPE_INSTALL_WINDOWED` (2)**: Updates install during a daily maintenance window.
- **`TYPE_POSTPONE` (3)**: Updates are postponed for a maximum of 30 days.
- **`TYPE_PAUSE` (4)**: Internally used to block updates, e.g., during a freeze period.

### `ValidationFailedException` (Nested Class)
- **Purpose**: A custom exception class to report specific validation errors related to freeze periods.
- **Algorithm**: Contains integer error codes (e.g., `ERROR_DUPLICATE_OR_OVERLAP`, `ERROR_NEW_FREEZE_PERIOD_TOO_LONG`) and provides static factory methods to create instances with predefined messages.

### Constructors / Factory Methods
- **`SystemUpdatePolicy()` (private)**: Default constructor, initializes `mPolicyType` to `TYPE_UNKNOWN` and `mFreezePeriods` as an empty list.
- **`createAutomaticInstallPolicy()`**: Returns a new policy instance set to `TYPE_INSTALL_AUTOMATIC`.
- **`createWindowedInstallPolicy(int startTime, int endTime)`**: Returns a new policy set to `TYPE_INSTALL_WINDOWED`. Validates `startTime` and `endTime` are within `[0, 1440)` minutes from midnight.
- **`createPostponeInstallPolicy()`**: Returns a new policy instance set to `TYPE_POSTPONE`.

### Getters
- **`getPolicyType()`**: Returns the integer type of the policy.
- **`getInstallWindowStart()` / `getInstallWindowEnd()`**: Return the start/end time of the maintenance window if `TYPE_INSTALL_WINDOWED`, otherwise -1.
- **`getFreezePeriods()`**: Returns an unmodifiable list of configured `FreezePeriod` objects.

### Validation Methods
- **`isValid()`**: Checks if the policy object has a correct type, valid maintenance window, and valid freeze periods.
- **`validateType()`**: Throws `IllegalArgumentException` if the `mPolicyType` or maintenance window settings are invalid.
- **`setFreezePeriods(List<FreezePeriod> freezePeriods)`**: Sets the list of freeze periods. Critically, it calls `FreezePeriod.validatePeriods()` to ensure the periods adhere to rules (max 90 days length, min 60 days separation, no overlaps/duplicates).
- **`validateFreezePeriods()`**: Calls `FreezePeriod.validatePeriods()` on its internal list.
- **`validateAgainstPreviousFreezePeriod(...)`**: Verifies new freeze periods against historical ones to prevent exceeding maximum combined freeze durations or violating separation rules.

### `InstallationOption` (Nested Class)
- **Purpose**: A small class to convey the effective update action and its duration to system update clients.
- **Algorithm**: Contains `mType` (e.g., `TYPE_INSTALL_AUTOMATIC`, `TYPE_PAUSE`, `TYPE_POSTPONE`) and `mEffectiveTime` (how long this option is valid).

### `getInstallationOptionAt(long when)`
- **Purpose**: Determines the effective installation option for system updates at a specific point in time, considering the policy type and any active freeze periods.
- **Algorithm**:
    1.  Checks if `when` falls within any configured `FreezePeriod`. If so, returns `TYPE_PAUSE` with an effective time until the end of that freeze.
    2.  Otherwise, delegates to `getInstallationOptionRegardlessFreezeAt()` to determine the basic policy action.
    3.  If freeze periods exist, `limitEffectiveTime()` is called to reduce the effective time of the basic policy if the next freeze period starts sooner.

### Date Conversion Helpers
- **`millisToDate(long when)`**: Converts a timestamp to `LocalDate` using the default timezone.
- **`dateToMillis(LocalDate when)`**: Converts `LocalDate` (at midnight) to a timestamp.
- **`roundUpLeapDay(LocalDate date)`**: Helper to normalize dates for leap years, treating Feb 28 as Feb 29 for calculations.

### XML Serialization/Deserialization
- **`saveToXml(TypedXmlSerializer out)`**: Writes the policy type, maintenance window start/end, and all freeze periods (with start/end month-day) to an XML stream.
- **`restoreFromXml(TypedXmlPullParser parser)`**: Reads policy configuration from an XML stream, including handling nested `<freeze>` tags.

## 4. Data Model
- **`mPolicyType`**: `private int` (`@SystemUpdatePolicyType`)
  - **Description**: The currently active update policy type.
- **`mMaintenanceWindowStart`**: `private int`
  - **Description**: Start time of the maintenance window in minutes from midnight, for `TYPE_INSTALL_WINDOWED`.
- **`mMaintenanceWindowEnd`**: `private int`
  - **Description**: End time of the maintenance window in minutes from midnight, for `TYPE_INSTALL_WINDOWED`.
- **`mFreezePeriods`**: `private final ArrayList<FreezePeriod>`
  - **Description**: A list of annual freeze periods during which updates are blocked.

## 5. Java-to-C++ Translation Guide
- **Class Structure**: A C++ equivalent would be a class with members mirroring the Java class, using `int` for policy types and window times, and `std::vector<FreezePeriod>` for freeze periods.
- **`FreezePeriod` Integration**: The `FreezePeriod` class itself would need to be translated to C++, encapsulating its date arithmetic and validation logic.
- **Date/Time Library**: Java's `java.time` APIs would be replaced with a robust C++ date/time library (e.g., `HowardHinnant/date` or Boost.DateTime) for handling `LocalDate`, `MonthDay`, and conversions.
- **XML Serialization**: A C++ XML library (e.g., pugixml, tinyxml2) would be used to replicate the `saveToXml` and `restoreFromXml` functionality, ensuring compatibility if cross-language persistence is required.
- **`Parcelable`**: A custom C++ serialization/deserialization mechanism would be required for IPC, carefully replicating the order and types written to the Java `Parcel`. This includes iterating through the `mFreezePeriods` list and serializing each `MonthDay`.

## 6. Implementation Risks & Key Considerations
- **Date/Time Logic Complexity**: Date calculations, especially involving year-end wraps and leap years, are complex. The Java implementation uses a clever normalization strategy to a 365-day sentinel year; the C++ implementation must replicate this logic precisely to avoid subtle bugs.
- **Validation Rules**: The validation rules for freeze periods (max length, min separation, no overlaps) are critical. The C++ implementation must strictly enforce these to maintain system stability and predictable update behavior.
- **XML Format Compatibility**: If the C++ implementation needs to read policies written by Java, or vice-versa, the XML serialization format must be perfectly compatible.

## 7. Questions for C++ Team
1.  What date/time library is preferred for this C++ project to handle `LocalDate`, `MonthDay`, and time zone conversions?
2.  What XML parsing/serialization library should be used, and are there specific formatting requirements for policy persistence to ensure compatibility with existing Android components?
3.  How will the `ValidationFailedException` and its specific error codes be represented in C++ (e.g., custom exception class, `std::runtime_error` with error codes)?
