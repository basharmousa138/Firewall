#include "string.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <iostream>

// now we declare true and false to use them in some functions //

const int TRUE = 1;
const int FALSE = 0;

const int ONE = 1;

String::String() {        //default constructor 

	length = 1;
	data = new char[1];  
	data[0] = '\0';   //empty string//    
}


        
String::String(const String& str) {     //copy consructor from string

	length = str.length;
	data = new char[length+1];
	strcpy(data, str.data);
	data[length-1] = '\0';
}




String:: String(const char *str){
	length=strlen(str)+ 1;//+1 because we need a place for the '\0'
	data=new char[length];
	strcpy(data,str);
	data[length-1]='\0';
}


String::~String() {        //destructor

	delete[] data;
}


String &String::operator=(const String& rhs) {

	if (this != &rhs) {

		delete[] data;
		length = rhs.length;
		data = new char[length+1];
		strcpy(data, rhs.data);
	}
	return *this;
}


String &String::operator=(const char* str) {

	if (data == NULL) {

		delete[] data;
	}
		 length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
        return *this;
	
	return *this;
}


bool String::equals(const String& rhs) const {

	if (rhs.length != this->length) {
		return FALSE;
	}
	if (strcmp(rhs.data,this->data))
	{
		return FALSE;
	}
	return TRUE;
}

bool String::equals(const char *rhs) const{	
	if(this->length != (strlen(rhs)+1)){
		return FALSE;
		}
	for(int i=0;i<(int)strlen(rhs);i++){
		if(this->data[i] != rhs[i]){
			return FALSE;
		}
		}
	return TRUE;		
}	


void copy_aux(const char* string, String** output, int first, int end, int tmp) {
    int our_len = end - first - 1;
    char* our_string = new char[our_len + 1];
    int index = 0;
    for (int i = first + 1; i < end; ++i) {
        our_string[index++] = string[i];
    }
    our_string[index] = '\0';
    (*output)[tmp] = String(our_string);
    delete[] our_string;
}



void String::split(const char* delimiters, String** output, size_t* size)
const {
	if (delimiters == NULL || size == NULL)
	{
		return;
	}
	if (this->data == NULL)
	{
		output = NULL;
		size = 0;
		return;
	}

	size_t counter = 0; //counter for how many delimiters
	int len = ((int)this->length);
	int total_deli = ((int)strlen(delimiters));
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < total_deli; j++) {
			if (this->data[i] == delimiters[j])
			{
				counter++;
			}
		}
	}
	// in this two for we counted how many delimiters are
	// in this so we now know how long the output will be

	//now we meet the demand:
	//If "output" is set to NULL, do not allocated memory
	//only compute "size".


	if (output == NULL)
	{
		*size = counter + 1;
		return;
	}

	// now we split the strings //

	*output = new String[counter + 1];
	int first = -1;
	int tmp = 0;
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < total_deli; j++) {
			if (this->data[i] == delimiters[j]) {
				copy_aux(this->data, output, first, i, tmp);
				first = i; //to know where to start in the next splited string
				tmp++; // to the next element in the output array
			}
		}
	}
	// now we print the last string 
	copy_aux(this->data, output, first, len, tmp);
	*size = counter + 1;
	return;
}


// we needed a helper function that copy the splited string
//to the output 
// our_len is the length of the splited string
// our_string is new char allocated with length of the splited string 
// we delete our_string in the end 



int String::to_integer() const {

	return atoi(this->data);
}


String String::trim() const {
	
	String clean_string;
	clean_string = String(this->data);

	for (int i = 0; i < (int)this->length;++i) {
		if (clean_string.data[i] == ' ') {
		     
			 	int j=i;
			      int k = i+ONE;
	              for (j,k; j < (int)this->length;++j,++k) {

	
				     clean_string.data[j] = clean_string.data[k];
			}
		}
	}
	return clean_string;
}
