#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;

class checkSensorValueTest : public CPPUNIT_NS :: TestFixture
{
	CPPUNIT_TEST_SUITE (checkSensorValueTest);
	CPPUNIT_TEST (testS01);
	CPPUNIT_TEST (testS02);
	CPPUNIT_TEST (testS03);
	CPPUNIT_TEST (testS04);
	CPPUNIT_TEST (testS05);
	CPPUNIT_TEST (testS06);
	CPPUNIT_TEST (testM01);
	CPPUNIT_TEST (testM02);
	CPPUNIT_TEST (testM03);
	CPPUNIT_TEST (testM04);
	CPPUNIT_TEST_SUITE_END ();

	public:
		void setUp (void);
		void tearDown (void);

	protected:
		void testS01 (void);
		void testS02 (void);
		void testS03 (void);
		void testS04 (void);
		void testS05 (void);
		void testS06 (void);
		void testM01 (void);
		void testM02 (void);
		void testM03 (void);
		void testM04 (void);

	private:
	// add private values
};
