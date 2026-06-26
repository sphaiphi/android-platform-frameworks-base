# Clarifications: Foundational View Classes

**Spec:** .specify/specs/001-view-foundational/spec.md
**Audited:** 2026-06-07
**Status:** Complete — Ready for Planning

---

## Summary

This spec was well-structured with clear user stories, functional requirements, and a comprehensive non-goals list. All 16 clarification questions have been resolved: alpha default confirmed as 1.0, visibility uses enum class, rotationZ added, focus management confirmed in scope, ViewParent/ViewGroup use CRTP for zero-cost abstractions, LayoutParams uses concrete class hierarchy with template-based ViewGroup, minimal Canvas interface defined, single-threaded model confirmed, minWidth/minHeight added as View properties, focusable/clickable flags added, layout direction defined, touch target simplified to single pointer, disappearingChildren removed, and pass ordering confirmed as no-enforcement. The spec is now complete and ready for planning.

**Blocking questions:** 0  
**Important questions:** 0  
**Nice-to-know questions:** 0

---

## 🔴 Blocking Questions

All resolved. See Answers section.

### Q1: Alpha default value contradiction

**Context:** FR-02 (line 192) states `alpha = 1.0` as a default. FR-17 (line 219) states alpha defaults to `1.0`. However, the View Lifecycle acceptance criteria (line 55: "The View initializes with default property values (VISIBLE, no padding, 0 alpha, no rotation/scale/translation)") stated alpha starts at `0`.

**Question:** What is the correct default value for alpha: `1.0` (fully opaque) or `0.0` (fully transparent)?

**Why it blocks:** The planner must set the correct constructor initialization. This is a behavioral difference from the Java reference (which uses 1.0).

---

### Q2: Visibility constants vs. enum class (Constitution Principle I)

**Context:** FR-15 (line 217) stated: "VISIBLE (0), INVISIBLE (4), and GONE (8)." These are hardcoded integer magic values matching the Java SDK. Constitution Principle I (line 13) mandates: "`enum class` and strong types only. No primitive obsession."

**Question:** How should visibility be represented in C++? Use an `enum class Visibility { Visible = 0, Invisible = 4, Gone = 8 }` that preserves Java-ABI-compatible integer values, or use a different representation?

**Why it blocks:** This determines the type used throughout the entire View API (getVisibility/setVisibility return types, LayoutParams visibility, visibility flag constants). If enum class is used, all getters/setters must convert to/from int for ABI compatibility.

---

### Q3: Missing FR for rotationZ

**Context:** US-05 (line 85) mentions `setRotation(), setRotationX(), setRotationY()` and their getters. The Overview (line 17) lists "rotation" as a property. FR-02 (line 192) lists defaults for `rotationX = 0, rotationY = 0, rotationZ = 0`. FR-18 (line 220) defined `getRotation()/setRotation(), getRotationX()/setRotationX(), getRotationY()/setRotationY()` but omitted `rotationZ` entirely.

**Question:** Should `getRotationZ()/setRotationZ()` be included as a View property? If so, it needs its own FR. If not, FR-02's mention of `rotationZ = 0` default and the Overview's "rotation" property need clarification.

**Why it blocks:** If rotationZ is in scope, a new FR and corresponding user story acceptance criteria must be added before planning. The planner cannot guess whether this property is intentional or an oversight.

---

### Q4: Focus management in scope vs. non-goals contradiction

**Context:** Non-Goals (line 27) explicitly lists "Accessibility (AccessibilityEvent, AccessibilityNodeInfo, TalkBack integration)" as out of scope. However, US-11 (lines 122-126) and FR-28/FR-29 (lines 233-234) define full focus management: `requestChildFocus()`, `clearChildFocus()`, `focusSearch()`.

**Question:** Is focus management (US-11, FR-28, FR-29) in scope or out of scope? If in scope, is this considered part of the View hierarchy contract (independent of accessibility) or does it fall under the accessibility non-goal?

**Why it blocks:** Focus management requires significant interface work on ViewParent, child-focus tracking state on ViewGroup, and direction-aware search logic. If out of scope, these FRs and US must be removed before planning. If in scope, the scope of focus features (keyboard vs. directional pad vs. both) must be defined.

---

### Q5: ViewParent interface vs. zero-cost abstractions (Constitution Principle II)

