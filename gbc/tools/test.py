# (AI-assisted) Build the host mGBA core and run the genuine adapter/graphics regressions.
from pathlib import Path
import subprocess,sys
r=Path(__file__).resolve().parents[2];core=r/'gbc/third_party/mgba';out=r/'gbc/build-core-host'
args=['-DBUILD_LIBRETRO=ON','-DSKIP_LIBRARY=ON','-DDISABLE_DEPS=ON','-DBUILD_QT=OFF','-DBUILD_SDL=OFF','-DBUILD_GL=OFF','-DBUILD_GLES2=OFF','-DBUILD_GLES3=OFF','-DUSE_DEBUGGERS=OFF','-DUSE_GDB_STUB=OFF','-DENABLE_SCRIPTING=OFF','-DM_CORE_GB=ON','-DM_CORE_GBA=OFF','-DUSE_LZMA=OFF','-DCMAKE_C_FLAGS=-include '+str(r/'gbc/ps5-compat/gb_only.h')]
subprocess.run(['cmake','-S',str(core),'-B',str(out),'-G','Ninja','-DCMAKE_C_COMPILER=clang-18',*args],check=True)
subprocess.run(['cmake','--build',str(out),'--target','mgba_libretro','-j4'],check=True)
for name in ['test_core.py','test_graphics.py']:subprocess.run([sys.executable,str(Path(__file__).with_name(name))],check=True)
