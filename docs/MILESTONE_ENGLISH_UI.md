# English-UI overlay milestone (name-entry + character-selection, all 5 pages)

## Status
MILESTONE ACCEPTED — name-entry labels (NAME/BACK/DONE), all five
character-selection pages, and the page-5 English message are user-confirmed
in-game. Central 東/西 column intentionally retained Japanese, not unfinished
work.

## Launch command (exact, PowerShell)
```powershell
& "C:\DecompProjects\SD Battle OHHB\build_overlay_verified\SDBattleSumo.exe" "C:\DecompProjects\SD Battle OHHB\SD Battle Oozumou - Heisei Hero Basho (Japan).nes" --english-ui
```

## Files (preserved outside disposable build dirs)
- `sd_battle_overlay.c` — overlay compositor + `--english-ui`/`--name-entry-diag`/`--overlay-test` flags
- `ne_detect.c` / `ne_detect.h` — name-entry + char-select detectors (self-contained, no engine deps)
- `tools/test_detector.c` — actual-C detector test harness (tests both detectors)
- `tools/test_preview.c` — actual-C preview harness (compositing code)
- `tools/gen_fixtures.py` — raw ARGB fixture generator (Python/Pillow)
- `tools/verify_*.py`, `tools/find_*.py` — analysis scripts
- `fixtures/*.raw` — raw ARGB8888 test fixtures from reference PNGs
- `captures/*.png` — reference captures (title, name-entry x2, char select pages 1-5, gameplay)
- `CMakeLists.txt` — integrates `ne_detect.c` into `CYC_HOST_EXTRAS_BUILD`

## Detectors (actual-C, verified against saved fixtures)

**Name-entry** `ne_detect_name_entry()` — 5 glyph-shaped patches (dark + non-dark):
- ref_name_a → true, ref_name_b → true (POSITIVES)
- ref_name_sel (char select), ref_title, ref_gameplay → false
- boot_falsepos, fully_black, uniform_light → false
- Re-evaluated every frame against `cyc_frame_argb()` (pre-composite), never latched.

**Character-selection** `ne_detect_char_select_page()` — pink outer-background corners +
  page-unique label/structure patches. Pages are mutually exclusive; detection
  order: 5 → 4 → 3 → 2 → 1 (most specific first). Exactly one page matches per
  char-select screen, or none (unknown page → no overlay).

Page detection fixtures (actual-C, all PASS):
- cs_ultraman..cs_baltan → page 1 (5 highlight states)
- cs_page2 → page 2, cs_page3 → page 3, cs_page4 → page 4, cs_page5 → page 5
- ref_name_a, ref_name_b, ref_title, ref_gameplay → page 0
- boot_falsepos, fully_black, uniform_light → page 0

**Coverage note:** Page 1 has 5 highlight-state fixtures; pages 2-5 have one
fixture each. Page identification is structurally verified. All pages user-tested
in-game.

## Labels

### Name-entry (user-confirmed in-game)
| Box (x,y,w,h) | Japanese label | English | Role |
|---------------|----------------|---------|------|
| (96, 32, 31, 7) | 㝪㝾㝈 | NAME | upper heading |
| (96, 92, 23, 11) | も㝩る | BACK | left grid control |
| (136, 96, 22, 7) | 㝊ゝり | DONE | right grid control |

### Character-selection page 1 (user-accepted in-game)
Measured from lossless `captures/char select.png` (= `captures/ref_name_sel.png`).
Erase boxes cover Japanese label pixels + raised dakuten; no borders/portraits/cursor affected.

| Erase box (x,y,w,h) | Draw pos (x,y) | Japanese label | English | Role | Note |
|---------------------|----------------|----------------|---------|------|------|
| (40, 89, 47, 7) | (47, 90) | 㝆る㝨ら㝾ん | ULTRAMAN | top-left portrait name | text centered in box |
| (176, 85, 23, 11) | (166, 96) | 㝛㝶ん | ULTRASEVEN | top-right portrait name | text drawn below portrait |
| (48, 201, 23, 7) | (51, 202) | 㝟ゝ㝆 | TARO | bottom-left portrait name | text centered in box |
| (112, 201, 23, 7) | (117, 202) | 㝈ー㝙 | ACE | bottom-center portrait name | text centered in box |
| (176, 197, 31, 11) | (179, 200) | 㝰る㝟ん | BALTAN | bottom-right portrait name | erase incl. raised dakuten y=197-198 |

### Character-selection page 2 (user-accepted in-game)
Measured from `captures/cs_page2.png`. MK-2 (top-right) is already English
text on screen and is preserved untouched.

