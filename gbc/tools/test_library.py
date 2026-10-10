from pathlib import Path
import subprocess
r=Path(__file__).resolve().parents[2];out=r/'gbc/build-tests'
(out/'library-settings.cpp').write_text('''// (AI-assisted) GB/GBC file/ZIP scanning and real settings persistence.
#include "games.h"
#include "fe_options.h"
#include "fe_settings.h"
#include "resampler.h"
#include <cassert>
#include <set>
#include <cstdio>
int main(int argc,char**argv){assert(argc==2);std::string root=argv[1],error;std::vector<uint8_t> raw,zip;assert(gbc::ReadRom(root+"/test.gba",raw,error));assert(gbc::ReadRom(root+"/test.zip",zip,error)&&zip==raw);auto games=gbc::Scan({root});assert(games.size()==2);std::set<std::string> keys;for(auto& group:fe::OptionGroups())for(auto& row:group.items)keys.insert(row.key);for(auto key:{"GBC/Graphics","GBC/Resolution","GBC/Aspect","GBC/Integer","GBC/Sharpness","GBC/ColorBoost","GBC/Contrast","GBC/FPS","GBC/VSync","GBC/ButtonA"})assert(keys.count(key));assert(fe::settings::WriteFileAtomic(root+"/settings.ini","GBC/Graphics=Enhanced\\nGBC/ButtonA=Square\\nGBC/Resolution=4K\\n"));std::string config;assert(fe::settings::ReadFile(root+"/settings.ini",config));auto state=fe::settings::ReadState(config);assert(state.kv.size()==3);gbc::Resampler whole,parts;whole.Reset(32768);parts.Reset(32768);std::vector<int16_t> in(65536);for(size_t i=0;i<in.size();++i)in[i]=i%17000;auto expected=whole.Process(in);std::vector<int16_t> joined;for(size_t i=0;i<in.size();i+=512){std::vector<int16_t> chunk(in.begin()+i,in.begin()+i+512);const auto& output=parts.Process(chunk);joined.insert(joined.end(),output.begin(),output.end());}assert(joined==expected&&joined.size()>95990&&joined.size()<96002);puts("PASS GB/GBC ZIP/raw loader, real ROM scan, graphics/control settings persistence and continuous 48-kHz stereo resampling");}
''')
subprocess.run(['clang++-18','-std=c++20','-O1','-ffunction-sections','-fdata-sections','-I'+str(r/'gbc/src'),'-I'+str(r/'gbc/include'),'-I'+str(r/'ps5/frontend'),'-I'+str(r/'3rdparty/vulkan/include'),str(out/'library-settings.cpp'),*[str(r/'gbc/src'/n)for n in ['games.cpp','controller_bindings.cpp']],*[str(r/'ps5/frontend'/n)for n in ['fe_nfs.cpp','fe_settings.cpp','fe_options.cpp']],'-Wl,--gc-sections','-lz','-pthread','-o',str(out/'library-settings')],check=True)
subprocess.run([str(out/'library-settings'),str(out)],check=True)
