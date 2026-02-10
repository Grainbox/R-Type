# 🛸 R-Type: Advanced Multithreaded Space Shooter

[![C++ 17](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![CMake](https://img.shields.io/badge/CMake-Build-green.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

R-Type is a modern C++ implementation of the classic arcade shooter, featuring a **multithreaded server** and a **graphical client**. This project serves as an exploration of advanced networked game development, implementing a custom binary protocol and a robust game engine architecture.

---

## ✨ Key Features

- **High-Performance Networking:** Multithreaded server utilizing `Asio` for low-latency UDP communication.
- **Custom Game Engine:** Modular architecture with a clear separation between game logic (Server) and rendering (Client).
# R-Type: Modern C++ Multiplayer Action

A fast-paced, modern C++ implementation of the classic R-Type game, featuring a custom ECS (Entity Component System) and robust UDP networking.

## Features

- **Custom ECS Engine**: High-performance entity management.
- **Cross-Platform Networking**: Reliable UDP communication using `asio`.
- **Dynamic Graphics**: Powered by `raylib`.
- **Automated Windows Build**: One-click setup on Windows.

## Quick Start (Windows)

To get started on Windows, simply run the automated setup script in PowerShell:

```powershell
.\setup.ps1
```

This will initialize dependencies, configure CMake, and build both the client and server.

## Running the Game

### Server
```powershell
.\build\server\Release\r-type_server.exe
```

### Client
```powershell
.\build\client\Release\r-type_client.exe --multiplayer
```

## Documentation

- [Initialization & Dependencies](docs/InitDependencies.md)
).
2. Build the project:
   ```bash
   ./build.sh
   ```

---

## 🎮 Launching the Game

### Multiplayer Mode
To play with others, you'll need one instance of the server and multiple instances of the client.

1. **Start the Server:**
   ```powershell
   # Windows
   .\build\server\Release\r-type-server.exe
   
   # Linux
   ./build/server/r-type-server
   ```

2. **Start the Client:**
   ```powershell
   # Windows
   .\build\client\Release\r-type-client.exe --multiplayer
   
   # Linux
   ./build/client/r-type-client --multiplayer
   ```

### Solo Mode
Simply run the client without any flags:
```bash
# Windows
.\build\client\Release\r-type-client.exe

# Linux
./build/client/r-type-client
```

---

## 📁 Project Structure

| Component | Description |
| :--- | :--- |
| `engine/` | Core logic, ECS patterns, and shared utilities. |
| `server/` | Authoritative game server (Logic & Networking). |
| `client/` | Visual client (Rendering & User Input). |
| `docs/` | In-depth documentation on architecture and protocols. |

---

## 🛠️ Built With

- **Language:** C++17
- **Networking:** [Asio](https://think-async.com/Asio/)
- **Graphics:** [raylib](https://www.raylib.com/)
- **Serialization:** [Boost.Serialization](https://www.boost.org/doc/libs/release/libs/serialization/)
- **Build System:** CMake
- **Dependency Manager:** vcpkg

---

## 📖 Documentation

For more detailed information, check out the `docs/` directory:
- [Windows Initial Setup](docs/WindowsInitialSetup.md)
- [Project Dependencies](docs/InitDependencies.md)
- [Building with CMake](docs/BuildWithCMake.md)

---

## 🗺️ Roadmap

Check out our [Open Source Roadmap](ROADMAP.md) for upcoming features and tasks.
