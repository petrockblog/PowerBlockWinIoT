#include "pch.h"
#include "StartupTask.h"

using namespace PowerBlockWinIoT;

using namespace Platform;
using namespace Windows::ApplicationModel::Background;

// The Background Application template is documented at http://go.microsoft.com/fwlink/?LinkID=533884&clcid=0x409

void StartupTask::Run(IBackgroundTaskInstance^ taskInstance)
{
	GpioPin ^statusPin = ConfigureGpioPin(statusPinNumber, GpioPinDriveMode::Output);
	GpioPin ^shutdownSignalPin = ConfigureGpioPin(shutdownSignalPinNumber, GpioPinDriveMode::Input);

	if ((statusPin != nullptr) && (shutdownSignalPin != nullptr))
	{		
		statusPin->Write(GpioPinValue::High);
		while (true)
		{
			GpioPinValue shutdownValue = shutdownSignalPin->Read();
			if (shutdownValue == GpioPinValue::High) {
				// Shutdowns the device immediately:
				const Windows::Foundation::TimeSpan timeSpan = { 0 };
				Windows::System::ShutdownManager::BeginShutdown(Windows::System::ShutdownKind::Shutdown, timeSpan);
			}

			Sleep(msSleepDuration);
		}
	}
}

GpioPin ^ PowerBlockWinIoT::StartupTask::ConfigureGpioPin(int pinNumber, GpioPinDriveMode mode)
{
	auto gpioController = GpioController::GetDefault();

	GpioPin ^pin = nullptr;
	if (gpioController != nullptr)
	{
		pin = gpioController->OpenPin(pinNumber);
		if (pin != nullptr) 
		{
			pin->SetDriveMode(mode);
		}
	}

	return pin;
}
