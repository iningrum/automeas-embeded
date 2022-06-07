#define BAUD 9600
#include "char_comm.c"
#include <util/setbaud.h>
char usart_getchar(void) {
// Wait for incoming data
while ( !(UCSR0A & (_BV(RXC0))) );
// Return the data
return UDR0;
}
int loop = 1;
char RECEIVED_DATA[200];
int RDATA_size = 0;
void set_transmission_mode(int mode){
    switch (mode){
        case 0: // transmitter
            UCSR0B = (1<<TXEN0);
        break;
        default: // receiver
            UCSR0B = (1<<RXEN0);
    }
}
void usart_init(){

    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    UCSR0B = (1<<TXEN0) | (1<<RXEN0);
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); // 8data 1 stop bit?
}
int main(void) 
{
    pin(DIR,0);
    pin(STEP,0);
    pin(MS1,0);
    pin(MS2,0);
    pin(MS3,1); 
    usart_init(); 
    sei();
    /*for(int i =0; i<150;i++){
        RECEIVED_DATA[i] = 's';
        RDATA_size++;
    }
    char* values = (char*) malloc(sizeof(char)*RDATA_size);
        for(int i=0; i<RDATA_size; i++){
            values[i] = RECEIVED_DATA[i];
        }
		RDATA_size = 0;
        exec_commands(values);

    while(1);*/
    while(1){
        char c = usart_getchar();
        if (c){
            for(int i=0; i<200;i++){
                pulse_pin(STEP);
            }
        }
        if(c=='\r'){
            break;
        }
        RECEIVED_DATA[RDATA_size] = c;
        RDATA_size++;
    }
    char* values = (char*) malloc(sizeof(char)*RDATA_size);
        for(int i=0; i<RDATA_size; i++){
            values[i] = RECEIVED_DATA[i];
        }
		RDATA_size = 0;
        exec_commands(values);
} 
 
ISR(USART_RX_vect)
{
	/*RECEIVED_DATA[RDATA_size]=UDR0;
	RDATA_size++;
    if(RECEIVED_DATA[RDATA_size]=='\r')
	{
		char* values = (char*) malloc(sizeof(char)*RDATA_size);
        for(int i=0; i<RDATA_size; i++){
            values[i] = RECEIVED_DATA[i];
        }
		RDATA_size = 0;
        exec_commands(values);
	}*/
}