// Boost Software License 1.0 - Julien Vernay 2021 jvernay.fr
// Source repository: https://github.com/J-Vernay/jv_screenshot
// You can reuse this library if you maintain this copyright
// notice in the source code.
// Small library to take screenshots in desktop environments.
// Currently only working with X11 (Linux).

#include "jv_screenshot.h"

#include <string.h>

#include "X11/Xlib.h"
#include "X11/Xutil.h"
#include "X11/X.h"

// X11-specific data.
typedef struct x11_data {
    Display* display;
    Window root_windows[JV_SCREENSHOT_MAXSCREENS];
} x11_data;

void jv_screenshot_init(jv_screenshot_data* data) {
    memset(data, 0, sizeof(*data));

    x11_data* x11 = (x11_data*)data->implementation_data;
    x11->display = XOpenDisplay(NULL);

    // Getting number of screens.
    data->screen_count = ScreenCount(x11->display);
    if (data->screen_count > JV_SCREENSHOT_MAXSCREENS)
        data->screen_count = JV_SCREENSHOT_MAXSCREENS;

    // Getting screens and their width and height.
    XWindowAttributes attributes;
    for (int i = 0; i < data->screen_count; ++i) {
        Window window = XRootWindow(x11->display, i);
        XGetWindowAttributes(x11->display, window, &attributes);
        x11->root_windows[i] = window;
        data->width[i] = attributes.width;
        data->height[i] = attributes.height;
    }
}

void jv_screenshot_take_rgb(jv_screenshot_data* data, int screen_id, char* rgb_buffer, int buffer_size) {
    x11_data* x11 = (x11_data*)data->implementation_data;

    if (screen_id < 0 || screen_id >= data->screen_count)
        return; // Error, the screen_id is invalid.
    if (!rgb_buffer)
        return; // NULL buffer passed.
    
    int width = data->width[screen_id], height = data->height[screen_id];

    if (buffer_size < 3 * width * height)
        return; // The buffer has not enough space.

    XImage* image = XGetImage(x11->display, x11->root_windows[screen_id], 0, 0, width, height, AllPlanes, ZPixmap);
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned long color = XGetPixel(image, x, y); // as 0x00RRGGBB
            *(rgb_buffer++) = (color >> 16) & 0xFF; // red channel
            *(rgb_buffer++) = (color >> 8) & 0xFF; // green channel
            *(rgb_buffer++) = color & 0xFF; // blue channel
        }
    }
}

void jv_screenshot_quit(jv_screenshot_data* data) {
    x11_data* x11 = (x11_data*)data->implementation_data;
    XCloseDisplay(x11->display);
    memset(data, 0, sizeof(*data));
}