#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../gMockTest/DeviceDriver.cpp"

using namespace testing;


class FlashMemoryDeviceMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(TestCaseName, TestName) {
	EXPECT_THAT(1, Eq(1));
}