**Context:** The spec defined `ViewParent` as an interface (FR-24 through FR-29, lines 229-234) with virtual methods (`requestLayout()`, `isLayoutRequested()`, `onDescendantInvalidated()`, `getParent()`, `requestChildFocus()`, `clearChildFocus()`, `focusSearch()`). Constitution Principle II (line 20) mandates: "Static polymorphism (templates, concepts) over virtual functions. Every abstraction MUST have zero measurable overhead vs. C equivalent."

**Question:** How should the ViewParent contract be implemented in C++ without virtual dispatch? Options include: CRTP base class, template concept constraints, or compile-time interface injection.

**Why it blocks:** This is a fundamental architectural decision. Virtual dispatch on ViewParent means every `invalidate()` and `requestLayout()` call through the parent chain incurs a vtable lookup, violating the zero-cost abstraction principle. The planner cannot design the hierarchy without knowing the dispatch mechanism.

---

### Q6: ViewGroup C++ inheritance model

**Context:** FR-30 (line 238) stated: "ViewGroup extends View and implements ViewParent and ViewManager." C++ does not support multiple inheritance from both a concrete class (View) and multiple interfaces (ViewParent, ViewManager) in the same way Java does. Constitution Principle I requires strong types.

**Question:** What is the C++ inheritance/composition model for ViewGroup? Options include: (a) ViewGroup inherits View privately and composes ViewParent/ViewManager via CRTP, (b) ViewGroup inherits View publicly and uses composition for ViewParent/ViewManager, or (c) a different pattern.

**Why it blocks:** This determines the entire class hierarchy design. The Java model (single class extends + multiple interfaces) does not map directly to C++. The choice affects how ViewParent methods are resolved and how `this` is cast between View and ViewParent.

---

### Q7: LayoutParams type mechanism

**Context:** FR-36 (line 244) defined LayoutParams with width and height fields. FR-37 (line 245) defined MarginLayoutParams extending LayoutParams. US-15 (lines 152-156) described LayoutParams behavior. However, the spec never defined how LayoutParams is instantiated, typed, or stored. Is it a concrete class hierarchy? A template? How does a custom ViewGroup with custom LayoutParams work?

**Question:** How should LayoutParams be typed in C++? Provide a concrete class hierarchy (LayoutParams, MarginLayoutParams), a template-based approach, or a different mechanism? How does a custom ViewGroup (e.g., custom FrameLayout) provide its own LayoutParams subclass?

**Why it blocks:** LayoutParams is central to the measure/layout system. Every child stores a LayoutParams reference. The type mechanism determines whether this uses virtual dispatch (violating Principle II), templates (requiring compile-time knowledge), or a type-erased wrapper (adding runtime cost).

---

### Q8: Canvas drawing surface interface

**Context:** The Assumptions section (line 332) stated: "Canvas-like drawing surface is provided by a separate graphics module (not in scope). The draw() method accepts an abstract drawing surface interface." FR-12 (line 211) stated draw() "executes the drawing sequence: background, content, foreground." But the spec never defined what methods this interface must expose.

**Question:** What is the minimal Canvas interface that the View system requires? List the methods (e.g., `drawRect()`, `drawColor()`, `save()`, `restore()`, `clipRect()`) or state that the interface is TBD and will be defined in a follow-up feature.

**Why it blocks:** The draw() method and onDraw() hook cannot be designed without knowing what operations the canvas supports. The background/content/foreground drawing sequence depends on available canvas operations.

---

### Q9: Thread safety requirements

**Context:** The spec described a UI framework where views are measured, laid out, drawn, and receive touch events. No thread safety discussion appeared anywhere in the spec. Constitution Principle I (Safety) covers type safety and lifetime but not concurrency. Android's View system is traditionally single-threaded (UI thread only).

**Question:** Is the View system single-threaded by assumption (all operations on one UI thread), or must it support concurrent access from multiple threads (e.g., background thread calling invalidate())? If single-threaded, what happens if a concurrent call is detected (assert, ignore, queue)?

**Why it blocks:** Thread safety determines whether internal state needs mutex protection, whether operations need to be queued to a message loop, and how touch events are processed. This affects the entire implementation architecture.

---

### Q10: minWidth / minHeight undefined

