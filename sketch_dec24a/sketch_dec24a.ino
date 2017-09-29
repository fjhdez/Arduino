#include <enc28j60.h>
#include <EtherCard.h>
#include <net.h>

#define STATIC 0  // set to 1 to disable DHCP (adjust myip/gwip values below)
 
#if STATIC
// ethernet interface ip address
static byte myip[] = { 192,168,8,40 };
// gateway ip address
static byte gwip[] = { 192,168,8,1 };
#endif
 
// ethernet mac address - must be unique on your network
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };
 
byte Ethernet::buffer[500]; // tcp/ip send and receive buffer
 
const char page[] PROGMEM =
"HTTP/1.0 503 Service Unavailable\r\n"
"Content-Type: text/html\r\n"
"Retry-After: 600\r\n"
"\r\n"
"&lt;html&gt;"
  "&lt;head&gt;&lt;title&gt;"
    "Service Temporarily Unavailable"
  "&lt;/title&gt;&lt;/head&gt;"
  "&lt;body&gt;"
    "&lt;h3&gt;This service is currently unavailable&lt;/h3&gt;"
    "&lt;p&gt;&lt;em&gt;"
      "The main server is currently off-line.&lt;br /&gt;"
      "Please try again later."
    "&lt;/em&gt;&lt;/p&gt;"
  "&lt;/body&gt;"
"&lt;/html&gt;"
;
 
void setup(){
  Serial.begin(57600);
  Serial.println("\n[backSoon]");
 
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0)
    Serial.println( "Failed to access Ethernet controller");
#if STATIC
  ether.staticSetup(myip, gwip);
#else
  if (!ether.dhcpSetup())
    Serial.println("DHCP failed");
#endif
 
  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);  
  ether.printIp("DNS: ", ether.dnsip);  
}
 
void loop(){
  // wait for an incoming TCP packet, but ignore its contents
  if (ether.packetLoop(ether.packetReceive())) {
    memcpy_P(ether.tcpOffset(), page, sizeof page);
    ether.httpServerReply(sizeof page - 1);
  }
}



