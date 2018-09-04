#include "pch.h"
#include "StartupTask.h"

using namespace PowerBlockWinIoT;

using namespace Platform;
using namespace Windows::ApplicationModel::Background;

// The Background Application template is documented at http://go.microsoft.com/fwlink/?LinkID=533884&clcid=0x409

void StartupTask::Run(IBackgroundTaskInstance^ taskInstance)
{
    // 
    // TODO: Insert code to perform background work
    //
    // If you start any asynchronous methods here, prevent the task
    // from closing prematurely by using BackgroundTaskDeferral as
    // described in http://aka.ms/backgroundtaskdeferral
    //
	while (true)
	{
		GpioPin ^statusPin = ConfigureGpioPin(statusPinNumber);
		if (statusPin != nullptr)
		{
			statusPin->Write(GpioPinValue::High);
		}

		Sleep(msSleepDuration);
	}
}

GpioPin ^ PowerBlockWinIoT::StartupTask::ConfigureGpioPin(int pinNumber)
{
	auto gpioController = GpioController::GetDefault();

	GpioPin ^pin = nullptr;
	if (gpioController != nullptr)
	{
		pin = gpioController->OpenPin(pinNumber);
		if (pin != nullptr) 
		{
			pin->SetDriveMode(GpioPinDriveMode::Output);
		}
	}

	return pin;
}
