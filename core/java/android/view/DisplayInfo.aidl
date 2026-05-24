/*
 * Copyright (C) 2012 The Android Open Source Project
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

import android.hardware.display.DeviceProductInfo;
import android.view.Display;
import android.view.DisplayAddress;
import android.view.DisplayCutout;
import android.view.DisplayShape;
import android.view.FrameRateCategoryRate;
import android.view.RoundedCorners;
import android.view.SurfaceControl;

/**
 * @hide
 */
parcelable DisplayInfo ndk_header "android/view" {
    int layerStack;
    int flags;
    int type;
    int displayId;
    int displayGroupId;
    DisplayAddress address;
    DeviceProductInfo deviceProductInfo;
    String name;
    String uniqueId;
    int appWidth;
    int appHeight;
    int smallestNominalAppWidth;
    int smallestNominalAppHeight;
    int largestNominalAppWidth;
    int largestNominalAppHeight;
    int logicalWidth;
    int logicalHeight;
    DisplayCutout.ParcelableWrapper displayCutout;
    int rotation;
    int modeId;
    float renderFrameRate;
    boolean hasArrSupport;
    FrameRateCategoryRate frameRateCategoryRate;
    float[] supportedRefreshRates;
    int defaultModeId;
    int userPreferredModeId;
    Display.Mode[] supportedModes;
    Display.Mode[] appsSupportedModes;
    int colorMode;
    int[] supportedColorModes;
    Display.HdrCapabilities hdrCapabilities;
    int[] userDisabledHdrTypes;
    boolean isForceSdr;
    boolean minimalPostProcessingSupported;
    int logicalDensityDpi;
    float physicalXDpi;
    float physicalYDpi;
    long appVsyncOffsetNanos;
    long presentationDeadlineNanos;
    int state;
    int committedState;
    int ownerUid;
    String ownerPackageName;
    float refreshRateOverride;
    int removeMode;
    float brightnessMinimum;
    float brightnessMaximum;
    float brightnessDefault;
    float brightnessDim;
    RoundedCorners roundedCorners;
    int installOrientation;
    DisplayShape displayShape;
    SurfaceControl.RefreshRateRange layoutLimitedRefreshRate;
    float hdrSdrRatio;
    int[] thermalRefreshRateThrottlingKeys;
    SurfaceControl.RefreshRateRange[] thermalRefreshRateThrottlingValues;
    String thermalBrightnessThrottlingDataId;
    boolean canHostTasks;
}
