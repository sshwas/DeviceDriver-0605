#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../gMockTest/DeviceDriver.cpp"
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
