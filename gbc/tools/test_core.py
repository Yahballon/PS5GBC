from pathlib import Path
import subprocess,struct,zipfile
r=Path(__file__).resolve().parents[2];out=r/'gbc/build-tests';out.mkdir(exist_ok=True);(out/'saves').mkdir(exist_ok=True);(out/'states').mkdir(exist_ok=True)
for color,ext in [(False,'gb'),(True,'gbc')]:
 rom=bytearray(32768);rom[0x100:0x104]=bytes([0,0xc3,0x50,1]);rom[0x134:0x13f]=b'PS5GBC TEST';rom[0x143]=0x80 if color else 0;rom[0x147]=0x10;rom[0x149]=2
 code=bytearray([0xf3,0x31,0xff,0xdf,0xaf,0xe0,0x40,0x3e,0xe4,0xe0,0x47,0x21,0,0x80,0x06,16,0x3e,0xaa,0x22,0x05,0x20,0xfc])
 if color:
  code+=bytes([0x3e,0x80,0xe0,0x68])
  for byte in [0x1f,0,0xe0,3,0,0x7c,0xff,0x7f]:code+=bytes([0x3e,byte,0xe0,0x69])
 code+=bytes([0x3e,0x0a,0xea,0,0,0xaf,0xea,0,0x40,0x3e,0x42,0xea,0,0xa0,0x3e,0x91,0xe0,0x40])
 for reg,val in [(0x26,0x80),(0x24,0x77),(0x25,0x11),(0x11,0x80),(0x12,0xf0),(0x13,0xd6),(0x14,0x86)]:code+=bytes([0x3e,val,0xe0,reg])
 loop=len(code);code+=bytes([0x3e,0x10,0xe0,0,0xf0,0,0x2f,0xe6,0xf,0xea,1,0xa0,0x18]);code.append((loop-(len(code)+1))&255);rom[0x150:0x150+len(code)]=code
 rom[0x14d]=(-sum(rom[0x134:0x14d])-25)&255
 # Public GBX metadata allows original homebrew recognition without copying Nintendo logo bytes.
 footer=bytearray(64);footer[:4]=b'MBC3';footer[4]=1;footer[6]=1;struct.pack_into('>II',footer,8,32768,8192);struct.pack_into('>III',footer,48,64,1,0);footer[60:64]=b'GBX!';rom+=footer;(out/('original.'+ext)).write_bytes(rom)
with zipfile.ZipFile(out/'original.zip','w',zipfile.ZIP_DEFLATED)as z:z.write(out/'original.gbc','original.gbc')
(out/'core-test.cpp').write_text('''// (AI-assisted) Real GB/GBC execution using original homebrew with GBX metadata.
#include "core_session.h"
#include "games.h"
#include "controller_bindings.h"
#include <cassert>
#include <algorithm>
#include <cstdio>
int main(int argc,char**argv){assert(argc==2);std::string root=argv[1],error;for(auto ext:{"gb","gbc"}){std::vector<uint8_t> rom;assert(gbc::ReadRom(root+"/original."+ext,rom,error));gbc::Session s(root+"/saves");s.SetOption("mgba_skip_bios","ON");assert(s.Load("original."+std::string(ext),rom));bool heard=false;for(int i=0;i<20;++i){s.Run();heard|=std::any_of(s.audio.begin(),s.audio.end(),[](auto v){return v!=0;});}assert(heard);assert(s.width==160&&s.height==144&&s.pixels.size()==160*144);assert(s.fps>59.72&&s.fps<59.74);assert(s.audio.size()>0);auto first=s.pixels[0];assert(std::any_of(s.pixels.begin(),s.pixels.end(),[&](auto p){return p!=first;}));auto* ram=(uint8_t*)retro_get_memory_data(RETRO_MEMORY_SAVE_RAM);assert(ram&&ram[0]==0x42);gbc::ControllerBindings c;c.Load({});c.Update(0,0);s.buttons[0]=c.Update(0x4000,1).joypad;s.Run();assert(ram[1]&1);assert(s.SaveState());ram[5]=0x99;assert(s.LoadState());assert(ram[5]!=0x99);ram[9]=0x77;assert(s.SaveBattery());assert(s.Unload());assert(s.Load("original."+std::string(ext),rom));ram=(uint8_t*)retro_get_memory_data(RETRO_MEMORY_SAVE_RAM);assert(ram[9]==0x77);assert(retro_get_memory_size(RETRO_MEMORY_RTC)>0);assert(s.Unload());printf("PASS %s: real 160x144 video, audio frames, %.8f FPS, inputs, SRAM/state and RTC save support\\n",ext,s.fps);}std::vector<uint8_t> zip,raw;assert(gbc::ReadRom(root+"/original.zip",zip,error));assert(gbc::ReadRom(root+"/original.gbc",raw,error)&&zip==raw);auto games=gbc::Scan({root});assert(games.size()==3);}
''')
subprocess.run(['cmake','--build',str(r/'gbc/build-core-host'),'--target','mgba_libretro','-j4'],check=True,stdout=open(out/'host-build.log','w'),stderr=subprocess.STDOUT)
subprocess.run(['clang++-18','-std=c++20','-O1','-I'+str(r/'gbc/src'),'-I'+str(r/'gbc/include'),'-I'+str(r/'ps5/frontend'),str(out/'core-test.cpp'),*[str(r/'gbc/src'/n)for n in ['core_session.cpp','games.cpp','controller_bindings.cpp']],str(r/'ps5/frontend/fe_nfs.cpp'),str(r/'gbc/build-core-host/mgba_libretro.so'),'-Wl,-rpath,'+str(r/'gbc/build-core-host'),'-lz','-pthread','-o',str(out/'core-test')],check=True)
subprocess.run([str(out/'core-test'),str(out)],check=True)
