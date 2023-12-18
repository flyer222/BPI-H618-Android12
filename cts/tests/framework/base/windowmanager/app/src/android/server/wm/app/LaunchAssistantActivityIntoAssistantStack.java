/*
 * Copyright (C) 2017 The Android Open Source Project
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
 * limitations under the License
 */

package android.server.wm.app;

import static android.server.wm.app.Components.LaunchAssistantActivityIntoAssistantStack.EXTRA_ASSISTANT_IS_TRANSLUCENT;

import android.app.Activity;
import android.content.Intent;

public class LaunchAssistantActivityIntoAssistantStack extends Activity {

    @Override
    protected void onResume() {
        super.onResume();

        final Intent intent = getIntent();
        if (isTranslucent(intent)) {
            TranslucentAssistantActivity.launchActivityIntoAssistantStack(this, intent.getExtras());
        } else {
            AssistantActivity.launchActivityIntoAssistantStack(this, getIntent().getExtras());
        }
        finishAndRemoveTask();
    }

    private static boolean isTranslucent(Intent intent) {
        return intent.hasExtra(EXTRA_ASSISTANT_IS_TRANSLUCENT)
                && Boolean.valueOf(intent.getStringExtra(EXTRA_ASSISTANT_IS_TRANSLUCENT));
    }
}
