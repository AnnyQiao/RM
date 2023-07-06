#include "tap/board/board.hpp"
#include "modm/platform/timer/timer_1.hpp"

#include "modm/architecture/interface/delay.hpp"
#include "modm/architecture/interface/interrupt.hpp"

/* arch includes ------------------------------------------------------------*/
#include "tap/architecture/periodic_timer.hpp"
#include "tap/architecture/profiler.hpp"

/* communication includes ---------------------------------------------------*/
#include "src/drivers_singleton.hpp"

/* error handling includes --------------------------------------------------*/
#include "tap/errors/create_errors.hpp"

/* control includes ---------------------------------------------------------*/
#include "tap/architecture/clock.hpp"

#include "src/robot/robot_control.hpp"

#include "tap/communication/gpio/pwm.hpp"

static void initializePWM(tap::Drivers *drivers)
{
    drivers->leds.set(tap::gpio::Leds::Blue, true);
    modm::delay_ms(1000);
    drivers->leds.set(tap::gpio::Leds::Blue, false);
    tap::gpio::Pwm::Pin pwmPin1= tap::gpio::Pwm::Pin::C1;
    drivers->pwm.setTimerFrequency(tap::gpio::Pwm::Timer::TIMER1, 100);
    tap::gpio::Pwm::Pin pwmPin2= tap::gpio::Pwm::Pin::C2;
    drivers->pwm.write(0.2,pwmPin1);
    drivers->pwm.write(0.2,pwmPin2);
    modm::delay_ms(2000);
    drivers->pwm.write(0.1,pwmPin1);
    drivers->pwm.write(0.1,pwmPin2);
    modm::delay_ms(100);
// every time robot got killed or power off, initialize the gpio again
// better to make it to the button
}

static void spinFrictionWheel(tap::Drivers *drivers)
{
    tap::gpio::Pwm::Pin pwmPin1= tap::gpio::Pwm::Pin::C1;
    drivers->pwm.write(0.125,pwmPin1);
}

static void stopFrictionWheel(tap::Drivers *drivers)
{
    tap::gpio::Pwm::Pin pwmPin1= tap::gpio::Pwm::Pin::C1;
    drivers->pwm.write(0.1,pwmPin1);
}