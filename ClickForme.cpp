/*		
		ClickForme.cpp : Popup Handler for fuzzing Peach
		Date:	 Mar 10  2017	 
		Author : Ermias Bayu,  Addis Ababa,Ethiopia   		
		
		Note : 

		This Code is Specifically Targeted towards MS OFFice - 2007 - WInWord Platform 
		Code wrtten as a support during fuzzing 

*/
#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>

using namespace std;

BOOL CALLBACK GetButtonHandler(HWND handle, LPARAM);

HWND _OpenHandle = 0; //(HWND)(0x02390A86);
HWND _NoHandle = 0;
HWND _ShowHelp = 0;
HWND _YesHandle = 0;
int Control = 0;


void setHandlers(HWND OpenHandle, HWND NoHandle,HWND ShowHelp,HWND YesHandle)
{
    _OpenHandle = OpenHandle;
    _NoHandle = NoHandle;
	_ShowHelp = ShowHelp;
	_YesHandle = YesHandle;
}

BOOL CALLBACK GetButtonHandler(HWND handle, LPARAM)
{
    char label[100];
    int size = GetWindowTextA(handle, label, sizeof(label));

	if(Control == 1 && strcmp(label,"&Recover Data")==0)
	{
		return false;
	}
	if(Control == 4 && strcmp(label, "Show H&elp >>") == 0)
	{
	_ShowHelp = handle;
	return false;
	}
	
	else if (strcmp(label,"&Yes") == 0) {
		_YesHandle = handle;
	}
	else if (strcmp(label, "&No") == 0) {
        _NoHandle = handle;
    }
    else if (strcmp(label, "&Open") == 0) {
        _OpenHandle= handle;
    }

	Control++;
    return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("#-##########################################################\n\r");
	printf("#                                                          #\n\r");
	printf("#    Click4Me : Popup Handler for fuzzing Peach            #\n\r");
	printf("#    Date:	 Mar 10  2017                              #\n\r");
	printf("#    Author :  - Ermias Bayu,  Addis Ababa,Ethiopia        #\n\r");
	printf("#    Peach quick crush monitoring                          #\n\r");
	printf("#                                                          #\n\r");
	printf("#-############### Waching For PopUps #####################-#\n\r");

	
	for (;;) {	
        HWND windowHandle = FindWindowA(NULL, "Microsoft Office Word");
		
		if (windowHandle != 0) {

			BOOL ret = EnumChildWindows(windowHandle, GetButtonHandler, 0);
			
			Control = 0; //Reset Control

			if (_NoHandle != 0 && _ShowHelp == 0) {
				PostMessage(_NoHandle, BM_CLICK, 0, 0);
				SendMessage(_NoHandle, BM_CLICK, 0, 0);
				printf("Safe Mode Dialoge  - Detected - Clicked No\n\r");
				setHandlers(0, 0,0,0); //Reset Handlers
				Sleep(3000);
				
			}
			else if(_ShowHelp != 0 && _NoHandle != 0 )
			{
				PostMessage(_YesHandle, BM_CLICK, 0, 0);
				SendMessage(_YesHandle, BM_CLICK, 0, 0);
				printf("Serious Error Dialoge  - Detected - Clicked Yes\n\r");
				setHandlers(0, 0,0,0);//Reset Handlers
				Sleep(3000);
				
			}
			else if (_OpenHandle != 0 && _ShowHelp == 0) {
				PostMessage(_OpenHandle, BM_CLICK, 0, 0);
				SendMessage(_OpenHandle, BM_CLICK, 0, 0);
				printf("Corrpted File Dialoge  - Detected - Clicked Open\n\r");
				setHandlers(0, 0,0,0); //Reset Handlers
				Sleep(3000);
				
			}
        }
		
    }
}


;