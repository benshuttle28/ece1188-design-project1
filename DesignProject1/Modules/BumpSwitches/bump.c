#include "msp.h"

void Bump_Init(void);
uint8_t Bump_Read(void);
void PORT4_IRQHandler(void);

// Initialize bump sensors on P4.7-P4.0
void Bump_Init(void) {
    P4->SEL0 &= ~0xED;  // Configure P4.7, P4.6, P4.3, P4.2, P4.1, P4.0 as GPIO
    P4->SEL1 &= ~0xED;
    P4->DIR &= ~0xED;   // Set P4.7, P4.6, P4.3, P4.2, P4.1, P4.0 as input
    P4->REN |= 0xED;    // Enable pull-up resistors
    P4->OUT |= 0xED;    // Pull-up selected

    P4->IES |= 0xED;    // Interrupt on high-to-low transition (falling edge)
    P4->IFG &= ~0xED;   // Clear any existing interrupt flags
    P4->IE |= 0xED;     // Enable interrupts for bump sensors

    NVIC->ISER[1] = 1 << ((PORT4_IRQn) & 31); // Enable Port 4 interrupt in NVIC
}

// Read bump sensor status
uint8_t Bump_Read(void) {
    return (~P4->IN) & 0xED; // Active low, invert logic
}

// Interrupt Service Routine for bump sensors
void PORT4_IRQHandler(void) {
    uint8_t status = Bump_Read(); // Get bump sensor status

    P4->IFG &= ~0xED; // Clear interrupt flag
    if (status) {
            // TODO FOR BUMP SENSOR INTEGRATION WITH MOTORS/FSM
    }
}
