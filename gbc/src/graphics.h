// (AI-assisted) Pure GB/GBC viewport calculations shared with the native runtime and tests.
#pragma once
#include <algorithm>
#include <cmath>
namespace gbc {struct Viewport {float x,y,width,height;};
inline Viewport GameViewport(float w,float h,bool stretch,bool integer){float width=std::min(w,h*(160.f/144.f)),height=width*(144.f/160.f);if(stretch){width=w;height=h;}else if(integer){float scale=std::max(1.f,std::floor(std::min(w/160.f,h/144.f)));width=160*scale;height=144*scale;}return {(w-width)/2,(h-height)/2,width,height};}}
