#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <vector>

struct ProcessInfo {
    DWORD pid;
    std::string name;
    HANDLE handle;
};

inline DWORD FindProcessByName(const std::string& name) {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return 0;

    PROCESSENTRY32 entry{};
    entry.dwSize = sizeof(entry);

    if (Process32First(snap, &entry)) {
        do {
            if (name == entry.szExeFile) {
                CloseHandle(snap);
                return entry.th32ProcessID;
            }
        } while (Process32Next(snap, &entry));
    }

    CloseHandle(snap);
    return 0;
}

inline HANDLE OpenGameProcess(DWORD pid) {
    return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
}

inline std::vector<ProcessInfo> ListRunningProcesses() {
    std::vector<ProcessInfo> result;
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return result;

    PROCESSENTRY32 entry{};
    entry.dwSize = sizeof(entry);

    if (Process32First(snap, &entry)) {
        do {
            result.push_back({ entry.th32ProcessID, entry.szExeFile, nullptr });
        } while (Process32Next(snap, &entry));
    }

    CloseHandle(snap);
    return result;
}
