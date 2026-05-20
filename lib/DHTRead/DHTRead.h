#pragma once
#include <Arduino.h>

struct DhtPack
{
    float t10;
    float h10;
    float t15;
    float h15;
    float t20;
    float h20;
};

void dhtBegin();
bool dhtRead(DhtPack &data);
