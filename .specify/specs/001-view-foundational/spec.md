# Feature: Foundational View Classes

**Feature ID:** 001-view-foundational
**Status:** Draft
**Created:** 2026-06-07

## Overview

This feature establishes the core building blocks of a standalone implementation that mirrors the behavior and API of the Java `android.view.*` package. It implements four foundational classes: `View` (the basic UI element occupying a rectangular area on screen), `ViewGroup` (a container that holds and arranges other views), `ViewParent` (the contract interface for parent-child communication), and `ViewManager` (the contract for adding, updating, and removing views from a container). This system provides the structural foundation upon which all higher-level UI components -- widgets, layouts, animations, and rendering -- are built. It is a native implementation, not a JNI wrapper, targeting NDK developers who need a complete UI framework using modern, safe, and efficient C++ features.

## Goals

- Allow developers to instantiate and manage UI elements (`View`) with full lifecycle support (measure, layout, draw).
- Enable hierarchical composition of UI by allowing `ViewGroup` to contain and arrange multiple child views.
- Define a bidirectional communication contract (`ViewParent`) between parent and child views for layout requests, invalidation, focus, and event dispatch.
- Provide a uniform interface (`ViewManager`) for adding, updating, and removing views from a container.
- Implement the View property system supporting position, size, visibility, alpha, rotation, scale, and translation.
- Establish touch event dispatch infrastructure that routes motion events from the root of the hierarchy to the appropriate target view.

## Non-Goals (Out of Scope)

- Widget classes (TextView, Button, ImageView, EditText, etc.) -- these are built on top of View.
- Layout managers (LinearLayout, RelativeLayout, FrameLayout, etc.) -- these are built on top of ViewGroup.
- Animation system -- already partially implemented as ViewPropertyAnimator in a prior feature.
- Rendering pipeline (RenderNode, HWUI, hardware acceleration) -- the spec defines the draw infrastructure hooks but not the GPU-backed rendering.
- Input method integration (InputConnection, IME handling).
- Accessibility (AccessibilityEvent, AccessibilityNodeInfo, TalkBack integration).
- Window management (WindowManager, Surface management, window tokens).
- XML layout inflation.
- Drag and drop infrastructure.
- Nested scrolling.
- Autofill.
- Content capture.
- Touch filtering for security (obscured-window touch filtering).
- Context menus and action modes.
- Scrollbars.
- Haptic feedback.
- Keyboard navigation clusters.

## User Roles

| Role | Description |
|------|-------------|
| Framework Developer | Implements and extends View/ViewGroup to create custom widgets or layout managers. |
| NDK Developer | Uses the C++ View system to construct UI hierarchies programmatically. |
| Test Engineer | Validates behavioral compliance against the Java reference implementation. |
| View | The primary entity for UI components in the hierarchy. |

## User Stories

### View Lifecycle

**US-01:** As a Framework Developer, I want to create a View with a Context so that it can participate in the view hierarchy.
  - Acceptance Criteria:
    - [ ] A View can be constructed with a Context argument.
    - [ ] The View initializes with default property values (VISIBLE, no padding, 1.0 alpha, no rotation/scale/translation).
    - [ ] The View starts in an unmeasured, unlaid-out state.

**US-02:** As a Framework Developer, I want the View to support a measure-pass so that it can determine its desired size.
  - Acceptance Criteria:
    - [ ] A View can receive a measure call with width and height specifications.
    - [ ] The View stores measured width and measured height accessible after measurement.
    - [ ] The View respects the parent's measure specification constraints (EXACTLY, AT_MOST, UNSPECIFIED).
    - [ ] A View can be overridden to customize measurement behavior.

**US-03:** As a Framework Developer, I want the View to support a layout pass so that it can position itself within its parent.
  - Acceptance Criteria:
    - [ ] A View can be laid out with left, top, right, bottom coordinates.
    - [ ] After layout, getLeft(), getTop(), getRight(), getBottom(), getWidth(), getHeight() return correct values.
    - [ ] The View stores its layout position relative to its parent.

