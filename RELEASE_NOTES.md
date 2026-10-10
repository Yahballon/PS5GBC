# PS5GBC v1

(AI-assisted) GB/GBC-only mGBA port based on PS5GBA, with its own app identity and data directory.

- Game Boy and Game Boy Color games, including single-ROM ZIP archives.
- Cover-flow library with local, USB and NFS loading and downloadable covers.
- 160x144 emulation with Vulkan presentation, scaling presets and stereo audio.
- Battery saves, RTC data, one save-state slot per game and configurable controls.

App ID: **PPSA99210**. Extract the app folder into `/data/homebrew/`; see [INSTALL.md](INSTALL.md). Preserve `/data/PS5GBC/` when updating.

**Console validation is pending.** Firmware/launcher compatibility and PS5 performance are not yet established. See [TESTING.md](TESTING.md) for the remaining checks. No commercial ROM or BIOS is included.
