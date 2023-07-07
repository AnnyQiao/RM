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

#include "example_subsystem.hpp"

#include "drivers.hpp"

ExampleSubsystem::ExampleSubsystem(
    Drivers* drivers,
    tap::motor::MotorId aMotorId,
    : tap::control::Subsystem(drivers),
      desiredRpm(0),
      agitator(drivers, aMotorId, CAN_BUS_MOTORS, true, "left example motor"),
{
}

void ExampleSubsystem::initialize()
{
    agitator.initialize();
}

void ExampleSubsystem::setDesiredRpm(float desRpm) { desiredRpm = desRpm; }

void ExampleSubsystem::refresh()
{
    updateMotor(desiredRpm);
}

void ExampleSubsystem::updateMotor(float desiredRpm)
{
    agitator->setDesiredOutput(static_cast<int32_t>(desiredRpm));
}
