// NFS Multilingual Support: restores the Asian and Russian language entries
// EA cut from Most Wanted 1.3 (speed.exe) and Carbon 1.4 (nfsc.exe).
// Every site is byte-verified against the expected original bytes first; a
// mismatching host is left completely untouched. MW.h / Carbon.h describe the
// per-game layout and are included after the shared types below.
#include "framework.h"
#include <cstdint>
#include <vector>

// image range check
static bool InImage(const uint8_t* base, uint32_t rva, size_t len)
{
    const auto* dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
    if (dos->e_magic != IMAGE_DOS_SIGNATURE)
        return false;
    const auto* nt = reinterpret_cast<const IMAGE_NT_HEADERS32*>(base + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE)
        return false;
    return rva <= nt->OptionalHeader.SizeOfImage &&
           len <= nt->OptionalHeader.SizeOfImage - rva;
}

struct DwordRef   // an immediate32 referencing the language table
{
    uint32_t rva;
    uint8_t  preLen;
    uint8_t  pre[5];
    uint32_t oldValue;
};

struct BytePatch  // an equal-length in-place byte replacement
{
    uint32_t rva;
    uint8_t  original[8];
    uint8_t  replacement[8];
    uint8_t  len;
};

struct LangEntry
{
    uint32_t    id;
    const char* name;      // feeds font-name matching and memcard/LOCALE_<name>.loc
    const char* paths[3];
};

struct RegRef  // a column base of the registry language-name table (name/id/region)
{
    uint32_t rva;
    uint8_t  preLen;
    uint8_t  pre[5];
    uint32_t oldValue;
    int      column;       // 0 = name base, 1 = id base (+4), 2 = region base (+8)
};

struct RegAppend  // registry mapping appended for Russian
{
    const char* name;
    uint32_t    id;
    uint32_t    region;
};

struct AuxRef  // an immediate referencing newTable + delta
{
    uint32_t rva;
    uint8_t  preLen;
    uint8_t  pre[5];
    uint32_t oldValue;
    uint32_t delta;
};

struct PSPathFix  // restores the paths of a copied ProStreet row
{
    int         index;
    const char* paths[4];
};

struct PSNewEntry  // a ProStreet row appended after the originals
{
    uint32_t    id;
    const char* name;
    const char* code;
    const char* paths[4];
};

struct GameDef
{
    const char* title;
    uint32_t fingerprintRva;
    const uint8_t* fingerprint;
    size_t fingerprintSize;
    uint32_t tableRva;
    int origEntries, entryStride, totalEntries;
    uint32_t countRva;
    int oldCount, newCount;
    uint32_t texListRva, code3Rva;
    const LangEntry* newEntries;
    int newEntryCount;
    const RegRef* regRefs;
    int regRefCount;
    uint32_t registryRva;          // original registry name table (name/id/region triples)
    int registryEntries;
    const RegAppend* registryAppend;
    const DwordRef* baseRefs;
    int baseRefCount;
    const DwordRef* endRefs;
    int endRefCount;
    const BytePatch* bytePatches;
    int bytePatchCount;
    const AuxRef* auxRefs;
    int auxRefCount;
    const PSPathFix* psPathFix;    // ProStreet: restore a defused row's paths
    const PSNewEntry* psNewEntries;
    int psNewEntryCount;
    uint32_t psSharedRva, psPerLangRva;
};

#include "MW.h"
#include "Carbon.h"
#include "PS.h"

static void WriteBytes(uint8_t* base, uint32_t rva, const void* data, size_t len)
{
    DWORD oldProtect = 0;
    if (!VirtualProtect(base + rva, len, PAGE_EXECUTE_READWRITE, &oldProtect))
        return;
    memcpy(base + rva, data, len);
    DWORD restored = 0;
    VirtualProtect(base + rva, len, oldProtect, &restored);
}