**US-04:** As a Framework Developer, I want the View to support a draw pass so that it can render its content.
  - Acceptance Criteria:
    - [ ] A View can be drawn via a draw method accepting a canvas-like object.
    - [ ] The draw method calls background rendering, then content rendering, then foreground rendering.
    - [ ] Subclasses can override the content rendering hook to provide custom drawing.

### View Properties

**US-05:** As an NDK Developer, I want to set and query View properties (position, size, visibility, alpha, rotation, scale, translation) so that I can control the visual appearance of a View.
  - Acceptance Criteria:
    - [ ] getVisibility() and setVisibility() support VISIBLE, INVISIBLE, and GONE states.
    - [ ] GONE visibility excludes the View from layout calculations.
    - [ ] INVISIBLE visibility hides the View but preserves its layout space.
    - [ ] setAlpha() and getAlpha() control transparency with a range of 0.0 to 1.0.
    - [ ] setRotation(), setRotationX(), setRotationY(), setRotationZ() and their getters control rotation around Z, X, Y, and Z axes.
    - [ ] setScaleX(), setScaleY() and their getters control scaling.
    - [ ] setTranslationX(), setTranslationY() and their getters control offset from the layout position.
    - [ ] The effective drawing position accounts for translation in addition to layout position.
    - [ ] The effective drawing dimensions account for scale and rotation.

**US-06:** As an NDK Developer, I want to set and query padding so that I can offset a View's content from its bounds.
  - Acceptance Criteria:
    - [ ] setPadding(10, 20, 30, 40) causes getPaddingLeft() to return 10, getPaddingTop() to return 20, getPaddingRight() to return 30, getPaddingBottom() to return 40.
    - [ ] Padding is subtracted from the available drawing area but does not affect the View's overall bounds (getWidth() == getRight() - getLeft() regardless of padding).
    - [ ] getPaddingStart() returns getPaddingLeft() when layout direction is LTR, and getPaddingRight() when layout direction is RTL. getPaddingEnd() returns the opposite.

**US-07:** As an NDK Developer, I want to set and query a View ID so that I can identify a specific View within a hierarchy.
  - Acceptance Criteria:
    - [ ] setId() and getId() store and retrieve an integer identifier.
    - [ ] The default ID value is NO_ID (-1).

**US-08:** As an NDK Developer, I want to attach an arbitrary object as a tag to a View so that I can associate data with it.
  - Acceptance Criteria:
    - [ ] setTag() and getTag() store and retrieve an associated object.
    - [ ] The tag is initially null.

### ViewParent Contract

**US-09:** As a View, I want to request layout from my parent via ViewParent so that the hierarchy re-measures and re-lays out when my size requirements change.
  - Acceptance Criteria:
    - [ ] A View can call requestLayout() on itself.
    - [ ] requestLayout() propagates upward through the ViewParent chain.
    - [ ] Each ViewParent in the chain calls requestLayout() on its own parent.
    - [ ] A ViewParent can query whether layout has been requested via isLayoutRequested().

**US-10:** As a View, I want to signal invalidation to my parent via ViewParent so that the hierarchy knows it needs to redraw.
  - Acceptance Criteria:
    - [ ] A View can call invalidate() to mark itself as needing redraw.
    - [ ] invalidate() propagates upward through the ViewParent chain via onDescendantInvalidated().
    - [ ] The propagation stops at the root parent.

**US-11:** As a View, I want to request focus through the ViewParent hierarchy so that I can receive keyboard and directional input.
  - Acceptance Criteria:
    - [ ] A View can call requestFocus().
    - [ ] Focus requests propagate through ViewParent via requestChildFocus() and clearChildFocus().
    - [ ] A ViewParent can search for the nearest focusable view in a direction via focusSearch().

