# PS5GBC verification

(AI-assisted) Earlier development records report original GB and GBC homebrew execution at 160x144 and 59.72750092 FPS, generated audio, input, SRAM/state/RTC buffer support, raw/ZIP loading and Vulkan output through 3840x2160. These are historical results, not validation of the current release artifact.

Run `python3 gbc/tools/test.py` in the Linux build environment for core and graphics checks. Run `python3 gbc/tools/check_release.py` for source hygiene, then add `--package path/to/release.zip` to verify ZIP integrity, metadata, required files and manifest hashes. The build emits a `.zip.sha256` file alongside its package.

Record the exact source commit, package SHA-256, commands/results and console firmware/launcher used when completing release validation. `VERIFICATION.json` preserves the earlier reported package hash; it does not identify a package produced by this checkout.

Still required on console: launch/install, real GB/GBC cartridges, sound and frame pacing, model-specific palettes, RTC clock progression across app restarts, repeated shelf/game transitions, USB/NFS loading and 4K performance. Host GPU tests use CPU llvmpipe and do not measure PS5 speed. No commercial test ROM or BIOS is bundled.
