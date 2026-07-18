
#pragma once

#include<cstdint>
#include<new>
#include<memalloc.hpp>

namespace rcc_add {}

namespace port_add { //port addresseclock

    using namespace rcc_add;
    
    inline volatile uint32_t* const GPIOA = reinterpret_cast<uint32_t*>(0x48000000);
    inline volatile uint32_t* const GPIOB = reinterpret_cast<uint32_t*>(0x48000400);
    inline volatile uint32_t* const GPIOC = reinterpret_cast<uint32_t*>(0x48000800);
    inline volatile uint32_t* const GPIOD = reinterpret_cast<uint32_t*>(0x48000C00);
    inline volatile uint32_t* const GPIOF = reinterpret_cast<uint32_t*>(0x48001400);

}


namespace rcc_add {

    inline volatile uint32_t* const RCC_AHB2ENR   = reinterpret_cast<uint32_t*>(0x4002104C);  // →  GPIOA-G, ADC1/2         — no timers here
    inline volatile uint32_t* const RCC_APB1ENR1  = reinterpret_cast<uint32_t*>(0x40021058);  // →  TIM2, TIM3, TIM4, TIM6, TIM7
    inline volatile uint32_t* const RCC_APB2ENR   = reinterpret_cast<uint32_t*>(0x40021060);  // →  TIM1, TIM8, TIM15, TIM16, TIM17

}

namespace bus_add {

    inline volatile uint32_t* const TIM1_bus    = reinterpret_cast<uint32_t*>(0x40012C00);
    inline volatile uint32_t* const TIM2_bus    = reinterpret_cast<uint32_t*>(0x40000000);
    inline volatile uint32_t* const TIM3_bus    = reinterpret_cast<uint32_t*>(0x40000400);
    inline volatile uint32_t* const TIM4_bus    = reinterpret_cast<uint32_t*>(0x40000800);
    inline volatile uint32_t* const TIM6_bus    = reinterpret_cast<uint32_t*>(0x40001000);
    inline volatile uint32_t* const TIM7_bus    = reinterpret_cast<uint32_t*>(0x40001400);
    inline volatile uint32_t* const TIM8_bus    = reinterpret_cast<uint32_t*>(0x40013400);
    inline volatile uint32_t* const TIM15_bus   = reinterpret_cast<uint32_t*>(0x40014000);
    inline volatile uint32_t* const TIM16_bus   = reinterpret_cast<uint32_t*>(0x40014400);
    inline volatile uint32_t* const TIM17_bus   = reinterpret_cast<uint32_t*>(0x40014800);
}

namespace pin_reg_add { //pin register address offsets

    const uint32_t MODER = 0x00;  // 00 input, 01 output, 10 alternate function, 11 analog
    const uint32_t OTYPER = 0x04; // output type: 0 push-pull, 1 open-drain
    const uint32_t OSPEEDR = 0x08; // speed 
    const uint32_t PUPDR = 0x0C;   // 00 no pull, 01 pull-up, 10 pull-down
    const uint32_t IDR = 0x10;     // input data register
    const uint32_t ODR = 0x14;     // output data register
    const uint32_t BSRR = 0x18;    

    const uint32_t AFRL  = 0x20; // Offset 0x20 controls Pins 0 to 7
    const uint32_t AFRH  = 0x24; // Offset 0x24 controls Pins 8 to 15

}

namespace timer_bus_offset {

    const uint32_t CR1   = 0x00;
    const uint32_t SMCR  = 0x08; 
    const uint32_t EGR   = 0x14;
    const uint32_t CCMR1 = 0x18;
    const uint32_t CCMR2 = 0x1C;
    const uint32_t CCER  = 0x20;
    const uint32_t PSC   = 0x28;
    const uint32_t ARR   = 0x2C;
    const uint32_t CCR1  = 0x34;
    const uint32_t CCR2  = 0x38;
    const uint32_t CCR3  = 0x3C;
    const uint32_t CCR4  = 0x40;
    const uint32_t BDTR  = 0x44;
}


namespace rcc_offset {