**Context:** Edge Cases section (line 314) stated: "A View with WRAP_CONTENT and no content: the system shall fall back to minimum dimensions (minWidth, minHeight) if specified." However, no FR defined `getMinWidth()`, `setMinWidth()`, `getMinHeight()`, or `setMinHeight()` as View properties. The Data & State section (line 271) did not list minWidth/minHeight as View attributes.

**Question:** Are minWidth and minHeight View properties that must be implemented? If so, they need FRs and acceptance criteria. If not, the Edge Cases reference is orphaned.

**Why it blocks:** WRAP_CONTENT measurement behavior depends on these values. Without them, the planner cannot implement the WRAP_CONTENT fallback logic described in the Edge Cases section.

---

## 🟡 Important Questions

All resolved. See Answers section.

### Q11: Touch target list type and lifecycle

**Context:** FR-45 (line 259) stated: "maintain a touch target list in ViewGroup tracking which child received the current ACTION_DOWN." US-16 (line 166) says "ACTION_DOWN starts a new touch target; ACTION_MOVE and ACTION_UP are delivered to the view that received the ACTION_DOWN." The Data & State section (line 273) mentioned "touchTargetList (linked list of active touch targets)."

**Question:** What is the concrete type of the touch target list? Is it a linked list of View pointers, a vector, or a single View reference (since typically only one view owns a gesture)? Is multi-pointer (hover) tracking required?

---

### Q12: Measure/layout/draw pass ordering enforcement

**Context:** The happy path (lines 286-294) described measure -> layout -> draw in sequence. FR-10 (line 206) defined `requestLayout()` as marking the view as needing layout. FR-14 (line 213) defined `invalidate()` as marking the view as needing redraw. But the spec did not state what happens if `draw()` is called before `measure()` or `layout()`, or if `measure()` is called after `layout()`.

**Question:** Should the system enforce pass ordering (e.g., assert or no-op if out of order), or should it allow out-of-order calls and let the developer manage the sequence?

---

### Q13: View focusable/clickable flags

**Context:** The Data & State section (line 271) listed "flags (focusable, clickable, etc.)" as View attributes. However, no FR defined `isFocusable()`, `setFocusable()`, `isClickable()`, or `setClickable()`. No acceptance criteria in any user story referenced these flags.

**Question:** Are focusable and clickable flags in scope? If so, they need FRs. If not, remove them from the Data & State description.

---

### Q14: disappearingChildren scope

**Context:** The Data & State section (line 273) listed `disappearingChildren (views being animated out)` as a ViewGroup attribute. The Non-Goals (line 24) stated "Animation system -- already partially implemented as ViewPropertyAnimator in a prior feature."

**Question:** Is `disappearingChildren` tracking in scope? If animations are out of scope (aside from ViewPropertyAnimator), does ViewGroup need to track disappearing children, or is this deferred to an animation integration feature?

---

## 🟢 Nice-to-Know Questions

All resolved. See Answers section.

### Q15: Padding start/end layout direction

**Context:** US-06 (lines 95-96) mentioned `getPaddingStart()` and `getPaddingEnd()` respecting layout direction. FR-21 (line 223) defined these getters. However, the spec did not define how layout direction (LTR vs. RTL) is determined or stored.

**Question:** Is layout direction a View property (settable per-view or inherited from context), or is it a global configuration? How is the start/end mapping determined?

---

### Q16: View flags type and full list

**Context:** The Data & State section (line 271) mentioned "flags (focusable, clickable, etc.)" but did not enumerate the full set of View flags or their type. Java's View has dozens of flag constants (FOCUSABLE, CLICKABLE, LONG_CLICKABLE, ENABLED, etc.).

**Question:** Which View flags are in scope for this feature? Provide the complete list or state that a minimal set (FOCUSABLE, CLICKABLE) is in scope with others deferred.

---

## Answers

