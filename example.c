#include "jv_screenshot.h"

#include <stdlib.h>
#include <stdio.h>

int main() {
    // We take a screenshot of the screen and save it in 'screenshot.ppm'.
    
    jv_screenshot_data screenshot_data;
    jv_screenshot_init(&screenshot_data);

    if (screenshot_data.screen_count == 0) {
        puts("Error, we have not detected any screen. Error with Xlib?");
        return EXIT_FAILURE;
    }
    
    int screen_id = 0;
    int width = screenshot_data.width[screen_id];
    int height = screenshot_data.height[screen_id];

    // Allocate enough space for RGB buffer (3 bytes per pixel).
    char* rgb_buffer = (char*)malloc(width * height * 3);
    jv_screenshot_take_rgb(&screenshot_data, screen_id, rgb_buffer, width*height*3);

    // We have taken the screenshot, close connection.
    jv_screenshot_quit(&screenshot_data);

    // Save it to PPM format (simplest image format widely supported).
    FILE* out = fopen("screenshot.ppm", "wb"); // 'w'rite in 'b'inary mode
    if (!out) {
        puts("Error, could not create file 'screenshot.ppm'... Permission?");
        return EXIT_FAILURE;
    }

    // 'P6' for binary PPM , then dimensions, then '255' the max value of a channel.
    fprintf(out, "P6\n%d %d\n255\n", width, height);
    fwrite(rgb_buffer, 1, width*height*3, out);
    fclose(out);

    free(rgb_buffer);

    return EXIT_SUCCESS;
}