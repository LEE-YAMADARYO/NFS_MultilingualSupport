#pragma once
// Need for Speed: Carbon v1.4 (nfsc.exe), western build.
//
// LanguageInfoTable @ .data 0x65EAC0: 13 entries x 28 bytes
//   { id, name*, globalBin*, frontendBin*, ingameBin*, textureStruct*, numberFormatCode* }
// CurrentLanguage @ 0x65EC2C doubles as the lookup loops' table end;
// language count @ 0x65EC30 = max language id + 1.
// Registry name table @ .data 0x665588: 19 x { name*, id, region } + terminator.
// eLanguages: 0 ENGLISH 1 FRENCH 2 GERMAN 3 ITALIAN 4 SPANISH 5 DUTCH
//   6 SWEDISH 7 DANISH 8 HUNGARIAN 9 CZECH 10 MEXICAN 11 KOREAN
//   12 CHINESE_TRAD 13 CHINESE_SIMP 14 JAPANESE 16 THAI 17 POLISH 18 FINNISH
//   19 RUSSIAN (appended by this plugin)

// LoadLanguageResources prologue
static const uint8_t carbonFingerprint[] = { 0x8B, 0x0D, 0x2C, 0xEC, 0xA5, 0x00 };

static const DwordRef carbonBaseRefs[] = {
    { 0x178007, 1, { 0xB9 },                       0x00A5EAC0 },
    { 0x178037, 1, { 0xB9 },                       0x00A5EAC0 },
    { 0x17807A, 1, { 0xB8 },                       0x00A5EAC0 },
    { 0x1782AB, 1, { 0xB8 },                       0x00A5EAC0 },
    { 0x183BF9, 1, { 0xB9 },                       0x00A5EAC0 },
    { 0x185BF7, 1, { 0xB9 },                       0x00A5EAC0 },
    { 0x188CC6, 1, { 0xB8 },                       0x00A5EAC0 },
    { 0x1936E1, 1, { 0xB9 },                       0x00A5EAC0 },
    { 0x178027, 4, { 0x6B, 0xC0, 0x1C, 0x05 },     0x00A5EAC0 },
    { 0x17805A, 4, { 0x6B, 0xC0, 0x1C, 0x05 },     0x00A5EAC0 },
    { 0x183CF8, 4, { 0x6B, 0xC0, 0x1C, 0x05 },     0x00A5EAC0 },
    { 0x185C42, 4, { 0x6B, 0xC0, 0x1C, 0x05 },     0x00A5EAC0 },
    { 0x1936FB, 4, { 0x6B, 0xC0, 0x1C, 0x05 },     0x00A5EAC0 },
    { 0x1780CA, 5, { 0x6B, 0xC9, 0x1C, 0x81, 0xC1 }, 0x00A5EAC0 },
    { 0x17831F, 5, { 0x6B, 0xF6, 0x1C, 0x81, 0xC6 }, 0x00A5EAC0 },
    { 0x188DFD, 5, { 0x6B, 0xF6, 0x1C, 0x81, 0xC6 }, 0x00A5EAC0 },
};

static const DwordRef carbonEndRefs[] = {
    { 0x17801A, 2, { 0x81, 0xF9 }, 0x00A5EC2C },
    { 0x17804A, 2, { 0x81, 0xF9 }, 0x00A5EC2C },
    { 0x17808A, 1, { 0x3D },       0x00A5EC2C },
    { 0x1780BD, 1, { 0x3D },       0x00A5EC2C },
    { 0x1782B9, 1, { 0x3D },       0x00A5EC2C },
    { 0x183C0E, 2, { 0x81, 0xF9 }, 0x00A5EC2C },
    { 0x185C0A, 2, { 0x81, 0xF9 }, 0x00A5EC2C },
    { 0x188CDD, 1, { 0x3D },       0x00A5EC2C },
    { 0x1936EF, 2, { 0x81, 0xF9 }, 0x00A5EC2C },
};

