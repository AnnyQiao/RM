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

#include "drivers_singleton.hpp"

static constexpr uint32_t SERVO_UPDATE_TIME = 100;
static constexpr float MIN_SERVO_PWM = 0.1f;
static constexpr float MAX_SERVO_PWM = 0.2f;

int main()
{
    /*
     * NOTE: We are using DoNotUse_getDrivers here because in the main
     *      robot loop we must access the singleton drivers to update
     *      IO states and run the scheduler.
     */
    ::Drivers *drivers = ::DoNotUse_getDrivers();

    Board::initialize();
    drivers->pwm.init();
    drivers->digital.init();

    while (1)
    {
        drivers->pwm.write(
            drivers->digital.read(tap::gpio::Digital::Button) ? MAX_SERVO_PWM : MIN_SERVO_PWM,
            tap::gpio::Pwm::X);

        modm::delay_ms(SERVO_UPDATE_TIME);
    }
    return 0;
}
