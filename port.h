#ifndef PORT_H
#define PORT_H


#include "generic-field.h"
#include "string.h"


const int LEN_PORT = 2 ;

class Port : public GenericField {
String portType;
int minPort;
int maxPort;


 public:
 Port (String portType);
 bool set_value(String value);
 bool aux_match(String Input);
 bool match(String packet);
};

#endif
