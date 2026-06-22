//Define the screen dimsensions
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

//Define color codes
#define COLOR_DARK_GRAY 8
#define COLOR_LIGHT_PINK 13 //Specifically for Strawberry OS

void kernel_main(void){
    //Ceate a pointer pointing directly to the hardware video memory address
    //'volatile' tells the compiler that the memory might change outside my code
    volatile char* video_memory = (volatile char*)0xB8000;

    //Create a color attribute byte:Pink text on a dark gray background
    //Shifted the background color left by 4 bits and combined it with foreground
    char color_attribute = (COLOR_DARK_GRAY << 4) | COLOR_LIGHT_PINK;

    //Clear the screen by filling it with blank spaces
    for(int i = 0;i < SCREEN_WIDTH * SCREEN_HEIGHT; i++){
        video_memory[i * 2] = ' '; //Set the character to space
        video_memory[i * 2] = color_attribute; //Set the color to background/foreground
    }

    //Define the Hello World string
    const char* message = "Welcome to Strawberry OS!";

    //Print the string to the top left of the screen
    int i = 0;
    while (message[i] != '\0'){
        video_memory[i * 2] = message[i]; //Write the letter ASCII code
        video_memory[i * 2] = color_attribute; //Write the color style
        i++;
    }

}
