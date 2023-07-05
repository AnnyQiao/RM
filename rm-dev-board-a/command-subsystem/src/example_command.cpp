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

#include "example_command.hpp"

#include "example_subsystem.hpp"

using tap::control::Subsystem;

ExampleCommand::ExampleCommand(ExampleSubsystem* subsystem, int speed)
    : subsystemExample(subsystem),
      speed(speed)
{
    addSubsystemRequirement(subsystem);
}

void ExampleCommand::initialize() {}

void ExampleCommand::execute() { subsystemExample->setDesiredRpm(speed); }

void ExampleCommand::end(bool)
{
    subsystemExample->setDesiredRpm(0);
}

bool ExampleCommand::isFinished(void) const { return false; }
