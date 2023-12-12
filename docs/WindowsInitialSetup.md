# Initial Setup for C++ Development on Windows

This documentation guides you through the steps to set up a C++ development environment on Windows, using Visual Studio Build Tools 2022 and Visual Studio Code.

## Installing Visual Studio Build Tools

Visual Studio Build Tools 2022 provides a C++ development environment for Windows, including the C++ compiler, standard libraries, and other utilities.

### Download and Installation

1. **Download the Build Tools:**
   - Go to the [Visual Studio downloads page](https://visualstudio.microsoft.com/en/downloads/).
   - Find "Build Tools for Visual Studio 2022" and download the installer.

2. **Install the Tools:**
   - Run the downloaded installer.
   - Select "Desktop development with C++".
   - Complete the installation.

### Environment Setup

After installation:

1. **Open Developer PowerShell:**
   - Go to "All Programs" > "Visual Studio 2022" > "Visual Studio Tools".
   - Launch "Developer PowerShell for VS" to set up your development environment.

2. **Follow Additional Documentation:**
   - For project dependencies and repository setup, refer to [`InitDependencies.md`](InitDependancies.md), which explains how to clone the repository and install dependencies using the provided vcpkg module.

## OPTIONAL: Configuring Visual Studio Code for C++

1. **Install Visual Studio Code:**
   - Download VS Code from the [official website](https://code.visualstudio.com/).

2. **Install Extensions:**
   - Open VS Code.
   - Install the "C/C++" extension for language support and the "CMake Tools" extension for build and debug capabilities.

3. **Configure the Workspace:**
   - Open the project folder in VS Code.
   - Follow the [VS Code documentation for C++](https://code.visualstudio.com/docs/cpp/config-msvc) to configure your workspace.

This documentation provides the basics to start C++ development on Windows with Visual Studio Build Tools 2022 and VS Code. Once the setup is complete, you can start working on your C++ projects.

## Next Step:
- For setting up your project, follow the instructions in [`InitDependencies.md`](InitDependancies.md).
