
#include<cstdint>
#include<new>
#include<memalloc.hpp>

namespace port_add { //port addresses
    constexpr uint32_t RCC_AHB2ENR = 0x4002104C; //port clock

    constexpr uint32_t GPIOA       = 0x48000000;
    constexpr uint32_t GPIOB       = 0x48000400;
    constexpr uint32_t GPIOC       = 0x48000800;
    constexpr uint32_t GPIOD       = 0x48000C00;
    constexpr uint32_t GPIOF       = 0x48001400;

    constexpr uint32_t RCC_APB1ENR1 = 0x40021044; // Clock bus register for Timer 2
    constexpr uint32_t TIM2          = 0x40000000; // Physical base address of Timer 2
}

namespace pin_reg_add { //pin register address offsets
    constexpr uint32_t MODER = 0x00;   // Offset 0x00
    constexpr uint32_t OTYPER = 0x04;  // Offset 0x04
    constexpr uint32_t OSPEEDR = 0x08; // Offset 0x08
    constexpr uint32_t PUPDR = 0x0C;   // Offset 0x0C
    constexpr uint32_t IDR = 0x10;     // Offset 0x10
    constexpr uint32_t ODR = 0x14;     // Offset 0x14
    constexpr uint32_t BSRR = 0x18;    // Offset 0x18

    constexpr uint32_t AFRL  = 0x20; // Offset 0x20 controls Pins 0 to 7
    constexpr uint32_t AFRH  = 0x24; // Offset 0x24 controls Pins 8 to 15
}
namespace TIM2_regs {
    inline volatile uint32_t& CR1   = *reinterpret_cast<volatile uint32_t*>(0x40000000 + 0x00);
    inline volatile uint32_t& EGR   = *reinterpret_cast<volatile uint32_t*>(0x40000000 + 0x14);
    inline volatile uint32_t& CCMR1 = *reinterpret_cast<volatile uint32_t*>(0x40000000 + 0x18);
    inline volatile uint32_t& CCMR2 = *reinterpret_cast<volatile uint32_t*>(0x40000000 + 0x1C);
    inline volatile uint32_t& CCER  = *reinterpret_cast<volatile uint32_t*>(0x40000000 + 0x20);
    inline volatile uint32_t& PSC   = *reinterpret_cast<volatile uint32_t*>(0x40000000 + 0x28);
    inline volatile uint32_t& ARR   = *reinterpret_cast<volatile uint32_t*>(0x40000000 + 0x2C);
    inline volatile uint32_t& CCR1  = *reinterpret_cast<volatile uint32_t*>(0x40000000 + 0x34);
    inline volatile uint32_t& CCR2  = *reinterpret_cast<volatile uint32_t*>(0x40000000 + 0x38);
    inline volatile uint32_t& CCR3  = *reinterpret_cast<volatile uint32_t*>(0x40000000 + 0x3C);
    inline volatile uint32_t& CCR4  = *reinterpret_cast<volatile uint32_t*>(0x40000000 + 0x40);
    inline volatile uint32_t& BDTR  = *reinterpret_cast<volatile uint32_t*>(0x40000000 + 0x44);
}


namespace RCC_regs {
    inline volatile uint32_t& CR        = *reinterpret_cast<volatile uint32_t*>(0x40021000 + 0x00);
    inline volatile uint32_t& CFGR      = *reinterpret_cast<volatile uint32_t*>(0x40021000 + 0x08);
    inline volatile uint32_t& AHB1ENR   = *reinterpret_cast<volatile uint32_t*>(0x40021000 + 0x48);
    inline volatile uint32_t& AHB2ENR   = *reinterpret_cast<volatile uint32_t*>(0x40021000 + 0x4C);
    inline volatile uint32_t& AHB3ENR   = *reinterpret_cast<volatile uint32_t*>(0x40021000 + 0x50);
    inline volatile uint32_t& APB1ENR1  = *reinterpret_cast<volatile uint32_t*>(0x40021000 + 0x58);
    inline volatile uint32_t& APB1ENR2  = *reinterpret_cast<volatile uint32_t*>(0x40021000 + 0x5C);
    inline volatile uint32_t& APB2ENR   = *reinterpret_cast<volatile uint32_t*>(0x40021000 + 0x60);
}

