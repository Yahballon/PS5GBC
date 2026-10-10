// (AI-assisted) GB/GBC playback hosted by the original PS5SX2 Vulkan shelf.
#pragma once
#include "core_session.h"
#include "controller_bindings.h"
#include "resampler.h"
#include "fe_renderer.h"
#include <memory>
#include <array>
namespace gbc {
class ShelfAudio;
class ShelfRuntime {
public:
    explicit ShelfRuntime(const std::string& directory,const fe::Fonts* text=nullptr);
    ~ShelfRuntime();
    bool Start(const std::string& path,fe::Renderer& renderer);
    bool Build(fe::Renderer& renderer,fe::FrameDesc& frame,uint32_t buttons,double now);
    void Stop(fe::Renderer& renderer);
    bool Active()const{return active;}
    bool UseLeftStickDpad()const{return bindings.left_stick_dpad;}
    std::string error;
private:
    Session core;
    ControllerBindings bindings;
    Resampler resampler;
    std::unique_ptr<ShelfAudio> audio;
    std::string root;
    fe::Texture* menu_atlas=nullptr;
    std::array<fe::Texture*,3> game_textures{};std::array<VkDescriptorSet,3> game_sets{};unsigned texture_slot=0;
    const fe::Fonts* fonts=nullptr;double fps_time=0;unsigned fps_frames=0;float measured_fps=0;
    bool active=false,sound=true;
    std::string aspect="Stretch",mode="Enhanced";
    bool integer=true,correction=false,fps_counter=false;float sharpness=.25f,boost=.15f,contrast=1.05f;
    double previous=0,accumulated=0,last_save=0;
};
}
