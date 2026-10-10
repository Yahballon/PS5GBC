from pathlib import Path
import subprocess,urllib.request
r=Path(__file__).resolve().parents[2];out=r/'gbc/build-tests'
(out/'v2-test.cpp').write_text('''// (AI-assisted) Confirm actual defaults and Libretro cover-name matching.
#include "cover_urls.h"
#include "fe_options.h"
#include <map>
#include <cassert>
#include <iostream>
int main(){std::map<std::string,std::string> defaults;for(auto& group:fe::OptionGroups())for(auto& row:group.items)defaults[row.key]=row.def;
assert(defaults["GBC/Resolution"]=="4K");assert(defaults["GBC/Graphics"]=="Enhanced");assert(defaults["GBC/Aspect"]=="Stretch");assert(defaults["GBC/Integer"]=="true");assert(defaults["GBC/VSync"]=="false");
fe::GameInfo a;a.stem="Pokemon - Emerald Version (USA, Europe)";a.title="Pokemon - Emerald Version";auto u=gbc::CoverUrls(a);assert(u.size()==1&&u[0].find("Emerald%20Version%20%28USA%2C%20Europe%29.png")!=std::string::npos);std::cout<<u[0]<<"\\n";
fe::GameInfo b;b.stem="Pokémon - Smaragd-Edition (Germany) [patched]";b.title="Pokémon - Smaragd-Edition";auto v=gbc::CoverUrls(b);assert(v.size()==1&&v[0].find("Smaragd")!=std::string::npos&&v[0].find("Germany")!=std::string::npos);std::cout<<v[0]<<"\\n";
fe::GameInfo c;c.stem="Unknown Original Homebrew (USA)";assert(gbc::CoverUrls(c)[0].starts_with("https://thumbnails.libretro.com/"));}
''')
subprocess.run(['clang++-18','-std=c++20','-O1','-ffunction-sections','-fdata-sections','-I'+str(r/'gbc/src'),'-I'+str(r/'ps5/frontend'),'-I'+str(r/'3rdparty/vulkan/include'),str(out/'v2-test.cpp'),str(r/'ps5/frontend/fe_options.cpp'),'-Wl,--gc-sections','-o',str(out/'v2-test')],check=True)
urls=subprocess.check_output([str(out/'v2-test')],text=True).splitlines()
for url in urls:
 data=urllib.request.urlopen(url,timeout=20).read();assert data.startswith(b'\x89PNG\r\n\x1a\n');print('Cover HTTP 200 / valid PNG:',len(data),'bytes')
print('PASS all five defaults, Emerald and German accented/patched title matching; both live cover PNGs verified')