enum class status : int32_t { 
    default_error = -1,
    unresolved = 0,
    default_success = 1,
    unchanged = 2,
    true_ = 3,
    false_ = 4,
};

class GPIO_PORT;

class GPIO {

public:

    GPIO(const GPIO&) = delete;
    GPIO& operator=(const GPIO&) = delete;

    GPIO() = default;

    static GPIO_PORT* bootstrap(char port) {

        GPIO::init_port_ins(port); //create port instance 

        GPIO::initialize_port(port); // initialize physical port

        int32_t n = 0;

        switch(port) {
            case 'A':
                n = 0;
                break;
            case 'B':
                n = 1;
                break;
            case 'C':
                n = 2;
                break;
            case 'D':
                n = 3;
                break;
            case 'F':
                n = 4;
                break;
            default:
                n = -1;
                break;
        };
        
        if (n == -1) {
            return nullptr;
        }

        return GPIO::return_ins_add(n);

    }   

    static void init_port_ins(char x) {
        create_port(x);
    }

    static GPIO_PORT* return_ins_add(uint32_t x) {
        return port_ptr[x];
    }

    static status initialize_port(char port) {

        switch(port) {
            case 'A': {
                volatile uint32_t* rcc_ahb2enr = reinterpret_cast<volatile uint32_t*>(port_add::RCC_AHB2ENR);
                if ((*rcc_ahb2enr | (1<<0)) == 1) {
                    return status::unchanged;
                }
                *rcc_ahb2enr |= 1 << 0; 
                return status::default_success;
            }

            case 'B': {
                volatile uint32_t* rcc_ahb2enr = reinterpret_cast<volatile uint32_t*>(port_add::RCC_AHB2ENR);
                if ((*rcc_ahb2enr | (1<<1)) == 1) {
                    return status::unchanged;
                }
                *rcc_ahb2enr |= 1 << 1; 
                return status::default_success;
            }

            case 'C': {
                volatile uint32_t* rcc_ahb2enr = reinterpret_cast<volatile uint32_t*>(port_add::RCC_AHB2ENR);
                if ((*rcc_ahb2enr | (1<<2)) == 1) {
                    return status::unchanged;
                }
                *rcc_ahb2enr |= 1 << 2; 
                return status::default_success;
            }

            case 'D': {
                volatile uint32_t* rcc_ahb2enr = reinterpret_cast<volatile uint32_t*>(port_add::RCC_AHB2ENR);
                if ((*rcc_ahb2enr | (1<<3)) == 1) {
                    return status::unchanged;
                }
                *rcc_ahb2enr |= 1 << 3; 
                return status::default_success;
            }

            case 'F': {
                volatile uint32_t* rcc_ahb2enr = reinterpret_cast<volatile uint32_t*>(port_add::RCC_AHB2ENR);
                if ((*rcc_ahb2enr | (1<<4)) == 1) {
                    return status::unchanged;
                }
                *rcc_ahb2enr |= 1 << 4; 
                return status::default_success;
            }   
            default: 
                return status::default_error;
                
        }

        return status::unresolved;

    }

    static status deinitialize_port(char port) {        
        
        switch(port) {
            case 'A': {
                volatile uint32_t* rcc_ahb2enr = reinterpret_cast<volatile uint32_t*>(port_add::RCC_AHB2ENR);
                if ((*rcc_ahb2enr | (0<<0)) == 0) {
                    return status::unchanged;
                }
                *rcc_ahb2enr &= 0 << 0;
                return status::default_success; 
            }

            case 'B': {
                volatile uint32_t* rcc_ahb2enr = reinterpret_cast<volatile uint32_t*>(port_add::RCC_AHB2ENR);
                if ((*rcc_ahb2enr | (0<<1)) == 0) {
                    return status::unchanged;
                }
                *rcc_ahb2enr &= 0 << 1; 
                return status::default_success;
            }

            case 'C': {
                volatile uint32_t* rcc_ahb2enr = reinterpret_cast<volatile uint32_t*>(port_add::RCC_AHB2ENR);
                if ((*rcc_ahb2enr | (0<<2)) == 0) {
                    return status::unchanged;
                }
                *rcc_ahb2enr &= 0 << 2; 
                return status::default_success; 
            }

            case 'D': {
                volatile uint32_t* rcc_ahb2enr = reinterpret_cast<volatile uint32_t*>(port_add::RCC_AHB2ENR);
                if ((*rcc_ahb2enr | (0<<3)) == 0) {
                    return status::unchanged;
                }
                *rcc_ahb2enr &= 0 << 3; 
                return status::default_success;
            }

            case 'F': {
                volatile uint32_t* rcc_ahb2enr = reinterpret_cast<volatile uint32_t*>(port_add::RCC_AHB2ENR);
                if ((*rcc_ahb2enr | (0<<4)) == 0) {
                    return status::unchanged;
                }
                *rcc_ahb2enr &= 0 << 4; 
                return status::default_success;
            }

            default: 
                return status::default_error;
                
        }

        return status::unresolved;

    }

