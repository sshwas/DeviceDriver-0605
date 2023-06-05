#include <string>
#include <iostream>
#include "DeviceDriver.h"

using namespace std;

class App
{
public:
    App(DeviceDriver* driver) : m_deviceDriver(driver)
    {}

    void ReadAndPrint(long startAddr, long endAddr)
    {
        for(int addr = startAddr; addr <= endAddr; ++addr)
			cout << m_deviceDriver->read(addr);
    }

    void WriteAll(int value)
    {
        m_deviceDriver->write(0x0, value);
        m_deviceDriver->write(0x1, value);
        m_deviceDriver->write(0x2, value);
        m_deviceDriver->write(0x3, value);
        m_deviceDriver->write(0x4, value);
    }

private:
    DeviceDriver* m_deviceDriver;
};