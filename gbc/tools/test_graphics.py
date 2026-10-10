from pathlib import Path
import subprocess,os
r=Path(__file__).resolve().parents[2];out=r/'gbc/build-tests';out.mkdir(exist_ok=True);old=(r/'ps5/frontend/host/fe_host.cpp').read_text();a=old.index('bool ReadAll(');b=old.index('\nstruct Step',a);helpers=old[a:b]
cpp='''// (AI-assisted) Actual Vulkan GB/GBC filter and viewport regression on host.
#include "fe_renderer.h"
#include "graphics.h"
#include <dlfcn.h>
#include <zlib.h>
#include <cassert>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <chrono>
using namespace fe;
'''+helpers+'''
int main(int argc,char**argv){assert(argc==2);std::string root=argv[1];for(uint32_t height:{720u,2160u}){uint32_t width=height*16/9;Gpu gpu;assert(gpu.Init(width,height));Renderer render;assert(render.Init(&gpu.vk,gpu.pd,gpu.device,gpu.qf,gpu.queue,width,height,VK_FORMAT_B8G8R8A8_UNORM,gpu.images,VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL));uint32_t white=0xffffffff;auto* atlas=render.CreateTexture(1,1,VK_FORMAT_R8G8B8A8_UNORM,&white);render.SetAtlas(atlas);std::vector<uint32_t> input(160*144);for(int y=0;y<144;++y)for(int x=0;x<160;++x){input[y*160+x]=x>y?0xffa0c0f0:0xff101010;if(x>120&&y>80)input[y*160+x]=0xff50aa55;}auto* texture=render.CreateTexture(160,144,VK_FORMAT_R8G8B8A8_UNORM,input.data());auto set=render.AllocTextureSet(texture,texture,texture);assert(set);std::vector<uint8_t> original;for(int mode=2;mode<=5;++mode){assert(render.WaitForSlot());if(mode==5){std::fill(input.begin(),input.end(),0xffee2200);assert(render.UpdateTexture(texture,VK_FORMAT_R8G8B8A8_UNORM,input.data()));}FrameDesc f;f.bg.misc[0]=float(width)/height;auto vp=gbc::GameViewport(width,height,false,false);auto v=[&](float x,float y,float u,float t){return UiVertex{x,y,u,t,0xffffffff,.25f,.15f,1.05f,float(mode)};};float x=vp.x,y=vp.y,w=vp.width,h=vp.height;f.ui={v(x,y,0,0),v(x+w,y,1,0),v(x,y+h,0,1),v(x,y+h,0,1),v(x+w,y,1,0),v(x+w,y+h,1,1)};f.game_set=set;f.game_vertices=6;auto start=std::chrono::steady_clock::now();assert(render.Render(f,0,VK_NULL_HANDLE,VK_NULL_HANDLE));std::vector<uint8_t> pixels;assert(render.ReadPixels(0,pixels));assert(pixels.size()==size_t(width)*height*4);if(mode==2)original=pixels;else{size_t different=0;for(size_t i=0;i<pixels.size();++i)if(pixels[i]!=original[i])++different;assert(different>100);}char name[100];snprintf(name,sizeof(name),"/graphics-%up-mode%d.png",height,mode);assert(WritePng(root+name,pixels,width,height));printf("Vulkan %ux%u mode %d host frame %.1f ms\\n",width,height,mode,std::chrono::duration<double,std::milli>(std::chrono::steady_clock::now()-start).count());}render.WaitIdle();render.FreeTextureSet(set);render.DestroyTexture(texture);render.SetAtlas(nullptr);render.DestroyTexture(atlas);render.Shutdown();}auto a=gbc::GameViewport(3840,2160,false,false);assert(a.x==720&&a.width==2400&&a.height==2160);auto b=gbc::GameViewport(1920,1080,false,true);assert(b.width==1120&&b.height==1008);auto c=gbc::GameViewport(1920,1080,true,false);assert(c.width==1920&&c.height==1080);puts("PASS real Vulkan original/smooth/enhanced filters, distinct images and 4K/1080p aspect/integer/stretch viewports (AI-assisted)");}
'''
(out/'graphics-test.cpp').write_text(cpp)
subprocess.run(['clang++-18','-std=c++20','-O1','-I'+str(r/'ps5/frontend'),'-I'+str(r/'gbc/src'),'-I'+str(r/'3rdparty/vulkan/include'),str(out/'graphics-test.cpp'),*[str(r/'ps5/frontend'/n)for n in ['fe_renderer.cpp','fe_vk.cpp']],'-lz','-ldl','-pthread','-o',str(out/'graphics-test')],check=True)
subprocess.run([str(out/'graphics-test'),str(out)],check=True,env=dict(os.environ,VK_ICD_FILENAMES='/usr/share/vulkan/icd.d/lvp_icd.json'),timeout=120)
