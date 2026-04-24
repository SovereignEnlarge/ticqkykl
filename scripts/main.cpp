#include "cheats.h"
#include <iostream>

constexpr const char* GAME_PROCESS = "CrimsonDesert.exe";

int main() {
    std::cout << "=== Crimson Desert Cheat Table ===\n\n";

    DWORD pid = FindProcessByName(GAME_PROCESS);
    if (!pid) {
        std::cerr << "[!] Game process not found. Launch Crimson Desert first.\n";
        std::cin.get();
        return 1;
    }

    HANDLE proc = OpenGameProcess(pid);
    if (!proc) {
        std::cerr << "[!] Failed to open process. Try running as Administrator.\n";
        std::cin.get();
        return 1;
    }

    std::cout << "[+] Attached to " << GAME_PROCESS << " (PID: " << pid << ")\n\n";

    CheatEngine cheat(proc);

    int choice = 0;
    while (true) {
        std::cout << "------------------------------\n";
        std::cout << "[1] God Mode\n";
        std::cout << "[2] Infinite Stamina\n";
        std::cout << "[3] Infinite Mana\n";
        std::cout << "[4] Infinite Silver\n";
        std::cout << "[0] Exit\n";
        std::cout << "------------------------------\n";
        std::cout << "> ";
        std::cin >> choice;

        switch (choice) {
            case 1: cheat.GodMode(true);         std::cout << "[+] God Mode ON\n";         break;
            case 2: cheat.InfiniteStamina(true);  std::cout << "[+] Infinite Stamina ON\n";  break;
            case 3: cheat.InfiniteMana(true);     std::cout << "[+] Infinite Mana ON\n";     break;
            case 4: cheat.InfiniteSilver(true);   std::cout << "[+] Infinite Silver ON\n";   break;
            case 0: CloseHandle(proc); return 0;
            default: std::cout << "[!] Unknown option\n"; break;
        }
    }
}
