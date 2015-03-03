// **************************************************************************
//
// Function for work with serial port
//
// **************************************************************************

#ifndef _COM_H_
#define _COM_H_

// open serial port
extern int com_open(const char *device, unsigned int baudrate, unsigned int databits, const char *parity, unsigned int stopbits);

#endif

