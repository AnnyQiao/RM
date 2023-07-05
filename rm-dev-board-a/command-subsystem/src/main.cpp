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

#include "tap/control/hold_command_mapping.hpp"

#include "drivers_singleton.hpp"
#include "example_command.hpp"
#include "example_comprised_command.hpp"
#include "example_subsystem.hpp"

driversFunc drivers = DoNotUse_getDrivers;

ExampleSubsystem subsystem(drivers());
ExampleCommand command(&subsystem, 1000);
ExampleComprisedCommand comprisedCommand(drivers(), &subsystem);

tap::control::HoldCommandMapping leftSwitchUp(
    drivers(),
    {&comprisedCommand},
    tap::control::RemoteMapState(tap::Remote::Switch::LEFT_SWITCH, tap::Remote::SwitchState::UP));

int main()
{
    Drivers *drivers = DoNotUse_getDrivers();

    drivers->commandScheduler.registerSubsystem(&subsystem);
    subsystem.setDefaultCommand(&command);
    subsystem.initialize();
    drivers->commandMapper.addMap(&leftSwitchUp);

    tap::arch::PeriodicMilliTimer schedulerTimer{2};

    drivers->remote.initialize();
    drivers->can.initialize();

    while (true)
    {
        if (schedulerTimer.execute())
        {
            drivers->commandScheduler.run();
            drivers->djiMotorTxHandler.processCanSendData();
        }

        drivers->remote.read();
        drivers->canRxHandler.pollCanData();

        modm::delay_us(10);
    }
}
