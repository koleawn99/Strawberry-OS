#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

#define COLOR_DARK_GRAY 8
#define COLOR_LIGHT_PINK 13

void kernel_main(void) 
{
    volatile unsigned short* video_memory = (volatile unsigned short*)0xB8000;
    unsigned short color_attribute = ((COLOR_DARK_GRAY << 4) | COLOR_LIGHT_PINK) << 8;

    // 1. Clear the screen
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        video_memory[i] = ' ' | color_attribute;
    }

    // 2. Define our welcome string as a static constant pointer
    static const char* message = "Welcome to Strawberry OS!";

    // 3. Print the string safely by pulling directly from physical memory
    int i = 0;
    while (message[i] != '\0') {
        video_memory[i] = message[i] | color_attribute;
        i++;
    }
}
