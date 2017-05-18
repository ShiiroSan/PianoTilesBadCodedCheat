// PianoTilesC++Cheat.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <bitset>
#include <sstream>
#include <algorithm>    // std::transform

using namespace std;
COLORREF centerColor;
POINT cent;
INPUT    Input = { 0 };

void LeftClickDown()
{
	// left down 
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));
}

void LeftClickUp()
{
	// left up
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));
}
void LeftClick(int x, int y)
{
	SetCursorPos(x, y);
	LeftClickDown();
	//Sleep(5);
	LeftClickUp();
}

string RGBHex(int decimalColor);
short int mouseposX[4] = {1055, 1150, 1240, 1330};
short int mouseposY = 350;
int main()
{
	HDC hdc_ = GetDC(NULL);  //I'm not sure if this is right or what exactly it does.
	BOOL gonnaCheat = false;
	POINT pt;
	do
	{
		GetCursorPos(&pt);
		cout << "CursorX:" << pt.x << "			CursorY: " << pt.y << endl;
		if (GetAsyncKeyState(VK_F1))
		{
			gonnaCheat = !gonnaCheat;
		}
		Sleep(1);
	} while (!gonnaCheat);
	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		for (int i = 0; i < 4; i++)
		{
			centerColor = GetPixel(hdc_, mouseposX[i], mouseposY);
			//cout << centerColor << endl;
			if (centerColor==0)
			{
				LeftClick(mouseposX[i], mouseposY);
			}
			if ((centerColor == 131328) || (centerColor == 131329) || (centerColor == 197120) || (centerColor == 328448))
			{
				LeftClick(mouseposX[i], mouseposY);
			}
			Sleep(1);
		}
		Sleep(1);
		//mouseposY = 200;
	}
	return 0;
}

string decToHex(int valueToConvert)
{
	std::stringstream ss("");
	ss << std::hex << valueToConvert;
	std::string hex(ss.str());
	transform(hex.begin(), hex.end(), hex.begin(), ::toupper);
	return hex;
}

string RGBHex(int decimalColor)
{
	short int redColor = GetRValue(decimalColor);
	short int greenColor = GetGValue(decimalColor);
	short int blueColor = GetBValue(decimalColor);
	string redHex = decToHex(redColor);
	string greenHex = decToHex(greenColor);
	string blueHex = decToHex(blueColor);
	string hex = redHex + greenHex + blueHex;
	return "0x" + hex;
}