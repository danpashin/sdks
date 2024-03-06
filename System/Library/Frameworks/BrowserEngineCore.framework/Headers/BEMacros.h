//
//  BEMacros.h
//

#ifndef BrowserEngineCoreMacros_h
#define BrowserEngineCoreMacros_h

#include <os/availability.h>

#if defined(__cplusplus)
#define BROWSERENGINE_EXTERN __attribute__((visibility("default"))) extern "C"
#else
#define BROWSERENGINE_EXTERN __attribute__((visibility("default"))) extern
#endif

#define BROWSERENGINE_EXPORT BROWSERENGINE_EXTERN
#define BROWSERENGINE_IMPORT BROWSERENGINE_EXTERN

#define BROWSERENGINE_TEXTINPUT_AVAILABILITY API_AVAILABLE(ios(17.4))

#ifndef BROWSERENGINE_FINAL
    #if defined(__has_attribute) && __has_attribute(objc_subclassing_restricted)
        #define BROWSERENGINE_FINAL __attribute__((objc_subclassing_restricted))
    #else
        #define BROWSERENGINE_FINAL
    #endif
#endif

#endif /* BrowserEngineCoreMacros_h */
