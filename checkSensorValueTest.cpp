#include <iostream>
#include <sstream>

#include "checkSensorValue.h"
#include "checkSensorValueTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION (checkSensorValueTest);

void checkSensorValueTest :: setUp (void)
{
	// set up test environment (initializing objects)
}

void checkSensorValueTest :: tearDown (void) 
{
	// finally delete objects
}

// v		va		n		r
// *		[]		0		0
// *		[a,b]		2		0
// x		[a,b,c,d,e]	5		0
// y		[a,b,c,d,e]	5		1
// z		[a,b,c,d,e]	5		2
// 
//
void checkSensorValueTest :: testS01 (void) 
{
	int16_t v = 3000;
	Values h({});
	
	int r = checkSensorValueSub(v,h);

    cout << "r=" << r;
	CPPUNIT_ASSERT ( r== 0 );
}

void checkSensorValueTest :: testS02 (void) 
{
	int16_t v = 3000;
	Values h({3005,3010});
	int r = checkSensorValueSub(v,h);	

    cout << "r=" << r;
	CPPUNIT_ASSERT ( r== 0 );
}

void checkSensorValueTest :: testS03 (void) 
{
	int16_t v = 3000;
	Values h({3005, 3010, 3015, 3020, 3030});
	int r = checkSensorValueSub(v,h);	

    cout << "r=" << r;
	CPPUNIT_ASSERT ( r== 0 );
}

void checkSensorValueTest :: testS04 (void) 
{
	int16_t v = 3000;
	Values h({3000, 3005, 3010, 3005, 3010});
	int r = checkSensorValueSub(v,h);	

    cout << "r=" << r;
	CPPUNIT_ASSERT ( r== 1 );
}

void checkSensorValueTest :: testS05 (void) 
{
	int16_t v = 3000;
	Values h({3000, 3105, 3210, 3100, 3000});
	int r = checkSensorValueSub(v,h);	

    cout << "r=" << r;
	CPPUNIT_ASSERT ( r== 2 );
}

void checkSensorValueTest :: testS06 (void) 
{
	int16_t v = 3200;
	Values h({3000, 3050, 3110, 3200, 3150});
	int r = checkSensorValueSub(v,h);	

    cout << "r=" << r;
	CPPUNIT_ASSERT ( r== 0 );
}

static int16_t ia1[] = {3000};
static Values rv1({3000});

void checkSensorValueTest :: testM01 (void) 
{
	Values defected;

	SensorHistory sh(0, ia1, 1);
	cout << endl << "sh= " << sh.str();
	
	checkSensorValue(rv1,sh,defected);
    cout << "r= " << defected[0];
	CPPUNIT_ASSERT ( defected[0] == 0 );
}

static int16_t ia2[] = { 3000, 3001 };
static Values rv2({3000});

void checkSensorValueTest :: testM02 (void) 
{
	Values defected;

	SensorHistory sh(0, ia2, 2);
	cout << endl << "sh= " << sh.str();
	
	checkSensorValue(rv2,sh,defected);
	cout << "r= " << defected[0];
	CPPUNIT_ASSERT ( defected[0] == 0 );
}

static int16_t ia3[] = { 3000,3001,3002,3003,3004 };
static Values rv3({3000});

// スタック故障検知
void checkSensorValueTest :: testM03 (void) 
{
	Values defected;

	SensorHistory sh(0, ia3, 5);
	cout << endl << "sh= " << sh.str();
	
	checkSensorValue(rv3,sh,defected);
    cout << "r= " << defected[0];
	CPPUNIT_ASSERT ( defected[0] == 1 );
}

static int16_t ia4[] = { 3000,4000,5000,4000,3000 };
static Values rv4({3015});

// ランダム故障検知
void checkSensorValueTest :: testM04 (void) 
{
	Values defected;

	SensorHistory sh(0, ia4, 5);
	cout << endl << "sh= " << sh.str();
	
	checkSensorValue(rv4,sh,defected);
    cout << "r= " << defected[0];
	CPPUNIT_ASSERT ( defected[0] == 2 );
}
