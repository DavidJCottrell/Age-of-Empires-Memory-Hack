#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <psapi.h>
#include <iomanip>
#include <vector>
#include "proc.h"

using namespace std;

int main() {

	//Get process ID of game
	DWORD procId = GetProcId(L"Age of Empires II: HD Edition");
	if (procId == NULL) {
		cout << "Could not obtain process ID..." << endl;
		return 1;
	}

	//Get base address from which offsets are used to find the individual memory locations of wood, stone, etc...
	uintptr_t moduleBase = getModuleBaseAddress(procId, L"AoK HD.exe");

	cout << " -------------------------------------------------------------- " << endl << endl;

	cout << "\tBase address = " << "0x" << hex << moduleBase << endl << endl;

	HANDLE hProcess = 0;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
	
	uintptr_t dynamicPtrBaseAddr = moduleBase + 0x006F4170;

	cout << "\tDynamic pointer base address = " << "0x" << hex << dynamicPtrBaseAddr << endl << endl;

	cout << " -------------------------------------------------------------- " << endl << endl;

	//get address of food, wood, stone and gold

	vector<unsigned int> foodOffsets = { 0x134, 0x3C, 0x0 };
	uintptr_t foodAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, foodOffsets);
	cout << "\tFood address = " << "0x" << hex << foodAddr << endl;

	vector<unsigned int> woodOffsets = { 0x134, 0x3C, 0x4 };
	uintptr_t wooddAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, woodOffsets);
	cout << "\tWood address = " << "0x" << hex << wooddAddr << endl;

	vector<unsigned int> stoneOffsets = { 0x134, 0x3C, 0x8 };
	uintptr_t stoneAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, stoneOffsets);
	cout << "\tStone address = " << "0x" << hex << stoneAddr << endl;

	vector<unsigned int> goldOffsets = {0x134, 0x3C, 0xC};
	uintptr_t goldAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, goldOffsets);
	cout << "\tGold address = " << "0x" << hex << goldAddr << endl << endl;

	//get population addresses

	vector<unsigned int> leftPopOffsets = { 0x134, 0x3C, 0x2C };
	uintptr_t leftPopAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, leftPopOffsets);
	cout << "\tLeft population address = " << "0x" << hex << goldAddr << endl;

	vector<unsigned int> rightPopOffsets = { 0x134, 0x3C, 0x10 };
	uintptr_t rightPopAddr = FindDMAAddy(hProcess, dynamicPtrBaseAddr, rightPopOffsets);
	cout << "\tRight population address = " << "0x" << hex << rightPopAddr << endl << endl;

	cout << " -------------------------------------------------------------- " << endl << endl << endl;

	float Gold = 6969;
	float Stone = 6969;
	float Wood = 6969;
	float Food = 6969;
	float RightPop = 351;
	float LeftPop = 69;

	cout << "Values are now frozen. Exit window to un-freeze." << endl;
	
	//Continuously writes to memory addresses prevented them from changing
	while (true) {
		
		//Resources
		WriteProcessMemory(hProcess, (BYTE*)goldAddr, &Gold, sizeof(Gold), nullptr);
		WriteProcessMemory(hProcess, (BYTE*)stoneAddr, &Stone, sizeof(Stone), nullptr);
		WriteProcessMemory(hProcess, (BYTE*)foodAddr, &Food, sizeof(Food), nullptr);
		WriteProcessMemory(hProcess, (BYTE*)wooddAddr, &Wood, sizeof(Wood), nullptr);

		//Population
		WriteProcessMemory(hProcess, (BYTE*)rightPopAddr, &RightPop, sizeof(RightPop), nullptr);
		WriteProcessMemory(hProcess, (BYTE*)leftPopAddr, &LeftPop, sizeof(LeftPop), nullptr);
		
	}

	return 0;
}