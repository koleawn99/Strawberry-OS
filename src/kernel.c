#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

//Variables to track terminal state
int terminal_row = 0;
int terminal_column = 0;

unsigned short attribute;
volatile unsigned short* video_memory = (volatile unsigned short*)0xB8000;


//Write a single raw character onto the grid
void termianl_putchar(char c){

        attribute = ((0 << 4) | 13) << 8;

        //Handling special escape chars
    switch(c){

        //Handle the newline escape char
        case '\n':
            terminal_column = 0;
            terminal_row++;
            return;
        //Handle the tab-advance char
        case '\t':
            terminal_column += 4;
            return;
        //Handle the carriage return;
        case '\r':
            terminal_column = 0;
            return;
    }
    
    //Map out the 1D absolute index from 2D coordinates
    int index = terminal_row * SCREEN_WIDTH + terminal_column;
    video_memory[index] = c | attribute;

    //Move the cursor right
    terminal_column++;

    //Move to the next line if we hit the edge of the screen
    if (terminal_column >= SCREEN_WIDTH){

        terminal_column = 0;
        terminal_row++; 
    }
}

//Clear the screen
void terminal_initalize(void) 
{
    
                
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        video_memory[i] = ' ' | attribute;
    }

    terminal_row = 0;
    terminal_column = 0;
    
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
    terminal_write_string("carriage return is working\rIf this sentence is correct,");
    terminal_write_string("\ntestig\tthe\ttab_advance\n");
}
