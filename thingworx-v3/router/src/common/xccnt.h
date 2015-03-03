// **************************************************************************
//
// Functions for work with XC-CNT expansion board
//
// **************************************************************************

#ifndef _XCCNT_H_
#define _XCCNT_H_

// get state of binary inputs
extern int xccnt_get_inputs(int port, unsigned short *value_ptr);

// get state of binary input
extern int xccnt_get_input(int port, int idx, unsigned short *value_ptr);

// get state of analog input
extern int xccnt_get_analog(int port, int idx, unsigned short *value_ptr);

// get state of counter input
extern int xccnt_get_counter(int port, int idx, unsigned int *value_ptr);

// set state of counter input
extern int xccnt_set_counter(int port, int idx, unsigned int value);

// get state of binary output
extern int xccnt_get_output(int port, unsigned short *value_ptr);

// set state of binary output
extern int xccnt_set_output(int port, unsigned short value);

#endif

