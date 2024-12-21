#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check if the user has passed an argument (YouTube URL)
    if (argc != 2) {
        printf("No YouTube URL provided. Attempting to install dependencies...\n");

        // Run the installation script to install dependencies
        printf("Running installation script...\n");
        int result = system("./install.sh");

        if (result != 0) {
            printf("Installation failed. Please check the error above.\n");
            return 1;
        }

        printf("Installation completed. Please run the program again with a YouTube URL.\n");
        return 0;
    }

    // If the YouTube URL is provided, proceed to download the video using yt-dlp
    printf("Downloading video from: %s\n", argv[1]);

    // Build the yt-dlp command to download the video
    char command[512];
    snprintf(command, sizeof(command), "yt-dlp %s", argv[1]);

    // Run the command to download the video
    int result = system(command);

    if (result == 0) {
        printf("Download successful!\n");
    } else {
        printf("Download failed.\n");
    }

    return 0;
}
