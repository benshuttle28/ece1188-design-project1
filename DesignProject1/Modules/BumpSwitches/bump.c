#include "msp.h"
#include <stdint.h>
#include "bump.h"

volatile uint8_t bumpFlag = 0;  // Stores last bump event

// ------------Bump_Init------------
// Initialize bump sensors
void Bump_Init(void) {
    P4->SEL0 &= ~0xED;  // Configure P4.7, P4.6, P4.5, P4.3, P4.2, P4.0 as GPIO
    P4->SEL1 &= ~0xED;
    P4->DIR &= ~0xED;   // Set as input
    P4->REN |= 0xED;    // Enable pull-up resistors
    P4->OUT |= 0xED;    // Pull-up selected

    P4->IES |= 0xED;    // Interrupt on high-to-low transition (falling edge)
    P4->IFG &= ~0xED;   // Clear any existing interrupt flags
    P4->IE |= 0xED;     // Enable interrupts for bump sensors

    NVIC->ISER[1] = 1 << ((PORT4_IRQn) & 31); // Enable Port 4 interrupt in NVIC
}

// ------------Bump_Read------------
// Read the bump sensor status
// Returns a 6-bit packed value representing the bump sensors
uint8_t Bump_Read(void) {
    uint8_t rawData = (~P4->IN) & 0xED;  // Correct mask for all 6 bump sensors

    return ((rawData & 0x80) >> 2) |  // Bump5 (P4.7) → Bit 5
           ((rawData & 0x40) >> 2) |  // Bump4 (P4.6) → Bit 4
           ((rawData & 0x20) >> 2) |  // Bump3 (P4.5) → Bit 3
           ((rawData & 0x08) >> 1) |  // Bump2 (P4.3) → Bit 2
           ((rawData & 0x04) >> 1) |  // Bump1 (P4.2) → Bit 1
           ((rawData & 0x01) << 0);   // Bump0 (P4.0) → Bit 0
}

// ------------PORT4_IRQHandler------------
// Interrupt handler for bump sensors (updates global bump flag)
void PORT4_IRQHandler(void) {
    bumpFlag = Bump_Read(); // Store which sensor triggered
    P4->IFG &= ~0xED; // Clear interrupt flag
}

void Reset_Flag(){
    bumpFlag = 0;
}
