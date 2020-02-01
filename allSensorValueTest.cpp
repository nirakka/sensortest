#include <iostream>
#include <sstream>

#include "readSensorValue.h"
#include "checkSensorValue.h"
#include "allSensorValueTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION (allSensorValuetest);

void allSensorValuetest :: setUp (void)
{
	// set up test environment (initializing objects)
}

void allSensorValuetest :: tearDown (void) 
{
	// finally delete objects
}

static SensorHistory history;
static Values v0{0,0,0,0}; // 1bit
static Values v1{3000,0,0,0}; // 16bit
static Values v2{3010,0,0,0}; // 16bit
static Values v3{3030,0,0,0}; // 16bit
static Values v4{3100,0,0,0}; // 16bit

static Values values[100] = { v1, v2, v3, v4, };

// 履歴なし
void allSensorValuetest :: test01 (void) 
{
	history.clear();
        int idx = 0;
	int r = 0;
	RawValue rv;

	readSensorValue(1, v0, values[idx++], rv);
	r = checkSensorValue(rv, history);
	CPPUNIT_ASSERT ( r==0 ); // 正常
}

// 1個
void allSensorValuetest :: test02 (void) 
{
	history.clear();
        int idx = 0;
	int r = 0;
	RawValue rv;

	readSensorValue(1, v0, values[idx++], rv);
	r = checkSensorValue(rv, history);

	readSensorValue(1, v0, values[idx++], rv);
	r = checkSensorValue(rv, history);
	CPPUNIT_ASSERT ( r==0 ); // 正常
}

// 2個:逸脱なし
void allSensorValuetest :: test03 (void) 
{
	history.clear();
        int idx = 0;
	int r = 0;
	RawValue rv;

	readSensorValue(1, v0, values[idx++], rv);
	r = checkSensorValue(rv, history);

	readSensorValue(1, v0, values[idx++], rv);
	r = checkSensorValue(rv, history);

	readSensorValue(1, v0, values[idx++], rv);
	r = checkSensorValue(rv, history);
	CPPUNIT_ASSERT ( r==0 ); // 正常
}

// 3個:逸脱あり
void allSensorValuetest :: test04 (void) 
{
	history.clear();
        int idx = 0;
	int r = 0;
	RawValue rv;

	readSensorValue(1, v0, values[idx++], rv);
	r = checkSensorValue(rv, history);

	readSensorValue(1, v0, values[idx++], rv);
	r = checkSensorValue(rv, history);

	readSensorValue(1, v0, values[idx++], rv);
	r = checkSensorValue(rv, history);

	readSensorValue(1, v0, values[idx++], rv);
	r = checkSensorValue(rv, history);
	CPPUNIT_ASSERT ( r==1 ); // 故障
}
