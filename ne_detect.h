#pragma once
/* ne_detect.h - project-local name-entry (kana selection) screen detector.
 *
 * Self-contained: no engine or host dependencies. Detects the name-entry
 * screen from a 256x240 ARGB8888 frame using small glyph-shaped patches that
 * require BOTH expected dark pixels (glyph) and expected non-dark pixels
 * (surrounding background). Re-evaluated every call; no state/latching.
 *
 * Black = 0xFF000000u (opaque black). Anything else is non-dark background.
 */
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Returns 1 when the name-entry signature is present, 0 otherwise.
 * `frame` is a 256x240 ARGB8888 image (row-major, 4 bytes/pixel). */
int ne_detect_name_entry(const uint32_t *frame, int w, int h);

/* Returns 1 when the character-selection screen signature is present, 0
 * otherwise. Signature: pink outer-background corners plus dark portrait
 * pixels inside each of the five character portraits. `frame` is a 256x240
 * ARGB8888 image (row-major, 4 bytes/pixel). Verified against the captured
 * char-select state only.
 */
int ne_detect_char_select(const uint32_t *frame, int w, int h);

/* Page-specific char-select detectors. Each returns 1 only when that
 * specific roster page is shown (verified against the captured page states).
 * Pages are mutually exclusive; exactly one should match on any char-select
 * screen, or none (unknown page -> no overlay).
 *
 * Page 1: うるとらまん/せぶん/たろう/えーす/ばるたん (dark-on-blue labels)
 * Page 2: あわじくっす/MK-2/にゃーがんたむ/じゃくしきかい/じゅあんぐ
 * Page 3: たーほろは/みゅうしゃさんく/ぐれーと5/ちゅうろは/しるは
 * Page 4: らいだー1ごう/らいだー2ごう/V3/RX/しゃどーむーん
 * Page 5: two light-on-black name panels + message panel (no overlay)
 */
int ne_detect_char_select_page1(const uint32_t *frame, int w, int h);
int ne_detect_char_select_page2(const uint32_t *frame, int w, int h);
int ne_detect_char_select_page3(const uint32_t *frame, int w, int h);
int ne_detect_char_select_page4(const uint32_t *frame, int w, int h);
int ne_detect_char_select_page5(const uint32_t *frame, int w, int h);

/* Page identifier: returns 1-5 for pages 1-5, 0 for unknown/non-char-select.
 * Detection order: 5 -> 4 -> 3 -> 2 -> 1 (most specific first). */
int ne_detect_char_select_page(const uint32_t *frame, int w, int h);

/* Returns 1 when the verified match-flow (versus) screen with the yokozuna
 * dialogue is shown. Detection uses a complete binary template of the
 * two-line text region (foreground glyph pixels + background pixels)
 * combined with layout checks. Re-evaluated every call; no state/latching.
 * `frame` is a 256x240 ARGB8888 image (row-major, 4 bytes/pixel). */
int ne_detect_match_versus(const uint32_t *frame, int w, int h);

/* Returns 1 when the initial title menu (START/CONTINUE) is shown.
 * Detection uses binary templates of both label rows plus layout checks.
 * Re-evaluated every call; no state/latching. */
int ne_detect_title_menu(const uint32_t *frame, int w, int h);

/* Returns 1 when the title mode-selection menu (INDIVIDUAL/TEAM) is shown.
 * Detection uses binary templates of both label rows (including dakuten)
 * plus layout checks. Re-evaluated every call; no state/latching. */
int ne_detect_title_mode(const uint32_t *frame, int w, int h);

/* Returns 1 when the title round-robin/knockout menu (ROUND ROBIN/KNOCKOUT)
 * is shown. Detection uses binary templates of both label rows plus layout
 * checks. Re-evaluated every call; no state/latching. */
int ne_detect_title_mode2(const uint32_t *frame, int w, int h);
int ne_detect_title_round_robin(const uint32_t *frame, int w, int h);
int ne_detect_round_robin(const uint32_t *frame, int w, int h);

/* Returns 1 when the password-entry screen is shown. Detection uses binary
 * templates of all three labels plus layout checks. Re-evaluated every call. */
int ne_detect_password_entry(const uint32_t *frame, int w, int h);
int ne_detect_password(const uint32_t *frame, int w, int h);

/* Four-portrait Round Robin team selection. */
int ne_detect_team_selection(const uint32_t *frame, int w, int h);

/* M78 team-selection screen. */
int ne_detect_m78_team(const uint32_t *frame, int w, int h);

int ne_detect_m78_overview(const uint32_t *frame, int w, int h);
int ne_detect_m78_order(const uint32_t *frame, int w, int h);

/* Green four-bubble pre-match dialogue. */
int ne_detect_green_dialogue(const uint32_t *frame, int w, int h);

#ifdef __cplusplus
}
#endif