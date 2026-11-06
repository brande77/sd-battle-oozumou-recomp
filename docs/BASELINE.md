# BASELINE.md — SD Battle Sumo: Heisei Hero Tournament

## ROM identity (verified)
- File: SD Battle Oozumou - Heisei Hero Basho (Japan).nes
- Path: C:\DecompProjects\SD Battle OHHB\SD Battle Oozumou - Heisei Hero Basho (Japan).nes
- Size: 262160 bytes
- SHA-256: E2916275B43D2301C64AB35BF6694AAC35402BB8570E7386B32537C2F1D1739F
- Header (hex): 4E 45 53 1A 08 10 40 08 00 00 00 00 00 00 00 01
- Format: NES 2.0
- PRG-ROM: 131072 bytes (h[4]=0x08), CHR-ROM: 131072 bytes (h[5]=0x10)
- Mapper (NES 2.0): ((h[6]>>4)&0xF)|(h[7]&0xF0)|((h[8]&0x0F)<<8) = ((0x40>>4)=4) | (0x08&0xF0)=0 | ((0x00)<<8)=0 = 4 (MMC3 family)
- Submapper: (h[8]>>4)=0
- Mirroring: horizontal (h[6]&1==0), Trainer: false, Battery: false
- Layout: matches file size (end 262160 == 262160)

## Engine
- Path: C:\DecompProjects\nesrecomp
- HEAD: fc0bf3fa46a710464960c0a1f2d3b83b4d345600
- Commit: Audit remaining NES native pipelines and correct performance acceptance guidance (Matthew Stanley 2026-10-27 23:00:28 -0700)
- Status: clean (git status --short empty)

## Project configuration
- New workspace CMakeLists.txt: uses NESRECOMP_ROOT="C:/DecompProjects/nesrecomp", NESRECOMP_BACKEND=cycle, includes runner/cyc/project.cmake, calls nesrecomp_add_cycle_game(SDBattleSumo ROM "/SD Battle Oozumou - Heisei Hero Basho (Japan).nes" REGION NTSC)
- .gitignore created (excludes ROMs, build/, saves, traces, etc.)
- Old project CMakeLists.txt matches same pattern (read-only).

## Build
- Configure: cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DNESRECOMP_ROOT="C:/DecompProjects/nesrecomp" (configured OK)
- Build: cmake --build build --parallel 2 (completed)
- Result: Built target SDBattleSumo
- Executable: C:\DecompProjects\SD Battle OHHB\build\SDBattleSumo.exe

## Launch & input bindings (verified from cyc_input.c)
- Default keyboard (Player 1): Z = A, X = B, Backslash = Select, Return/Enter = Start, Arrow keys = Up/Down/Left/Right
- Controller defaults also configured (as documented). Player 1 uses keyboard+first controller; player 2 uses next controller by default.
- Windowed launch (from build dir): SDBattleSumo.exe "<ROM path>" (ROM path passed at configure time is used; executable runs with ROM identity check)
- Exact windowed launch command (example): C:\DecompProjects\SD Battle OHHB\build\SDBattleSumo.exe "C:\DecompProjects\SD Battle OHHB\SD Battle Oozumou - Heisei Hero Basho (Japan).nes"

## Manual gameplay test
- Status: PENDING USER
- Note: User reports manual play through menus with Start worked on old port; automated title-loop failures not proof of breakage.
