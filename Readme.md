# R-Type Game Project

## Overview
R-Type is an advanced C++ project focused on developing a multithreaded server and a graphical client for the legacy video game R-Type. This project is an exploration of networked game development, incorporating advanced software engineering techniques.

## Project Structure
- **Part 1:** Core game architecture and a working prototype.
- **Part 2:** Expansion of the prototype with specialized features.

## Key Features
- Networking with a multithreaded server and client.
- Architectural patterns of a real game engine.
- Implementation of a binary protocol for client-server communication.
- Cross-platform compatibility (Windows and Linux).

## Server
- Manages game logic.
- Acts as an authoritative source for game events.
- Robust and multithreaded design.

## Client
- Graphical display and input handling.
- Partial game logic execution.

## Tools and Practices
- CMake for build system management.
- Git for version control.
- Continuous Integration and Continuous Deployment (CI/CD) workflows.

## Documentation
- Emphasis on proper, continuous documentation throughout the project.

## Getting Started

### Windows:
- [Setup Environment](docs/WindowsInitialSetup.md)

### Linux:
- [Setup Project](docs/InitDependancies.md)

## Launching the Game

### Solo Play (Linux)
To play R-Type in solo mode on Linux:
1. Navigate to the `build/client` directory.
2. Run the game using the command:
   ```
   ./r-type-client
   ```

### Multiplayer Play (Linux)
To play R-Type in multiplayer mode on Linux:
1. Start the server:
   - Navigate to the `build/server` directory.
   - Run the server using the command:
     ```
     ./r-type-server
     ```
2. Then, start the client in multiplayer mode:
   - Navigate to the `build/client` directory.
   - Run the client with the multiplayer flag using the command:
     ```
     ./r-type-client --multiplayer
     ```
