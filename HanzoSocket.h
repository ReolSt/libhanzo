#ifndef HANZO_SOCKET_H
#define HANZO_SOCKET_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "HanzoCall.h"
#include "HanzoString.h"
#include "HanzoFileStream.h"

typedef struct sockaddr HanzoSocketAddress;
typedef struct sockaddr_in HanzoSocketAddressIPv4;
typedef struct sockaddr_in6 HanzoSocketAddressIPv6;
typedef struct sockaddr_un HanzoSocketAddressUnix;

typedef enum __Hanzo_Socket_Type
{
  HanzoSocketType_Stream = SOCK_STREAM,
  HanzoSocketType_Dgram = SOCK_DGRAM,
  HanzoSocketType_Raw = SOCK_RAW,
#ifdef SOCK_RDM
  HanzoSocketType_RDM = SOCK_RDM,
#endif
#ifdef SOCK_SEQPACKET
  HanzoSocketType_SeqPacket = SOCK_SEQPACKET,
#endif
#ifdef SOCK_PACKET
  HanzoSocketType_Packet = SOCK_PACKET
#endif
} HanzoSocketType;

typedef enum __Hanzo_Address_Family
{
  HanzoAddressFamily_UnSpec = PF_UNSPEC,
#ifdef AF_UNIX
  HanzoAddressFamily_Unix = AF_UNIX,
#endif
  HanzoAddressFamily_IPv4 = AF_INET,
#ifdef AF_AX25
  HanzoAddressFamily_AX25 = AF_AX25,
#endif
#ifdef AF_IPX
  HanzoAddressFamily_IPX = AF_IPX
#endif
#ifdef AF_APPLETALK
  HanzoAddressFamily_AppleTalk = AF_APPLETALK,
#endif
#ifdef AF_NETROM
  HanzoAddressFamily_NetRom = AF_NETROM,
#endif
#ifdef AF_BRIDGE
  HanzoAddressFamily_Bridge = AF_BRIDGE,
#endif
#ifdef AF_AAL5
  HanzoAddressFamily_AAL5 = AF_AAL5,
#endif
#ifdef AF_X25
  HanzoAddressFamily_X25 = AF_X25,
#endif
  HanzoAddressFamily_IPv6 = AF_INET6,
#ifdef AF_MAX
  HanzoAddressFamily_Max = AF_MAX
#endif
} HanzoAddressFamily;

typedef enum __Protocol_Family
{
  HanzoProtocolFamily_UnSpec = PF_UNSPEC,
#ifdef PF_UNIX
  HanzoProtocolFamily_Unix = PF_UNIX,
#endif
  HanzoProtocolFamily_IPv4 = PF_INET,
#ifdef PF_AX25
  HanzoProtocolFamily_AX25 = PF_AX25,
#endif
#ifdef PF_IPX
  HanzoProtocolFamily_IPX = PF_IPX
#endif
#ifdef PF_APPLETALK
  HanzoProtocolFamily_AppleTalk = PF_APPLETALK,
#endif
#ifdef PF_NETROM
  HanzoProtocolFamily_NetRom = PF_NETROM,
#endif
#ifdef PF_BRIDGE
  HanzoProtocolFamily_Bridge = PF_BRIDGE,
#endif
#ifdef PF_AAL5
  HanzoProtocolFamily_AAL5 = PF_AAL5,
#endif
#ifdef PF_X25
  HanzoProtocolFamily_X25 = PF_X25,
#endif
  HanzoProtocolFamily_IPv6 = PF_INET6,
#ifdef PF_MAX
  HanzoProtocolFamily_Max = PF_MAX
#endif
} HanzoProtocolFamily;

typedef struct __Hanzo_Socket_TCP
{
  int initialized;
  unsigned int port_host;
  HanzoFileStream file_stream;
  HanzoString address_HanzoString;
  HanzoProtocolFamily protocol_family;
  HanzoAddressFamily address_family;
  HanzoSocketAddress server_address;

  int (*Initialize)(struct __Hanzo_Socket_TCP *, HanzoProtocolFamily, HanzoAddressFamily);
  int (*IsInitialized)(struct __Hanzo_Socket_TCP *);
  HanzoFileStream * (*GetFileStream)(struct __Hanzo_Socket_TCP *);
  unsigned int (*GetPort)(struct __Hanzo_Socket_TCP *);
  void (*SetPort)(struct __Hanzo_Socket_TCP *, unsigned int port);
  HanzoProtocolFamily (*GetProtocolFamily)(struct __Hanzo_Socket_TCP *);
  void (*SetProtocolFamily)(struct __Hanzo_Socket_TCP *, HanzoProtocolFamily);
  HanzoAddressFamily (*GetAddressFamily)(struct __Hanzo_Socket_TCP *);
  void (*SeAddressFamily)(struct __Hanzo_Socket_TCP *, HanzoAddressFamily);
  int (*Connect)(struct __Hanzo_Socket_TCP *, const char *, size_t);
  const char * (*GetAddress)(struct __Hanzo_Socket_TCP *);
  void (*Destroy)(struct __Hanzo_Socket_TCP *);
} HanzoSocketTCP;

int HanzoSocketTCP_Initialize
(
  HanzoSocketTCP * socket_tcp,
  HanzoProtocolFamily protocol_family,
  HanzoAddressFamily address_family
);
int HanzoSocketTCP_IsInitialized
(
  HanzoSocketTCP * socket_tcp
);
HanzoFileStream * HanzoSocketTCP_GetFileStream(HanzoSocketTCP * socket_tcp);
unsigned int HanzoSocketTCP_GetPort(HanzoSocketTCP * socket_tcp);
void HanzoSocketTCP_SetPort(HanzoSocketTCP * socket_tcp, unsigned int port);
HanzoProtocolFamily HanzoSocketTCP_GetProtocolFamily(HanzoSocketTCP * socket_tcp);

void HanzoSocketTCP_SetProtocolFamily
(
  HanzoSocketTCP * socket_tcp,
  HanzoProtocolFamily protocol_family
);
HanzoAddressFamily HanzoSocketTCP_GetAddressFamily(HanzoSocketTCP * socket_tcp);
void HanzoSocketTCP_SetAddressFamily
(
  HanzoSocketTCP * socket_tcp,
  HanzoAddressFamily address_family
);
int HanzoSocketTCP_Connect(HanzoSocketTCP * socket_tcp, const char *address, size_t len);
const char *HanzoSocketTCP_GetAddress(HanzoSocketTCP * socket_tcp);
void HanzoSocketTCP_Destroy(HanzoSocketTCP * socket_tcp);

#endif