### ViewGroup Child Management

**US-12:** As a Framework Developer, I want ViewGroup to manage a collection of child views so that I can compose complex UI hierarchies.
  - Acceptance Criteria:
    - [ ] ViewGroup maintains an ordered list of child views.
    - [ ] getChildCount() returns the number of direct children.
    - [ ] getChildAt(index) returns the child at the given position.
    - [ ] Children are iterated in z-order: back-to-front for drawing (child at index 0 drawn first / at the back), front-to-back for touch dispatch (child at highest index tested first / at the front).

**US-13:** As a Framework Developer, I want ViewGroup to propagate measure and layout passes to all children so that the entire hierarchy is sized and positioned.
  - Acceptance Criteria:
    - [ ] When ViewGroup is measured, it measures each child according to the child's LayoutParams.
    - [ ] When ViewGroup is laid out, it positions each child within its bounds.
    - [ ] Children that are GONE are skipped during measure and layout.
    - [ ] The measure pass is top-down; the layout pass is top-down.

**US-14:** As a Framework Developer, I want ViewGroup to draw all its children so that the composite UI is rendered.
  - Acceptance Criteria:
    - [ ] ViewGroup draws its background, then each child in z-order, then its foreground.
    - [ ] Child drawing respects clip children and clip to padding flags.
    - [ ] Children outside the ViewGroup bounds (when clip children is enabled) are not drawn.

### ViewGroup Layout Parameters

**US-15:** As a Framework Developer, I want ViewGroup to define LayoutParams so that children can declare their desired sizing behavior.
  - Acceptance Criteria:
    - [ ] LayoutParams supports specifying width and height as an exact value, MATCH_PARENT, or WRAP_CONTENT.
    - [ ] LayoutParams can carry margin values (left, top, right, bottom).
    - [ ] Each child in a ViewGroup carries its own LayoutParams instance.

### Touch Event Dispatch

**US-16:** As a Framework Developer, I want touch events to be dispatched from the root of the hierarchy down to the appropriate child View so that user interactions are handled correctly.
  - Acceptance Criteria:
    - [ ] A MotionEvent is delivered to the topmost View whose bounds contain the event coordinates.
    - [ ] ViewGroup can intercept touch events before they reach children (onInterceptTouchEvent).
    - [ ] A child can request that the parent not intercept touch events (requestDisallowInterceptTouchEvent).
    - [ ] Touch events that are not consumed by any child are delivered to the ViewGroup itself.
    - [ ] ACTION_DOWN starts a new touch target; ACTION_MOVE and ACTION_UP are delivered to the view that received the ACTION_DOWN.

### ViewManager Contract

**US-17:** As a Framework Developer, I want to add a View to a container with LayoutParams so that it becomes part of the UI hierarchy.
  - Acceptance Criteria:
    - [ ] addView(view, params) assigns the LayoutParams to the view and adds it as a child.
    - [ ] The added view's parent is set to the container.
    - [ ] A layout pass is triggered after adding a view.

**US-18:** As a Framework Developer, I want to update the LayoutParams of an existing view so that its sizing behavior can change dynamically.
  - Acceptance Criteria:
    - [ ] updateViewLayout(view, newParams) replaces the existing LayoutParams on the view.
    - [ ] A layout pass is triggered after updating LayoutParams.

**US-19:** As a Framework Developer, I want to remove a View from a container so that it is no longer part of the UI hierarchy.
  - Acceptance Criteria:
    - [ ] removeView(view) removes the view from the container's child list.
    - [ ] The view's parent reference is cleared.
    - [ ] A layout pass is triggered after removing a view.

## Functional Requirements

### View Construction and Initialization

**FR-01 (US-01):** The system shall provide a View constructor that accepts a Context argument and initializes all properties to their default values.
**FR-02 (US-01):** The system shall initialize a View with the following defaults: visibility = VISIBLE, alpha = 1.0, rotationX = 0, rotationY = 0, rotationZ = 0, scaleX = 1.0, scaleY = 1.0, translationX = 0, translationY = 0, padding = (0, 0, 0, 0), id = NO_ID, tag = null, minWidth = 0, minHeight = 0.

