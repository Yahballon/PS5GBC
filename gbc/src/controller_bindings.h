// (AI-assisted) GB/GBC controller mapping and edge-triggered emulator shortcuts.
#pragma once
#include <array>
#include <cstdint>
#include <map>
#include <string>
namespace gbc {
struct ButtonDefinition {const char* key;const char* label;const char* fallback;unsigned nes_id;};
inline constexpr ButtonDefinition buttons[]={
 {"GBC/ButtonA","GB/GBC A","Cross",8},{"GBC/ButtonB","GB/GBC B","Circle",0},
 {"GBC/ButtonStart","GB/GBC Start","Options",3},{"GBC/ButtonSelect","GB/GBC Select","Create",2},
 {"GBC/ButtonUp","GB/GBC Up","Up",4},{"GBC/ButtonDown","GB/GBC Down","Down",5},
 {"GBC/ButtonLeft","GB/GBC Left","Left",6},{"GBC/ButtonRight","GB/GBC Right","Right",7}
};
struct Source {const char* name;const char* label;uint32_t mask;bool all;};
inline constexpr Source sources[]={
    {"None","None",0,false},{"Cross","Cross",0x4000,false},{"Circle","Circle",0x2000,false},
    {"Square","Square",0x8000,false},{"Triangle","Triangle",0x1000,false},
    {"Options","Options",8,false},{"Touchpad","Touchpad click",0x40100000,false},{"Create","Create",1,false},
    {"Touchpad/Create","Touchpad / Create",0x40100001,false},
    {"L1","L1",0x400,false},{"R1","R1",0x800,false},{"L2","L2",0x100,false},{"R2","R2",0x200,false},
    {"L3","L3",2,false},{"R3","R3",4,false},{"Up","D-pad Up",0x10,false},{"Down","D-pad Down",0x40,false},
    {"Left","D-pad Left",0x80,false},{"Right","D-pad Right",0x20,false},
    {"L3R3","L3 + R3",6,true},{"L1R1","L1 + R1",0xc00,true}
};
struct ShortcutDefinition {const char* name;const char* label;std::array<const char*,3> fallback;};
inline constexpr ShortcutDefinition shortcuts[]={
    {"Save","Save state",{"L3R3","Up","None"}},
    {"Load","Load state",{"L3R3","Down","None"}},
    {"Menu","Back to menu",{"Touchpad","None","None"}}
};
struct ControllerFrame {uint16_t joypad=0;bool save=false,load=false,menu=false,fast_forward=false;};
class ControllerBindings {
public:
    void Load(const std::map<std::string,std::string>& settings);
    ControllerFrame Update(uint32_t raw,double now);
    bool left_stick_dpad=true;
private:
    std::array<Source,8> mapping{};
    std::array<std::array<Source,3>,3> chords{};
    std::array<bool,3> previous{};
    Source fast_source{};
    bool initialized=false;
    double emergency_since=-1;
};
}
