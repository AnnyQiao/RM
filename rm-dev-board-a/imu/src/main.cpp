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

#include "tap/architecture/periodic_timer.hpp"
#include "tap/board/board.hpp"

#include "drivers_singleton.hpp"

tap::arch::PeriodicMilliTimer updateImuTimeout(2);

float yaw;

int main()
{
    /*
     * NOTE: We are using DoNotUse_getDrivers here because in the main
     *      robot loop we must access the singleton drivers to update
     *      IO states and run the scheduler.
     */
    ::Drivers *drivers = ::DoNotUse_getDrivers();

    Board::initialize();
    drivers->mpu6500.init();

    while (1)
    {
        drivers->mpu6500.read();

        if (updateImuTimeout.execute())
        {
            drivers->mpu6500.periodicIMUUpdate();
            yaw = drivers->mpu6500.getYaw();
            // TODO use yaw
        }

        modm::delay_us(10);
    }
    return 0;
}
