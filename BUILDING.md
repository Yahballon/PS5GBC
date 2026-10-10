# Building PS5GBC

(AI-assisted) Use the existing PS5GBA/PS5SNES dependency layout with Clang/LLVM 18, Python, CMake, Ninja and the PS5 Payload SDK, Vulkan archives/runtime, libnfs and pacbrew curl/OpenSSL/zlib. No other emulator project source is required.

`PS5GBC_DEPS=/path/to/prepared/ps5-build bash gbc/tools/build.sh`

Sources: `gbc/src/`, `gbc/third_party/mgba/`, `ps5/frontend/`. Upstream mGBA 0.10.5 is configured with M_CORE_GB=ON and M_CORE_GBA=OFF. A forced compatibility header supplies declarations used unconditionally by the upstream libretro adapter. Its framebuffer pointer is cleared after free to make repeated deinit/init safe.

After shader edits: `GLSLANG_VALIDATOR=/path/to/glslangValidator bash ps5/frontend/build_shaders.sh`.

Host tests: `python3 gbc/tools/test.py`. They require Clang/LLVM 18, Mesa Vulkan/llvmpipe and zlib.

Run these commands in Linux or WSL; the scripts use Linux compiler tools and shared libraries. Native Windows builds are not supported by these entry points.

The prepared dependency directory must contain:

- `PS5_Vulkan/`: driver archives in `build/driver/ps5/`, native SDK and Vulkan/PSBC archives in `.deps/native/`, and `runtime/libc.prx`.
- `libnfs-install/`: headers and `lib/libnfs.a`.
- `filesystem-helper/`: `tools/build-lapy-helper.py` and `.deps/pacbrew/v0.40.2/sysroot/user/homebrew/` with curl, libpsl, OpenSSL, zstd and zlib headers/static libraries.
- `libnfs/COPYING`: the dependency license copied into the package.

`PS5_PAYLOAD_SDK`, `LIBNFS_PREFIX` and `LIBZ_PREFIX` can override their default locations. The build also invokes `clang++-18`, `ld.lld-18` and `llvm-objcopy-18`.

Release output: `gbc/build-shelf/PS5GBC-v1-Covers-Performance-Defaults-by-YAHBALLON.zip`. App identity: PPSA99210, metadata 01.000.001. Hardware validation pending. Generated output is ignored by Git; attach the ZIP and its SHA-256 file as release assets.

Before publishing, run `python3 gbc/tools/check_release.py --package gbc/build-shelf/PS5GBC-v1-Covers-Performance-Defaults-by-YAHBALLON.zip` and complete the console checks in [TESTING.md](TESTING.md).
