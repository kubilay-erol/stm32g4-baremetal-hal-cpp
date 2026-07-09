
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
}


namespace pin_reg_add { //pin register addresses
    constexpr uint32_t MODER = 0x00;   // Offset 0x00
    constexpr uint32_t OTYPER = 0x04;  // Offset 0x04
    constexpr uint32_t OSPEEDR = 0x08; // Offset 0x08
    constexpr uint32_t PUPDR = 0x0C;   // Offset 0x0C
    constexpr uint32_t IDR = 0x10;     // Offset 0x10
    constexpr uint32_t ODR = 0x14;     // Offset 0x14
    constexpr uint32_t BSRR = 0x18;    // Offset 0x18
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

    
    void setPinMode(uint8_t pinNumber, uint8_t mode) {
        volatile uint32_t* moder = reinterpret_cast<volatile uint32_t*>(port_base + pin_reg_add::MODER);
        uint8_t shift = pinNumber * 2;
    
        *moder &= ~(0x3 << shift); // Clear old 2 bits
        *moder |=  (mode << shift); // Set new 2 bits
    }

   
    void setPinOutputType(uint8_t pinNumber, uint8_t type) {
        volatile uint32_t* otyper = reinterpret_cast<volatile uint32_t*>(port_base + pin_reg_add::OTYPER);
    
        *otyper &= ~(0x1 << pinNumber); // Clear old 1 bit
        *otyper |=  (type << pinNumber); // Set new 1 bit
    }

    
    void setPinSpeed(uint8_t pinNumber, uint8_t speed) {
        volatile uint32_t* ospeedr = reinterpret_cast<volatile uint32_t*>(port_base + pin_reg_add::OSPEEDR);
        uint8_t shift = pinNumber * 2;
    
        *ospeedr &= ~(0x3 << shift); // Clear old 2 bits
        *ospeedr |=  (speed << shift); // Set new 2 bits
    }

    
    void setPinPull(uint8_t pinNumber, uint8_t pull) {
        volatile uint32_t* pupdr = reinterpret_cast<volatile uint32_t*>(port_base + pin_reg_add::PUPDR);
        uint8_t shift = pinNumber * 2;
    
        *pupdr &= ~(0x3 << shift); // Clear old 2 bits
        *pupdr |=  (pull << shift); // Set new 2 bits
    }

    
    void writePin(uint8_t pinNumber, bool state) {
        volatile uint32_t* bsrr = reinterpret_cast<volatile uint32_t*>(port_base + pin_reg_add::BSRR);
    
        if (state) {
            *bsrr = (1 << pinNumber);        // Writing to lower 16 bits forces pin HIGH
        } else {
            *bsrr = (1 << (pinNumber + 16)); // Writing to upper 16 bits forces pin LOW
        }
    }

    bool readPin(uint32_t portBase, uint8_t pinNumber) {
        volatile uint32_t* idr = reinterpret_cast<volatile uint32_t*>(portBase + pin_reg_add::IDR);
    
       
        return (*idr & (1 << pinNumber)) != 0;
    }

    void set_port_base(uint32_t n) {
        port_base = n;
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


int main() {

    GPIO_PORT* ins = GPIO::bootstrap('B');

    ins->set_port_base(port_add::GPIOB);
    ins->setPinMode(3, 1);    // Pin 5 -> Output Mode
    ins->writePin(3, true);   // Pin 5 -> HIGH (LED Turns ON!)

    
}
