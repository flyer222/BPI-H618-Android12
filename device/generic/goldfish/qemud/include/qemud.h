/*
 * Copyright (C) 2020 The Android Open Source Project
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

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

int qemud_channel_open(const char* name);
int qemud_channel_send(int pipe, const void* msg, int size);
int qemud_channel_recv(int pipe, void* msg, int maxsize);

#ifdef __cplusplus
}  // extern "C"
#endif
