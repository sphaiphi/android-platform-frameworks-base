# FreezePeriod - Reverse Engineering Documentation

## 1. Executive Summary
`FreezePeriod` is a class that represents a recurring, annual window of time during which system updates are blocked. It is a core component of the `SystemUpdatePolicy` framework. The class is defined by a start and end `MonthDay` and contains sophisticated logic to handle date calculations, including periods that wrap around the end of the year and normalization for leap years. It also provides a suite of static utility methods for validating and canonicalizing lists of freeze periods according to a set of business rules.

## 2. Architecture Overview
`FreezePeriod` is a value object designed to encapsulate the logic of an annual date interval. It is not `Parcelable` itself, but is serialized manually by its containing class, `SystemUpdatePolicy`.

- **Date Abstraction**: The class's key architectural decision is to abstract away the complexity of leap years. It internally represents all dates as a "day of the year" (1-365) by mapping them to a non-leap sentinel year (2001). This greatly simplifies all interval arithmetic, such as calculating lengths and distances.
- **Interval Logic**: It contains robust logic to handle both simple intervals (e.g., March 1 to March 31) and "wrapped" intervals that span the year-end (e.g., December 1 to January 31).
- **Validation Utility**: A significant portion of the class consists of `static` methods that act as a validation and utility library for `SystemUpdatePolicy`. These methods enforce business rules about the maximum length of freeze periods and the minimum separation between them.

### Design Patterns
- **Value Object**: An instance of `FreezePeriod` represents an immutable time interval. Its `mStart` and `mEnd` fields are final.
- **Utility Class**: The `static` methods (`canonicalizePeriods`, `validatePeriods`, etc.) make the class also serve as a utility library for its domain.

## 3. Detailed Functionality

### `FreezePeriod(MonthDay start, MonthDay end)`
- **Purpose**: The primary constructor.
- **Algorithm**:
    1.  Stores the start and end `MonthDay` objects.
    2.  Calculates and stores the integer day-of-year representation (`mStartDay`, `mEndDay`) for both dates, using the non-leap sentinel year to normalize the values.

### `contains(LocalDate localDate)`
- **Purpose**: Checks if a given `LocalDate` falls within the freeze period.
- **Algorithm**:
    1.  Normalizes the input `localDate` to its day-of-year in the sentinel non-leap year.
    2.  If the period is not wrapped (`mStartDay <= mEndDay`), it performs a simple range check: `mStartDay <= day <= mEndDay`.
    3.  If the period is wrapped, it checks if the day is in either of the two parts of the interval: `mStartDay <= day` OR `day <= mEndDay`.

### `toCurrentOrFutureRealDates(LocalDate now)`
- **Purpose**: A complex but crucial hidden method. Given a reference date (`now`), it projects the abstract `MonthDay` interval onto the actual calendar to find the concrete `LocalDate` range for the current or next-upcoming freeze period instance.
- **Algorithm**: It determines the correct year for both the start and end dates by checking if `now` is already inside the period or before/after it, and whether the period wraps the year-end. This involves adding or subtracting years from `now.getYear()` as needed.

### `static List<FreezePeriod> canonicalizePeriods(List<FreezePeriod> intervals)`
- **Purpose**: Merges overlapping or adjacent periods in a list into a minimal, sorted set of disjoint periods.
- **Algorithm**: A clever, robust approach:
    1.  Creates a `boolean` array of 365 days.
    2.  Iterates through the input list of `FreezePeriod`s, "painting" the corresponding days in the boolean array to `true`. This flattens all complex interval logic.
    3.  Iterates through the boolean array, reconstructing a new list of `FreezePeriod` objects from the contiguous blocks of `true` values.
    4.  Performs a final check to merge a period ending on day 365 with one starting on day 1 into a single wrapped period.

### `static void validatePeriods(List<FreezePeriod> periods)`
- **Purpose**: Enforces business rules on a list of freeze periods.
- **Algorithm**:
    1.  First, canonicalizes the list. If the size changes, it means there were duplicates or overlaps, and it throws a `ValidationFailedException`.
    2.  Iterates through the canonical list and checks that each period's length is not greater than `FREEZE_PERIOD_MAX_LENGTH` (90 days).
    3.  Calculates the separation between each adjacent period, handling the wrap-around case between the last and first periods.
    4.  Checks that the separation is not less than `FREEZE_PERIOD_MIN_SEPARATION` (60 days).
    5.  Throws a specific `ValidationFailedException` if any rule is violated.

## 4. Data Model
- **`mStart`, `mEnd`**: `private final MonthDay`. The public representation of the start and end dates.
- **`mStartDay`, `mEndDay`**: `private final int`. The internal, normalized day-of-year (1-365) representation used for all calculations.

## 5. Java-to-C++ Translation Guide
- **`java.time`**: The `java.time` package is extensive. A C++ implementation would need to use a robust date/time library, such as `HowardHinnant/date` (which is the basis for C++20's `<chrono>` extensions) or Boost.DateTime.
- **Core Logic**: The core logic of normalizing to a 365-day year and handling wrapped intervals is directly translatable. The `canonicalizePeriods` algorithm using a boolean array is also easily ported.
- **No `Parcelable`**: Since the class is not directly `Parcelable`, no custom C++ IPC serialization is needed for the class itself, but rather for its container, `SystemUpdatePolicy`.

## 6. Implementation Risks & Key Considerations
- **Date/Time Complexity**: Date and time calculations are notoriously prone to off-by-one errors and edge case bugs (like leap years). The class's strategy of normalizing to a 365-day year is a good way to mitigate this, and a C++ port should adopt the same strategy to ensure identical behavior.
- **Validation Logic**: The validation rules are strict and have specific error types. A C++ implementation must replicate this validation precisely to maintain compatibility with the Android framework's expectations.

## 7. Questions for C++ Team
1.  Which date and time library is standard for this C++ project?
2.  How should exceptions corresponding to `ValidationFailedException` be handled? Should we use a custom exception class with error codes, or standard exceptions like `std::invalid_argument`?
