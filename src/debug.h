#ifndef DEBUG_H
#define DEBUG_H

  #define DEBUG_PORT Serial

  #define DEBUG_PRINT(data) DEBUG_PORT.print(data);

  #define DEBUG_PRINTLN(data) DEBUG_PORT.println(data);

  #define DEBUG_SETUP \
    DEBUG_PORT.begin(9600); \
    while (!DEBUG_PORT) \
    ;

#endif