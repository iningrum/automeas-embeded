// not mine code
// it's a frankenstein
// code hasnt been tested nor deployed
#include <avr/io.h> 
#include <avr/interrupt.h>  
//#define BAUD_RATE_2304 2
int main(){
    PORTB |= 
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
