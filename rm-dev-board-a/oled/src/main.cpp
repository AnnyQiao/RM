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

#include "tap/board/board.hpp"
#include "tap/display/sh1106.hpp"

#include "drivers_singleton.hpp"

tap::display::Sh1106<
#ifndef PLATFORM_HOSTED
    Board::DisplaySpiMaster,
    Board::DisplayCommand,
    Board::DisplayReset,
#endif
    128,
    64,
    false>
    display;

int main()
{
    /*
     * NOTE: We are using DoNotUse_getDrivers here because in the main
     *      robot loop we must access the singleton drivers to update
     *      IO states and run the scheduler.
     */
    ::Drivers *drivers = ::DoNotUse_getDrivers();

    Board::initialize();
    display.initializeBlocking();

    display << "Hello world";
    display.update();

    while (1)
    {
        display.updateNonblocking();
        modm::delay_us(10);
    }
    return 0;
}
