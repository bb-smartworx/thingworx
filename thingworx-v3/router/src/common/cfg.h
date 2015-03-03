// **************************************************************************
//
// Functions for work with configuration
//
// **************************************************************************

#ifndef _CFG_H_
#define _CFG_H_

#include <stdio.h>

// open configuration file
extern FILE *cfg_open(const char *config_name, const char *open_mode);

// close configuration file
extern void cfg_close(FILE *file_ptr);

// put string into configuration file
extern void cfg_put_str(FILE *file_ptr, const char *name, const char *value);

// put integer into configuration file
extern void cfg_put_int(FILE *file_ptr, const char *name, int value, int store_zero);

// put boolean into configuration file
extern void cfg_put_bool(FILE *file_ptr, const char *name, int value);

// put IP address into configuration file
extern void cfg_put_ip(FILE *file_ptr, const char *name, unsigned int value);

// get string from configuration file
extern char *cfg_get_str(FILE *file_ptr, const char *name);

// get integer from configuration file
extern unsigned int cfg_get_int(FILE *file_ptr, const char *name);

// get IP address from configuration file
extern unsigned int cfg_get_ip(FILE *file_ptr, const char *name);

#endif

