#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace std;

class readSensorValuetest : public CPPUNIT_NS :: TestFixture
{
	CPPUNIT_TEST_SUITE (readSensorValuetest);
	CPPUNIT_TEST (test01);
	CPPUNIT_TEST (test02);
	CPPUNIT_TEST (test03);
	CPPUNIT_TEST (test04);
	CPPUNIT_TEST_SUITE_END ();

	public:
		void setUp (void);
		void tearDown (void);

	protected:
		void test01 (void);
		void test02 (void);
		void test03 (void);
		void test04 (void);

	private:
	// add private values
};