| Erase box (x,y,w,h) | Draw pos (x,y) | Japanese label | English | Role | Note |
|---------------------|----------------|----------------|---------|------|------|
| (48, 89, 39, 7) | (56, 90) | 㝂ゝ㝘㝝㝣㝙 | ALEX | top-left portrait name | text centered in box |
| (40, 190, 41, 18) | (40, 200) | 㝫ゅー㝌ん㝠む | NU GUNDAM | bottom-left portrait name | text at left edge |
| (104, 190, 60, 18) | (104, 200) | 㝘ゃ㝝㝗㝝㝋㝄 | HYAKU SHIKI KAI | bottom-center portrait name | text at left edge |
| (177, 190, 30, 18) | (182, 200) | 㝘ゅ㝂ん㝝 | ZEONG | bottom-right portrait name | text centered |

### Character-selection page 3 (user-accepted in-game)
Measured from `captures/cs_page3.png`.

| Erase box (x,y,w,h) | Draw pos (x,y) | Japanese label | English | Role | Note |
|---------------------|----------------|----------------|---------|------|------|
| (40, 85, 40, 11) | (40, 89) | 㝟ー㝻ゝ㝯 | TURBO ROBO | top-left portrait name | text at left edge |
| (170, 89, 51, 7) | (170, 96) | 㝿ゅ㝆㝗ゃ㝕ん㝝 | FLASH KING | top-right portrait name | text at left edge |
| (41, 190, 40, 18) | (41, 208) | 㝝れー㝨5 | GREAT FIVE | bottom-left portrait name | text below box |
| (113, 190, 38, 18) | (113, 208) | 㝡ゅ㝆ゝ㝯 | LIVE ROBO | bottom-center portrait name | text below box |
| (177, 190, 27, 18) | (178, 200) | 㝗る㝯 | SILVA | bottom-right portrait name | text centered |

### Character-selection page 4 (user-accepted in-game)
Measured from `captures/cs_page4.png`. V3 (bottom-left) and RX (bottom-center)
are already English text on screen and are preserved untouched.

| Erase box (x,y,w,h) | Draw pos (x,y) | Japanese label | English | Role | Note |
|---------------------|----------------|----------------|---------|------|------|
| (33, 85, 54, 11) | (49, 89) | ら㝄㝠ー1㝔㝆 | Rider 1 | top-left portrait name | text centered |
| (173, 85, 50, 11) | (173, 87) | ら㝄㝠ー2㝔㝆 | Rider 2 | top-right portrait name | text at left edge |
| (161, 190, 50, 18) | (161, 200) | 㝗ゃ㝩ーむーん | Shadow Moon | bottom-right portrait name | text at left edge |

### Character-selection page 5 (user-accepted in-game)
Measured from `captures/cs_page5.png`. Page 5 uses light-on-black rendering:
two black name panels at top with white English text drawn inside each panel.
Bottom message panel preserved untouched. Central 東/西 column intentionally
retained Japanese — not unfinished work, not deferred.

| Erase box (x,y,w,h) | Draw pos (x,y) | Japanese label | English | Role | Note |
|---------------------|----------------|----------------|---------|------|------|
| (48, 70, 40, 7) | (48, 70) | 㝱ん㝷れ㝝㝣㝨 | BANPRE KID | top-left name panel | text at panel top-left |
| (173, 70, 55, 7) | (173, 70) | G. 㝋㝿㝪りもん | G. KAMINARIMON | top-right name panel | text at panel left edge |

Overlay covers each label's pixels with screen background (0xFFC0D8FF for
pages 1-4; black 0xFF000000 for page 5 panels), then draws English text in
black (pages 1-4) or white (page 5) via `cyc_overlay_text`. Gated on
`--english-ui` + detector page match.

## Preview verification (actual compositing code)
All pages verified on saved frames:
- Detector: correct page number for all 5 page-1 highlights, pages 2-5,
  and page 0 for all non-char-select screens ✓
- 0 pixels differ outside erase/draw regions for all 12 screens → borders,
  portraits, cursor, message panel preserved ✓
- All English names drawn at correct positions on all pages ✓

## Logging (unchanged)
Option logged once at startup; detectors log only on result change; real errors visible; no per-frame spam; no startup delay; no stderr suppression.


## Title Menu � Initial State (START/CONTINUE)
- **Source:** `captures/title.png` (native 256�240)
- **English:** `START` (row 1, x=128-157, y=200-206) / `CONTINUE` (row 2, x=128-182, y=216-222)
- **Live smoke-test PASS (2026-11-05):**
  - Both English labels visible.
  - Cursor preserved when moving between choices.
  - Labels remain visible with either choice selected.
  - START transition to mode selection clears the initial-menu overlay.
  - CONTINUE transition to password entry clears the initial-menu overlay.
