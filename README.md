[![pipeline status](https://gitlab.com/aruw/controls/taproot-examples/badges/develop/pipeline.svg)](https://gitlab.com/aruw/controls/taproot-examples/-/commits/develop)

## taproot-examples

This repository contains small example projects to demonstrate various features in
[Taproot](https://gitlab.com/aruw/controls/taproot). This repository currently has examples specific
to the RoboMaster Development Board Type A and Type C.

## Examples

The following examples have been implemented:

- RoboMaster Development Board Type A:
    - [IMU](rm-dev-board-a/imu/src/main.cpp) - The onboard Inertial Measurement Unit. Reads data
      such as orientation and acceleration from the internal mpu6500 IMU. Data can be retrieved via
      the `mpu6500` object.
    - [LEDs](rm-dev-board-a/leds/src/main.cpp) - The example blinks one of the LEDs.
    - [OELD](rm-dev-board-a/oled/src/main.cpp) - Prints "Hello World" if a [RoboMaster OLED
      display](https://store.dji.com/product/rm-development-board-oled) is connected to the
      development board.
    - [Remote Control](rm-dev-board-a/remote-control/src/main.cpp) - Reads data from a connected
      DR16 remote receiver. Use the API provided by the `remote` object to get remote data.
    - [Servo](rm-dev-board-a/servo/src/main.cpp) - Changes the desired PWM value of a servo
      connected to the development board between some min and max values based on input from a
      digital pin.
    - [Velocity Motor Controller](rm-dev-board-a/velocity-motor-controller/src/main.cpp) - Runs a
      PID controller to command a "DJI" motor (currently supported motors include any RoboMaster
      branded motor) connected on a particular CAN bus with a particular motor ID to some desired
      velocity.

- RoboMaster Development Board Type C:
    - [IMU](rm-dev-board-c/imu/src/main.cpp) - The onboard Inertial Measurement Unit. Reads data
      such as orientation and acceleration from the internal bmi088 IMU. Data can be retrieved via
      the `bmi088` object. Not yet implemented because waiting for
      https://gitlab.com/aruw/controls/taproot/-/merge_requests/96 to be merged in
    - [LEDs](rm-dev-board-c/leds/src/main.cpp) - Identical to the type A example but for the type C
      board.
    - [Remote Control](rm-dev-board-c/remote-control/src/main.cpp) - Reads data from a connected
      DR16 remote receiver. Use the API provided by the `remote` object to get remote data.
    - [Servo](rm-dev-board-c/servo/src/main.cpp) - Identical to the type A example but for the type
      C board.
    - [Velocity Motor Controller](rm-dev-board-c/velocity-motor-controller/src/main.cpp) - Identical
      to the type A example but for the type C board.

## Using these examples

It is assumed you have a development environment set up that allows you to deploy to the development
board. See
[here](https://gitlab.com/aruw/controls/taproot/-/blob/develop/README.md#user-content-development-guide)
for setting up your development environment. Once this is done, you can use these examples via the
following steps:

1. Clone the repository. `cd` into the repository and update submodules (`git submodule update
   --init --recursive`).
1. `cd` into the `taproot-examples` directory and if its your first time running an example, run
   `pipenv install`.
1. `cd` into the `taproot-examples` directory and run `pipenv shell`.
1. `cd` into the example project that you would like to try out.
1. Run `lbuild build` to generate code necessary for the example.
1. Run `scons build` to build the example code.
1. Use either a J-Link or ST-Link to deploy the code to the development board you are using. If you
   are using an ST-Link, run `scons run` with the ST-Link plugged into your computer. If you are
   using a J-Link, use
   [Ozone](https://www.segger.com/products/development-tools/ozone-j-link-debugger/) to flash the
   built `.elf` file to the development board.
