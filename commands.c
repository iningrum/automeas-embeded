#include <avr/io.h> 
#include <avr/interrupt.h>  
/*
    Defines format of communication PC->AVR
*/
enum key{
    START,
    SET_RESOLUTION,
    DIRECTION,
    MOVE,
    END,
    PROCEED, // start execution
    WAIT, // for N miliseconds
    HALT
};
typedef struct{
    int val : 8;
    int type : 4;
} Command;
void exec_command(Command* cmd){
    switch(cmd->type){
        case START:
        // AVR -> [READY_TO_RECEVE_DATA]
        // {allocating required space}
        break;
        case SET_RESOLUTION:
        // set combination of three inputs
        break;
        case DIRECTION:
        // set some pin high or low
        break;
        case MOVE:
        // manage movement
        break;
        case END:
        // end transmission
        // AVR -> [DATA_RECEIVED] -> PC
        // AVR <- [PROCEED] <- PC
        // AVR -> [TASK_COMPLETE] -> PC
        break;
        case PROCEED:
        // start execution of cached commands
        break;
        case WAIT:
        // wait for N ms
        break;
        case HALT:
        // interrupt execution
        // any USART transmission halts current task
        break;
        default:
        break;
    }
}