### View Measurement

**FR-03 (US-02):** The system shall provide a measure() method that accepts width and height specifications and stores the resulting measured dimensions.
**FR-04 (US-02):** The system shall provide onMeasure() as an overridable method that subclasses implement to compute their desired size.
**FR-05 (US-02):** The system shall provide getMeasuredWidth() and getMeasuredHeight() returning the last measured dimensions.
**FR-06 (US-02):** The system shall support measure specification modes: EXACTLY, AT_MOST, and UNSPECIFIED.

### View Layout

**FR-07 (US-03):** The system shall provide a layout() method that sets the view's left, top, right, bottom coordinates.
**FR-08 (US-03):** The system shall provide onLayout() as an overridable method (no-op in View, implemented in ViewGroup).
**FR-09 (US-03):** The system shall provide getLeft(), getTop(), getRight(), getBottom(), getWidth(), getHeight() returning the current layout position and dimensions.
**FR-10 (US-03):** The system shall provide requestLayout() that marks the view as needing layout and propagates upward through the ViewParent chain.
**FR-11 (US-03):** The system shall provide isLayoutRequested() that returns true if layout has been requested and not yet completed.

### View Drawing

**FR-12 (US-04):** The system shall provide a draw() method that executes the drawing sequence: background, content, foreground.
**FR-13 (US-04):** The system shall provide onDraw() as an overridable method for subclasses to render their content.
**FR-14 (US-04):** The system shall provide invalidate() that marks the view as needing redraw and propagates the invalidation signal upward.

### Canvas Interface (Minimal In-Scope Drawing Surface)

**FR-14a (US-04):** The system shall define a minimal Canvas interface with the following methods: `drawColor(int color)`, `drawRect(float left, float top, float right, float bottom)`, `save()`, `restore()`, `clipRect(float left, float top, float right, float bottom)`, `translate(float dx, float dy)`. This is the minimal set needed for background/content/foreground drawing. The full Canvas from HWUI is out of scope.

### View Properties

**FR-15 (US-05):** The system shall provide getVisibility()/setVisibility() supporting three distinct visibility states: Visible, Invisible, and Gone.
**FR-16 (US-05):** The system shall trigger a layout pass when visibility changes to or from GONE.
**FR-17 (US-05):** The system shall provide getAlpha()/setAlpha() with a range of 0.0 to 1.0, defaulting to 1.0.
**FR-18 (US-05):** The system shall provide getRotation()/setRotation(), getRotationX()/setRotationX(), getRotationY()/setRotationY(), getRotationZ()/setRotationZ() in degrees, defaulting to 0.
**FR-19 (US-05):** The system shall provide getScaleX()/setScaleX() and getScaleY()/setScaleY() defaulting to 1.0.
**FR-20 (US-05):** The system shall provide getTranslationX()/setTranslationX() and getTranslationY()/setTranslationY() in pixels, defaulting to 0.
**FR-21 (US-05):** The system shall provide getMinWidth()/setMinWidth() and getMinHeight()/setMinHeight() in pixels, defaulting to 0. These are needed for WRAP_CONTENT fallback in measure().
**FR-22 (US-06):** The system shall provide getPaddingLeft()/getPaddingTop()/getPaddingRight()/getPaddingBottom()/setPadding() and getPaddingStart()/getPaddingEnd().
**FR-23 (US-06):** The system shall provide getLayoutDirection()/setLayoutDirection() returning/setting the layout direction (LayoutDirection.Ltr, LayoutDirection.Rtl), defaulting to LTR. getPaddingStart()/getPaddingEnd() compute based on the view's layout direction.
**FR-24 (US-07):** The system shall provide getId()/setId() with integer ID storage, defaulting to NO_ID (-1).
**FR-25 (US-08):** The system shall provide getTag()/setTag() for arbitrary object association.
**FR-26 (US-11):** The system shall provide isFocusable()/setFocusable() and isClickable()/setClickable() as View flag properties. These are required for focus management and touch event consumption.

