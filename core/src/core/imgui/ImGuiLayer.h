#pragma once
#include "_Core.h"

#include "layer/Layer.h"

#include <imgui.h>
#include <imgui_internal.h>
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <implot.h>
#include <implot_internal.h>

namespace core {

    class ImGuiLayer : public Layer {
    private:
        ImGuiID dockspace_id = 0;
        ImGuiID dock_id_main = 0;
        ImGuiID dock_id_top = 0;
        ImGuiID dock_id_down = 0;
        ImGuiID dock_id_left = 0;
        ImGuiID dock_id_right = 0;
        ImGuiID dock_id_right2 = 0;
        ImGuiID dock_id_left_bottom = 0;
        std::unordered_map<std::string, ImGuiID> dock_panel_queue;

        void ApplicationPanel(const float dt, bool first);
        void CustomPanel(const float dt, bool first);
        void LayerPanel(const float dt, bool first);
        void InspectorPanel(const float dt, bool first);
        void ViewPortPanel(const float dt, bool first);

        glm::vec2 viewport_size;

        GameObject* selected_gameobject = nullptr;

        std::unordered_map<std::string, void*> variable_pool;


    public:
        ImGuiLayer()
	        : Layer("ImGuiLayer") { }
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void update(const float dt) override { }
        void imgui(const float dt) override;
        void OnEvent(Event& e) override { }

        void begin(const float dt);
        void end();

        void DockPanel(std::string name, ImGuiID dock_id);
        void AddVariable(std::string name, void* variable);

        ImGuiID getDockspaceMAIN() const { return dock_id_main; }
        ImGuiID getDockspaceTOP() const { return dock_id_top; }
        ImGuiID getDockspaceBOTTOM() const { return dock_id_down; }
        ImGuiID getDockspaceLEFT() const { return dock_id_left; }
        ImGuiID getDockspaceRIGHT() const { return dock_id_right; }
        ImGuiID getDockspaceRIGHT2() const { return dock_id_right2; }
        ImGuiID getDockspaceLEFT_BOTTOM() const { return dock_id_left_bottom; }

    };

}

struct ScrollingBuffer {
    int MaxSize;
    int Offset;
    ImVector<ImVec2> Data;
    ScrollingBuffer(int max_size = 2000) {
        MaxSize = max_size;
        Offset = 0;
        Data.resize(max_size);
        for (int i = 0; i < max_size; i++)
        {
            Data[i].x = -i * 0.016f;
            Data[i].y = 10000;
        }
    }
    void AddPoint(float x, float y) {
        if (Data.size() < MaxSize)
            Data.push_back(ImVec2(x, y));
        else {
            Data[Offset] = ImVec2(x, y);
            Offset = (Offset + 1) % MaxSize;
        }
    }
    void Erase() {
        if (Data.size() > 0) {
            Data.shrink(0);
            Offset = 0;
        }
    }
};