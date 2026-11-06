# FONT_ANALYSIS.md — SD Battle Sumo: Heisei Hero Tournament

## Extraction
- ROM: SD Battle Oozumou - Heisei Hero Basho (Japan).nes (NES 2.0, Mapper 4, PRG 128KB, CHR 128KB)
- CHR-ROM start: 131088 (0x20010); size: 131072 bytes; total tiles: 8192 (global indices 0x0000–0x1FFF)
- Extraction tool: tools/extract_chr_atlas.py (2bpp decode, both bitplanes, labels tile index + CHR offset)
- Matcher tool: tools/match_chr.py (palette-independent screenshot-to-CHR matching, validated selftest VAL1–VAL4)
- Atlases: LocalAnalysis/atlases/*.png (excluded from Git via .gitignore)

## Offset correction (verified)
- rom_file_offset = 0x20010 + global_tile_index * 16. Extraction script is CORRECT.
- Earlier doc entries 0x10 lower were WRONG; script not regenerated.

## Retracted conclusion
- The earlier luminance-based report ("font not stored in CHR-ROM / almost certainly CHR-RAM") is RETRACTED. It used an invalid brightness->CHR-index mapping.
- Corrected palette-independent matcher shows the font IS present in CHR-ROM. No CHR-RAM claim is made or supported.

## Verified character matches — name-entry screenshot cyc_shot_0000.png (256x240)
Each cell matched via palette-independent render-back comparison (every candidate passes independent render-back; no spurious acceptances).
IMPORTANT: a pixel match verifies the TILE only. The Unicode readings below are PROPOSED VISUAL READINGS from external review of the contact sheet — NOT derived from kana ordering, NOT source-byte encoding, NOT live bank mapping. Reading review recorded as "external visual review," not "user-confirmed" or "source encoding verified."

Fifth-column patches were originally cropped at x=201 (clipped, no match). Recropped at x=200 (full patches), all match:
- c5 (200,120) → 0x172E (0x0372F0)
- r2c5 (200,136) → 0x172F (0x037300)
- r3c5 (200,152) → 0x1730 (0x037310)
- r4c5 (200,168) → 0x1731 (0x037320)
These are NOT missing from CHR-ROM.

Authoritative glyph map (pixel match + external visual reading):

| Cell | (x,y) | Global tile | ROM offset | Pixel match | Proposed unicode (external visual review) | Reading confidence |
|---|---|---|---|---|---|---|
| c1 | 136,120 | 0x1714 | 0x037150 | exact | な | high |
| c2 | 152,120 | 0x170F | 0x037100 | exact | た | high |
| c3 | 168,120 | 0x170A | 0x0370B0 | exact | さ | high |
| c4 | 184,120 | 0x1705 | 0x037060 | exact | か | high |
| c5 | 200,120 | 0x172E | 0x0372F0 | exact | — | unresolved (fifth-column recrop) |
| c6 | 216,120 | 0x1700 | 0x037010 | exact | あ | high |
| r2c1 | 136,136 | 0x1715 | 0x037160 | exact | に | high |
| r2c2 | 152,136 | 0x1710 | 0x037110 | exact | ち | high |
| r2c3 | 168,136 | 0x170B | 0x0370C0 | exact | し | high |
| r2c4 | 184,136 | 0x1706 | 0x037070 | exact | き | high |
| r2c5 | 200,136 | 0x172F | 0x037300 | exact | — | unresolved (fifth-column recrop) |
| r2c6 | 216,136 | 0x1701 | 0x037020 | exact | い | high |
| r3c1 | 136,152 | 0x1716 | 0x037170 | exact | ぬ | high |
| r3c2 | 152,152 | 0x1711 | 0x037120 | exact | つ | high |
| r3c3 | 168,152 | 0x170C | 0x0370D0 | exact | す | high |
| r3c4 | 184,152 | 0x1707 | 0x037080 | exact | く | high |
| r3c5 | 200,152 | 0x1730 | 0x037310 | exact | — | unresolved (fifth-column recrop) |
| r3c6 | 216,152 | 0x1702 | 0x037030 | exact | う | high |
| r4c1 | 136,168 | 0x1717 | 0x037180 | exact | ね | high |
| r4c2 | 152,168 | 0x1712 | 0x037130 | exact | て | high |
| r4c3 | 168,168 | 0x170D | 0x0370E0 | exact | せ | high |
| r4c4 | 184,168 | 0x1708 | 0x037090 | exact | け | high |
| r4c5 | 200,168 | 0x1731 | 0x037320 | exact | — | unresolved (fifth-column recrop) |
| r4c6 | 216,168 | 0x1703 | 0x037040 | exact | え | high |

20 full-size patches with corrected readings; 4 fifth-column patches matched but readings left unresolved.

Glyph table (machine-readable, csv.DictWriter, newline='', UTF-8, palette as JSON):
- LocalAnalysis/preliminary_glyph_table_v2.csv (24 rows)
- Round-trip test: fields match, 24 rows, 20 Japanese characters survive write/read, 4 fifth-column recrops all exact. valid UTF-8 alone does NOT prove absence of mojibake; v2 is the current table based on its expected-character round-trip assertions.
- Older preliminary_glyph_table.csv (Set-Content version) is also valid UTF-8 but superseded by v2.

## Match-type / palette distinction
- "exact" = palette-consistent render-back match (every CHR index -> exactly one screenshot RGB). Verified by independent render-back comparison for every reported candidate.
- Duplicate tiles at different CHR locations share the same glyph pattern; some differ only in which palette index is foreground vs background (a COLOR mapping, NOT a spatial flip/rotation or "inverse orientation"). Duplicate candidates preserved, not arbitrarily chosen.

## Name-entry capture milestone

During a user-confirmed name-entry screen capture, all 16 byte offsets
of global CHR tile 0x1700 were observed. Every recorded byte matched
the corresponding ROM byte. Exact background-cell attribution and
source text encoding remain unverified.

This capture does not validate all glyph readings or an English renderer.

### Trace artifact
- File: `C:\DecompProjects\SD Battle OHHB\build_diag\cyc_trace_name_entry.bin` (404,893 bytes)
- Source executable: `C:\DecompProjects\SD Battle OHHB\build_diag\SDBattleSumo.exe` (SHA-256: 4A23946B0ACDA1AFED2F09BE10AC96C1892EF3FCB108FE98B5F76314192977B9)
- ROM: `C:\DecompProjects\SD Battle OHHB\SD Battle Oozumou - Heisei Hero Basho (Japan).nes` (SHA-256: E2916275B43D2301C64AB35BF6694AAC35402BB8570E7386B32537C2F1D1739F)
- Engine base: `C:\DecompProjects\engine-test` @ 9ba801c "baseline"
- Diagnostic diff: `runner/cyc/hw_machine.c`, `runner/cyc/cyc_sdl.c`, `runner/cyc/hw_internal.h` (CYC_TRACE_PATTERN_FETCH=ON)
- Parser: `C:\DecompProjects\SD Battle OHHB\parse_trace.py` (record format `<IIHxxIBBxx`, 20 bytes/record; header: version u32, count u64, overflow u8)
- Validation command: `python parse_trace.py cyc_trace_name_entry.bin <ROM path>`

### Validation results (name-entry capture)
- Records decoded: 20,244
- Overflow flag: false
- Out-of-range CHR offsets: 0
- ROM-byte matches: 20,244 / 20,244
- ROM-byte mismatches: 0
- All recorded bytes match ROM at `chr_start (0x20010) + chr_offset`

### Unclassified-fetch limitation
All records carry `classification=0` (unclassified). The diagnostic records the
fetched byte and CHR offset but does not classify whether the access was
background pattern, nametable, attribute, or sprite data. Exact
background-cell attribution for any glyph remains unverified.

### Glyph coverage table (20 externally reviewed full-size glyphs)

| Cell | Proposed Unicode | Global CHR tile | Distinct tile-byte offsets observed (0–16) | Observed PPU pattern-address range | Earliest/latest recorded scanline |
|------|------------------|-----------------|---------------------------------------------|------------------------------------|-----------------------------------|
| c1 | な | 0x1714 | 16 (complete) | 0x0140–0x014F | 32–127 |
| c2 | た | 0x170F | 16 (complete) | 0x00F0–0x00FF | 120–127 |
| c3 | さ | 0x170A | 16 (complete) | 0x00A0–0x00AF | 120–127 |
| c4 | か | 0x1705 | 16 (complete) | 0x0050–0x005F | 120–127 |
| c5 | — | 0x172E | 16 (complete) | 0x02E0–0x02EF | 120–127 |
| c6 | あ | 0x1700 | 16 (complete) | 0x0000–0x000F | 120–127 |
| r2c1 | に | 0x1715 | 16 (complete) | 0x0150–0x015F | 136–143 |
| r2c2 | ち | 0x1710 | 16 (complete) | 0x0100–0x010F | 136–143 |
| r2c3 | し | 0x170B | 16 (complete) | 0x00B0–0x00BF | 136–143 |
| r2c4 | き | 0x1706 | 16 (complete) | 0x0060–0x006F | 136–143 |
| r2c5 | — | 0x172F | 16 (complete) | 0x02F0–0x02FF | 136–143 |
| r2c6 | い | 0x1701 | 16 (complete) | 0x0010–0x001F | 136–143 |
| r3c1 | ぬ | 0x1716 | 16 (complete) | 0x0160–0x016F | 152–159 |
| r3c2 | つ | 0x1711 | 16 (complete) | 0x0110–0x011F | 152–159 |
| r3c3 | す | 0x170C | 16 (complete) | 0x00C0–0x00CF | 152–159 |
| r3c4 | く | 0x1707 | 16 (complete) | 0x0070–0x007F | 152–159 |
| r3c5 | — | 0x1730 | 16 (complete) | 0x0300–0x030F | 152–159 |
| r3c6 | う | 0x1702 | 16 (complete) | 0x0020–0x002F | 152–159 |
| r4c1 | ね | 0x1717 | 16 (complete) | 0x0170–0x017F | 168–175 |
| r4c2 | て | 0x1712 | 16 (complete) | 0x0120–0x012F | 168–175 |
| r4c3 | せ | 0x170D | 16 (complete) | 0x00D0–0x00DF | 168–175 |
| r4c4 | け | 0x1708 | 16 (complete) | 0x0080–0x008F | 168–175 |
| r4c5 | — | 0x1731 | 16 (complete) | 0x0310–0x031F | 168–175 |
| r4c6 | え | 0x1703 | 16 (complete) | 0x0030–0x003F | 32–175 |

All 20 glyphs achieved complete 16/16 byte-offset coverage in the name-entry
capture. Absent or partial coverage: none.

The earlier luminance-based report ("font not stored in CHR-ROM / almost certainly CHR-RAM") remains RETRACTED. The corrected palette-independent matcher and this trace capture confirm the font IS present in CHR-ROM.

No modifications to gameplay, input, rendering, or shared engine. No translation catalogs created. No English replacement of the Japanese name-entry grid. Diagnostic patch not promoted into the original shared engine.
