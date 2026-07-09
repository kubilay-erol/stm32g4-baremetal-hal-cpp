# Custom OOP HAL for STM32G4 GPIO

A lightweight, object-oriented custom Hardware Abstraction Layer (HAL) written in bare-metal C++ for the **STM32G431KB** microcontroller (ARM Cortex-M4). 

This library serves as a minimal, high-performance alternative to bloated manufacturer-provided HALs, proving that register-level peripheral manipulation can be type-safe, readable, and structured around clean C++ design patterns.

## 🚀 Features

* **Object-Oriented HAL:** Capsulates raw hardware register complexity behind an intuitive, self-documenting C++ class interface.
* **Safe Port Bootstrapping:** Uses a factory pattern (`bootstrap()`) to simultaneously allocate the HAL port object and safely enable the corresponding peripheral clock in the Reset and Clock Control (RCC) register.
* **Type-Safe Drivers:** Avoids macro-heavy solutions (`#define`) by leveraging `constexpr` addresses and scoped `enum class` states for error tracking.
* **Explicit Memory Control:** Plugs into an isolated external allocation system (`memalloc::alloc`) utilizing placement `new` syntax to enforce predictable memory layouts for embedded systems.

---

## 🛠️ HAL Architecture & Register Mapping

The HAL abstracts direct memory-mapped I/O registers using volatile raw pointers based on the standard STM32G4 boundary offsets:

| Register | Offset | HAL Method | Description |
| :--- | :--- | :--- | :--- |
| `MODER` | `0x00` | `setPinMode()` | Configures pin as Input, Output, Alternate Function, or Analog. |
| `OTYPER` | `0x04` | `setPinOutputType()` | Toggles between Push-Pull and Open-Drain (e.g., for I2C). |
| `OSPEEDR` | `0x08` | `setPinSpeed()` | Sets I/O output speed (Low, Medium, High, Very High). |
| `PUPDR` | `0x0C` | `setPinPull()` | Controls internal Pull-Up / Pull-Down / Floating resistors. |
| `IDR` | `0x10` | `readPin()` | Reads the digital logic voltage state from the pin. |
| `BSRR` | `0x18` | `writePin()` | Atomically Sets or Resets pins via a single write cycle. |

---

## ⚙️ How to Use

### Prerequisites
1. An environment set up for ARM cross-compilation (e.g., PlatformIO on Visual Studio Code).
2. Implementation of `memalloc.hpp` providing the `memalloc::alloc(size_t)` interface to track/manage heap configurations.
