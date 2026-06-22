#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

#define COLOR_DARK_GRAY 8
#define COLOR_LIGHT_PINK 13

//Variables to track terminal state
int terminal_row = 0;
int terminal_column = 0;
volatile unsigned short* video_memory = (volatile unsigned short*)0xB8000;
unsigned short color_atribute;

//Clear the screen
void terminal_initalize(void) 
{
    unsigned short color_attribute = ((COLOR_DARK_GRAY << 4) | COLOR_LIGHT_PINK) << 8;
 
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        video_memory[i] = ' ' | color_attribute;
    }

    terminal_row = 0;
    terminal_column = 0;
    
}

//Write a single raw character onto the grid
void termianl_putchar(char c){

    //Handle the newline escape character
    if (c == '\n'){
        terminal_column = 0;
        terminal_row++;
        return;
    }
    
    //Map out the 1D absolute index from 2D coordinates
    int index = terminal_row * SCREEN_WIDTH + terminal_column;
    video_memory[index] = c | color_atribute;

    //Move the cursor right
    terminal_column++;

    //Move to the next line if we hit the edge of the screen
    if (terminal_column >= SCREEN_WIDTH){

        terminal_column = 0;
        terminal_row++; 
    }
}

//Loop throgh an entire string array until the null terminator
void terminal_write_string(const char* data){
    int i = 0;
    while(data[i] != '\0'){
        termianl_putchar(data[i]);
        i++;
    }
}

void kernel_main(void){
    //Initialize the clean canvas
    terminal_initalize();

    //Using the new print function
    terminal_write_string("Welcome to Strawberry OS!\n");
    terminal_write_string("-------------------------\n");
    terminal_write_string("The core print engine is alive.\n");
    terminal_write_string("Successfully tracking cursor and procesing new lines!\n");
}
