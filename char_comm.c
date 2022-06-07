#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL
#define DELAY _delay_us(1000)
#define MS1 PB5
#define MS2 PB4
#define MS3 PB3
#define DIR PB2
#define STEP PB1
#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct{
    char cmd;
    int val;
} Command;
Command BUFFER[200];
int BUFFER_size = 0;
void get_struct(char* begin, char* end){
    Command T;
    T.cmd = *end;
    { // get number
        char* string = (char*)malloc(sizeof(char)*(end-begin));
        int i = 0;
        while(begin<end){
            string[i] = *begin;
            i++;
            begin++;
        }
        T.val = atoi(string);
        free(string);
    }
    BUFFER[BUFFER_size] = T;
    BUFFER_size += (BUFFER_size<200)? 1 : 0;
    //printf("Bsize %i\n", BUFFER_size);
}
int isnum(char* c){
    return (*c=='0' || *c=='1' || *c=='2' || *c=='3' || *c=='4' || *c=='5' || *c=='6' || *c=='7' || *c=='8' || *c=='9')? 1 : 0;
}
void parse_commands(char* cmd){
    char* next = cmd;
    char* end = cmd + strlen(cmd);
    while(cmd<end){
        while (next<end && isnum(next)){next++;} // skip all numbers
        get_struct(cmd, next);
        next++;
        cmd = next;
    }
}
void pin(int id, int state){
    if(state){
        DELAY;
        PORTB |= (1<<id);
    }
    else{
        DELAY;
        PORTB &= ~(1<<id);
    }
}
int pulse_pin(int id){
    DELAY;
    PORTB ^= (1<<id);
    DELAY;
    PORTB ^= (1<<id);
}
void exec_commands(char* cmd){
    parse_commands(cmd);
    for(int i =0; i< BUFFER_size; i++){
        if(BUFFER[i].val==0){BUFFER[i].val=1;}
        switch(BUFFER[i].cmd){
            case 's':
                for(int i=0; i < 5; i++){
                    pulse_pin(STEP);
                }
            break;
            case 'r':
                pin(DIR, 1);
            break;
            case 'l':
                pin(DIR, 0);
            break;
            case 'w':
                _delay_ms(BUFFER[i].val);
            break;
        }
    }
    BUFFER_size = 0;
}