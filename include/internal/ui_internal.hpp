//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#pragma once

#include <unordered_map>

//external
#include "imgui.h"
#include "input.hpp"

using KalaKit::KalaInput;
using KalaKit::Key;

using std::unordered_map;
using std::size;

namespace Internal
{
	class UI_Internal
	{
	public:
		static inline unordered_map<Key, ImGuiKey> imguikeyMap =
		{
			{ Key::A, ImGuiKey_A }, { Key::B, ImGuiKey_B }, { Key::C, ImGuiKey_C },
			{ Key::D, ImGuiKey_D }, { Key::E, ImGuiKey_E }, { Key::F, ImGuiKey_F },
			{ Key::G, ImGuiKey_G }, { Key::H, ImGuiKey_H }, { Key::I, ImGuiKey_I },
			{ Key::J, ImGuiKey_J }, { Key::K, ImGuiKey_K }, { Key::L, ImGuiKey_L },
			{ Key::M, ImGuiKey_M }, { Key::N, ImGuiKey_N }, { Key::O, ImGuiKey_O },
			{ Key::P, ImGuiKey_P }, { Key::Q, ImGuiKey_Q }, { Key::R, ImGuiKey_R },
			{ Key::S, ImGuiKey_S }, { Key::T, ImGuiKey_T }, { Key::U, ImGuiKey_U },
			{ Key::V, ImGuiKey_V }, { Key::W, ImGuiKey_W }, { Key::X, ImGuiKey_X },
			{ Key::Y, ImGuiKey_Y }, { Key::Z, ImGuiKey_Z },

			{ Key::Escape, ImGuiKey_Escape },
			{ Key::Tab, ImGuiKey_Tab },
			{ Key::Enter, ImGuiKey_Enter },
			{ Key::Backspace, ImGuiKey_Backspace },
			{ Key::Insert, ImGuiKey_Insert },
			{ Key::Delete, ImGuiKey_Delete },
			{ Key::Home, ImGuiKey_Home },
			{ Key::End, ImGuiKey_End },
			{ Key::PageUp, ImGuiKey_PageUp },
			{ Key::PageDown, ImGuiKey_PageDown },
			{ Key::Left, ImGuiKey_LeftArrow },
			{ Key::Right, ImGuiKey_RightArrow },
			{ Key::Up, ImGuiKey_UpArrow },
			{ Key::Down, ImGuiKey_DownArrow },

			{ Key::Space, ImGuiKey_Space },
			{ Key::LeftControl, ImGuiKey_LeftCtrl },
			{ Key::RightControl, ImGuiKey_RightCtrl },
			{ Key::LeftShift, ImGuiKey_LeftShift },
			{ Key::RightShift, ImGuiKey_RightShift },
			{ Key::LeftAlt, ImGuiKey_LeftAlt },
			{ Key::RightAlt, ImGuiKey_RightAlt },

			{ Key::F1, ImGuiKey_F1 }, { Key::F2, ImGuiKey_F2 }, { Key::F3, ImGuiKey_F3 },
			{ Key::F4, ImGuiKey_F4 }, { Key::F5, ImGuiKey_F5 }, { Key::F6, ImGuiKey_F6 },
			{ Key::F7, ImGuiKey_F7 }, { Key::F8, ImGuiKey_F8 }, { Key::F9, ImGuiKey_F9 },
			{ Key::F10, ImGuiKey_F10 }, { Key::F11, ImGuiKey_F11 }, { Key::F12, ImGuiKey_F12 },
		};

		static void UpdateImGuiInput()
		{
			ImGuiIO& io = ImGui::GetIO();

			//mouse position
			kvec2 mousePos = KalaInput::GetMousePosition();
			io.MousePos = ImVec2(
				mousePos.x,
				mousePos.y);

			//mouse buttons
			io.MouseDown[0] = KalaInput::IsKeyHeld(Key::MouseLeft);
			io.MouseDown[1] = KalaInput::IsKeyHeld(Key::MouseRight);
			io.MouseDown[2] = KalaInput::IsKeyHeld(Key::MouseMiddle);
			io.MouseDown[3] = KalaInput::IsKeyHeld(Key::MouseX1);
			io.MouseDown[4] = KalaInput::IsKeyHeld(Key::MouseX2);

			//mouse wheel
			float mouseWheelDelta = KalaInput::GetMouseWheelDelta();
			io.MouseWheel += mouseWheelDelta;

			//keyboard
			for (const auto& [InternalKey, ImGuiKey] : imguikeyMap)
			{
				io.AddKeyEvent(ImGuiKey, KalaInput::IsKeyHeld(InternalKey));
			}
		}
	};
}