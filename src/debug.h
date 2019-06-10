#ifndef DEBUG_H
#define DEBUG_H

#ifdef ENABLE_DEBUG
  #define DEBUG_PORT Serial
  #define DEBUG_PRINTF(...) DEBUG_PORT.printf(__VA_ARGS__)
  #define DEBUG_PRINT(data) DEBUG_PORT.print(data);

  #define DEBUG_PRINTLN(data) DEBUG_PORT.println(data);

  #define DEBUG_SETUP \
    DEBUG_PORT.begin(115200); \
    while (!DEBUG_PORT) \
    ;
#else
  #define DEBUG_PORT
  #define DEBUG_PRINT(data)
  #define DEBUG_PRINTLN(data)
  #define DEBUG_SETUP
  #define DEBUG_PRINTF(...)
#endif

#endif
