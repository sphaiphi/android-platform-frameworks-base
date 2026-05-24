/*
 * Copyright (C) 2024 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package android.view;

import android.util.MergedConfiguration;
import android.view.InsetsSourceControlArray;
import android.view.InsetsState;
import android.view.SurfaceControl;
import android.window.ActivityWindowInfo;
import android.window.ClientWindowFrames;

/**
 * Stores information to pass to {@link IWindowSession#relayout} as AIDL out type.
 * @hide
 */
parcelable WindowRelayoutResult {
    ClientWindowFrames frames;
    MergedConfiguration mergedConfiguration;
    SurfaceControl surfaceControl;
    InsetsState insetsState;
    InsetsSourceControlArray activeControls;
    int syncSeqId;
    @nullable ActivityWindowInfo activityWindowInfo;
}
