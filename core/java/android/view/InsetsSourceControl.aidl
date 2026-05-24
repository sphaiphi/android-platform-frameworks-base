/**
 * Copyright (c) 2018, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package android.view;

import android.graphics.Insets;
import android.graphics.Point;
import android.view.SurfaceControl;
import android.view.inputmethod.ImeTracker;

/**
 * @hide
 */
parcelable InsetsSourceControl ndk_header "android/view" {
    int id;
    int type;
    @nullable SurfaceControl leash;
    boolean initiallyVisible;
    Point surfacePosition;
    Insets insetsHint;
    boolean skipAnimationOnce;
    @nullable ImeTracker.Token imeStatsToken;
}

/**
 * @hide
 */
parcelable InsetsSourceControl.Array ndk_header "android/view" {
    @nullable InsetsSourceControl[] controls;
    int seq;
}