### ViewParent Interface

**FR-27 (US-09):** The system shall define ViewParent with a requestLayout() method that triggers hierarchy-wide layout recalculation.
**FR-28 (US-09):** The system shall define ViewParent with an isLayoutRequested() method.
**FR-29 (US-10):** The system shall define ViewParent with an onDescendantInvalidated(View child, View target) method that propagates invalidation upward.
**FR-30 (US-10):** The system shall define ViewParent with a getParent() method returning the parent ViewParent or null.
**FR-31 (US-11):** The system shall define ViewParent with requestChildFocus(View child, View focused) and clearChildFocus(View child).
**FR-32 (US-11):** The system shall define ViewParent with focusSearch(View v, int direction) returning the nearest focusable view in the given direction.

### ViewGroup Child Management

**FR-33 (US-12):** The system shall define ViewGroup as publicly inheriting View and privately composing ViewParent/ViewManager via CRTP: `class ViewGroup : public View, private ViewParentMixin<ViewGroup>, private ViewManagerMixin<ViewGroup>`. ViewGroup casts `this` to ViewParent/ViewManager via static_cast.
**FR-34 (US-12):** The system shall provide getChildCount() returning the number of direct children.
**FR-35 (US-12):** The system shall provide getChildAt(int index) returning the child at the specified index.
**FR-36 (US-13):** The system shall provide measureChildren() that measures all non-GONE children.
**FR-37 (US-13):** The system shall provide layoutChildren() that positions all children within the ViewGroup bounds.
**FR-38 (US-13):** The system shall provide dispatchDraw() that draws the background, then each child, then the foreground.
**FR-39 (US-15):** The system shall define a concrete LayoutParams class hierarchy: `class LayoutParams` (width, height), `class MarginLayoutParams : LayoutParams` (leftMargin, topMargin, rightMargin, bottomMargin). ViewGroup uses template-based custom LayoutParams: `ViewGroup<TLayoutParams>` where TLayoutParams derives from LayoutParams.
**FR-40 (US-15):** MarginLayoutParams extends LayoutParams with leftMargin, topMargin, rightMargin, bottomMargin fields. Uses static polymorphism with no virtual dispatch on LayoutParams.

### ViewGroup Flags and Behavior

**FR-41 (US-14):** The system shall define FLAG_CLIP_CHILDREN (default true) controlling whether children are clipped to the ViewGroup bounds.
**FR-42 (US-14):** The system shall define FLAG_CLIP_TO_PADDING (default true) controlling whether the invalidation region excludes padding.
**FR-43 (US-14):** The system shall define descendant focusability modes: FOCUS_BEFORE_DESCENDANTS, FOCUS_AFTER_DESCENDANTS, FOCUS_BLOCK_DESCENDANTS.

### Touch Event Dispatch

**FR-44 (US-16):** The system shall provide dispatchTouchEvent() on View that delivers MotionEvent to the view and returns true if consumed.
**FR-45 (US-16):** The system shall provide onInterceptTouchEvent() on ViewGroup as an overridable method returning true to intercept, false to pass to children.
**FR-46 (US-16):** The system shall provide onTouchEvent() on View as an overridable method handling motion events.
**FR-47 (US-16):** The system shall provide requestDisallowInterceptTouchEvent() on ViewParent that, when true, prevents the parent ViewGroup from intercepting touch events.
**FR-48 (US-16):** The system shall maintain a single View pointer (`View* touchTarget`) in ViewGroup representing the current gesture owner. Multi-pointer (hover) tracking is out of scope.

### ViewManager Interface

