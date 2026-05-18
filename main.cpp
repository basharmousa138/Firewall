#include <iostream>
#include "port.h"
#include "ip.h"
#include "input.h"
#include "string.h"


const int ERROR = -1;
const int ONE =1;
const int LENGTH=2;


int main(int argc, char ** argv)
{

    if(check_args(argc,argv))
    {
        return ERROR;
    }

    // now we prepare the split variables//
    size_t size =0;
    String *splited_array;
    char delimiters[LENGTH]={'=',','};
   
    String trim_array = String(argv[ONE]);
  	trim_array = trim_array.trim();
    
    trim_array.split(delimiters,&splited_array,&size);
    
       // now we check what is the string in the splited array 
       // 
    if(splited_array[0].equals("src-port"))
    {
    	Port SP("src-port");    // sp = source port
        SP.set_value(splited_array[ONE]);
        parse_input(SP);
    }
    
    if(splited_array[0].equals("src-ip"))
    {
    	ip SI("src-ip");  // si = source ip
        SI.set_value(splited_array[ONE]);
        parse_input(SI);
    }

    if(splited_array[0].equals("dst-port"))
    {
    	Port DP("dst-port");    // dp = dest port
        DP.set_value(splited_array[ONE]);
        parse_input(DP);
    }
 
    if(splited_array[0].equals("dst-ip"))
    {
    	ip DI("dst-ip");   // di = dest ip
        DI.set_value(splited_array[ONE]);
        parse_input(DI);
    }
    delete[] splited_array;

    return 0;
}
