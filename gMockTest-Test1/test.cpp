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


#if __teacher
TEST(TestCaseName, TestNameFiveRead) {

	MockDevice mock_device;
	EXPECT_CALL(mock_device, read)
		.Times(5);

	DeviceDriver driver(&mock_device);
	driver.read(0xA);
}

TEST(TestCaseName, RaiseReadFailException) {
	MockDevice mock_device;
	//스터빙 4번은 잘 읽히는데 5번째 다른값이 읽힐 때
	EXPECT_CALL(mock_device, read(0x2))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x3));

	DeviceDriver driver(&mock_device);
	EXPECT_THROW(driver.read(0x2), ReadFailException);
}

TEST(TestCaseName, ReadTest) {
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read(0x2))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7));

	DeviceDriver driver(&mock_device);
	EXPECT_EQ(0x7, driver.read(0x2));
}

TEST(TestCaseName, WhenWriteThenReadeOneTime) {
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read(0xC))
		.Times(1)
		.WillOnce(Return(0xFF));

	DeviceDriver driver(&mock_device);
	driver.write(0xC, 787);
}

TEST(TestCaseName, WhenWriteThen0xFE) {
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read(0xC))
		.WillOnce(Return(0xFE));

	DeviceDriver driver(&mock_device);
	EXPECT_THROW(driver.write(0xC, 777), WriteFailException);
}

TEST(TestCaseName, Application_read) {
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read(_))
		.Times(25);

	DeviceDriver driver(&mock_device);
	Application app(&driver);

	app.ReadAndPrint(0x00, 0x04);
}


TEST(TestCaseName, Application_write) {
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read(_))
		.Times(5)
		.WillRepeatedly(Return(0xFF));
	EXPECT_CALL(mock_device, write(_, _))
		.Times(5);

	DeviceDriver driver(&mock_device);
	Application app(&driver);

	app.WriteAll(0x7);
}
#endif