**FR-49 (US-17):** The system shall define ViewManager with addView(View view, LayoutParams params) that adds a view to the container.
**FR-50 (US-17):** The system shall define ViewManager with updateViewLayout(View view, LayoutParams params) that replaces the view's LayoutParams.
**FR-51 (US-17):** The system shall define ViewManager with removeView(View view) that removes a view from the container.
**FR-52 (US-17):** The system shall set the added view's parent reference to the container.
**FR-53 (US-17):** The system shall trigger a layout pass after addView, updateViewLayout, and removeView.

## Data & State

- **View**: Represents a single UI element. Key attributes: id (int), tag (arbitrary object), visibility (enum class Visibility), alpha (float 0.0-1.0), rotationX/Y/Z (float degrees), scaleX/Y (float), translationX/Y (float px), padding (left/top/right/bottom in px), minWidth/minHeight (int px, default 0), measuredWidth/Height (int), layoutLeft/Top/Right/Bottom (int), width/Height (int), flags (enum class with bit flags: FOCUSABLE, CLICKABLE, LONG_CLICKABLE, ENABLED), layoutDirection (LayoutDirection enum, default LTR), parent (ViewParent pointer via CRTP), child count (for ViewGroup).
- **ViewGroup**: Extends View with a collection of child views. Key attributes: children (ordered list of View pointers), layoutParams (per-child LayoutParams via template), groupFlags (clipChildren, clipToPadding, descendantFocusability, disallowIntercept), touchTarget (single View pointer representing current gesture owner).
- **ViewParent**: Interface defined via CRTP (Curiously Recursive Template Pattern) for static polymorphism. View inherits from `ViewParentMixin<View>`. Methods like requestLayout(), isLayoutRequested(), onDescendantInvalidated() are resolved via static dispatch through the CRTP base. No state of its own; provides methods for lifecycle communication (requestLayout, invalidate, focus management).
- **ViewManager**: Interface defining view container operations. No state of its own; provides methods for hierarchy manipulation (addView, updateViewLayout, removeView).
- **LayoutParams**: Per-child sizing specification. Key attributes: width (int), height (int), margin values (int).
- **MeasureSpec**: Parent-to-child dimension specification. Key attributes: mode (EXACTLY/AT_MOST/UNSPECIFIED), size (int px).

## UX & Behavior

### Entry Points

- An NDK developer creates a View or ViewGroup subclass instance with a Context.
- Views are assembled into a hierarchy via addView() on ViewGroup.
- The hierarchy root is attached to a container implementing ViewManager.

### Happy Path: Building and Displaying a View Hierarchy

1. Developer creates a ViewGroup (e.g., a custom container).
2. Developer creates child Views and sets their properties (size, position, visibility).
3. Developer calls addView(child, params) on the ViewGroup for each child.
4. The ViewGroup assigns LayoutParams to each child and sets the child's parent reference.
5. The framework triggers a measure pass: ViewGroup.measure() calls measure() on each child, passing appropriate MeasureSpecs derived from the ViewGroup's own constraints and each child's LayoutParams.
6. The framework triggers a layout pass: ViewGroup.layout() calls layout() on each child, passing the computed left/top/right/bottom coordinates.
7. The framework triggers a draw pass: ViewGroup.draw() draws its background, then calls drawChild() for each child in z-order, then draws its foreground.

### Happy Path: Touch Event Delivery

1. A MotionEvent arrives at the root of the view hierarchy.
2. The root ViewGroup iterates its children in z-order (front-to-back) to find the topmost child whose bounds contain the event coordinates.
3. If a child is found and onInterceptTouchEvent() returns false, the event is dispatched to that child via dispatchTouchEvent().
4. If onInterceptTouchEvent() returns true, the ViewGroup intercepts the event and handles it itself; subsequent events in the same gesture are delivered to the ViewGroup without checking intercept.
5. If no child contains the coordinates, the event is delivered to the ViewGroup itself.
6. The consuming view returns true from onTouchEvent() to indicate consumption.