// copies the original table and appends the rebuilt entries
static uint8_t* BuildTable(uint8_t* base, const GameDef& g)
{
    uint8_t* table = static_cast<uint8_t*>(VirtualAlloc(
        nullptr, size_t(g.totalEntries) * g.entryStride, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
    if (!table)
        return nullptr;

    memcpy(table, base + g.tableRva, size_t(g.origEntries) * g.entryStride);

    if (g.psNewEntries)
    {
        if (g.psPathFix)
        {
            uint32_t* row = reinterpret_cast<uint32_t*>(table + size_t(g.psPathFix->index) * g.entryStride);
            for (int i = 0; i < 4; ++i)
                row[3 + i] = uint32_t(uintptr_t(g.psPathFix->paths[i]));
        }
        for (int i = 0; i < g.psNewEntryCount; ++i)
        {
            const PSNewEntry& src = g.psNewEntries[i];
            uint32_t* entry = reinterpret_cast<uint32_t*>(table + size_t(g.origEntries + i) * g.entryStride);
            entry[0] = src.id;
            entry[1] = uint32_t(uintptr_t(src.name));
            entry[2] = uint32_t(uintptr_t(src.code));
            for (int p = 0; p < 4; ++p)
                entry[3 + p] = uint32_t(uintptr_t(src.paths[p]));
            entry[7] = uint32_t(uintptr_t(base) + g.psSharedRva);
            entry[8] = uint32_t(uintptr_t(base) + g.psPerLangRva);
        }
        return table;
    }

    const uint32_t texList = uint32_t(uintptr_t(base) + g.texListRva);
    const uint32_t code3 = uint32_t(uintptr_t(base) + g.code3Rva);
    for (int i = 0; i < g.newEntryCount; ++i)
    {
        const LangEntry& src = g.newEntries[i];
        uint32_t* entry = reinterpret_cast<uint32_t*>(table + size_t(g.origEntries + i) * g.entryStride);
        int slots = g.entryStride / 4 - 3;
        entry[0] = src.id;
        entry[1] = uint32_t(uintptr_t(src.name));
        for (int s = 0; s < slots - 1; ++s)
            entry[2 + s] = uint32_t(uintptr_t(src.paths[s]));
        entry[2 + slots - 1] = texList;
        entry[2 + slots] = code3;
    }
    return table;
}

// relocates the registry name table and appends the Russian mapping
static uint8_t* BuildRegistry(uint8_t* base, const GameDef& g)
{
    uint8_t* reg = static_cast<uint8_t*>(VirtualAlloc(
        nullptr, size_t(g.registryEntries) * 12 + 24, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
    if (!reg)
        return nullptr;

    memcpy(reg, base + g.registryRva, size_t(g.registryEntries) * 12);

    uint8_t* tail = reg + size_t(g.registryEntries) * 12;
    uint32_t name = uint32_t(uintptr_t(g.registryAppend->name));
    memcpy(tail, &name, 4);
    memcpy(tail + 4, &g.registryAppend->id, 4);
    memcpy(tail + 8, &g.registryAppend->region, 4);
    memset(tail + 12, 0, 12); // terminator: empty name
    return reg;
}

// patches references/byte sites/count with rollback on failure
static bool ApplyReferences(uint8_t* base, const GameDef& g,
                            uint32_t newTable, uint32_t newEnd,
                            uint32_t newRegistry)
{
    std::vector<std::pair<uint32_t, std::vector<uint8_t>>> undo;

    auto write = [&](uint32_t rva, const void* data, size_t len) {
        undo.push_back({ rva, std::vector<uint8_t>(static_cast<const uint8_t*>(data),
                                                   static_cast<const uint8_t*>(data) + len) });
        DWORD oldProtect = 0;
        if (!VirtualProtect(base + rva, len, PAGE_EXECUTE_READWRITE, &oldProtect))
            return false;
        memcpy(base + rva, data, len);
        DWORD restored = 0;
        VirtualProtect(base + rva, len, oldProtect, &restored);
        return true;
    };

    uint32_t count = g.newCount;
    for (int i = 0; i < g.baseRefCount && write(g.baseRefs[i].rva, &newTable, 4); ++i);
    for (int i = 0; i < g.endRefCount && write(g.endRefs[i].rva, &newEnd, 4); ++i);
    bool complete = undo.size() == size_t(g.baseRefCount + g.endRefCount);
    for (int i = 0; complete && i < g.auxRefCount; ++i)
    {
        uint32_t value = newTable + g.auxRefs[i].delta;
        complete = write(g.auxRefs[i].rva, &value, 4);
    }
    complete = undo.size() == size_t(g.baseRefCount + g.endRefCount + g.auxRefCount);
    for (int i = 0; complete && i < g.bytePatchCount; ++i)
        complete = write(g.bytePatches[i].rva, g.bytePatches[i].replacement, g.bytePatches[i].len);
    if (complete && g.countRva)
        complete = write(g.countRva, &count, 4);
    for (int i = 0; complete && i < g.regRefCount; ++i)
    {
        const RegRef& r = g.regRefs[i];
        uint32_t value = newRegistry + uint32_t(r.column) * 4;
        complete = write(r.rva, &value, 4);
    }

    if (!complete)
    {
        for (size_t i = undo.size(); i-- > 0;)
            WriteBytes(base, undo[i].first, undo[i].second.data(), undo[i].second.size());
    }
    return complete;
}

static bool TryApply(uint8_t* base, const GameDef& g)
{
    bool inImage = InImage(base, g.fingerprintRva, g.fingerprintSize) &&
                   InImage(base, g.tableRva, size_t(g.origEntries) * g.entryStride) &&
                   (!g.countRva || InImage(base, g.countRva, 4)) &&
                   (!g.registryRva || InImage(base, g.registryRva, size_t(g.registryEntries) * 12));
    for (int i = 0; inImage && i < g.baseRefCount; ++i)
        inImage = InImage(base, g.baseRefs[i].rva, 4);
    for (int i = 0; inImage && i < g.endRefCount; ++i)
        inImage = InImage(base, g.endRefs[i].rva, 4);
    for (int i = 0; inImage && i < g.auxRefCount; ++i)
        inImage = InImage(base, g.auxRefs[i].rva, 4);
    for (int i = 0; inImage && i < g.bytePatchCount; ++i)
        inImage = InImage(base, g.bytePatches[i].rva, g.bytePatches[i].len);
    for (int i = 0; inImage && i < g.regRefCount; ++i)
        inImage = InImage(base, g.regRefs[i].rva, 4);
    if (!inImage)
        return false;

    if (memcmp(base + g.fingerprintRva, g.fingerprint, g.fingerprintSize) != 0 ||
        memcmp(base + g.tableRva, "\0\0\0\0", 4) != 0 ||
        (g.countRva && memcmp(base + g.countRva, &g.oldCount, 4) != 0) ||
        (g.registryRva && memcmp(base + g.registryRva, "\0\0\0\0", 4) == 0))
        return false;
    for (int i = 0; i < g.baseRefCount; ++i)
        if (memcmp(base + g.baseRefs[i].rva - g.baseRefs[i].preLen,
                   g.baseRefs[i].pre, g.baseRefs[i].preLen) != 0 ||
            memcmp(base + g.baseRefs[i].rva, &g.baseRefs[i].oldValue, 4) != 0)
            return false;
    for (int i = 0; i < g.endRefCount; ++i)
        if (memcmp(base + g.endRefs[i].rva - g.endRefs[i].preLen,
                   g.endRefs[i].pre, g.endRefs[i].preLen) != 0 ||
            memcmp(base + g.endRefs[i].rva, &g.endRefs[i].oldValue, 4) != 0)
            return false;
    for (int i = 0; i < g.bytePatchCount; ++i)
        if (memcmp(base + g.bytePatches[i].rva, g.bytePatches[i].original, g.bytePatches[i].len) != 0)
            return false;
    for (int i = 0; i < g.regRefCount; ++i)
        if (memcmp(base + g.regRefs[i].rva - g.regRefs[i].preLen,
                   g.regRefs[i].pre, g.regRefs[i].preLen) != 0 ||
            memcmp(base + g.regRefs[i].rva, &g.regRefs[i].oldValue, 4) != 0)
            return false;

    uint8_t* table = BuildTable(base, g);
    if (!table)
        return false;
    uint8_t* registry = g.registryRva ? BuildRegistry(base, g) : nullptr;
    if (g.registryRva && !registry)
    {
        VirtualFree(table, 0, MEM_RELEASE);
        return false;
    }

    const uint32_t newTable = uint32_t(uintptr_t(table));
    const uint32_t newEnd = newTable + uint32_t(g.totalEntries * g.entryStride);
    return ApplyReferences(base, g, newTable, newEnd, uint32_t(uintptr_t(registry)));
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    if (reason != DLL_PROCESS_ATTACH)
        return TRUE;
    DisableThreadLibraryCalls(module);
    (void)module;
    (void)reserved;

    uint8_t* base = reinterpret_cast<uint8_t*>(GetModuleHandleA(nullptr));
    if (TryApply(base, MW_GAME))
        return TRUE;
    if (TryApply(base, CARBON_GAME))
        return TRUE;
    TryApply(base, PS_GAME);
    return TRUE;
}
