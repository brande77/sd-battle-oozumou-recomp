# PROJECT_FACTS.md — SD Battle Sumo: Heisei Hero Tournament (fresh inspection)

## 1) Workspace
- Current working directory: C:\DecompProjects\SD Battle OHHB
- New workspace: C:\DecompProjects\SD Battle OHHB (confirmed)
- Old project (read-only reference): C:\DecompProjects\SD Battle Oozumou Heisei Hero Basho Recomp
- Engine (read-only for this milestone): C:\DecompProjects\nesrecomp
- Local handoff docs present in new workspace: Famicom-Recompilation-and-Translation-LLM-Handoff.md

## 2) ROM identity (verified)
- Filename: SD Battle Oozumou - Heisei Hero Basho (Japan).nes
- Full path: C:\DecompProjects\SD Battle OHHB\SD Battle Oozumou - Heisei Hero Basho (Japan).nes
- Size (bytes): 262160
- SHA-256 (full file): E2916275B43D2301C64AB35BF6694AAC35402BB8570E7386B32537C2F1D1739F
- Reference SHA-256: e2916275b43d2301c64ab35bf6694aac35402bb8570e7386b32537c2f1d1739f
- Match: EXACT

## 3) ROM header (verified from file)
- Raw 16-byte header (hex): 4E 45 53 1A 08 10 40 08 00 00 00 00 00 00 00 01
- Indexed bytes (zero-based):
  - h[0]=0x4E, h[1]=0x45, h[2]=0x53, h[3]=0x1A (NES\x1A)
  - h[4]=0x08 (PRG-ROM size LSB in iNES units)
  - h[5]=0x10 (CHR-ROM size LSB)
  - h[6]=0x40
  - h[7]=0x08
  - h[8]=0x00
  - h[9]=0x00, h[10]=0x00, h[11]=0x00, h[12]=0x00, h[13]=0x00, h[14]=0x00, h[15]=0x01
- Format detection: NES 2.0 ( (h[7] & 0x0C) == 0x08 )
- PRG-ROM: h[4]*16384 = 8*16384 = 131072 bytes
- CHR-ROM: h[5]*8192  = 16*8192  = 131072 bytes
- Trainer: (h[6] & 0x04) = 0 -> False
- Mirroring: (h[6] & 0x01) = 0 -> horizontal
- Battery/PRG-RAM: (h[6] & 0x02) = 0 -> False
- NES 2.0 mapper (calculated): mapper = ((h[6] >> 4) & 0x0F) | (h[7] & 0xF0) | ((h[8] & 0x0F) << 8) = ((0x40>>4)&0xF)=0x04 | (0x08 & 0xF0)=0x00 | ((0x00 & 0x0F)<<8)=0 = 4
- Submapper: (h[8] >> 4) & 0x0F = (0x00>>4)&0xF = 0
- File layout: prg_start=16, chr_start=16+131072=131088, end=131088+131072=262160; equals actual file size (262160). Declarations match file size.
- Notes: Mapper is 4 (MMC3 family) with submapper 0 (NES 2.0). Header declarations are treated as declarations; actual board behavior still needs verification at runtime if needed.

## 4) Engine (read-only inspection)
- Path: C:\DecompProjects\nesrecomp
- Git worktree: true
- HEAD: fc0bf3fa46a710464960c0a1f2d3b83b4d345600
- Commit: "Audit remaining NES native pipelines and correct performance acceptance guidance" (Matthew Stanley, 2026-10-27 23:00:28 -0700)
- Branch/reflog: clone from https://github.com/mstan/nesrecomp.git at fc0bf3f (main had no commits at inspection time)
- Working tree: clean (git status --short empty)
- Relevant docs: README.md, AGENTS.md, CLAUDE.md present; runner/cyc/project.cmake and docs/GETTING_STARTED.md, docs/MAPPERS.md reviewed.

## 5) Old project (read-only inspection)
- Path: C:\DecompProjects\SD Battle Oozumou Heisei Hero Basho Recomp
- CMakeLists.txt (raw): uses NESRECOMP_ROOT cache, NESRECOMP_BACKEND cycle/legacy; if cycle includes \"\/runner/cyc/project.cmake\" and calls nesrecomp_add_cycle_game(SDBattleSumo ROM \"\/SD Battle Oozumou - Heisei Hero Basho (Japan).nes\" REGION NTSC). Variable references are literal CMake syntax (not expanded). No game.toml/README visible in root listing. Minimal files needed: CMakeLists.txt as above + ROM in source dir + engine at NESRECOMP_ROOT.

## 6) Build tools (verified)
- git 2.56.0.windows.3, Python 3.13.15, cmake 4.4.4
- gcc/g++ 16.2.0 (MinGW-W64 x86_64-ucrt-posix-seh), GNU Make 4.4.1, ninja present. All available.

## 7) User observation (recorded)
- User previously played the old Windows port, advanced through menus with Start, and began a game. Automated title-loop failures did not establish manual gameplay was broken.
