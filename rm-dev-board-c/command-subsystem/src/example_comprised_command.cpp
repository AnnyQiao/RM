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

#include "example_comprised_command.hpp"

#include "drivers.hpp"
#include "example_command.hpp"
#include "example_subsystem.hpp"

ExampleComprisedCommand::ExampleComprisedCommand(
    Drivers* drivers,
    ExampleSubsystem* subsystem)
    : tap::control::ComprisedCommand(drivers),
      exampleCommand(subsystem, 2000),
      otherExampleCommand(subsystem, 500),
      switchTimer(2000),
      switchCommand(false)
{
    this->addSubsystemRequirement(subsystem);
    this->comprisedCommandScheduler.registerSubsystem(subsystem);
}

void ExampleComprisedCommand::initialize()
{
    this->comprisedCommandScheduler.addCommand(&exampleCommand);
}

void ExampleComprisedCommand::execute()
{
    if (switchTimer.execute())
    {
        switchTimer.restart(2000);
        if (switchCommand)
        {
            comprisedCommandScheduler.addCommand(&otherExampleCommand);
        }
        else
        {
            comprisedCommandScheduler.addCommand(&exampleCommand);
        }
        switchCommand = !switchCommand;
    }

    this->comprisedCommandScheduler.run();
}

void ExampleComprisedCommand::end(bool interrupted)
{
    comprisedCommandScheduler.removeCommand(&exampleCommand, interrupted);
}
