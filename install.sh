#!/bin/bash

# Function to detect the OS
detect_os() {
    if [ "$(uname)" == "Darwin" ]; then
        OS="macOS"
    elif [ "$(uname)" == "Linux" ]; then
        if [ -f /etc/os-release ]; then
            # Check if it's Fedora-based or Arch-based
            if grep -q "Fedora" /etc/os-release; then
                OS="Fedora"
            elif grep -q "Arch" /etc/os-release; then
                OS="Arch"
            else
                OS="Linux"  # Generic Linux
            fi
        else
            OS="Linux"
        fi
    elif [ "$(uname -o)" == "Msys" ]; then
        OS="Windows"
    else
        OS="Unknown"
    fi
}

# Detect the OS
detect_os

# Function to install dependencies for Fedora
install_fedora() {
    echo "Installing dependencies for Fedora..."
    sudo dnf install -y gcc make git curl ffmpeg python3 python3-pip
    pip3 install --user yt-dlp
}

# Function to install dependencies for Arch-based systems
install_arch() {
    echo "Installing dependencies for Arch..."
    sudo pacman -S --noconfirm gcc make git curl ffmpeg python python-pip
    pip install --user yt-dlp
}

# Function to install dependencies for macOS
install_mac() {
    echo "Installing dependencies for macOS..."
    # Check if Homebrew is installed
    if ! command -v brew &> /dev/null; then
        echo "Homebrew is not installed. Installing Homebrew..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi
    brew install gcc make git curl ffmpeg python yt-dlp
}

# Function to install dependencies for Windows (via WSL or Git Bash)
install_windows() {
    echo "Installing dependencies for Windows..."
    # Check if WSL (Windows Subsystem for Linux) or Git Bash is used
    if command -v wsl &> /dev/null; then
        echo "Using WSL for Linux commands"
        sudo apt update && sudo apt install -y gcc make git curl ffmpeg python3 python3-pip
        pip3 install --user yt-dlp
    else
        echo "Windows installation is not fully automated. Please install dependencies manually."
        exit 1
    fi
}

# Perform installation based on OS
case $OS in
    "Fedora")
        install_fedora
        ;;
    "Arch")
        install_arch
        ;;
    "macOS")
        install_mac
        ;;
    "Windows")
        install_windows
        ;;
    *)
        echo "Unsupported OS: $OS. Please install dependencies manually."
        exit 1
        ;;
esac

# Check if yt-dlp is installed successfully
if ! command -v yt-dlp &> /dev/null
then
    echo "yt-dlp could not be installed. Please check the error above."
    exit 1
else
    echo "yt-dlp installed successfully."
fi

# Inform the user about how to run the program
echo "Installation completed. You can now build and run the program."