- **Candidate build:** `build_match_versus/SDBattleSumo.exe` SHA-256: 17CC4F7DCD68066C1E283C20BBDD63D19EF29D81506977C3E855AF9CA42E196E
- **Status:** Candidate verified (smoke test), NOT promoted. Accepted checkpoint unchanged.
- **Not implemented:** Mode selection (INDIVIDUAL MATCH / TEAM MATCH), password entry screen.

## Match-Flow Dialogue (Post-Selection)
- **cyc_shot_0003 verified dialogue:** `???????? / ?????????????`
- **English:** `Someday, I'll become / a yokozuna too...`
- **Live runtime verification:** Both English lines confirmed visible by user (2026-11-05).
- **Smoke test:** User reports both lines appear, transition into match works, no stale overlay noticed. User-observed smoke test, NOT exhaustive runtime verification.
- **Root cause (fixed):** `draw_match_versus_ui()` erased the full dialogue rectangle on each label iteration, destroying line 1. Fixed by erasing once then drawing both lines (erase-once/draw-both-lines pattern).
- **Candidate build:** `build_match_versus/SDBattleSumo.exe` SHA-256: `7610CFD8B73BFF5C581AE7BF31E4A84A7F8FEC8C01B2715E371D6EA601933613`
- **Status:** Candidate verified, NOT promoted. Accepted checkpoint (`checkpoint_english_ui_accepted/`) remains unchanged.
## Not tested / not claimed
- Kana grid (y=120-188) and entered-name field behavior are NOT converted.
- Central 東/西 column intentionally retained Japanese — not unfinished work,
  not deferred.
- Character-selection overlay user-tested in-game on all five pages;
  page-5 English message user-accepted. Page 1 highlight states verified via
  5 fixtures; pages 2-5 verified against one capture each (page 5 highlight
  states not tested).

## Title Mode-Selection (ROUND ROBIN / KNOCKOUT)
- **Source:** `captures/new_mode_select/new_mode_select_capture_0.png` and `_1.png` (native 256�240)
- **English:** `ROUND ROBIN` (row 1, erase (128,200,55,7)) / `KNOCKOUT` (row 2, erase (128,216,47,7))
- **Detector:** `ne_detect_title_mode2()` (aliases `ne_detect_title_round_robin`, `ne_detect_round_robin`); binary templates of both label rows plus layout checks.
- **Live smoke-test PASS (2026-11-05):** START/CONTINUE, INDIVIDUAL/TEAM, and ROUND ROBIN/KNOCKOUT all work through both 1P and 2P routes; cursor, label visibility, and screen transitions pass. User-observed smoke test, not exhaustive verification.
- **Candidate build:** `build_round_robin/SDBattleSumo.exe` SHA-256: `1BE1EAA484586929ECE4C13ADED3182828E7B6A4EA23668F6413AC7A3FE43420`
- **Status:** Candidate verified (smoke test), NOT promoted. Accepted checkpoint unchanged.

## Password Entry (PASSWORD / BACK / DONE)
- **Source:** `captures/password_entry.png` (native 256�240, from `cyc_shot_0000.png`)
- **English:** `PASSWORD` (erase (96,29,63,10)) / `BACK` (erase (96,108,23,11)) / `DONE` (erase (136,112,22,7))
- **Detector:** `ne_detect_password_entry()` (alias `ne_detect_password`); binary templates of all three labels plus layout checks.
- **Observed failure:** First live smoke test failed: password entry remained Japanese.
- **Diagnosed cause:** HD-pack presentation can bypass `extras.present` on the password screen, so the overlay canvas was not the displayed buffer.
- **Fix:** Draw the password labels into the native frame (`cyc_frame_argb()`) as well as the overlay canvas, allowing the HD path to upscale them.
- **Status:** Implemented/offline-tested, awaiting user live smoke test.
- **Candidate build:** `build_password_entry/SDBattleSumo.exe` SHA-256: `1D8993BD29FF23B513492DEABA71154810826094310DCD44113AA41FF1B35A05`

## Regression requirements (all met)
- Page 1: all 5 char selections → page=1 ✓
- Pages 2-5: each detected as correct page ✓
- Name entry, title, gameplay, boot, uniform → page=0 ✓
- All existing name-entry tests preserved ✓
- No latching, no timeout, no startup delay ✓
- 0 pixels differ outside erase/draw regions for all 12 screens ✓