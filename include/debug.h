

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

// Define debug levels
#define DEBUG_LEVEL_NONE   0
#define DEBUG_LEVEL_ERROR  1
#define DEBUG_LEVEL_WARN   2
#define DEBUG_LEVEL_INFO   3
#define DEBUG_LEVEL_DEBUG  4

// Set your desired debug level here:
#define DEBUG_LEVEL DEBUG_LEVEL_INFO

// Macros for different levels
#if DEBUG_LEVEL >= DEBUG_LEVEL_ERROR
  #define DEBUG_ERROR(fmt, ...) \
      printf("[ERROR] " fmt, ##__VA_ARGS__)
#else
  #define DEBUG_ERROR(fmt, ...) do {} while(0)
#endif

#if DEBUG_LEVEL >= DEBUG_LEVEL_WARN
  #define DEBUG_WARN(fmt, ...) \
      printf("[WARN] " fmt, ##__VA_ARGS__)
#else
  #define DEBUG_WARN(fmt, ...) do {} while(0)
#endif

#if DEBUG_LEVEL >= DEBUG_LEVEL_INFO
  #define DEBUG_INFO(fmt, ...) \
      printf("[INFO] " fmt, ##__VA_ARGS__)
#else
  #define DEBUG_INFO(fmt, ...) do {} while(0)
#endif

#if DEBUG_LEVEL >= DEBUG_LEVEL_DEBUG
  #define DEBUG_DEBUG(fmt, ...) \
      printf("[DEBUG] " fmt, ##__VA_ARGS__)
#else
  #define DEBUG_DEBUG(fmt, ...) do {} while(0)
#endif

#endif // DEBUG_H