#include "tap/drivers.hpp"

namespace xcysrc::control{
    class ControlOperatorInterface;
}

namespace xcysrc::chassis
{
class MecanumChassisSubsystem;

/**
 * A helper object that performs the computations necessary for chassis relative driving.
 * Call the function of the object in a chassis command's "execute" phase.
 * This will be used if you want to drive independently of the turret.
 */
class ChassisRelDrive
{
public:
    static void computeDesiredUserTranslation(
        xcysrc::control::ControlOperatorInterface *operatorInterface,
        tap::Drivers *drivers,
        MecanumChassisSubsystem *chassis,
        float chassisRotation,
        float *chassisXDesiredWheelspeed,
        float *chassisYDesiredWheelspeed);

    static void onExecute(
        xcysrc::control::ControlOperatorInterface *operatorInterface,
        tap::Drivers *drivers,
        MecanumChassisSubsystem *chassis);
};
}  // namespace xcysrc::chassis

