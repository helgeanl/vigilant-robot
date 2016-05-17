#ifndef __MCP2515_H
#define __MCP2515_H

/*
mcp2515.h

This file contains constants that are specific to the MCP2515.

Version     Date        Description
----------------------------------------------------------------------
v1.00       2003/12/11  Initial release

Copyright 2003 Kimberly Otten Software Consulting
*/

// Define MCP2515 register addresses

#define MCP_RXF0SIDH	0x00    // FILTER 0 STANDARD IDENTIFIER HIGH
#define MCP_RXF0SIDL	0x01    // FILTER 0 STANDARD IDENTIFIER LOW
#define MCP_RXF0EID8	0x02    // FILTER 0 EXTENDED IDENTIFIER HIGH
#define MCP_RXF0EID0	0x03    // FILTER 0 EXTENDED IDENTIFIER LOW
#define MCP_RXF1SIDH	0x04    // FILTER 1 STANDARD IDENTIFIER HIGH
#define MCP_RXF1SIDL	0x05    // FILTER 1 STANDARD IDENTIFIER LOW
#define MCP_RXF1EID8	0x06    // FILTER 1 EXTENDED IDENTIFIER HIGH
#define MCP_RXF1EID0	0x07    // FILTER 1 EXTENDED IDENTIFIER LOW
#define MCP_RXF2SIDH	0x08    // FILTER 2 STANDARD IDENTIFIER HIGH
#define MCP_RXF2SIDL	0x09    // FILTER 2 STANDARD IDENTIFIER LOW
#define MCP_RXF2EID8	0x0A    // FILTER 2 EXTENDED IDENTIFIER HIGH
#define MCP_RXF2EID0	0x0B    // FILTER 2 EXTENDED IDENTIFIER LOW

#define MCP_CANSTAT		0x0E    // CAN STATUS REGISTER
// bit 7-5: operation mode bits
// bit 4 and 0: unimplemented
// bit 3-1: Interrupt Flag Code bits 
//			000 = no int, 001 = error, 010 = wake-up, 011 = TXB0, 100 = TXB1, 101 = TXB2, 110 = RXB0, 111 = RXB1
#define MCP_CANCTRL		0x0F    // CAN CONTROL REGISTER

#define MCP_RXF3SIDH	0x10    // FILTER 3 STANDARD IDENTIFIER HIGH
#define MCP_RXF3SIDL	0x11    // FILTER 3 STANDARD IDENTIFIER LOW
#define MCP_RXF3EID8	0x12    // FILTER 3 EXTENDED IDENTIFIER HIGH
#define MCP_RXF3EID0	0x13    // FILTER 3 EXTENDED IDENTIFIER LOW
#define MCP_RXF4SIDH	0x14    // FILTER 4 STANDARD IDENTIFIER HIGH
#define MCP_RXF4SIDL	0x15    // FILTER 4 STANDARD IDENTIFIER LOW
#define MCP_RXF4EID8	0x16    // FILTER 4 EXTENDED IDENTIFIER HIGH
#define MCP_RXF4EID0	0x17    // FILTER 4 EXTENDED IDENTIFIER LOW
#define MCP_RXF5SIDH	0x18    // FILTER 5 STANDARD IDENTIFIER HIGH
#define MCP_RXF5SIDL	0x19    // FILTER 5 STANDARD IDENTIFIER LOW
#define MCP_RXF5EID8	0x1A    // FILTER 5 EXTENDED IDENTIFIER HIGH
#define MCP_RXF5EID0	0x1B    // FILTER 5 EXTENDED IDENTIFIER LOW

#define MCP_TEC			0x1C    // Transmit Error Counter
#define MCP_REC			0x1D    // Receiver Error Counter