    static status is_initialized(char port) {
        
        uint32_t n(0);

        switch(port) {
            case 0:
                n = 0;
                break;
            case 1:
                n = 1;
                break;
            case 2:
                n = 2;
                break;
            case 3:
                n = 3;
                break;
            case 4:
                n = 4;
                break;
            default:
                return status::default_error;
        };
    
        if ((*(uint32_t*)port_add::RCC_AHB2ENR & (1 << n))) {
            return status::true_;
        }
        else {
            return status::false_;
        }

        return status::unresolved;
    }

private:

    constexpr static inline char pins[5] = {'A', 'B', 'C', 'D', 'F'};

    static inline bool count = 0;

    static inline GPIO_PORT* port_ptr[5] = {};

protected:
    friend class GPIO_PORT;

    static GPIO_PORT* create_port(char port);

};

class GPIO_PORT {
    
    friend GPIO_PORT* GPIO::create_port(char port);

public:    

    
    void setPinMode(uint8_t pinNumber, uint8_t mode) {// 0 (input), 1 (output), 2 (alternate function), 3 (analog)
        volatile uint32_t* moder = reinterpret_cast<volatile uint32_t*>(port_base + pin_reg_add::MODER);
        uint8_t shift = pinNumber * 2;
    
        *moder &= ~(0x3 << shift); // clear old 2 bits
        *moder |=  (mode << shift); // set new 2 bits
    }

   // Push-Pull (0) or Open-Drain (1).
    void setPinOutputType(uint8_t pinNumber, uint8_t type) {
        volatile uint32_t* otyper = reinterpret_cast<volatile uint32_t*>(port_base + pin_reg_add::OTYPER);
    
        *otyper &= ~(0x1 << pinNumber); // Clear old 1 bit
        *otyper |=  (type << pinNumber); // Set new 1 bit
    }

    // speed: Low (0), Medium (1), High (2), or Very High (3).
    void setPinSpeed(uint8_t pinNumber, uint8_t speed) {
        volatile uint32_t* ospeedr = reinterpret_cast<volatile uint32_t*>(port_base + pin_reg_add::OSPEEDR);
        uint8_t shift = pinNumber * 2;
    
        *ospeedr &= ~(0x3 << shift); // clear old 2 bits
        *ospeedr |=  (speed << shift); // set new 2 bits
    }

    // Floating (0), Pull-Up (1), or Pull-Down (2).
    void setPinPull(uint8_t pinNumber, uint8_t pull) {
        volatile uint32_t* pupdr = reinterpret_cast<volatile uint32_t*>(port_base + pin_reg_add::PUPDR);
        uint8_t shift = pinNumber * 2;
    
        *pupdr &= ~(0x3 << shift); // clear old 2 bits
        *pupdr |=  (pull << shift); // set new 2 bits
    }

    
    void writePin(uint8_t pinNumber, bool state) {
        volatile uint32_t* bsrr = reinterpret_cast<volatile uint32_t*>(port_base + pin_reg_add::BSRR);
    
        if (state) {
            *bsrr = (1 << pinNumber);        // write to lower 16 bits forces pin HIGH
        } else {
            *bsrr = (1 << (pinNumber + 16)); // write upper 16 bits forces pin LOW
        }
    }
    // Reads the instant voltage level on the external wire, returning true for 3.3V and false for Ground.
    bool readPin(uint32_t portBase, uint8_t pinNumber) {
        volatile uint32_t* idr = reinterpret_cast<volatile uint32_t*>(portBase + pin_reg_add::IDR);
    
       
        return (*idr & (1 << pinNumber)) != 0;
    }

