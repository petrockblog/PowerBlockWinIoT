#pragma once

#include "pch.h"

using namespace Windows::Devices::Gpio;

namespace PowerBlockWinIoT
{
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class StartupTask sealed : public Windows::ApplicationModel::Background::IBackgroundTask
    {
    public:
        virtual void Run(Windows::ApplicationModel::Background::IBackgroundTaskInstance^ taskInstance);

	private:
		const int statusPinNumber = 17;
		const int shutdownSignalPinNumber = 18;
		const int msSleepDuration = 500;

		GpioPin ^ConfigureGpioPin(int pinNumber, GpioPinDriveMode mode);

    };
}
