#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define VGA_ADRESS 0xB8000

// Prototypes: Telling the compiler these functions exist somewhere down below
void scroll_up(void);
void terminal_putchar(char c);

//Variables to track terminal state
int terminal_row = 0;
int terminal_column = 0;

int is_scrolling = 0; //The flag for the scroll

unsigned short  attribute = ((0 << 4) | 13) << 8;
volatile unsigned short* video_memory = (volatile unsigned short*)VGA_ADRESS;

//Introducing the moving up the rows<D-`>
void scroll_up(){
   for(int row = 1; row < SCREEN_HEIGHT; row++){    //rows counter(1 to 24)
       for(int col = 0; col < SCREEN_WIDTH; col++){    //columns counter(1 to 79)
            //Copying the rows and pasting them to the row above
           video_memory[(row - 1) * SCREEN_WIDTH + col] = video_memory[row * SCREEN_WIDTH + col];  
       }
   }

   // Move the cursor variables to the start of the bottom row (Row 24)
   terminal_row = SCREEN_HEIGHT - 1; 
   terminal_column = 0;

   is_scrolling = 1; //flag on

    //Clearning up the last row
    for(int i = 0; i < SCREEN_WIDTH; i++){
        terminal_putchar(' ');
       
   }
    is_scrolling = 0; //flag off

}


//Write a single raw character onto the grid
void terminal_putchar(char c){

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
   
    //Implementig the scrolling mechanic(if we get past row 24)
    if(terminal_row >= SCREEN_HEIGHT && is_scrolling == 0){     
        scroll_up();  
        terminal_row = SCREEN_HEIGHT - 1;  //pulling the cursor back to the cleared up line
          }
}

//Loop throgh an entire string array until the null terminator
void terminal_write_string(const char* data){
    int i = 0;
    while(data[i] != '\0'){
        terminal_putchar(data[i]);
        i++;
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



void kernel_main(void){
    //Initialize the clean canvas
    terminal_initalize();

    //Testing the new scrolling feat
    terminal_write_string("Line 00: Initializing Strawberry OS...\n");
    terminal_write_string("Line 01: Booting system components\n");
    terminal_write_string("Line 02: Loading memory maps\n");
    terminal_write_string("Line 03: Setting up the GDT\n");
    terminal_write_string("Line 04: Setting up the IDT\n");
    terminal_write_string("Line 05: Checking video memory buffers\n");
    terminal_write_string("Line 06: Strawberry text mode initialized successfully\n");
    terminal_write_string("Line 07: Testing terminal boundaries\n");
    terminal_write_string("Line 08: Visual check on row tracking\n");
    terminal_write_string("Line 09: Hello from the kernel!\n");
    terminal_write_string("Line 10: Padding out the screen lines\n");
    terminal_write_string("Line 11: Almost halfway there\n");
    terminal_write_string("Line 12: Halfway point reached!\n");
    terminal_write_string("Line 13: Moving past the center line\n");
    terminal_write_string("Line 14: Verifying nested loop variables\n");
    terminal_write_string("Line 15: Checking memory shifting mechanisms\n");
    terminal_write_string("Line 16: Keep an eye on the top row\n");
    terminal_write_string("Line 17: Preparing to cross the threshold\n");
    terminal_write_string("Line 18: Getting close to the bottom\n");
    terminal_write_string("Line 19: Approaching terminal boundary limits\n");
    terminal_write_string("Line 20: Five lines left until overflow\n");
    terminal_write_string("Line 21: Four lines left until overflow\n");
    terminal_write_string("Line 22: Three lines left until overflow\n");
    terminal_write_string("Line 23: This line should sit perfectly on the second-to-last row\n");
    terminal_write_string("Line 24: This line should sit perfectly on the very bottom row\n");

    // --- THE TEST TRIGGERS HERE ---
    terminal_write_string("Line 25: SCROLL TRIGGER 1! Line 00 should vanish from the top!\n");
    terminal_write_string("Line 26: SCROLL TRIGGER 2! Line 01 should vanish, and this sits at the bottom!\n");
    terminal_write_string("Line 27: Last check\n");
}
