#pragma once
// Need for Speed: Most Wanted v1.3 (speed.exe), western build.
//
// LanguageInfoTable @ .data 0x4F40F8: 10 entries x 20 bytes
//   { id, name*, path*, textureHashList*, numberFormatCode* }
// CurrentLanguage_0 @ 0x4F41C0 doubles as the lookup loops' table end;
// language count @ 0x4F41C4 = max language id + 1.
// Registry name table @ .data 0x4FB578: 16 x { name*, id, region } + terminator.
// eLanguages: 0 ENGLISH 1 FRENCH 2 GERMAN 3 ITALIAN 4 SPANISH 5 DUTCH
//   6 SWEDISH 7 DANISH 8 KOREAN 9 CHINESE 10 JAPANESE 11 THAI 12 POLISH 13 FINNISH
//   14 RUSSIAN (appended by this plugin)
// memcard/LOCALE_<name>.loc gate (RVA 0x118285) excludes ids 14/15; relax to 15 only.

// LoadLanguageResources prologue
static const uint8_t mwFingerprint[] = { 0x8B, 0x15, 0xC0, 0x41, 0x8F, 0x00 };

// mov reg, offset LanguageInfoTable / lea reg, [reg*4 + LanguageInfoTable]
static const DwordRef mwBaseRefs[] = {
    { 0x16B7B7, 1, { 0xB8 },             0x008F40F8 },
    { 0x16B7E7, 1, { 0xB8 },             0x008F40F8 },
    { 0x16B82A, 1, { 0xB8 },             0x008F40F8 },
    { 0x16B95D, 1, { 0xB8 },             0x008F40F8 },
    { 0x17E715, 1, { 0xB8 },             0x008F40F8 },
    { 0x185BF5, 1, { 0xB8 },             0x008F40F8 },
    { 0x18F6B1, 1, { 0xB8 },             0x008F40F8 },
    { 0x16B7D8, 3, { 0x8D, 0x04, 0x85 }, 0x008F40F8 },
    { 0x16B80B, 3, { 0x8D, 0x04, 0x85 }, 0x008F40F8 },
    { 0x16B87B, 3, { 0x8D, 0x04, 0x85 }, 0x008F40F8 },
    { 0x185C43, 3, { 0x8D, 0x04, 0x85 }, 0x008F40F8 },
    { 0x18F6CC, 3, { 0x8D, 0x04, 0x85 }, 0x008F40F8 },
    { 0x16BB14, 3, { 0x8D, 0x34, 0xB5 }, 0x008F40F8 },
    { 0x17E841, 3, { 0x8D, 0x34, 0xB5 }, 0x008F40F8 },
};

// cmp reg, <table end> closing every lookup loop
static const DwordRef mwEndRefs[] = {
    { 0x16B7C9, 1, { 0x3D }, 0x008F41C0 },
    { 0x16B7F9, 1, { 0x3D }, 0x008F41C0 },
    { 0x16B83A, 1, { 0x3D }, 0x008F41C0 },
    { 0x16B86D, 1, { 0x3D }, 0x008F41C0 },
    { 0x16B96E, 1, { 0x3D }, 0x008F41C0 },
    { 0x17E72D, 1, { 0x3D }, 0x008F41C0 },
    { 0x185C09, 1, { 0x3D }, 0x008F41C0 },
    { 0x18F6BE, 1, { 0x3D }, 0x008F41C0 },
};

static const BytePatch mwBytePatches[] = {
    // InitLocalization pool head-room: 0x37FC8 -> 0x1400000 (CJK atlases)
    { 0x16B89D, { 0x81, 0xC6, 0xC8, 0x7F, 0x03, 0x00 },
                { 0x81, 0xC6, 0x00, 0x00, 0x40, 0x01 }, 6 },
    // id 14 then falls through to GetLanguageName -> memcard/LOCALE_RUSSIAN.loc
    { 0x118285, { 0x83, 0xF8, 0x0E }, { 0x83, 0xF8, 0x0F }, 3 },
};

// Asian entries as they existed in v1.2, plus Russian on a fresh id
static const LangEntry mwNewEntries[] = {
    { 8,  "KOREAN",   { "LANGUAGES\\KOREAN.BIN",   nullptr, nullptr } },
    { 9,  "CHINESE",  { "LANGUAGES\\CHINESE.BIN",  nullptr, nullptr } },
    { 10, "JAPANESE", { "LANGUAGES\\JAPANESE.BIN", nullptr, nullptr } },
    { 11, "THAI",     { "LANGUAGES\\THAI.BIN",     nullptr, nullptr } },
    { 14, "RUSSIAN",  { "LANGUAGES\\RUSSIAN.BIN",  nullptr, nullptr } },
};

// registry name table: repoint name/id/region column bases (regeditthang)
static const RegRef mwRegRefs[] = {
    { 0x2CB8EC, 1, { 0xA1 },          0x008FB578, 0 },
    { 0x2CB8F5, 1, { 0xB8 },          0x008FB578, 0 },
    { 0x2CB931, 2, { 0x8B, 0x88 },    0x008FB578, 0 },
    { 0x2CB92B, 2, { 0x8B, 0x90 },    0x008FB57C, 1 },
    { 0x2CB93D, 2, { 0x8B, 0x90 },    0x008FB580, 2 },
};

// appended registry mapping: Language = "Russian" -> id 14, region 1 (western)
static const RegAppend mwRegistryAppend = { "Russian", 14, 1 };

static const GameDef MW_GAME = {
    "Need for Speed: Most Wanted 1.3 (speed.exe)",
    0x16B950, mwFingerprint, sizeof(mwFingerprint),
    0x4F40F8, 10, 20, 15,
    0x4F41C4, 10, 15,
    0x4F4060, 0x4F40CC,
    mwNewEntries, 5,
    mwRegRefs, 5,
    0x4FB578, 16,
    &mwRegistryAppend,
    mwBaseRefs, 14,
    mwEndRefs, 8,
    mwBytePatches, 2,
};
