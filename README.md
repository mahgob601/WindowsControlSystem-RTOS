# POWER WINDOW CONTROL SYSTEM USING TIVA C RUNNING FREERTOS

## Project Scope

This project involves the implementation of a power window control system for a car's front passenger door using Tiva C and FreeRTOS. The system includes both driver and passenger control panels, limit switches, obstacle detection, and an ON/OFF switch for locking the passenger panel from the driver panel.

### Key Features
1. **Control Panels**: Both driver and passenger can control the front passenger door window.
2. **Limit Switches**: Two limit switches to limit the window motor from top and bottom limits.
3. **Obstacle Detection**: The system can detect obstacles and respond accordingly.
4. **ON/OFF Switch**: Allows the driver to lock the passenger's control panel.

## Hardware Implementation

### Components
1. **Motor Driver**: Controls the DC motor with a 12V power supply.
2. **Push Buttons**: Simulate motor movement and automatic up/down operations.
3. **Limit Switches**: Limit the motor's up and down movement.
4. **Obstacle Signal**: Simulated using a push button.
5. **ON/OFF Switch**: Locks the passenger control panel.

### Connections to the Tiva C
- **VCC**: For the breadboard.
- **Motor Driver Pins**: Connected to Tiva C for motor control.
- **Buttons**: Connected to Tiva C for user input.
- **Limit Switches and Obstacle Signal**: Connected to Tiva C for motor control and obstacle detection.

### Button Layout
- **Driver Control**: Auto up, auto down, manual up, manual down.
- **Passenger Control**: Auto up, auto down, manual up, manual down.
- **Obstacle Detection**: Simulated with a button.

## Software Implementation

The software is organized into several files, each handling specific functionalities.

### Files and Functions

#### motorControl.c
- **void motorUP()**: Activates the motor to move the window up.
- **void motorDown()**: Activates the motor to move the window down.
- **void motorOFF()**: Turns off the motor.

#### functions.c
- **openCloseDriver()**: Manages the driver's manual window control using semaphores and a queue.
- **openClosePassenger()**: Manages the passenger's manual window control.
- **openCloseDriverAuto()**: Manages the driver's automatic window control.
- **openClosePassengerAuto()**: Manages the passenger's automatic window control.
- **obstacle()**: Handles obstacle detection and response.
- **control()**: Continuously checks input pins and sends corresponding messages to the queue and semaphores.

#### main.c
- **Initialization**: Declares queues, task handlers, and semaphore handlers.
- **Task Creation**: Creates tasks for controlling the windows and managing the overall system.
- **Scheduler**: Starts the FreeRTOS scheduler to manage task execution.

### Task and Semaphore Management

The project uses FreeRTOS tasks and semaphores to manage the window control operations, ensuring synchronization and efficient CPU utilization.

- **Tasks**: Separate tasks for driver and passenger control, both manual and automatic.
- **Semaphores**: Binary semaphores for synchronizing access to shared resources.

### Flow Chart

A flow chart is used to represent the logical flow of operations within the system, ensuring clear understanding and effective debugging.

## Getting Started

### Prerequisites
- **Tiva C Series Microcontroller**
- **FreeRTOS**
- **Motor Driver and DC Motor**
- **Push Buttons and Limit Switches**
- **Breadboard and Connecting Wires**

### Installation
1. Clone the repository:
   ```
   git clone https://github.com/yourusername/RTOS-Power-Window-Control.git
   ```
2. Open the project in your preferred IDE (e.g., Keil uVision, Code Composer Studio).
3. Compile and upload the code to the Tiva C microcontroller.

### Usage
- Connect the hardware components as specified in the connections section.
- Power on the system.
- Use the buttons to simulate window control operations and observe the system's response.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your changes.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

## Acknowledgments

- FreeRTOS community for providing the RTOS framework.
- Texas Instruments for the Tiva C microcontroller platform.

---
