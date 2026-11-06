# SD Battle Oozumou: Heisei Hero Basho - Recompilation

Experimental native Windows recompilation and English translation of the Nintendo Famicom game.

## Project Status
Work in progress. Uses the NESRecomp cycle backend.

## Features
- Native Windows executable
- Optional English interface (--english-ui)
- English translations for all four team-selection screens
- Translated character names and pre-match dialogue
- Experimental post-match translations
- Ongoing translation and graphical cleanup

## Requirements
- Windows, CMake 3.20+, MinGW-w64, Python 3.11+
- NESRecomp cycle backend (currently requires local modifications)
- User-supplied original Japanese ROM

## Building
Configure: cmake -S . -B build -G "MinGW Makefiles" -DNESRECOMP_ROOT="C:/DecompProjects/engine-test" -DNESRECOMP_BACKEND=cycle -DCYC_HOST_EXTRAS_BUILD=ON
Build: cmake --build build
Run: .\build\SDBattleSumo.exe "SD Battle Oozumou - Heisei Hero Basho (Japan).nes" --english-ui

## ROM
Original ROM not included. SHA-256: e2916275b43d2301c64ab35bf6694aac35402bb8570e7386b32537c2f1d1739f

## Legal
Unofficial preservation, recompilation, and English translation project. Original game and characters belong to their respective rights holders.
