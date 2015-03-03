// **************************************************************************
//
// Functions for BASE64 encoding/decoding
//
// **************************************************************************

#ifndef _BASE64_H_
#define _BASE64_H_

// encode BASE64 (don't allocate memory)
extern void base64_encode(const unsigned char *src, char *dst, int size);

// encode BASE64 (allocate memory)
extern char *base64_encode_str(const char *str);

// decode BASE64 (allocate memory)
extern char *base64_decode_str(const char *str);

#endif