    void set_port_base(uint32_t n) {
        port_base = n;
    }

    void setPinAlternateFunction(uint8_t pinNumber, uint8_t alternateFunctionCode) {
        volatile uint32_t* afr_register;
        uint8_t shift;

        if (pinNumber < 8) {
            afr_register = reinterpret_cast<volatile uint32_t*>(port_base + 0x20);
            shift = pinNumber * 4;        // map 0-7
        } else {
            afr_register = reinterpret_cast<volatile uint32_t*>(port_base + 0x24);
            shift = (pinNumber - 8) * 4;  //normalize back to 0-7
        }

    // clear existing 4-bit configuration for this pin
        *afr_register &= ~(0xF << shift); // 0xF = 1111
    
    // inject the new 4-bit alternate function routing code
        *afr_register |= (alternateFunctionCode << shift);
    }

private:

    uint32_t port_base;

    GPIO_PORT(uint32_t* p, char pr ) : ptr_data(p), port(pr) {

    }

    uint32_t* ptr_data = nullptr;

    char port = 0;

};


GPIO_PORT* GPIO::create_port(char port) {

    int32_t n = 0;

    switch(port) {
        case 'A':
            n = 0;
            break;
        case 'B':
            n = 1;
            break;
        case 'C':
            n = 2;
            break;
        case 'D':
            n = 3;
            break;
        case 'F':
            n = 4;
            break;
        default:
            n = -1;
            break;
    };

    if (n == -1) {
        return nullptr;
    }

    uint32_t* data_ptr = memalloc::alloc(sizeof(GPIO_PORT)); 

    GPIO_PORT* ptr = new ((uint32_t*)(*data_ptr)) GPIO_PORT(data_ptr, n); 

    port_ptr[n] = ptr;

    return ptr;
}

class PWM {
private:
    uint32_t psc_value;
    uint32_t arr_value;
    uint8_t channel;
    uint32_t duty_value;

public:
    PWM(uint32_t p_v, uint32_t a_v, uint8_t ch, uint32_t d_v) : psc_value(p_v), arr_value(a_v), channel(ch), duty_value(d_v) { 

        RCC_regs::APB1ENR1 |= (1 << 0);

        [[maybe_unused]] volatile uint32_t dummy = RCC_regs::APB1ENR1;

        TIM2_regs::PSC = psc_value; // prescaler

        TIM2_regs::ARR = arr_value; //period

        volatile uint32_t* ccr;
        if (channel == 1) {
            ccr = &TIM2_regs::CCR1;
        }
        else if (channel == 2) {
            ccr = &TIM2_regs::CCR2;
        }
        else if (channel == 3) {
            ccr = &TIM2_regs::CCR3;
        }
        else {
            ccr = &TIM2_regs::CCR4;
        }

        *ccr = duty_value; //write duty cycle


        volatile uint32_t* ccmr;
        uint8_t shift;
        if (channel == 1) { 
            ccmr = &TIM2_regs::CCMR1; shift = 4; 
        }
        else if (channel == 2) { 
            ccmr = &TIM2_regs::CCMR1; shift = 12; 
        }
        else if (channel == 3) { 
            ccmr = &TIM2_regs::CCMR2; shift = 4; 
        }
        else { 
            ccmr = &TIM2_regs::CCMR2; shift = 12; 
        }

        *ccmr &= ~(0x7 << shift);
        *ccmr |= (0x6 << shift); 

        uint8_t ccer_bit = (channel - 1) * 4;
 
        TIM2_regs::CCER |= (1 << ccer_bit);

        TIM2_regs::EGR = (1 << 0);

        TIM2_regs::CR1 |= (1 << 0); //start the counter
        

    }
};

int main() {
   
    GPIO_PORT* ins = GPIO::bootstrap('B');
    ins->set_port_base(port_add::GPIOB);

    ins->setPinMode(3, 2);              
    ins->setPinAlternateFunction(3, 1); 

    PWM pwm1(15, 999, 2, 1000); 

    while (1) {}
}
