#include <iostream> 
#include <string> 
using namespace std;
// comment
void testInput(string input);
void errorMessage(string protocol, string fault);
void printOutput(string protocol, string domain, string port, string filePath, string parameters);

int main() {
 string input;

 cout << "Enter a url" << endl;
 getline(cin, input);
 testInput(input);
 return 0;
}

void testInput(string input) {
 string protocol = "";
 string domain = "";
 string port = "";
 string filePath = "";
 string parameters = "";
 int total = 0;

 // test protocol
 string protocolCheck = input.substr(0,5);

 if( protocolCheck.find("https") != string::npos) {
     protocol = "https";

   } else if( protocolCheck.find("http:") != string::npos) {
     protocol = "http";

   } else if (protocolCheck.find("ftps") != string::npos){
     protocol = "ftps";

   } else if(protocolCheck.find("ftps") != string::npos) {
     protocol = "ftp";

   } else {errorMessage("protocol", protocolCheck);}
 
 total = protocol.length() + 1;
 
  // test domain
 int domainStart = (input.find("//")) + 2; 
 int domainEnd = (input.substr(domainStart).find(":"));
 string domainCheck = input.substr(domainStart, domainEnd);
 
 if( domainCheck.find(".com") != string::npos || domainCheck.find(".net") != string::npos
     || domainCheck.find(".edu") != string::npos || domainCheck.find(".biz") != string::npos
     || domainCheck.find(".gov") != string::npos){
     domain = domainCheck;

   } else {errorMessage("domain", domainCheck);}

 total += domain.length() + 2;
    
  // test port
 if(input.substr(total).find(":") != string::npos){
    int portEnd = (input.substr(total).find("/"));
    string portCheck = input.substr(total+1, portEnd-1);

    if(portCheck >= "1" && portCheck.length() < 5 ||
       portCheck.compare("65535") < 1){

        port = portCheck;
     } else {errorMessage("port", portCheck);}
    total+=portCheck.length() + 1;
   }

// file path
int pathEnd = (input.substr(total).find("?"));
string pathCheck = input.substr(total,pathEnd);

if(pathCheck.substr(0,1) == "/" && pathCheck.find(".html") != string::npos || pathCheck.find(".net") != string::npos){
    filePath = pathCheck;
} 
else {errorMessage("fp", pathCheck);}

total += pathCheck.length();

// parameters
if (total < input.length()) {
string parameterCheck = (input.substr(total));

if(parameterCheck.substr(0,1) == "?"){
    parameters = parameterCheck.substr(1);
  } 
}
 // print
 printOutput(protocol, domain, port, filePath, parameters);

}

void errorMessage (string component, string fault){
 cout << "Invalid URL with following erroneous components: " << endl;
 
 if(component == "protocol") {
    cout << "Protocol: " << fault << " is not a valid protocol." << endl;

  } else if(component == "domain") {
    cout << "Domain: " << fault << " is an invalid domain name." << endl;
 
  }  else if(component == "port") {
    cout << "Port: " << fault << " port must be between 1 and 65535" << endl;

  }  else if(component == "fp") {
    cout << "File path: " << fault << " is an invalid path name" << endl;
  }
}

void printOutput(string protocol, string domain, string port, string filePath, string parameters){
 cout << "Protocol:     " << protocol << endl;
 cout << "Domain:       " << domain << endl;
 cout << "Port:         " << port << endl;
 cout << "File path:    " << filePath << endl;
 cout << "Parameters:   " << parameters << endl;
}




