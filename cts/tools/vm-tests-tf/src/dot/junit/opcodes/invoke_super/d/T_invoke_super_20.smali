# Copyright (C) 2008 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

.source "T_invoke_super_20.java"
.class  public Ldot/junit/opcodes/invoke_super/d/T_invoke_super_20;
.super  Ljava/lang/Object;


.method public constructor <init>()V
.registers 2

       invoke-direct {v1}, Ljava/lang/Object;-><init>()V
       return-void
.end method

.method public run(Ldot/junit/opcodes/invoke_super/TestStubs;)V
.registers 5

       invoke-super {v4}, Ldot/junit/opcodes/invoke_super/TestStubs;->TestStubP()V
       return-void
.end method


