// not mine code
// it's a frankenstein
// code hasnt been tested nor deployed
#define F_CPU 16000000UL
#include <avr/io.h> 
#include <util/delay.h>
#include <avr/interrupt.h>
#include "music_notes.h"  
//#define BAUD_RATE_2304 2
int main(){
    DDRB |= (1<<DDB1) | (1<<DDB2) | (1<<DDB3);
    while (1){
        OCR0A = NOTE_G2;
        PORTB |= (1<<PORTB1);
        PORTB |= (1<<PB0);
        _delay_ms(500);
        PORTB &= ~(1<<PB0);
        PORTB |= (1<<PORTB2);
        OCR0A = NOTE_G5;
        _delay_ms(500);
        PORTB &= ~(1<<PORTB1);
        PORTB |= (1<<PB0);
        _delay_ms(500);
        PORTB &= ~(1<<PB0);
        PORTB &= ~(1<<PORTB2);
        _delay_ms(500);
    } 
}
/*void set_transmission_mode(int mode){
    switch (mode){
        case 0: // transmitter
            UCSR0B = (1<<TXEN0);
        break;
        default: // receiver
            UCSR0B = (1<<RXEN0);
    }
}
void usart_init(){
    UBRR0H = (BAUD_RATE_2304 >> 8);
    UBRR0L = BAUD_RATE_2304;
    UCSR0B = (1<<TXEN0) | (1<<RXEN0);
    UCSR0C = 0x06; // 8data 1 stop bit?
}
int main(void) 
{ 
    usart_init(); 
    sei(); 
    while(1);
} 
 
ISR(USART_RX_vect)        //przerwanie od odbioru danej 
{ 
    static char datum;        //zmienna pomocnicza 
    datum = UDR0;            //zapis odebranej danej 
    datum ^= 0xff;                //operacja bitowa XOR 
    UDR0 = datum;            //wysłanie danej zwrotnej 
}*/