#define MCP_RXM0SIDH	0x20    // MASK 0 standard identifier HIGH
#define MCP_RXM0SIDL	0x21    // MASK 0 standard identifier LOW
#define MCP_RXM0EID8	0x22    // MASK 0 extended identifier HIGH
#define MCP_RXM0EID0	0x23    // MASK 0 extended identifier LOW
#define MCP_RXM1SIDH	0x24    // MASK 1 standard identifier HIGH
#define MCP_RXM1SIDL	0x25    // MASK 1 standard identifier LOW
#define MCP_RXM1EID8	0x26    // MASK 1 extended identifier HIGH
#define MCP_RXM1EID0	0x27    // MASK 1 extended identifier LOW

#define MCP_CNF3		0x28    // Configuration 1
#define MCP_CNF2		0x29    // Configuration 1
#define MCP_CNF1		0x2A    // Configuration 1
#define MCP_CANINTE		0x2B    // Interrupt enable
#define MCP_CANINTF		0x2C    // Interrupt flag
#define MCP_EFLG		0x2D    // Error flag

#define MCP_TXB0CTRL	0x30    // TRANSMIT BUFFER 0, CONTROL REGISTER
#define MCP_TXB0SIDH	0x31    // TRANSMIT BUFFER 0, STANDARD IDENTIFIER HIGH
#define MCP_TXB0SIDL	0x32    // TRANSMIT BUFFER 0, STANDARD IDENTIFIER LOW
#define MCP_TXB0DLC		0x35    // TRANSMIT BUFFER 0, DATA LENGTH CODE
#define MCP_TXB0D0		0x36    // TRANSMIT BUFFER 0, DATA BYTE 0
#define MCP_TXB0D1		0x37    // TRANSMIT BUFFER 0, DATA BYTE 1
#define MCP_TXB0D2		0x38    // TRANSMIT BUFFER 0, DATA BYTE 2
#define MCP_TXB0D3		0x39    // TRANSMIT BUFFER 0, DATA BYTE 3
#define MCP_TXB0D4		0x3A    // TRANSMIT BUFFER 0, DATA BYTE 4
#define MCP_TXB0D5		0x3B    // TRANSMIT BUFFER 0, DATA BYTE 5
#define MCP_TXB0D6		0x3C    // TRANSMIT BUFFER 0, DATA BYTE 6
#define MCP_TXB0D7		0x3D    // TRANSMIT BUFFER 0, DATA BYTE 7

#define MCP_TXB1CTRL	0x40    // TRANSMIT BUFFER 1, CONTROL REGISTER
#define MCP_TXB1SIDH	0x41    // TRANSMIT BUFFER 1, STANDARD IDENTIFIER HIGH
#define MCP_TXB1SIDL	0x42    // TRANSMIT BUFFER 1, STANDARD IDENTIFIER LOW
#define MCP_TXB1DLC		0x45    // TRANSMIT BUFFER 1, DATA LENGTH CODE

#define MCP_TXB2CTRL	0x50    // TRANSMIT BUFFER 2, CONTROL REGISTER
#define MCP_TXB2SIDH	0x51    // TRANSMIT BUFFER 2, STANDARD IDENTIFIER HIGH
#define MCP_TXB2SIDL	0x52    // TRANSMIT BUFFER 2, STANDARD IDENTIFIER LOW
#define MCP_TXB2DLC		0x55    // TRANSMIT BUFFER 2, DATA LENGTH CODE

