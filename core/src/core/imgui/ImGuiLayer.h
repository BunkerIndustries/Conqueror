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
        std::unordered_map<std::string, ImGuiID> dockPanelQueue;

        void ApplicationPanel(const float dt, bool first);
        void CustomPanel(const float dt, bool first);
        void LayerPanel(const float dt, bool first);
        void InspectorPanel(const float dt, bool first);
        void ViewPortPanel(const float dt, bool first);

        glm::vec2 viewportSize;
        glm::vec2 viewportBounds[2];

        glm::ivec2 mousePosViewportRelative;

        GameObject* selectedGameobject = nullptr;

        std::unordered_map<std::string, void*> variablePool;


    public:
        ImGuiLayer();
    	~ImGuiLayer() override;

        void OnAttach() override;
        void OnDetach() override;
        void Update(const float dt) override;
        void Imgui(const float dt) override;
        void OnEvent(Event& e) override { }

        void Begin(const float dt);
        void End();

        void ScreenPanel();

        void DockPanel(std::string name, ImGuiID dock_id);
        void AddVariable(std::string name, void* variable);

        glm::ivec2 GetMousePosViewportRelative() const { return mousePosViewportRelative; }
        bool IsMouseInsideViewport() const { return mousePosViewportRelative.x >= 0 && mousePosViewportRelative.y >= 0 && mousePosViewportRelative.x < viewportSize.x&& mousePosViewportRelative.y < viewportSize.y; }

        ImGuiID GetDockspaceMain() const { return dock_id_main; }
        ImGuiID GetDockspaceTop() const { return dock_id_top; }
        ImGuiID GetDockspaceBottom() const { return dock_id_down; }
        ImGuiID GetDockspaceLeft() const { return dock_id_left; }
        ImGuiID GetDockspaceRight() const { return dock_id_right; }
        ImGuiID GetDockspaceRight2() const { return dock_id_right2; }
        ImGuiID GetDockspaceLeftBottom() const { return dock_id_left_bottom; }

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