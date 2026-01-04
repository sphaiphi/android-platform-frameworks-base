# ViewTranslationCallback - Reverse Engineering Documentation

## Executive Summary
Interface defining how a `View` handles showing/hiding translated content. The default implementation for `TextView` handles text replacement/transformation.

## Methods
*   `onShowTranslation`: Display the translated content.
*   `onHideTranslation`: Revert to original content.
*   `onClearTranslation`: Cleanup.
*   `enableContentPadding`: Request compat padding.
*   `setAnimationDurationMillis`: Config animation speed.

## Java-to-C++ Translation Guide
*   **Interface**: Virtual class. Strongly tied to `View` lifecycle.
