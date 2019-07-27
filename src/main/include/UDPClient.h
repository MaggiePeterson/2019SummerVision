
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <frc/DriverStation.h>

#define PORT 5801
#define MAX_BUFF 100000   

class UDPClient{

private:
    int bCastSock = 0;
    int srcaddrSize;
    struct sockaddr_in localUdp; 
    struct sockaddr_in bCastRecv;
    socklen_t addrlen = sizeof(struct sockaddr_in); 
    char  *buffHolder; 
    char *hostIpString;
    const int bCastPort = 5801;
    char buffer[MAX_BUFF] = {0}; 
    struct sockaddr_in serv_addr; 
    ssize_t currPacket;
    double angle;
    double distance;
    bool stopThread = false;
    bool threadFinished = false;
    bool stopAngleThread = false;
    bool stopDistanceThread = false;
    bool isAngleThreadFinished = false;
    bool isDistanceThreadFinished = false;
    std::thread * UDPthread = nullptr;
    std::thread * angleThread = nullptr;
    std::thread * distanceThread = nullptr;
    std::mutex * UDPmutex = new std::mutex;
    
public:

    UDPClient();
    void setup_socket();
    void read(); 
    bool UDPReadThread();
    double getAngle();
    double getDistance();
    void joinUDPThread();
    void stopUDPThread();
    

   
};