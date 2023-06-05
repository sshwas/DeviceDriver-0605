#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../gMockTest/DeviceDriver.cpp"
#include "../gMockTest/App.cpp"
#include <ctime>
#include <vector>

using namespace testing;
using namespace std;

class FlashMemoryDeviceMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};


TEST(TestCaseName, TCReadElapsedTimeCheck)
{
	FlashMemoryDeviceMock mockDevice;

	EXPECT_CALL(mockDevice, read)
		.Times(5); // for behavior verification

	DeviceDriver driver(&mockDevice);

	time_t start = clock();
	driver.read(0xA);
	time_t end = clock();

	EXPECT_THAT((int)(end - start), Ge(800));
}

TEST(TestCaseName, TCReadFiveTimes)
{
	FlashMemoryDeviceMock mockDevice;

	EXPECT_CALL(mockDevice, read)
		.Times(5); // for behavior verification

	DeviceDriver driver(&mockDevice);
	driver.read(0xA);
}

TEST(TestCaseName, TCReadException)
{
	FlashMemoryDeviceMock mockDevice;

	EXPECT_CALL(mockDevice, read)
		.Times(5) // for behavior verification
		.WillOnce(Return(100))
		.WillOnce(Return(100))
		.WillOnce(Return(100))
		.WillOnce(Return(100))
		.WillOnce(Return(101)); // for stubbing

	DeviceDriver driver(&mockDevice);
	EXPECT_THROW(driver.read(0xA), std::exception);
}


TEST(TestCaseName, TCWrite)
{
	FlashMemoryDeviceMock mockDevice;

	EXPECT_CALL(mockDevice, read)
		.Times(1) // for behavior verification
		.WillOnce(Return(0xFF));

	DeviceDriver driver(&mockDevice);
	driver.write(0xA, 100);
}

TEST(TestCaseName, TCOverWrite)
{
	FlashMemoryDeviceMock mockDevice;

	EXPECT_CALL(mockDevice, write)
		.Times(1); // for behavior verification

	EXPECT_CALL(mockDevice, read)
		.Times(2) // for behavior verification
		.WillOnce(Return(0xFF))
		.WillOnce(Return(100));

	DeviceDriver driver(&mockDevice);
	driver.write(0xA, 100);
	EXPECT_THROW(driver.write(0xA, 120), std::exception);
}

TEST(TestCaseName, TCAppReadAndPrint)
{
	FlashMemoryDeviceMock mockDevice;

	EXPECT_CALL(mockDevice, read(_))
		.Times(25) // for behavior verification
		.WillRepeatedly(Return(0xFF));

	DeviceDriver driver(&mockDevice);
	App app(&driver);
	app.ReadAndPrint(0, 4);
}

TEST(TestCaseName, TCAppWriteAll)
{
	FlashMemoryDeviceMock mockDevice;

	EXPECT_CALL(mockDevice, read(_))
		.Times(5) // for behavior verification
		.WillRepeatedly(Return(0xFF));
	EXPECT_CALL(mockDevice, write(_,_))
		.Times(5); // for behavior verification

	DeviceDriver driver(&mockDevice);
	App app(&driver);
	app.WriteAll(55);
}