    const uint32_t CR        = 0x00;
    const uint32_t CFGR      = 0x08;
    const uint32_t AHB1ENR   = 0x48;
    const uint32_t AHB2ENR   = 0x4C;
    const uint32_t AHB3ENR   = 0x50;
    const uint32_t APB1ENR1  = 0x58;
    const uint32_t APB1ENR2  = 0x5C;
    const uint32_t APB2ENR   = 0x60;

}

namespace adc_base {

    inline volatile uint32_t* const ADC1 = reinterpret_cast<uint32_t*>(0x50000000);
    inline volatile uint32_t* const ADC2 = reinterpret_cast<uint32_t*>(0x50000100);

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

    static void init_port_ins(char x) {
        create_port(x);
    }

    static GPIO_PORT* return_ins_add(uint32_t x) {
        return port_ptr[x];
    }
    static GPIO_PORT* bootstrap(char port);

    static status initialize_port(char port) {

        switch(port) {
            case 'A': {
                volatile uint32_t* rcc_ahb2enr = reinterpret_cast<volatile uint32_t*>(port_add::RCC_AHB2ENR);
                *rcc_ahb2enr |= 1 << 0; 
                return status::default_success;
            }

            case 'B': {
                volatile uint32_t* rcc_ahb2enr = reinterpret_cast<volatile uint32_t*>(port_add::RCC_AHB2ENR);
                *rcc_ahb2enr |= 1 << 1; 
                return status::default_success;
            }

            case 'C': {
                volatile uint32_t* rcc_ahb2enr = reinterpret_cast<volatile uint32_t*>(port_add::RCC_AHB2ENR);
                *rcc_ahb2enr |= 1 << 2; 
                return status::default_success;
            }

            case 'D': {
                volatile uint32_t* rcc_ahb2enr = reinterpret_cast<volatile uint32_t*>(port_add::RCC_AHB2ENR);
                *rcc_ahb2enr |= 1 << 3; 
                return status::default_success;
            }

            case 'F': {
                volatile uint32_t* rcc_ahb2enr = reinterpret_cast<volatile uint32_t*>(port_add::RCC_AHB2ENR);
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
                *rcc_ahb2enr &= 0 << 0;
                return status::default_success; 
            }

            case 'B': {
                volatile uint32_t* rcc_ahb2enr = reinterpret_cast<volatile uint32_t*>(port_add::RCC_AHB2ENR);
                *rcc_ahb2enr &= 0 << 1; 
                return status::default_success;
            }

            case 'C': {
                volatile uint32_t* rcc_ahb2enr = reinterpret_cast<volatile uint32_t*>(port_add::RCC_AHB2ENR);
                *rcc_ahb2enr &= 0 << 2; 
                return status::default_success; 
            }

            case 'D': {
                volatile uint32_t* rcc_ahb2enr = reinterpret_cast<volatile uint32_t*>(port_add::RCC_AHB2ENR);
                *rcc_ahb2enr &= 0 << 3; 
                return status::default_success;
            }

            case 'F': {
                volatile uint32_t* rcc_ahb2enr = reinterpret_cast<volatile uint32_t*>(port_add::RCC_AHB2ENR);
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

    constexpr static char pins[5] = {'A', 'B', 'C', 'D', 'F'};

    static inline bool count = 0;

    static inline GPIO_PORT* port_ptr[5] = {};

protected:
    friend class GPIO_PORT;

    static GPIO_PORT* create_port(char port);

};



class GPIO_PORT {
    
    friend GPIO_PORT* GPIO::create_port(char port);

public:    

    
    void set_pin_mode(uint8_t pinNumber, uint8_t mode) {// 0 (input), 1 (output), 2 (alternate function), 3 (analog)
        volatile uint32_t* moder = reinterpret_cast<volatile uint32_t*>(port_base + pin_reg_add::MODER);
        uint8_t shift = pinNumber * 2;
    
        *moder &= ~(0x3 << shift); // clear old 2 bits
        *moder |=  (mode << shift); // set new 2 bits
    }

   // Push-Pull (0) or Open-Drain (1).
    void set_output_type(uint8_t pinNumber, uint8_t type) {
        volatile uint32_t* otyper = reinterpret_cast<volatile uint32_t*>(port_base + pin_reg_add::OTYPER);
    
        *otyper &= ~(0x1 << pinNumber); // Clear old 1 bit
        *otyper |=  (type << pinNumber); // Set new 1 bit
    }

    // speed: Low (0), Medium (1), High (2), or Very High (3).
    void set_pin_speed(uint8_t pinNumber, uint8_t speed) {
        volatile uint32_t* ospeedr = reinterpret_cast<volatile uint32_t*>(port_base + pin_reg_add::OSPEEDR);
        uint8_t shift = pinNumber * 2;
    
        *ospeedr &= ~(0x3 << shift); // clear old 2 bits
        *ospeedr |=  (speed << shift); // set new 2 bits
    }

    // Floating (0), Pull-Up (1), or Pull-Down (2).
    void set_pin_pull(uint8_t pinNumber, uint8_t pull) {
        volatile uint32_t* pupdr = reinterpret_cast<volatile uint32_t*>(port_base + pin_reg_add::PUPDR);
        uint8_t shift = pinNumber * 2;
    
        *pupdr &= ~(0x3 << shift); // clear old 2 bits
        *pupdr |=  (pull << shift); // set new 2 bits
    }

    
    void write_pin(uint8_t pinNumber, bool state) {
        volatile uint32_t* bsrr = reinterpret_cast<volatile uint32_t*>(port_base + pin_reg_add::BSRR);
    
        if (state) {
            *bsrr = (1 << pinNumber);        // write to lower 16 bits forces pin HIGH
        } else {
            *bsrr = (1 << (pinNumber + 16)); // write upper 16 bits forces pin LOW
        }
    }
    // Reads the instant voltage level on the external wire, returning true for 3.3V and false for Ground.
    bool read_pin(uint32_t portBase, uint8_t pinNumber) {
        volatile uint32_t* idr = reinterpret_cast<volatile uint32_t*>(portBase + pin_reg_add::IDR);
    
       
        return (*idr & (1 << pinNumber)) != 0;
    }

    void set_port_base(volatile uint32_t* n) {

        port_base = (uint32_t)n;
    }

    volatile uint32_t* get_gpio_base(char port) {
        switch (port) {
            case 'A': return port_add::GPIOA;
            case 'B': return port_add::GPIOB;
            case 'C': return port_add::GPIOC;
            case 'D': return port_add::GPIOD;
            case 'F': return port_add::GPIOF;
            default:      return nullptr; // invalid port
        }
    }
    
    void set_pin_alternate_function(uint8_t pin) {
        volatile uint32_t* base = get_gpio_base(port);
        if (base == nullptr) return;

        volatile uint32_t* moder_reg = reinterpret_cast<volatile uint32_t*>(
            reinterpret_cast<volatile uint8_t*>(base) + pin_reg_add::MODER
        );

        *moder_reg &= ~(0b11 << (pin * 2));  // clear both bits

        *moder_reg |= (0b10 << (pin * 2));
    }

    char get_port() {
        return port;
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

    GPIO_PORT* ptr = new ((uint32_t*)(*data_ptr)) GPIO_PORT(data_ptr, port); 

    port_ptr[n] = ptr;

    return ptr;
}


GPIO_PORT* GPIO::bootstrap(char port) {

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


    GPIO_PORT* p = GPIO::return_ins_add(n);

    p->set_port_base(p->get_gpio_base(port));

    return GPIO::return_ins_add(n);

}   




class PWM {
private:
    GPIO_PORT* port_instance;
    char port_instance_char;
    uint32_t psc_value;
    uint32_t arr_value;
    uint8_t channel_;
    uint32_t duty_value;

public:

    PWM(GPIO_PORT* ins) : port_instance(ins) {

        port_instance_char = port_instance->get_port();

    }

    void enable_timer_clock(int timer) {
        switch (timer) {
            case 2: 
                *rcc_add::RCC_APB1ENR1 |= (1 << 0); 
                break;  // TIM2
            case 3: 
                *rcc_add::RCC_APB1ENR1 |= (1 << 1); 
                break;  // TIM3
            case 4: 
                *rcc_add::RCC_APB1ENR1 |= (1 << 2);
                break;  // TIM4
            case 6: 
                *rcc_add::RCC_APB1ENR1 |= (1 << 4); 
                break;  // TIM6
            case 7: 
                *rcc_add::RCC_APB1ENR1 |= (1 << 5); 
                break;  // TIM7

            case 1:  
                *rcc_add::RCC_APB2ENR |= (1 << 11); 
                break; // TIM1
            case 8:  
                *rcc_add::RCC_APB2ENR |= (1 << 13); 
                break; // TIM8
            case 15: 
                *rcc_add::RCC_APB2ENR |= (1 << 16); 
                break; // TIM15
            case 16: 
                *rcc_add::RCC_APB2ENR |= (1 << 17); 
                break; // TIM16
            case 17: 
                *rcc_add::RCC_APB2ENR |= (1 << 18); 
                break; // TIM17

            default: 
                return; // invalid timer number
        }
    }

    volatile uint32_t* get_timer_base(int timer) {
        switch (timer) {
            case 1:  return 
                bus_add::TIM1_bus;
            case 2:  return 
                bus_add::TIM2_bus;
            case 3:  return 
                bus_add::TIM3_bus;
            case 4:  return 
                bus_add::TIM4_bus;
            case 6:  return 
                bus_add::TIM6_bus;
            case 7:  return 
                bus_add::TIM7_bus;
            case 8:  return 
                bus_add::TIM8_bus;
            case 15: return 
                bus_add::TIM15_bus;
            case 16: return 
                bus_add::TIM16_bus;
            case 17: return 
                bus_add::TIM17_bus;
            default:
                return nullptr; 
        }
    }   


    volatile uint32_t* get_gpio_base(char port) {
        switch (port) {
            case 'A': 
                return port_add::GPIOA;
            case 'B': 
                return port_add::GPIOB;
            case 'C': 
                return port_add::GPIOC;
            case 'D': 
                return port_add::GPIOD;
            case 'F': 
                return port_add::GPIOF;
            default:      
                return nullptr;
        }
    }

    void select_af_number(uint8_t pin, uint8_t af_number) {

        volatile uint32_t* base = get_gpio_base(port_instance_char);
        if (base == nullptr) return;

        if (pin <= 7) {
            volatile uint32_t* afrl_reg = reinterpret_cast<volatile uint32_t*>(
            reinterpret_cast<volatile uint8_t*>(base) + pin_reg_add::AFRL
            );

            *afrl_reg |= (af_number << (pin * 4));
        } else {
            volatile uint32_t* afrh_reg = reinterpret_cast<volatile uint32_t*>(
                reinterpret_cast<volatile uint8_t*>(base) + pin_reg_add::AFRH
            );

            *afrh_reg |= (af_number << ((pin - 8) * 4));
        }
    }


    void set_prescaler(int timer, uint32_t value) {

        psc_value = value;

        volatile uint32_t* base = get_timer_base(timer);
        if (base == nullptr) return;

        volatile uint32_t* psc_reg = reinterpret_cast<volatile uint32_t*>(
            reinterpret_cast<volatile uint8_t*>(base) + timer_bus_offset::PSC
        );

        *psc_reg = value;  
    }

    void set_auto_reload(int timer, uint32_t value) {

        arr_value = value;

        volatile uint32_t* base = get_timer_base(timer);
        if (base == nullptr) return;

        volatile uint32_t* arr_reg = reinterpret_cast<volatile uint32_t*>(
            reinterpret_cast<volatile uint8_t*>(base) + timer_bus_offset::ARR
        );

        *arr_reg = value;
    }

    void set_duty(int timer, uint8_t channel, uint32_t value) {

        duty_value = value;

        volatile uint32_t* base = get_timer_base(timer);
        if (base == nullptr) return;

        uint32_t offset;
        switch (channel) {
            case 1: offset = timer_bus_offset::CCR1; break;
            case 2: offset = timer_bus_offset::CCR2; break;
            case 3: offset = timer_bus_offset::CCR3; break;
            case 4: offset = timer_bus_offset::CCR4; break;
            default: return; 
        }

        volatile uint32_t* ccr_reg = reinterpret_cast<volatile uint32_t*>(
            reinterpret_cast<volatile uint8_t*>(base) + offset
        );

        *ccr_reg = value;
    }


    void set_pwm_mode(int timer, uint8_t channel) {
        volatile uint32_t* base = get_timer_base(timer);
        if (base == nullptr) return;

        uint32_t offset;
        uint8_t shift;

        switch (channel) {
            case 1: offset = timer_bus_offset::CCMR1; shift = 4;  break;
            case 2: offset = timer_bus_offset::CCMR1; shift = 12; break;
            case 3: offset = timer_bus_offset::CCMR2; shift = 4;  break; 
            case 4: offset = timer_bus_offset::CCMR2; shift = 12; break; 
            default: return;
        }

        volatile uint32_t* ccmr_reg = reinterpret_cast<volatile uint32_t*>(
            reinterpret_cast<volatile uint8_t*>(base) + offset
        );

        *ccmr_reg |= (0b110 << shift);
    }

    void enable_channel(int timer, uint8_t channel) {

        channel_ = channel;

        volatile uint32_t* base = get_timer_base(timer);
        if (base == nullptr) return;

        uint8_t bit;
        switch (channel) {
            case 1: bit = 0;  break;  
            case 2: bit = 4;  break;
            case 3: bit = 8;  break; 
            case 4: bit = 12; break;  
            default: return;
        }

        volatile uint32_t* ccer_reg = reinterpret_cast<volatile uint32_t*>(
            reinterpret_cast<volatile uint8_t*>(base) + timer_bus_offset::CCER
        );

        *ccer_reg |= (1 << bit);
    }

    void start_timer(int timer) {
        volatile uint32_t* base = get_timer_base(timer);
        if (base == nullptr) return;

        volatile uint32_t* cr1_reg = reinterpret_cast<volatile uint32_t*>(
            reinterpret_cast<volatile uint8_t*>(base) + timer_bus_offset::CR1
        );

        *cr1_reg |= (1 << 0); 
    }

    void set_input_capture_mode(int timer) {
        volatile uint32_t* base = get_timer_base(timer);
        if (base == nullptr) return;

        volatile uint32_t* ccmr1_reg = reinterpret_cast<volatile uint32_t*>(
            reinterpret_cast<volatile uint8_t*>(base) + timer_bus_offset::CCMR1
        );

        *ccmr1_reg &= ~(0x3 << 0);   
        *ccmr1_reg |=  (0x1 << 0);  

        *ccmr1_reg &= ~(0x3 << 8);   
        *ccmr1_reg |=  (0x2 << 8); 
    }

    void set_input_polarity(int timer) {
        volatile uint32_t* base = get_timer_base(timer);
        if (base == nullptr) return;

        volatile uint32_t* ccer_reg = reinterpret_cast<volatile uint32_t*>(
            reinterpret_cast<volatile uint8_t*>(base) + timer_bus_offset::CCER
        );

        *ccer_reg &= ~(1 << 1);   
        *ccer_reg |=  (1 << 5);  
    }

    void set_trigger_reset_mode(int timer) {
        volatile uint32_t* base = get_timer_base(timer);
        if (base == nullptr) return;

        volatile uint32_t* smcr_reg = reinterpret_cast<volatile uint32_t*>(
            reinterpret_cast<volatile uint8_t*>(base) + timer_bus_offset::SMCR
        );

        *smcr_reg &= ~(0x7 << 4);  
        *smcr_reg |=  (0x5 << 4);  

        *smcr_reg &= ~(0x7 << 0);  
        *smcr_reg |=  (0x4 << 0);   
    }

    uint32_t read_period(int timer) {
        volatile uint32_t* base = get_timer_base(timer);
        if (base == nullptr) {
            return 0;
        }
        volatile uint32_t* ccr1_reg = reinterpret_cast<volatile uint32_t*>(
            reinterpret_cast<volatile uint8_t*>(base) + timer_bus_offset::CCR1
        );

        return *ccr1_reg;
    }

    uint32_t read_pulse_width(int timer) {
        volatile uint32_t* base = get_timer_base(timer);
        if (base == nullptr) {
            return 0;
        }
        volatile uint32_t* ccr2_reg = reinterpret_cast<volatile uint32_t*>(
            reinterpret_cast<volatile uint8_t*>(base) + timer_bus_offset::CCR2
        );

        return *ccr2_reg;
    }

};


