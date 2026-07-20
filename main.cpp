

#include <cstdint>
#include <stm32hal.hpp>

int main() {


    GPIO_PORT* portA = GPIO::bootstrap('A');

    
    portA->set_pin_mode(2, 0b10);
    portA->set_alternate_function(2, 7);

    
    UART uart2(usart_base::USART2);
    uart2.enable_usart_clock(USART::USART2);
    uart2.init(139);   

    
    while (true) {
        uart2.sendString("hello world how are you\r\n");

        for (volatile uint32_t i = 0; i < 1000000; i++) {
            
        };   
    }
}



