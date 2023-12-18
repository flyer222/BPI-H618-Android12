// Auto-generated with: android/scripts/gen-entries.py --mode=funcargs android/android-emugl/host/libs/libOpenGLESDispatch/gles12tr.entries --output=android/android-emugl/host/include/OpenGLESDispatch/gles12tr.h
// DO NOT EDIT THIS FILE

#ifndef GLES12_TR_FUNCTIONS_H
#define GLES12_TR_FUNCTIONS_H

typedef void* voidptr;
#define LIST_GLES12_TR_FUNCTIONS(X) \
  X(voidptr, create_gles1_context, (void* share, const void* underlying_apis), (share, underlying_apis)) \
  X(voidptr, get_current_gles_context, (), ()) \
  X(void, set_current_gles_context, (void* ctx), (ctx)) \
  X(voidptr, create_underlying_api, (), ()) \
  X(void, make_current_setup, (uint32_t surf_width, uint32_t surf_height), (surf_width, surf_height)) \
  X(void, destroy_gles1_context, (void* ctx), (ctx)) \


#endif  // GLES12_TR_FUNCTIONS_H
