#pragma once

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <random>

static uint32_t GetRandUniqueId()
{   
   // generate a random unique id
   std::random_device rd;
   std::mt19937 gen(rd()); 
    std::uniform_int_distribution<uint32_t> dis(0x9999, UINT32_MAX);
    return dis(gen);
}
