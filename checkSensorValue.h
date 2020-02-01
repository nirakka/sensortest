#pragma once

#include "typedef.h"

using namespace std;

extern void checkSensorValue(
		Values& val,
		SensorHistory& sh, 
		Values& defected);

extern int checkSensorValueSub(
		int v,
		Values& val);

extern bool checkSF(int16_t v, Values& va);
extern bool checkRF(int16_t v, Values& va);