### Error States

- Adding a view that already has a parent: the system shall remove the view from its previous parent before adding to the new one (mirroring Java View behavior).
- Removing a view that is not a child of this ViewGroup: the operation is a no-op (no exception).
- Accessing a child index out of bounds: the system shall return null or throw an out-of-range error.
- Setting GONE visibility: the view is excluded from layout and measurement; subsequent layout passes skip it entirely.

### Edge Cases

- A View with WRAP_CONTENT and no content: the system shall fall back to minimum dimensions (minWidth, minHeight) if specified.
- Nested ViewGroups with conflicting size constraints: the measure pass iterates until all parents accept all children's measurements (may require multiple passes).
- A child requesting layout while being measured: the system shall mark the ancestor as needing relayout rather than triggering an immediate recursive measure.
- Touch event during an ongoing gesture: ACTION_MOVE and ACTION_UP are delivered to the view that received the corresponding ACTION_DOWN, regardless of whether the pointer has moved outside that view's bounds.

## Constraints & Assumptions

### Constraints
- The implementation must follow the safety and type rules defined in the constitution.
- All public APIs must be documented.
- The behavioral reference is `core/java/android/view/View.java`, `ViewGroup.java`, `ViewParent.java`, and `ViewManager.java` on the lineageos-23.0 branch.
- Zero measurable overhead vs. equivalent C code (Principle II: Zero-Cost Abstractions).
- TDD is non-negotiable: Red -> Green -> Refactor with >80% coverage (Principle III).
- The implementation is standalone and does not depend on any external build system or interoperability layer.
- Code lives under `core/cpp/src/android/view/`.
- Namespaces mirror Android SDK: `android::view`.

### Assumptions
- Assumption: Canvas-like drawing surface is provided by a separate graphics module (not in scope). The draw() method accepts an abstract drawing surface interface. Confirm before planning.
- Assumption: MotionEvent and KeyEvent types are provided by a separate input module (not in scope). The dispatch methods accept these types as parameters. Confirm before planning.
- Assumption: Context is a minimal interface providing resource access; full Android Context is out of scope. Confirm before planning.
- Assumption: The Choreographer and frame loop infrastructure (already implemented) will drive the measure/layout/draw passes. The View system integrates with it via requestLayout() and invalidate() hooks. Confirm before planning.
- Assumption: Window attachment and detachment lifecycle (onAttachedToWindow/onDetachedFromWindow) is coordinated by a higher-level Window system module. The View system provides the lifecycle hooks but does not manage window attachment itself. Confirm before planning.
- Assumption: LayoutParams and MeasureSpec types are shared across the View system and will be defined in a common header. Confirm before planning.
- Assumption: Single-threaded by assumption -- all View operations occur on the UI thread. If a call is detected from a non-UI thread, the system asserts (debug) or ignores (release). No mutex protection on internal state. This matches Android's traditional View threading model.

## Review & Acceptance Checklist

- [x] All user roles are identified (Framework Developer, NDK Developer, Test Engineer)
- [x] Every user story has at least two acceptance criteria
- [x] Non-goals are explicit (widgets, layouts, animations, rendering, input method, accessibility, window management, XML inflation)
- [x] Functional requirements are testable (each FR is specific and verifiable)
- [x] Data entities are named and described (View, ViewGroup, ViewParent, ViewManager, LayoutParams, MeasureSpec)
- [x] Primary happy path is described end-to-end (build hierarchy -> measure -> layout -> draw)
- [x] At least one error/edge case is documented (duplicate parent, out-of-bounds access, GONE layout exclusion, nested measure)
- [x] Constitution principles are respected (Safety-First, Zero-Cost Abstractions, TDD, Spec as Source of Truth, Tech Stack)
- [x] No implementation and tech stack choices appear in this document beyond namespace convention
