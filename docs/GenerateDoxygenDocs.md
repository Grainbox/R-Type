# Project Documentation - Generation with Doxygen

## Installation

### Windows

#### Doxygen
1. Download the Doxygen installer from [doxygen.nl](https://www.doxygen.nl/).
2. Run the installer and follow the on-screen instructions to install Doxygen.

#### Graphviz (for dependency graphs)
1. Download Graphviz from [graphviz.org](https://graphviz.org/).
2. Install Graphviz by following the on-screen instructions.

### Linux

#### Doxygen
- On Arch Linux, use the command:
  ```bash
  sudo pacman -Sy doxygen
  ```
- On other Linux distributions, use the appropriate package manager, for example `sudo apt-get install doxygen` for Ubuntu.

#### Graphviz
- On Arch Linux:
  ```bash
  sudo pacman -Sy graphviz
  ```
- On other Linux distributions, use the appropriate package manager.

### MacOS

#### Doxygen
- Install Doxygen via Homebrew:
  ```bash
  brew install doxygen
  ```

#### Graphviz
- Install Graphviz via Homebrew:
  ```bash
  brew install graphviz
  ```

## Generating Documentation

Once Doxygen and Graphviz are installed, follow these steps to generate your project's documentation:

1. **Open a terminal** in the root directory of the project.
2. **Run Doxygen** with the following command:
   ```bash
   doxygen Doxyfile
   ```
   - Ensure that the `Doxyfile` is correctly configured and present in the directory.
3. **Navigate to the documentation output directory** (as specified in `Doxyfile`, `docs/doxygen/html`).
4. **Open `index.html`** in a web browser to view the generated documentation.

For any updates to the code, repeat step 2 to regenerate the documentation.

### Troubleshooting `index.html` Display Issues

If `index.html` is not displaying correctly, try starting a simple HTTP server in the `docs/doxygen/html` directory using Python:

- Navigate to the `docs/doxygen/html` directory in a terminal.
- Run the following command:
  ```bash
  python -m http.server
  ```
- Open your web browser and go to `http://localhost:8000`.

This should serve your documentation on a local web server, which can help to resolve any issues with loading local files directly in the browser.