#define MCP_RXB0CTRL	0x60    // RECEIVE BUFFER 0, CONTROL
#define MCP_RXB0SIDH	0x61    // RECEIVE BUFFER 0, STANDARD IDENTIFIER HIGH
#define MCP_RXB0SIDL	0x62    // RECEIVE BUFFER 0, STANDARD IDENTIFIER LOW
#define MCP_RXB0DLC     0x65    // RECEIVE BUFFER 0, DATA LENGTH CODE
#define MCP_RXB0D0		0x66    // RECEIVE BUFFER 0, DATA BYTE 0
#define MCP_RXB0D1		0x67    // RECEIVE BUFFER 0, DATA BYTE 1
#define MCP_RXB0D2		0x68    // RECEIVE BUFFER 0, DATA BYTE 2
#define MCP_RXB0D3		0x69    // RECEIVE BUFFER 0, DATA BYTE 3
#define MCP_RXB0D4		0x6A    // RECEIVE BUFFER 0, DATA BYTE 4
#define MCP_RXB0D5		0x6B    // RECEIVE BUFFER 0, DATA BYTE 5
#define MCP_RXB0D6		0x6C    // RECEIVE BUFFER 0, DATA BYTE 6
#define MCP_RXB0D7		0x6D    // RECEIVE BUFFER 0, DATA BYTE 7

#define MCP_RXB1CTRL	0x70    // RECEIVE BUFFER 1, CONTROL
#define MCP_RXB1SIDH	0x71    // RECEIVE BUFFER 1, STANDARD IDENTIFIER HIGH
#define MCP_RXB1SIDL	0x72    // RECEIVE BUFFER 1, STANDARD IDENTIFIER LOW
#define MCP_RXB1DLC     0x75    // RECEIVE BUFFER 1, DATA LENGTH CODE
#define MCP_RXB1D0		0x76    // RECEIVE BUFFER 1, DATA BYTE 0

// Interrupt bits
#define MCP_TX_INT		0x1C	// Enable all transmit interrupts
#define MCP_TX01_INT	0x0C	// Enable TXB0 and TXB1 interrupts
#define MCP_RX_INT		0x03	// Enable receive interrupts
#define MCP_NO_INT		0x00	// Disable all interrupts

#define MCP_TX01_MASK	0x14
#define MCP_TX_MASK		0x54


// Define SPI Instruction Set

#define MCP_WRITE		0x02

#define MCP_READ		0x03

#define MCP_BITMOD		0x05

#define MCP_LOAD_TX0	0x40
#define MCP_LOAD_TX1	0x42
#define MCP_LOAD_TX2	0x44

#define MCP_RTS_TX0		0x81
#define MCP_RTS_TX1		0x82
#define MCP_RTS_TX2		0x84
#define MCP_RTS_ALL		0x87

#define MCP_READ_RX0	0x90
#define MCP_READ_RX1	0x94

#define MCP_READ_STATUS	0xA0

#define MCP_RX_STATUS	0xB0

#define MCP_RESET		0xC0


// CANCTRL Register Values

#define MODE_NORMAL     0x00
#define MODE_SLEEP      0x20
#define MODE_LOOPBACK   0x40
#define MODE_LISTENONLY 0x60
#define MODE_CONFIG     0x80
#define MODE_POWERUP	0xE0
#define MODE_MASK		0xE0
#define ABORT_TX        0x10
#define MODE_ONESHOT	0x08
#define CLKOUT_ENABLE	0x04
#define CLKOUT_DISABLE	0x00
#define CLKOUT_PS1		0x00
#define CLKOUT_PS2		0x01
#define CLKOUT_PS4		0x02
#define CLKOUT_PS8		0x03


// CNF1 Register Values

#define SJW1            0x00
#define SJW2            0x40
#define SJW3            0x80
#define SJW4            0xC0


// CNF2 Register Values

#define BTLMODE			0x80
#define SAMPLE_1X       0x00
#define SAMPLE_3X       0x40


// CNF3 Register Values

#define SOF_ENABLE		0x80
#define SOF_DISABLE		0x00
#define WAKFIL_ENABLE	0x40
#define WAKFIL_DISABLE	0x00


// CANINTF Register Bits

#define MCP_RX0IF		0x01
#define MCP_RX1IF		0x02
#define MCP_TX0IF		0x04
#define MCP_TX1IF		0x08
#define MCP_TX2IF		0x10
#define MCP_ERRIF		0x20
#define MCP_WAKIF		0x40
#define MCP_MERRF		0x80



#endif
