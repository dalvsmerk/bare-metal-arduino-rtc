#pragma once

typedef struct logger_t {
  void (*init)(void);
  void (*debug)(char* msg);
  void (*debug_byte)(uint8_t byte);
} logger_t;