| # | Answer |
|---|--------|
| Q1 | Alpha default is 1.0 (fully opaque). This matches Java android.view.View. Change the lifecycle acceptance criteria that says '0 alpha' to '1.0 alpha'. |
| Q2 | Use enum class Visibility : int { Visible = 0, Invisible = 4, Gone = 8 }. This satisfies Constitution Principle I (enum class) while preserving Java-ABI-compatible integer values. All getters/setters use the enum class type; implicit conversion to int is provided for ABI compatibility. |
| Q3 | Include getRotationZ()/setRotationZ() as a View property. Add FR-19 for rotationZ with default 0. This matches Java View.java. |
| Q4 | Focus management IS in scope. It is part of the View hierarchy contract (requestChildFocus, clearChildFocus, focusSearch) independent of accessibility. Accessibility (TalkBack, AccessibilityNodeInfo) remains out of scope but the underlying focus infrastructure is needed. |
| Q5 | ViewParent uses CRTP (Curiously Recursive Template Pattern) for static polymorphism. View inherits from ViewParentMixin<View>. requestLayout(), isLayoutRequested(), onDescendantInvalidated() are resolved via static dispatch through the CRTP base. This satisfies Constitution Principle II (zero-cost abstractions). |
| Q6 | GroupView publicly inherits View and privately composes ViewParent/ViewManager via CRTP: class ViewGroup : public View, private ViewParentMixin<ViewGroup>, private ViewManagerMixin<ViewGroup>. ViewGroup casts `this` to ViewParent/ViewManager via static_cast, matching Java's behavior without virtual dispatch overhead. |
| Q7 | LayoutParams is a concrete class hierarchy: class LayoutParams (width, height), class MarginLayoutParams : LayoutParams (leftMargin, topMargin, rightMargin, bottomMargin). ViewGroup uses template-based custom LayoutParams: ViewGroup<TLayoutParams> where TLayoutParams derives from LayoutParams. This uses static polymorphism — no virtual dispatch on LayoutParams. |
| Q8 | Define a minimal Canvas interface in scope: drawColor(int color), drawRect(float left, float top, float right, float bottom), save(), restore(), clipRect(float left, float top, float right, float bottom), translate(float dx, float dy). This is the minimal set needed for background/content/foreground drawing. The full Canvas from HWUI is out of scope. |
| Q9 | Single-threaded by assumption: all View operations occur on the UI thread. If a call is detected from a non-UI thread, the system asserts (debug) or ignores (release). No mutex protection on internal state. This matches Android's traditional View threading model. |
| Q10 | minWidth and minHeight ARE View properties. Add FR-20 (getMinWidth/setMinWidth) and FR-21 (getMinHeight/setMinHeight) with defaults of 0. These are needed for WRAP_CONTENT fallback in measure(). |
| Q11 | Single View pointer (View*) representing the current gesture owner. Multi-pointer (hover) tracking is out of scope for this feature. |
| Q12 | No runtime enforcement. The system tracks state flags (measured, laid out, drawn) but does not assert on out-of-order calls. The Choreographer integration is responsible for ordering passes. |
| Q13 | focusable and clickable flags ARE in scope. Add FR for isFocusable/setFocusable and isClickable/setClickable. These are required for focus management and touch event consumption. |
| Q14 | disappearingChildren is OUT of scope for this feature. It will be added when integrating ViewPropertyAnimator with ViewGroup in a follow-up feature. |
| Q15 | Layout direction is a per-view property (getLayoutDirection/setLayoutDirection), defaulting to LTR (LayoutDirection.Ltr). getPaddingStart()/getPaddingEnd() compute based on the view's layout direction. |
| Q16 | Minimal set of View flags in scope: FOCUSABLE, CLICKABLE, LONG_CLICKABLE, ENABLED. These are defined as an enum class with bit flags. Other flags (HAPTIC_FEEDBACK_ENABLED, SOUND_EFFECTS_ENABLED, etc.) are deferred. |

---

## Spec Update Log

