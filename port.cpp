#include "port.h"
#include <iostream>
#include <stddef.h>
#include "string.h"

const int LENGTH=2;
const int MAX=65535;
const int ONE=1;

Port::Port(String portType):portType(portType){}


bool Port::aux_match(String Value){
    int port_number=(Value.trim()).to_integer();
    if(minPort>port_number || maxPort<port_number){
        return false;
    }
    return true;
}

bool Port::match(String packet){
    size_t size;
    bool value = false;
    String *after_split;

    packet.split("=, ", &after_split, &size);
    if(!size){ 
        delete[] after_split;
        return false;
    }
    for(size_t i = 0; i < size; i+=LENGTH)
    {
        if(portType.equals(after_split[i])){
            value = aux_match(after_split[i+ONE]);
            break;
        }
    }
    delete[] after_split;
    return value;
}

bool Port::set_value(String value){
    char delimiters[ONE]={'-'};
	size_t size =0;
	String *our_string;
	value.split(delimiters,&our_string,&size);

	if((int)size!=LENGTH){
        return false;//split failed
 	}
        int tmpMin = our_string[0].to_integer();
        int tmpMax = our_string[1].to_integer();
        if(tmpMin>=0 && tmpMax<=MAX && tmpMin<=tmpMax){
            minPort= tmpMin ;
            maxPort = tmpMax ;
        }
        else {
            delete[] our_string;
            return false;
        }
    delete[] our_string;
    return true;
}
