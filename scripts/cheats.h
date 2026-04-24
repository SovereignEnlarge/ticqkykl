#pragma once
#include "memory.h"
#include "process.h"

// Offsets — update after each game patch
namespace Offsets {
    constexpr uintptr_t BaseModule  = 0x0;        // CrimsonDesert.exe base
    constexpr uintptr_t HP          = 0x0;
    constexpr uintptr_t Stamina     = 0x0;
    constexpr uintptr_t Mana        = 0x0;
    constexpr uintptr_t Silver      = 0x0;
}

class CheatEngine {
public:
    explicit CheatEngine(HANDLE proc) : m_proc(proc) {}

    void GodMode(bool enable) {
        if (!m_proc) return;
        float val = enable ? 99999.0f : 0.0f;
        Write<float>(m_proc, Offsets::HP, val);
    }

    void InfiniteStamina(bool enable) {
        if (!m_proc) return;
        float val = enable ? 99999.0f : 0.0f;
        Write<float>(m_proc, Offsets::Stamina, val);
    }

    void InfiniteMana(bool enable) {
        if (!m_proc) return;
        float val = enable ? 99999.0f : 0.0f;
        Write<float>(m_proc, Offsets::Mana, val);
    }

    void InfiniteSilver(bool enable) {
        if (!m_proc) return;
        int64_t val = enable ? 999999999LL : 0LL;
        Write<int64_t>(m_proc, Offsets::Silver, val);
    }

    float GetHP()      { return Read<float>(m_proc, Offsets::HP); }
    float GetStamina() { return Read<float>(m_proc, Offsets::Stamina); }
    float GetMana()    { return Read<float>(m_proc, Offsets::Mana); }

private:
    HANDLE m_proc;
};
