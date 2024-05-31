// hello_world1.c

typedef short int16_t;
typedef unsigned char uint8_t;

#define STDOUT_ADDRESS ((volatile uint8_t*)(0x7110))
#define STDOUT (*(STDOUT_ADDRESS))
#define STOP_ADDRESS ((volatile uint8_t*)(0x7200))
#define STOP *(STOP_ADDRESS) = 0

int main(void) {
    STDOUT = 'H';
    STDOUT = 'e';
    STDOUT = 'l';
    STDOUT = 'l';
    STDOUT = 'o';
    STDOUT = ',';
    STDOUT = ' ';
    STDOUT = 'W';
    STDOUT = 'o';
    STDOUT = 'r';
    STDOUT = 'l';
    STDOUT = 'd';
    STDOUT = '!';
    STDOUT = '\n';
    STOP;
}

void loop(void) { }