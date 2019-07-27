#include "UDPClient.h"

UDPClient::UDPClient(){}

void UDPClient::read(){

   do{
        if(stopThread){
           stopThread = false;
           break;
       }

        std::cout << "Waiting for broadcast..." <<std::endl;
        memset(&bCastRecv, '0', sizeof(bCastRecv));
        currPacket = recvfrom(bCastSock, buffer, MAX_BUFF, 0, (struct sockaddr *) &bCastRecv, &addrlen);
        std::istringstream iss(buffer);
        frc::DriverStation::ReportError("String before filled " + iss.str());
        iss >> angle >> distance;
        frc::DriverStation::ReportError("Sttring " + iss.str());
    } while(currPacket != -1); 

    threadFinished = true;


}

bool UDPClient::UDPReadThread(){
    stopThread = false;

    if(UDPthread == nullptr){ //thread has not started
        threadFinished = false;
         UDPthread = new std::thread(&UDPClient::read, this);
         return true;
    }
    if(threadFinished) //If there is a thread but it's done, delete it and make another one
   {
      threadFinished = false;
      joinUDPThread(); //join
      delete UDPthread;
      UDPthread = new std::thread(&UDPClient::read, this);
      return true;
   }
   return false; //If thread already executing, do nothing
}


void UDPClient::setup_socket(){
    if ((bCastSock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) 
    { 
        perror("UDP socket failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (setsockopt(bCastSock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &srcaddrSize, sizeof(srcaddrSize))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    memset(&localUdp, '0', sizeof(serv_addr)); 
    localUdp.sin_family = AF_INET; 
    localUdp.sin_addr.s_addr = INADDR_ANY;
    localUdp.sin_port = htons( bCastPort ); 

    bind(bCastSock, (struct sockaddr *)&localUdp,sizeof(localUdp)); 
}

double UDPClient::getAngle(){
    return angle;
}

double UDPClient::getDistance(){
    return distance;
}

 void UDPClient::joinUDPThread(){
     if(UDPthread == nullptr || !UDPthread->joinable())
        return;

    UDPthread->join();
 }

  void UDPClient::stopUDPThread(){
      joinUDPThread();
      stopThread = false; 
  }