#pragma once

typedef struct logger_t {
  void (*init)(void);
  void (*debug)(char* msg);
} logger_t;
