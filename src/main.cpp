/*
 * Copyright (c) 2020-2021 Advanced Robotics at the University of Washington <robomstr@uw.edu>
 *
 * This file is part of taproot-examples.
 *
 * taproot-examples is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * taproot-examples is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with taproot-examples.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "control/chassis/chassis_subsystem.hpp"
#include "tap/board/board.hpp"

#include "drivers_singleton.hpp"

static void updateIo(tap::Drivers *drivers);
static void initializeIo(tap::Drivers *drivers);
::Drivers *drivers = ::DoNotUse_getDrivers();
tap::arch::PeriodicMilliTimer remoteControl(2);

int main()
{
    /*
     * NOTE: We are using DoNotUse_getDrivers here because in the main
     *      robot loop we must access the singleton drivers to update
     *      IO states and run the scheduler.
     */
    Board::initialize();

    initializeIo(drivers);
    xcysrc::chassis::MecanumChassisSubsystem chassis(drivers);
    drivers->leds.set(tap::gpio::Leds::Red, true);
    modm::delay_ms(1000);
    drivers->leds.set(tap::gpio::Leds::Red, false);
    chassis.initialize();
    while (1)
    {
        if (remoteControl.execute())
        {
            chassis.setDesiredOutput(
                drivers->remote.getChannel(tap::Remote::Channel::LEFT_HORIZONTAL) * 4500.0f,
                drivers->remote.getChannel(tap::Remote::Channel::LEFT_VERTICAL) * 4500.0f,
                drivers->remote.getChannel(tap::Remote::Channel::RIGHT_HORIZONTAL) * -4500.0f);

            chassis.refresh();
            bool b = drivers->remote.getChannel(tap::Remote::Channel::LEFT_VERTICAL) < 0.5;
            drivers->leds.set(tap::gpio::Leds::Blue, b);

            drivers->djiMotorTxHandler.processCanSendData();
        }
        updateIo(drivers);
        modm::delay_us(10);
    }

    return 0;
}

static void initializeIo(tap::Drivers *drivers)
{
    // drivers->analog.init();
    // drivers->pwm.init();
    // drivers->digital.init();
    drivers->leds.init();
    drivers->can.initialize();
    // drivers->errorController.init();
    drivers->remote.initialize();
    // drivers->refSerial.initialize();
    // drivers->terminalSerial.initialize();
    // drivers->schedulerTerminalHandler.init();
    // drivers->djiMotorTerminalSerialHandler.init();
    drivers->leds.set(tap::gpio::Leds::Green, true);
    modm::delay_ms(1000);
    drivers->leds.set(tap::gpio::Leds::Green, false);
}

static void updateIo(tap::Drivers *drivers)
{
    // drivers->refSerial.updateSerial();
    drivers->remote.read();
    drivers->canRxHandler.pollCanData();
}
