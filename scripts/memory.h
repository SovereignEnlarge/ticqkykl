#pragma once
#include <Windows.h>
#include <cstdint>

inline bool ReadMem(HANDLE proc, uintptr_t addr, void* buf, size_t size) {
    SIZE_T read = 0;
    return ReadProcessMemory(proc, reinterpret_cast<LPCVOID>(addr), buf, size, &read) && read == size;
}

inline bool WriteMem(HANDLE proc, uintptr_t addr, const void* buf, size_t size) {
    SIZE_T written = 0;
    return WriteProcessMemory(proc, reinterpret_cast<LPVOID>(addr), buf, size, &written) && written == size;
}

template<typename T>
inline T Read(HANDLE proc, uintptr_t addr) {
    T val{};
    ReadMem(proc, addr, &val, sizeof(T));
    return val;
}

template<typename T>
inline bool Write(HANDLE proc, uintptr_t addr, T val) {
    return WriteMem(proc, addr, &val, sizeof(T));
}

inline uintptr_t ResolvePointer(HANDLE proc, uintptr_t base, const std::initializer_list<uintptr_t>& offsets) {
    uintptr_t addr = Read<uintptr_t>(proc, base);
    for (auto it = offsets.begin(); it != offsets.end(); ++it) {
        if (it + 1 == offsets.end()) return addr + *it;
        addr = Read<uintptr_t>(proc, addr + *it);
        if (!addr) return 0;
    }
    return 0;
}
