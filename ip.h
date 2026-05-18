#ifndef IP_H
#define IP_H
#include "string.h"
#include "generic-field.h"
const int POINTS = 4;  // there are 4 bytes in the ip address

class ip : public GenericField {

	String ipType;
	int subnet_mask;
	int ruleIP[POINTS];
	bool aux_match(String temp);

public :

	ip(String ipType);  //constructor
	bool match(String packet);
	bool set_value(String value);
};

#endif
