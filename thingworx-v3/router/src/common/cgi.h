// **************************************************************************
//
// Functions for getting parameters of CGI script
//
// **************************************************************************

#ifndef _CGI_H_
#define _CGI_H_

// start of CGI script parameters processing
extern void cgi_begin(void);

// end of CGI script parameters processing
extern void cgi_end(void);

// check if query is ok
extern int cgi_query_ok(void);

// get CGI script parameter (raw string)
extern int cgi_get_raw(const char *name, char **value_ptr);

// get CGI script parameter (string)
extern int cgi_get_str(const char *name, char **value_ptr, int no_spaces);

// get CGI script parameter (integer)
extern int cgi_get_int(const char *name, unsigned int *value_ptr);

// get CGI script parameter (boolean)
extern int cgi_get_bool(const char *name, unsigned int *value_ptr);

// get CGI script parameter (IP address)
extern int cgi_get_ip(const char *name, unsigned int *value_ptr, int zero);

// get CGI script parameter (MAC address)
extern int cgi_get_mac(const char *name, char **value_ptr, int zero);

#endif

