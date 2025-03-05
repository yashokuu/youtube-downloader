#!/bin/bash

# Function to detect the OS
detect_os() {
    if [ "$(uname)" == "Darwin" ]; then
        OS="macOS"
    elif [ "$(uname)" == "Linux" ]; then
        if [ -f /etc/os-release ]; then
            if grep -q "Fedora" /etc/os-release; then
                OS="Fedora"
            elif grep -q "Arch" /etc/os-release; then
                OS="Arch"
            else
                OS="Linux"
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
    sudo dnf install -y gcc make git curl ffmpeg python3 python3-pip yt-dlp gtk3-devel pkg-config
}

# Function to install dependencies for Arch-based systems
install_arch() {
    echo "Installing dependencies for Arch..."
    sudo pacman -S --noconfirm gcc make git curl ffmpeg python python-pip yt-dlp gtk3 pkg-config
}

# Function to install dependencies for macOS
install_mac() {
    echo "Installing dependencies for macOS..."
    if ! command -v brew &> /dev/null; then
        echo "Homebrew is not installed. Installing Homebrew..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi
    brew install gcc make git curl ffmpeg python yt-dlp gtk+3 pkg-config
}

# Function to install dependencies for Windows (via WSL)
install_windows() {
    echo "Installing dependencies for Windows..."
    if command -v wsl &> /dev/null; then
        echo "Using WSL for Linux commands"
        sudo apt update && sudo apt install -y gcc make git curl ffmpeg python3 python3-pip yt-dlp libgtk-3-dev pkg-config
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

# Check if yt-dlp and GTK are installed successfully
if ! command -v yt-dlp &> /dev/null || ! pkg-config --exists gtk+-3.0; then
    echo "Installation failed. Please check the errors above."
    exit 1
else
    echo "All dependencies installed successfully."
fi

# Build the program
echo "Compiling the program..."
gcc youtube_downloader.c -o youtube_downloader `pkg-config --cflags --libs gtk+-3.0`

if [ $? -eq 0 ]; then
    echo "Build successful. Run './youtube_downloader' to start the application."
else
    echo "Build failed. Please check for errors."
fi
