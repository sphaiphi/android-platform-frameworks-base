/**
 * Copyright (c) 2017, The Android Open Source Project
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

import android.graphics.Rect;
import android.view.DisplayCutout;
import android.view.DisplayShape;
import android.view.InsetsSource;
import android.view.PrivacyIndicatorBounds;
import android.view.RoundedCorners;

/**
 * @hide
 */
parcelable InsetsState ndk_header "android/view" {
    Rect displayFrame;
    DisplayCutout.ParcelableWrapper displayCutout;
    RoundedCorners roundedCorners;
    Rect roundedCornerFrame;
    PrivacyIndicatorBounds privacyIndicatorBounds;
    DisplayShape displayShape;
    int seq;
    InsetsSource[] sources;
}
