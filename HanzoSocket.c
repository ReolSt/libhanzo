#include "HanzoSocket.h"

int HanzoSocketTCP_Initialize
(
  HanzoSocketTCP * socket_tcp,
  HanzoProtocolFamily protocol_family,
  HanzoAddressFamily address_family
)
{
  memset(&(socket_tcp->server_address), 0, sizeof(socket_tcp->server_address));
  int socket_descriptor = socket(protocol_family, HanzoSocketType_Stream, 0);
  if(socket_descriptor < 0)
  {
    return socket_descriptor;
  }
  HanzoSocketTCP_SetProtocolFamily(socket_tcp, protocol_family);
  HanzoSocketTCP_SetAddressFamily(socket_tcp, address_family);
  HanzoFileStream_Initialize(&(socket_tcp->file_stream), socket_descriptor, "r+");
//function pointers
  socket_tcp->Initialize = HanzoSocketTCP_Initialize;
  socket_tcp->IsInitialized = HanzoSocketTCP_IsInitialized;
  socket_tcp->GetFileStream = HanzoSocketTCP_GetFileStream;
  socket_tcp->GetPort = HanzoSocketTCP_GetPort;
  socket_tcp->SetPort = HanzoSocketTCP_SetPort;
  socket_tcp->GetProtocolFamily= HanzoSocketTCP_GetProtocolFamily;
  socket_tcp->SetProtocolFamily= HanzoSocketTCP_SetProtocolFamily;
  socket_tcp->Connect = HanzoSocketTCP_Connect;
  socket_tcp->GetAddress = HanzoSocketTCP_GetAddress;
  socket_tcp->Destroy = HanzoSocketTCP_Destroy;
//
  socket_tcp->initialized = 1;
  return socket_descriptor;
}

int HanzoSocketTCP_IsInitialized(HanzoSocketTCP * socket_tcp)
{
  return socket_tcp->initialized;
}
HanzoFileStream * HanzoSocketTCP_GetFileStream(HanzoSocketTCP * socket_tcp)
{
  return &(socket_tcp->file_stream);
}

unsigned int HanzoSocketTCP_GetPort(HanzoSocketTCP * socket_tcp)
{
  return socket_tcp->port_host;
}

void HanzoSocketTCP_SetPort(HanzoSocketTCP * socket_tcp, unsigned int port)
{
  switch(socket_tcp->address_family)
  {
    case HanzoAddressFamily_IPv4:
    {
      HanzoSocketAddressIPv4 *server_address = (HanzoSocketAddressIPv4 *)&(socket_tcp->server_address);
      server_address->sin_port = htons(port);
      break;
    }
  }
}

HanzoProtocolFamily HanzoSocketTCP_GetProtocolFamily(HanzoSocketTCP * socket_tcp)
{
  return socket_tcp->protocol_family;
}

void HanzoSocketTCP_SetProtocolFamily
(
  HanzoSocketTCP * socket_tcp,
  HanzoProtocolFamily protocol_family
)
{
  socket_tcp->protocol_family = protocol_family;
}

HanzoAddressFamily HanzoSocketTCP_GetAddressFamily(HanzoSocketTCP * socket_tcp)
{
  return socket_tcp->address_family;
}

void HanzoSocketTCP_SetAddressFamily
(
  HanzoSocketTCP * socket_tcp,
  HanzoAddressFamily address_family
)
{
  socket_tcp->address_family = address_family;
  socket_tcp->server_address.sa_family = address_family;
}

int HanzoSocketTCP_Connect(HanzoSocketTCP * socket_tcp, const char *address, size_t len)
{
  size_t size = 0;
  switch(socket_tcp->address_family)
  {
    case HanzoAddressFamily_IPv4:
    {
      HanzoSocketAddressIPv4 *server_address = (HanzoSocketAddressIPv4 *)&(socket_tcp->server_address);
      server_address->sin_addr.s_addr = inet_addr(address);
      size = sizeof(HanzoSocketAddressIPv4);
      break;
    }
  }
  int result =
    connect(
      HanzoCall(socket_tcp->file_stream, GetDescriptor),
      (struct sockaddr*)&(socket_tcp->server_address),
      sizeof(socket_tcp->server_address)
    );
  if(result < 0)
  {
    return result;
  }
  HanzoString_Initialize(&(socket_tcp->address_HanzoString), address, len);
  return result;
}

const char *HanzoSocketTCP_GetAddress(HanzoSocketTCP * socket_tcp)
{
  return HanzoString_CStr(&(socket_tcp->address_HanzoString));
}

void HanzoSocketTCP_Destroy(HanzoSocketTCP * socket_tcp)
{
  HanzoString_Destroy(&(socket_tcp->address_HanzoString));
  HanzoCall(socket_tcp->file_stream, Destroy);
}

// for test
int main()
{

}
