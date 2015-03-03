// **************************************************************************
//
// Functions for work with sockets
//
// **************************************************************************

#ifndef _SOCKET_H_
#define _SOCKET_H_

// open TCP socket (client mode)
extern int socket_open_tcp_client(unsigned int ip, unsigned int port);

// open TCP socket (server mode)
extern int socket_open_tcp_server(unsigned int port);

// open UDP socket
extern int socket_open_udp(unsigned int port);

// close socket
extern void socket_close(int sock);

// enable keepalive on TCP socket
extern void socket_keepalive(int sock, int time, int intvl, int probes);

#endif

