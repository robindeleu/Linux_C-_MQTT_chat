#include <iostream>
#include <string>
#include <unistd.h>
#include<fstream>
#include<sstream>
#include<stdio.h>
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#include <ctime>
#include "../include/simple_mqtt_client/simple_mqtt_client.h"


using namespace BiosSimpleMqttClient;



class SomeMessageHandler : public IMQTTMessageHandler {
  public:
    void handle_mqtt_message(MQTTMessage mqttMessage) override {
      std::string outputmessage;
      outputmessage = mqttMessage.get_message();
      std::ofstream out("output.txt",std::ios::app);
      out << outputmessage << std::endl;
      out.close();
       std::cout << BOLDRED << outputmessage << RESET << std::endl;
      
      
    }
};

class Drawerbeginner
{
public:
       void printInformation();
       void printWelcomebanner();
       void printLoader();
};

void Drawerbeginner::printInformation()
{
  std::system("clear");

  std::string line;
  std::ifstream myfile ("line1art.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      std::cout << BOLDRED << line << RESET << std::endl;
    }
    std::cout << RED << " " << RESET << std::endl;
    myfile.close();
  }
  else{
    std::cout << "can not open art file 1" << std::endl;
  }

  std::string line2;
  std::ifstream myfile2 ("line2art.txt");
  if (myfile2.is_open())
  {
    while ( getline (myfile2,line2) )
    {
      std::cout << BOLDRED << line2 << RESET << std::endl;
    }
    std::cout << RED << " " << RESET << std::endl;
    myfile2.close();
  }
  else{
    std::cout << "can not open art file 2" << std::endl;
  }

std::cout << RED << "Press Q to quit, first type you're username and then have fun!" << RESET << std::endl;
    
}

void Drawerbeginner::printWelcomebanner()
{
  std::system("clear");

  std::string line;
  std::ifstream myfile ("welcomemessage.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      std::cout << BOLDRED << line << RESET << std::endl;
    }
    std::cout << RED << " " << RESET << std::endl;
    myfile.close();
  }
  else{
    std::cout << "can not open welcome art file" << std::endl;
  }
  
  sleep(5);  
}

void Drawerbeginner::printLoader()
{
  std::system("clear");

  std::string line;
  std::ifstream myfile ("loading.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      std::cout << BOLDRED << line << RESET << std::endl;
    }
    std::cout << RED << " " << RESET << std::endl;
    myfile.close();
  }
  else{
    std::cout << "can not open loading art file" << std::endl;
  }
  int sleeptime = rand() % 4;
  sleep(sleeptime);  
}

class Filehistory
{
public:
       void historyloader();
       void historydelete();
};

void Filehistory::historyloader()
{
  std::string line;
  std::ifstream myfile ("output.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      std::cout << BOLDRED << line << RESET << std::endl;
    }
    std::cout << RED << " " << RESET << std::endl;
    myfile.close();
  }
  else{
    std::cout << "can not open history file" << std::endl;
  }
  
}
void Filehistory::historydelete()
{  
  std::string historydeleter;
  std::cout << RED << "Press delete to delete chat history, press any key to continue" << RESET << std::endl;
  std::cin >> historydeleter;
  if(historydeleter == "delete"){
    std::cout << RED << "History deleted" << RESET << std::endl;
    std::ofstream out("output.txt");
    out << " " << std::endl;
    out.close();
  }
}

const std::string SERVER_ADDRESS("tcp://labict.be:1883");
const std::string CLIENT_ID("ghj489543jghewr");
const std::string TOPIC("test/hello");

int main(int argc, char* argv[])
{ 
  std::string username;
  std::string messagepayload;
  std::string hour;
  std::string minutes;
  std::string seconds;

  Drawerbeginner().printWelcomebanner();
  Drawerbeginner().printLoader();
  Drawerbeginner().printInformation();



	SimpleMQTTClient simpleClient(SERVER_ADDRESS, CLIENT_ID);
  simpleClient.connect();
  
  SomeMessageHandler messageHandler;
  simpleClient.subscribe(TOPIC, &messageHandler);
  sleep(2); 
  std::getline(std::cin, username);
  
  Filehistory().historyloader();
  do{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    hour = std::to_string(ltm->tm_hour);
    minutes = std::to_string(ltm->tm_min);
    seconds = std::to_string(ltm->tm_sec);

    std::string messageuserinput;
    std::getline(std::cin, messageuserinput);
    messagepayload = "[" + username + "]" + " " + messageuserinput + " @ " + hour + ":" + minutes + ":" + seconds;
    
    MQTTMessage message(TOPIC, messagepayload);
  
    simpleClient.publish(message);
	
  }
  while(std::tolower(std::cin.get()) != 'q');

  Filehistory().historydelete();
  
  
  std::cout << RED << "Goodbye, hope to see you back" << RESET << std::endl;
 	return 0;


}
