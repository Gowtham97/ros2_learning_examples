#ifndef PUBLISHER_PLUGIN__VISIBILITY_CONTROL_H_
#define PUBLISHER_PLUGIN__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define PUBLISHER_PLUGIN_EXPORT __attribute__ ((dllexport))
    #define PUBLISHER_PLUGIN_IMPORT __attribute__ ((dllimport))
  #else
    #define PUBLISHER_PLUGIN_EXPORT __declspec(dllexport)
    #define PUBLISHER_PLUGIN_IMPORT __declspec(dllimport)
  #endif
  #ifdef PUBLISHER_PLUGIN_BUILDING_LIBRARY
    #define PUBLISHER_PLUGIN_PUBLIC PUBLISHER_PLUGIN_EXPORT
  #else
    #define PUBLISHER_PLUGIN_PUBLIC PUBLISHER_PLUGIN_IMPORT
  #endif
  #define PUBLISHER_PLUGIN_PUBLIC_TYPE PUBLISHER_PLUGIN_PUBLIC
  #define PUBLISHER_PLUGIN_LOCAL
#else
  #define PUBLISHER_PLUGIN_EXPORT __attribute__ ((visibility("default")))
  #define PUBLISHER_PLUGIN_IMPORT
  #if __GNUC__ >= 4
    #define PUBLISHER_PLUGIN_PUBLIC __attribute__ ((visibility("default")))
    #define PUBLISHER_PLUGIN_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define PUBLISHER_PLUGIN_PUBLIC
    #define PUBLISHER_PLUGIN_LOCAL
  #endif
  #define PUBLISHER_PLUGIN_PUBLIC_TYPE
#endif

#endif  // PUBLISHER_PLUGIN__VISIBILITY_CONTROL_H_
