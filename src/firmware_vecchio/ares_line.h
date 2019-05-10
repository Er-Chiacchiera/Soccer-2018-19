
#pragma once
#include <Arduino.h>
#include "ares_Line_internal.cpp"
#include "ares_status.h"

#define ESCAPE_TTL 2000

typedef struct{
    LineDetector* ld;
    uint16_t mask;

    double border_x;
    double border_y;
    uint8_t escape_flag;
    uint16_t escape_direction[3];

    int16_t escape_ttl;
} AresLineHandler;

void AresLineHandler_init(AresLineHandler*, LineDetector*);
void AresLineHandler_handle(AresLineHandler*);
void AresLineHandler_reset(AresLineHandler);