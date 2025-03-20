# ECE1188 Design Project 1

Shared repository for Design Challenge #1: Line Following Race

## Project Structure

The top level project contains dependency files like `Clock.C`, `Reflectance.C` and `CortexM.c`

The relevant folders in the top level project are:

### Modules Folder
Contains separate folders for each module:
- **BumpSwitches**: Code for bump sensor functionality
- **FSM**: Code for the finite state machine implementation
- **Motors**: Code for motor control and movement

### Integration Folder
Contains `main.c`, which is the code that runs on the robot during the line following race.
