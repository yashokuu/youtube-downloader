# Easy Local Youtube Video Downloader

## Overview
**Easy Local Youtube Video Downloader** is a simple C-based YouTube video downloader that leverages `yt-dlp` to fetch videos locally. This project is designed to work across multiple platforms, including Linux, macOS, and Windows. The setup process includes an automated installation script for dependencies.

---

## Features
- Minimal and lightweight.
- Cross-platform compatibility.
- Automated dependency installation.
- Supports downloading YouTube videos via `yt-dlp`.

---

## Prerequisites
Ensure that you have the following installed on your system:

- **GCC or Clang compiler** (for building the C program)
- **`yt-dlp`** (automatically installed if missing)
- **Bash Shell** (for running `install.sh`)

---

## Installation

### 1. Clone the Repository
```bash
git clone https://github.com/yourusername/easy-local-yt-downloader.git
cd easy-local-yt-downloader
```

### 2. Build the Program

#### Linux / macOS
```bash
gcc -o yt_downloader youtube_downloader.c
```

#### Windows (Using MinGW)
```bash
gcc -o yt_downloader.exe youtube_downloader.c
```

### 3. Install Dependencies
Run the following command to execute the dependency installation script:
```bash
sudo ./install.sh
```

---

## Usage

### Command-Line Usage
To download a YouTube video, use the following command:

```bash
./yt_downloader <YouTube Video URL>
```

#### Example:
```bash
./yt_downloader https://www.youtube.com/watch?v=8OuJUFMiMfE
```

---

## Troubleshooting
- **`yt-dlp: command not found`**: Ensure `yt-dlp` is installed by rerunning `install.sh` or manually installing it.
- **Unsupported OS**: Currently, the `install.sh` script supports Linux and macOS. For Windows, ensure you manually install the required tools.

---