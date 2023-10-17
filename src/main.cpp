#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <stdio.h>

using namespace std;

class Bypass{
    public:
        Bypass();
        ~Bypass();
        bool Attach(DWORD pid);
        bool Read(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead = NULL);
        bool Write(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesWritten = NULL);

    private:
        HANDLE m_hProcess = NULL;
};

Bypass::Bypass(){}

Bypass::~Bypass(){
    if(m_hProcess != NULL){
        CloseHandle(m_hProcess);
    }
}

bool Bypass::Attach(DWORD pid){
    m_hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);
    if(m_hProcess != NULL){
        return true;
    }
    return false;
}

bool Bypass::Read(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead){
    if(ReadProcessMemory(m_hProcess, (LPCVOID)lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead)){
        return true;
    }
    return false;
}

bool Bypass::Write(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesWritten){
    if(WriteProcessMemory(m_hProcess, (LPVOID)lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten)){
        return true;
    }
    return false;
}



int main(){
    DWORD pid = 0;
    cout << "Enter PID: ";
    cin >> dec >> pid;

    Bypass* bypass = new Bypass();
    if(!bypass->Attach(pid)){
        cout << "OpenProcess Fail. GetLastError = " << dec << GetLastError() << endl;
        system("pause");
        return EXIT_FAILURE;
    }

	// Prompting user for memory address to overwrite
	uintptr_t memoryAddress = 0x0;
	cout << "Memory address of the integer to overwrite (in hexadecimal): 0x";
	cin >> hex >> memoryAddress;

    // Prompting user for integer value to overwrite
	int intToWrite = 0;
	cout << "Integer to write (in decimal): ";
	cin >> dec >> intToWrite;
 
	// Overwriting the integer in the other process
	if (!bypass->Write(memoryAddress, &intToWrite, sizeof(int))) {
		cout << "WriteProcessMemory failed. GetLastError = " << dec << GetLastError() << endl;
		system("pause");
		return EXIT_FAILURE;
	}
 
	cout << "Overwritten successfully" << endl;
 
	cout << "Press ENTER to quit." << endl;
	system("pause > nul");
 
	delete bypass;
 
	return EXIT_SUCCESS;


}