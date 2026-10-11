#pragma once
// Need for Speed: ProStreet 1.1 (nfs.exe), western build.
//
// LanguageTable @ .data 0xA54EF0: 16 entries x 0x24 bytes, id first:
//   { id, name*, code*, globalBin*, frontendBin*, ingameBin*, globalDlcBin*, shared*, perLang* }
// The lookup loops scan the id fields from the base with a 0x24 stride and bound
// against base + 16*0x24; entry 15 is a defused Japanese row (id 14 kept, paths
// swapped for English ones) rather than a deletion.
// eLanguages: 0 ENGLISH 1 FRENCH 2 GERMAN 3 ITALIAN 4 SPANISH 5 DUTCH 6 SWEDISH
//   7 DANISH 8 HUNGARIAN 9 CZECH 10 MEXICAN 11 KOREAN 12 CHINESE_TRAD 13 CHINESE_SIMP
//   14 JAPANESE 15 RUSSIAN 16 THAI 17 POLISH 18 FINNISH 19 NORWEGIAN
// The registry name table @ .data 0xA64A98 still maps every language (Asian
// ones included) to its id, so only the table itself needs restoring.

// language init prologue (sizing + pool + defaults)
static const uint8_t psFingerprint[] = { 0x83, 0xEC, 0x14, 0xA1, 0x00, 0xBE, 0xA8, 0x00,
                                         0x33, 0xC4, 0x89, 0x44, 0x24, 0x10, 0x53, 0x55 };

// table base: id-scan loop starts (mov) and entry-address returns (lea [r*4+base])
static const DwordRef psBaseRefs[] = {
    { 0x194F97, 1, { 0xB8 },             0x00A54EF0 },
    { 0x194FC7, 1, { 0xB8 },             0x00A54EF0 },
    { 0x195007, 1, { 0xB8 },             0x00A54EF0 },
    { 0x19514E, 1, { 0xB8 },             0x00A54EF0 },
    { 0x1A160A, 1, { 0xB8 },             0x00A54EF0 },
    { 0x1C3781, 1, { 0xB8 },             0x00A54EF0 },
    { 0x1DAF1D, 1, { 0xB8 },             0x00A54EF0 },
    { 0x194FBA, 3, { 0x8D, 0x04, 0x85 }, 0x00A54EF0 },
    { 0x194FED, 3, { 0x8D, 0x04, 0x85 }, 0x00A54EF0 },
    { 0x19502D, 3, { 0x8D, 0x04, 0x85 }, 0x00A54EF0 },
    { 0x19518F, 3, { 0x8D, 0x3C, 0xBD }, 0x00A54EF0 },
    { 0x1A1657, 3, { 0x8D, 0x04, 0x85 }, 0x00A54EF0 },
    { 0x1C382A, 3, { 0x8D, 0x34, 0xB5 }, 0x00A54EF0 },
    { 0x1DAF90, 3, { 0x8D, 0x3C, 0xBD }, 0x00A54EF0 },
};

// table end: id-scan bounds
static const DwordRef psEndRefs[] = {
    { 0x194FAB, 1, { 0x3D }, 0x00A55130 },
    { 0x194FDB, 1, { 0x3D }, 0x00A55130 },
    { 0x19501B, 1, { 0x3D }, 0x00A55130 },
    { 0x19515D, 1, { 0x3D }, 0x00A55130 },
    { 0x1A161B, 1, { 0x3D }, 0x00A55130 },
    { 0x1C3794, 1, { 0x3D }, 0x00A55130 },
    { 0x1DAF2F, 1, { 0x3D }, 0x00A55130 },
    { 0x1DAF82, 1, { 0x3D }, 0x00A55130 },
};

// pool sizing loop in the language init: start (entry0 ingame path) and bound
static const AuxRef psAuxRefs[] = {
    { 0x1DAEC9, 1, { 0xBF },     0x00A54F04, 0x14 },
    { 0x1DAF0D, 2, { 0x81, 0xFF }, 0x00A55144, 0x2E4 },
};

// restore the defused Japanese row's paths (its id 14 was kept)
static const PSPathFix psPathFix = { 15, {
    "LANGUAGES\\JAPANESE_GLOBAL.BIN", "LANGUAGES\\JAPANESE_FRONTEND.BIN",
    "LANGUAGES\\JAPANESE_INGAME.BIN", "LANGUAGES\\JAPANESE_GLOBAL_DLC.BIN" } };

// rows cut from the 1.0 table; the 1.0 data uses the shared "EN" code for these
static const PSNewEntry psNewEntries[] = {
    { 11, "KOREAN", "EN", { "LANGUAGES\\KOREAN_GLOBAL.BIN", "LANGUAGES\\KOREAN_FRONTEND.BIN",
                            "LANGUAGES\\KOREAN_INGAME.BIN", "LANGUAGES\\KOREAN_GLOBAL_DLC.BIN" } },
    { 16, "THAI", "EN", { "LANGUAGES\\THAI_GLOBAL.BIN", "LANGUAGES\\THAI_FRONTEND.BIN",
                          "LANGUAGES\\THAI_INGAME.BIN", "LANGUAGES\\THAI_GLOBAL_DLC.BIN" } },
    { 12, "CHINESE_TRAD", "EN", { "LANGUAGES\\CHINESE_TRAD_GLOBAL.BIN", "LANGUAGES\\CHINESE_TRAD_FRONTEND.BIN",
                                  "LANGUAGES\\CHINESE_TRAD_INGAME.BIN", "LANGUAGES\\CHINESE_TRAD_GLOBAL_DLC.BIN" } },
    { 13, "CHINESE_SIMP", "EN", { "LANGUAGES\\CHINESE_SIMP_GLOBAL.BIN", "LANGUAGES\\CHINESE_SIMP_FRONTEND.BIN",
                                  "LANGUAGES\\CHINESE_SIMP_INGAME.BIN", "LANGUAGES\\CHINESE_SIMP_GLOBAL_DLC.BIN" } },
};

static const GameDef PS_GAME = {
    "Need for Speed: ProStreet 1.1 (nfs.exe)",
    0x1DAEB0, psFingerprint, sizeof(psFingerprint),
    0x654EF0, 16, 0x24, 20,
    0, 0, 0,
    0, 0,
    nullptr, 0,
    nullptr, 0,
    0, 0, nullptr,
    psBaseRefs, 14,
    psEndRefs, 8,
    nullptr, 0,
    psAuxRefs, 2,
    &psPathFix, psNewEntries, 4, 0x654E58, 0x649D4,
};