static const BytePatch carbonBytePatches[] = {
    // InitLocalization pool head-room: 0x37FC8 -> 0x1400000
    { 0x1780EC, { 0x81, 0xC6, 0xC8, 0x7F, 0x03, 0x00 },
                { 0x81, 0xC6, 0x00, 0x00, 0x40, 0x01 }, 6 },

    // The MenuScreen base class dereferences a "randomizing strings" helper at
    // this+0x20 that nothing initializes (raw allocation poison for the loading
    // screen, movie id 0xFF for the FEAnyMovie screen). Four ungated paths
    // crash on it with Asian/Russian packages. Each gate below becomes an
    // unconditional skip - equal length, no writes to +0x20, branch always
    // taken - disabling a purely cosmetic text-scramble effect.

    // per-frame tick: mov eax,[esi+20h]; test eax,eax -> xor eax,eax; nops
    { 0x1A1A3E, { 0x8B, 0x46, 0x20, 0x85, 0xC0 },
                { 0x31, 0xC0, 0x90, 0x90, 0x90 }, 5 },
    // tick "done?" branch: mov ecx,[esi+20h]; call sub_577490 -> xor al,al; nops
    { 0x1A1A98, { 0x8B, 0x4E, 0x20, 0xE8, 0xF0, 0x59, 0xFD, 0xFF },
                { 0x32, 0xC0, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }, 8 },
    // "start randomizing" helper: mov eax,[ecx+20h]; test eax,eax
    //   -> xor eax,eax; nop; test eax,eax
    { 0x19A1A0, { 0x8B, 0x41, 0x20, 0x85, 0xC0, 0x74, 0x58 },
                { 0x31, 0xC0, 0x90, 0x85, 0xC0, 0x74, 0x58 }, 7 },
    // screen destructor: mov edi,[esi+20h]; test edi,edi
    //   -> xor edi,edi; nop; test edi,edi
    { 0x1B13F6, { 0x8B, 0x7E, 0x20, 0x85, 0xFF },
                { 0x31, 0xFF, 0x90, 0x85, 0xFF }, 5 },
};

static const LangEntry carbonNewEntries[] = {
    { 11, "KOREAN",
      { "LANGUAGES\\KOREAN_GLOBAL.BIN", "LANGUAGES\\KOREAN_FRONTEND.BIN", "LANGUAGES\\KOREAN_INGAME.BIN" } },
    { 12, "traditional_chinese",
      { "LANGUAGES\\CHINESE_TRAD_GLOBAL.BIN", "LANGUAGES\\CHINESE_TRAD_FRONTEND.BIN", "LANGUAGES\\CHINESE_TRAD_INGAME.BIN" } },
    { 13, "simplified_chinese",
      { "LANGUAGES\\CHINESE_SIMP_GLOBAL.BIN", "LANGUAGES\\CHINESE_SIMP_FRONTEND.BIN", "LANGUAGES\\CHINESE_SIMP_INGAME.BIN" } },
    { 14, "JAPANESE",
      { "LANGUAGES\\JAPANESE_GLOBAL.BIN", "LANGUAGES\\JAPANESE_FRONTEND.BIN", "LANGUAGES\\JAPANESE_INGAME.BIN" } },
    { 16, "THAI",
      { "LANGUAGES\\THAI_GLOBAL.BIN", "LANGUAGES\\THAI_FRONTEND.BIN", "LANGUAGES\\THAI_INGAME.BIN" } },
    { 19, "RUSSIAN",
      { "LANGUAGES\\RUSSIAN_GLOBAL.BIN", "LANGUAGES\\RUSSIAN_FRONTEND.BIN", "LANGUAGES\\RUSSIAN_INGAME.BIN" } },
};

// registry name table: repoint name/id/region column bases (sub_7346B0)
static const RegRef carbonRegRefs[] = {
    { 0x3348FC, 1, { 0xA1 },       0x00A65588, 0 },
    { 0x334905, 1, { 0xB8 },       0x00A65588, 0 },
    { 0x334942, 2, { 0x8B, 0x90 }, 0x00A65588, 0 },
    { 0x33493C, 2, { 0x8B, 0x88 }, 0x00A6558C, 1 },
    { 0x334948, 2, { 0x8B, 0x80 }, 0x00A65590, 2 },
};

// appended registry mapping: Language = "Russian" -> id 19, region 1 (western)
static const RegAppend carbonRegistryAppend = { "Russian", 19, 1 };

static const GameDef CARBON_GAME = {
    "Need for Speed: Carbon 1.4 (nfsc.exe)",
    0x1782A0, carbonFingerprint, sizeof(carbonFingerprint),
    0x65EAC0, 13, 28, 19,
    0x65EC30, 14, 20,
    0x65EA20, 0x65EA8C,
    carbonNewEntries, 6,
    carbonRegRefs, 5,
    0x665588, 19,
    &carbonRegistryAppend,
    carbonBaseRefs, 16,
    carbonEndRefs, 9,
    carbonBytePatches, 5,
};