Q1 -> Updated US-01 acceptance criteria: Changed alpha default from "0 alpha" to "1.0 alpha" in View lifecycle initialization.
Q2 -> Updated FR-15: Replaced magic integer visibility constants with `enum class Visibility : int { Visible = 0, Invisible = 4, Gone = 8 }` with implicit int conversion for ABI compatibility.
Q3 -> Updated FR-18: Added getRotationZ()/setRotationZ() to rotation properties. Updated US-05 acceptance criteria to include rotationZ.
Q4 -> No spec change needed: Focus management confirmed as in scope (View hierarchy contract, not accessibility).
Q5 -> Updated ViewParent Data & State description: Clarified CRTP-based static polymorphism via `ViewParentMixin<View>`.
Q6 -> Updated FR-30: Replaced Java-style inheritance description with C++ CRTP model (`class ViewGroup : public View, private ViewParentMixin<ViewGroup>, private ViewManagerMixin<ViewGroup>`).
Q7 -> Updated FR-36/FR-37: Defined concrete LayoutParams class hierarchy with template-based ViewGroup (`ViewGroup<TLayoutParams>`). Updated US-15 references.
Q8 -> Added new Canvas Interface section with FR-14a: Defined minimal Canvas interface (drawColor, drawRect, save, restore, clipRect, translate).
Q9 -> Updated Assumptions: Added single-threaded UI thread assumption with debug assert / release ignore behavior.
Q10 -> Added FR-21 (getMinWidth/setMinWidth, getMinHeight/setMinHeight, default 0). Updated FR-02 defaults to include minWidth=0, minHeight=0.
Q11 -> Updated FR-45: Changed touch target from "list" to single `View* touchTarget`. Updated Data & State ViewGroup attributes.
Q12 -> No spec change needed: Matches default assumption (no runtime enforcement, Choreographer handles ordering).
Q13 -> Added FR-26 (isFocusable/setFocusable, isClickable/setClickable). Updated Data & State flags to specific enum class with FOCUSABLE, CLICKABLE, LONG_CLICKABLE, ENABLED.
Q14 -> Removed `disappearingChildren` from ViewGroup Data & State attributes.
Q15 -> Added FR-23 (getLayoutDirection/setLayoutDirection, default LTR). Updated FR-22 to reference layout direction in getPaddingStart/getPaddingEnd.
Q16 -> Updated Data & State View flags: Replaced "flags (focusable, clickable, etc.)" with specific enum class listing FOCUSABLE, CLICKABLE, LONG_CLICKABLE, ENABLED.

---

## Spec Changes Summary

The following FR numbers were renumbered due to new FR insertions:

| Old FR | New FR | Reason |
|--------|--------|--------|
| FR-21 | FR-22 | minWidth/minHeight inserted as FR-21 |
| FR-22 | FR-24 | minWidth/minHeight inserted as FR-21 |
| FR-23 | FR-25 | minWidth/minHeight inserted as FR-21 |
| FR-24 | FR-27 | focusable/clickable inserted as FR-26 |
| FR-25 | FR-28 | focusable/clickable inserted as FR-26 |
| FR-26 | FR-29 | focusable/clickable inserted as FR-26 |
| FR-27 | FR-30 | focusable/clickable inserted as FR-26 |
| FR-28 | FR-31 | focusable/clickable inserted as FR-26 |
| FR-29 | FR-32 | focusable/clickable inserted as FR-26 |
| FR-30 | FR-33 | focusable/clickable inserted as FR-26 |
| FR-31 | FR-34 | focusable/clickable inserted as FR-26 |
| FR-32 | FR-35 | focusable/clickable inserted as FR-26 |
| FR-33 | FR-36 | focusable/clickable inserted as FR-26 |
| FR-34 | FR-37 | focusable/clickable inserted as FR-26 |
| FR-35 | FR-38 | focusable/clickable inserted as FR-26 |
| FR-36 | FR-39 | focusable/clickable inserted as FR-26 |
| FR-37 | FR-40 | focusable/clickable inserted as FR-26 |
| FR-38 | FR-41 | focusable/clickable inserted as FR-26 |
| FR-39 | FR-42 | focusable/clickable inserted as FR-26 |
| FR-40 | FR-43 | focusable/clickable inserted as FR-26 |
| FR-41 | FR-44 | focusable/clickable inserted as FR-26 |
| FR-42 | FR-45 | focusable/clickable inserted as FR-26 |
| FR-43 | FR-46 | focusable/clickable inserted as FR-26 |
| FR-44 | FR-47 | focusable/clickable inserted as FR-26 |
| FR-45 | FR-48 | focusable/clickable inserted as FR-26 |
| FR-46 | FR-49 | focusable/clickable inserted as FR-26 |
| FR-47 | FR-50 | focusable/clickable inserted as FR-26 |
| FR-48 | FR-51 | focusable/clickable inserted as FR-26 |
| FR-49 | FR-52 | focusable/clickable inserted as FR-26 |
| FR-50 | FR-53 | focusable/clickable inserted as FR-26 |

New FRs inserted: FR-14a (Canvas interface), FR-21 (minWidth/minHeight), FR-23 (layout direction), FR-26 (focusable/clickable).
