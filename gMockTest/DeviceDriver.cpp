#include <windows.h>
#include <stdexcept>
#include "DeviceDriver.h"

using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
	int value = (int)(m_hardware->read(address));
	for (int tryCount = 2; tryCount <= READ_TRY_COUNT; ++tryCount)
	{
		Sleep(READ_INTERVAL_IN_MS);
		int nextValue = (int)(m_hardware->read(address));
		if (value == nextValue)
			continue;
		
		throw std::invalid_argument("read fail");
	}
	return value;
}

void DeviceDriver::write(long address, int data)
{
	int value = (int)(m_hardware->read(address));
	if (value != 0xFF)
		throw std::invalid_argument("over-write");

    m_hardware->write(address, (unsigned char)data);
}
