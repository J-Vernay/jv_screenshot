// Boost Software License 1.0 - Julien Vernay 2021 jvernay.fr
// Source repository: https://github.com/J-Vernay/jv_screenshot
// You can reuse this library if you maintain this copyright
// notice in the source code.
// Small library to take screenshots in desktop environments.
// Currently only working with X11 (Linux).

#ifndef JV_SCREENSHOT_H
#define JV_SCREENSHOT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef JV_SCREENSHOT_MAXSCREENS
#define JV_SCREENSHOT_MAXSCREENS 4
#endif

typedef struct jv_screenshot_data {
    int screen_count; // Number of screens.
    int width[JV_SCREENSHOT_MAXSCREENS]; // Width of the i-th screen.
    int height[JV_SCREENSHOT_MAXSCREENS]; // Height of the i-th screen.
    
    void* implementation_data[4*JV_SCREENSHOT_MAXSCREENS]; // Implementation-specific data.
} jv_screenshot_data;

// Initializes screenshot environment, 'data' is an output argument
// which is used by 'jv_screenshot_take()' and must be passed back
// to 'jv_screenshot_quit()' after usage.
void jv_screenshot_init(jv_screenshot_data* data);

// Take a screenshot of a screen in RGB format. '0 <= screen_id < data->screen_count'.
// To access individual pixel colors, do rgb_buffer[(y * width + x) * 3 + c]
// with 'c' being 0 for red, 1 for green and 2 for blue.
// Exactly (width * height * 3) bytes are written into 'rgb_buffer'.
// If the 'buffer_size' is not sufficient, no bytes are written.
void jv_screenshot_take_rgb(jv_screenshot_data* data, int screen_id, char* rgb_buffer, int buffer_size);

// Close connections to operating system and reset 'data'.
void jv_screenshot_quit(jv_screenshot_data* data);

#ifdef __cplusplus
} // extern "C"
#endif

#endif