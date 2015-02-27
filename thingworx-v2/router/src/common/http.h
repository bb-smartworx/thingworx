// **************************************************************************
//
// Function for sending file via HTTP protocol
//
// **************************************************************************

#ifndef _HTTP_H_
#define _HTTP_H_

// start of file transfer
extern void http_file_begin(const char *filename);

// send content of file
extern void http_file_content(const char *filename, const char *error);

// end of file transfer
extern void http_file_end(void);

#endif

