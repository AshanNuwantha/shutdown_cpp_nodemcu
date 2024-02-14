#include <stdio.h>
#define CE_SERIAL_IMPLEMENTATION
#include "ceSerial.h"
#include <bits/stdc++.h>
#include <string>
#include <unistd.h> 
#include <list>
#include <Windows.h>

#define OFF_LOG {'O','F','F'}
#define ON_LOG {'O','N'}

using namespace std;


void readRx_Message(char readChar,char bufferChar[8],bool successFlag);
void shutdownFunction();
void serialConnectionClose();
bool charater_ArrayCompare(char refer[] ,int sizeofArray , char bufferChar[] );
int serialConnecter();


#ifdef CE_WINDOWS
	ceSerial com("\\\\.\\COM9",115200,8,'N',1); // Windows
#else
	ceSerial com("/dev/ttyS0",9600,8,'N',1); // Linux
#endif

int main(){

	serialConnecter();

	bool successFlag = false;
	char readChar;
	char bufferChar[8] , off_Logic[] = OFF_LOG ,on_Logic[] = ON_LOG;
	
	while(true){
		readRx_Message(readChar,bufferChar,successFlag);
	    if( charater_ArrayCompare(off_Logic ,3, bufferChar) ){printf("start os command.. \n"); shutdownFunction();}     
	}
    serialConnectionClose();
	return 0;
}
bool charater_ArrayCompare(char refer[] ,int sizeofArray , char bufferChar[] ){
	bool equalbool= 1;
	for(int index = 0; index < sizeofArray ; index++){
		if(refer[index]==bufferChar[index]){ equalbool = equalbool*1; }else{ equalbool = equalbool*0; }
	}
	return equalbool;
}

void serialConnectionClose(){com.Close();}

int serialConnecter(){
	printf("Opening port %s.\n",com.GetPort().c_str());
	if (com.Open() == 0) {
		printf("connected.\n");
		ceSerial::Delay(3000); // first to wait for a start script
		return 1;
	}else {
		printf("connection fail.\n");
		return 0;
	}
}

void shutdownFunction(){
	#ifdef CE_WINDOWS
		system("shutdown /s /t 0"); // Windows
	#else
		system("sudo shutdown now"); // Linux
	#endif
}

void readRx_Message(char readChar,char bufferChar[],bool successFlag){
	 ceSerial::Delay(600); //delay to wait for a word read
	 bufferChar[0]=bufferChar[1] = bufferChar[2]=bufferChar[3]=bufferChar[4]=bufferChar[5]=bufferChar[6]=bufferChar[7] = '\0'; // SET DEFAULT VALUES 
	    for(int index = 0,asignIndex = 0; index < 8; index++){ 
			readChar = com.ReadChar(successFlag);
			if( (int)readChar > 0X30 && (int)readChar < 0X7A ){ bufferChar[asignIndex] = readChar; asignIndex++;} // ASCII FILTER
			readChar = '\0';	
		}
}



