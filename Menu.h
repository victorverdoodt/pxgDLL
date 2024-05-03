#pragma once
#include "stdafx.h"
#include "ComponentBase.hpp"

bool MenuIsOpen = true;

const char * tr(const char*str)
{
	return str;
}

static bool show_app_console = true;
static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
bool bEnabled = true;

void CustomImGUIStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.WindowPadding = ImVec2(14, 14);
	style.FramePadding = ImVec2(8, 8);
	style.ItemSpacing = ImVec2(8, 8);
	style.ItemInnerSpacing = ImVec2(8, 8);

	ImVec4* colors = style.Colors;
	colors[ImGuiCol_FrameBg] = ImVec4(0.48f, 0.16f, 0.16f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.98f, 0.26f, 0.26f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.98f, 0.26f, 0.26f, 0.67f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.48f, 0.16f, 0.16f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.98f, 0.39f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.88f, 0.41f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.47f, 0.98f, 0.26f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.26f, 0.98f, 0.61f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.98f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.98f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.98f, 0.26f, 0.26f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.98f, 0.26f, 0.26f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.98f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.75f, 0.10f, 0.10f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.75f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.98f, 0.26f, 0.26f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.98f, 0.26f, 0.26f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.98f, 0.26f, 0.26f, 0.95f);
	colors[ImGuiCol_Tab] = ImVec4(0.58f, 0.18f, 0.18f, 0.86f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.98f, 0.26f, 0.26f, 0.80f);
	colors[ImGuiCol_TabActive] = ImVec4(0.68f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.15f, 0.07f, 0.07f, 0.97f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.42f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.98f, 0.26f, 0.26f, 0.35f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.98f, 0.26f, 0.26f, 1.00f);
}

void LSMenu()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	if (MenuIsOpen)
	{

		ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
		if (ImGui::Begin("WakeBot", &MenuIsOpen, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse))
		{
			if (ImGui::BeginTabBar("DummyTabBar", ImGuiTabBarFlags_None))
			{
				pComponent::ComponentEvents_onMenu();
				ShowExampleAppConsole(&show_app_console);
				ImGui::EndTabBar();
			}
		}
		//if (ImGui::IsItemHovered() || (ImGui::IsAnyItemFocused() && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0)))
			//ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
		ImGui::End();
		// Rendering
	}
	ImGui::EndFrame();


	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static WNDPROC def_wndproc = nullptr;
LRESULT WINAPI hkWndProc(HWND window, UINT message_type, WPARAM w_param, LPARAM l_param) {

	if (MenuIsOpen)
		ImGui_ImplWin32_WndProcHandler(FindWindow(NULL, "pxgclient_dx9"), message_type, w_param, l_param);

	//if (MenuIsOpen)
	//	return 0;

	return CallWindowProc(def_wndproc, window, message_type, w_param, l_param);
};

static void ImGuiEx(HWND Chwnd, IDirect3DDevice9 * CDevice)
{
	//DirectxMenu(pDevice);
	if (GetAsyncKeyState(VK_INSERT))
	{
		MenuIsOpen = !MenuIsOpen;
	}

	static bool nope = true;
	if (nope)
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		CustomImGUIStyle();
		//ImGui::StyleColorsClassic();
		def_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(Chwnd, GWLP_WNDPROC, LONG_PTR(hkWndProc)));
		// Setup Platform/Renderer bindings
		ImGui_ImplWin32_Init(Chwnd);
		ImGui_ImplDX9_Init(CDevice);
		nope = false;
	}
	LSMenu();
}
