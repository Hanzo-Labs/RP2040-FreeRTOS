# RP2040-FreeRTOS Template 1.2.0

This repo contains my base project for [FreeRTOS](https://freertos.org/) on the [Raspberry Pi RP2040 microcontroller](https://www.raspberrypi.com/products/rp2040/). It can be run as a demo and then used as the basis of a new project.

More details [in this blog post](https://blog.smittytone.net/2022/02/24/how-to-use-freertos-with-the-raspberry-pi-pico/).

## Project Structure

```
/RP2040-FreeRTOS
|___/App-Template           // Application 1 (FreeRTOS template) source code
    |___CMakeLists.txt      // Application-level CMake config file
|___/App-Scheduling         // Application 2 (scheduling demo) source code
    |___CMakeLists.txt      // Application-level CMake config file
|___/App-IRQs               // Application 3 (IRQs demo) source code
    |___CMakeLists.txt      // Application-level CMake config file
|___/Config
    |___FreeRTOSConfig.h    // FreeRTOS project config file
|___/FreeRTOS-Kernel        // FreeRTOS kernel files, included as a submodule
|___/pico-sdk               // Raspberry Pi Pico SDK, included as a submodule
|___CMakeLists.txt          // Top-level project CMake config file
|___pico_sdk_import.cmake   // Raspberry Pi Pico SDK CMake import script
|___deploy.sh               // Build-and-deploy shell script
|___rp2040.code-workspace   // Visual Studio Code workspace
|___rp2040.xcworkspace      // Xcode workspace
|___README.md
|___LICENSE.md
```

## Prerequisites

To use the code in this repo, your system must be set up for RP2040 C/C++ development. See [this blog post of mine](https://blog.smittytone.net/2021/02/02/program-raspberry-pi-pico-c-mac/) for setup details.

## Usage

1. Clone the repo: `git clone https://github.com/smittytone/RP2040-FreeRTOS`.
1. Enter the repo: `cd RP2040-FreeRTOS`.
1. Install the submodules: `git submodule update --init --recursive`.
1. Optionally, edit `CMakeLists.txt` and `/<Application>/CMakeLists.txt` to rename the project.
1. Optionally, manually configure the build process: `cmake -S . -B build/`.
1. Optionally, manually build the app: `cmake --build build`.
1. Connect your device so it’s ready for file transfer.
1. Install the app: `./deploy.sh`.
    * To trigger a build, include the `--build` or `-b` flag: `./deploy.sh -b`.
    * Pass the app you wish to deplopy:
        * `./deploy.sh build/App-Template/TEMPLATE.uf2`.
        * `./deploy.sh build/App-Scheduling/SCHEDULING_DEMO.uf2`.

## The Apps

This repo includes a number of deployable apps. The project builds them all, sequentially. Exclude apps from the build process by commenting out their `add_subdirectory()` lines in the top-level `CMakeLists.txt`.

### App One: Template

This app provides a simple flip-flop using an on-board LED and an LED wired between GPIO 20 and GND. The board LED flashes every 500ms under one task. When its state changes, a message containing its state is added to a FreeRTOS inter-task xQueue. A second task checks for an enqueued message: if one is present, it reads the message and sets the LED it controls — the GPIO LED — accordingly to the inverse of the board LED’s state.

![Circuit layout](./images/plus.png)

The code demonstrates a basic FreeRTOS setup, but you can replace it entirely with your own code if you’re using this repo’s contents as a template for your own projects.

### App Two: Scheduling

This app builds on the first by adding an MCP9808 temperature sensor and an HT16K33-based LED display. It is used in [this blog post](https://blog.smittytone.net/2022/03/04/further-fun-with-freertos-scheduling/).

![Circuit layout](./images/scheduler.png)

### App Three: IRQs

This app builds on the second by using the MCP9808 temperature sensor to trigger an interrupt. It is used in [this blog post](https://blog.smittytone.net/2022/03/20/fun-with-freertos-and-pi-pico-interrupts-semaphores-notifications/).

![Circuit layout](./images/irqs.png)

## IDEs

Workspace files are included for the Visual Studio Code and Xcode IDEs.

## Credits

This work was inspired by work done on [Twilio Microvisor FreeRTOS Demo code](https://github.com/twilio/twilio-microvisor-freertos), but the version of the `FreeRTOSConfig.h` file included here was derived from [work by @yunka2](https://github.com/yunkya2/pico-freertos-sample).

## Copyright and Licences

Application source © 2022, Tony Smith and licensed under the terms of the [MIT Licence](./LICENSE.md).

[FreeRTOS](https://freertos.org/) © 2021, Amazon Web Services, Inc. It is also licensed under the terms of the [MIT Licence](./LICENSE.md).

The [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk) is © 2020, Raspberry Pi (Trading) Ltd. It is licensed under the terms of the [BSD 3-Clause "New" or "Revised" Licence](https://github.com/raspberrypi/pico-sdk/blob/master/LICENSE.TXT).
