#include "Menu.h"

void CMenu::Run(IDirect3DDevice9 *pDevice)
{
	static bool init = false;
	if (!init)
	{
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(FindWindowA(0, "Team Fortress 2"));
		ImGui_ImplDX9_Init(pDevice);

		ImGuiStyle &Style       = ImGui::GetStyle();
		Style.WindowTitleAlign	= ImVec2(0.5f, 0.5f);
		Style.FrameBorderSize   = 1.0f;
		Style.FramePadding      = ImVec2(4.0f, 2.0f);
		Style.ItemSpacing       = ImVec2(8.0f, 2.0f);
		Style.WindowBorderSize  = 1.0f;
		Style.TabBorderSize     = 1.0f;
		Style.WindowRounding    = 0.0f;
		Style.ChildRounding     = 0.0f;
		Style.FrameRounding     = 0.0f;
		Style.ScrollbarRounding = 0.0f;
		Style.GrabRounding      = 0.0f;
		Style.TabRounding       = 0.0f;

		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg]               = ImVec4(0.01f, 0.01f, 0.01f, 1.00f);
		colors[ImGuiCol_ChildBg]                = ImVec4(0.01f, 0.01f, 0.01f, 1.00f);
		colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border]                 = ImVec4(0.08f, 0.08f, 0.08f, 0.50f);
		colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg]                = ImVec4(0.04f, 0.04f, 0.04f, 0.54f);
		colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.06f, 0.06f, 0.06f, 0.54f);
		colors[ImGuiCol_FrameBgActive]          = ImVec4(0.06f, 0.06f, 0.06f, 0.54f);
		colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		colors[ImGuiCol_TitleBgActive]          = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg]              = ImVec4(0.01f, 0.01f, 0.01f, 1.00f);
		colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.71f, 0.57f, 0.57f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark]              = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_SliderGrab]             = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_SliderGrabActive]       = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_Button]                 = ImVec4(0.08f, 0.08f, 0.08f, 0.40f);
		colors[ImGuiCol_ButtonHovered]          = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_ButtonActive]           = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_Header]                 = ImVec4(0.06f, 0.06f, 0.06f, 0.54f);
		colors[ImGuiCol_HeaderHovered]          = ImVec4(0.06f, 0.06f, 0.06f, 0.54f);
		colors[ImGuiCol_HeaderActive]           = ImVec4(0.06f, 0.06f, 0.06f, 0.54f);
		colors[ImGuiCol_Separator]              = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
		colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
		colors[ImGuiCol_SeparatorActive]        = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
		colors[ImGuiCol_ResizeGrip]             = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
		colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		colors[ImGuiCol_Tab]                    = ImVec4(0.08f, 0.08f, 0.08f, 0.40f);
		colors[ImGuiCol_TabHovered]             = ImVec4(0.25f, 0.25f, 0.25f, 0.40f);
		colors[ImGuiCol_TabActive]              = ImVec4(0.25f, 0.25f, 0.25f, 0.40f);
		colors[ImGuiCol_TabUnfocused]           = ImVec4(0.15f, 0.21f, 0.28f, 0.97f);
		colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
		colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.08f, 0.08f, 0.08f, 0.54f);
		colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

		init = true;
	}

	if (GetAsyncKeyState(VK_INSERT) & 1) {
		bOpen = !bOpen;
		gInts.Surface->SetCursorAlwaysVisible(bOpen); //also disables game's mouse clicks
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (bOpen)
	{
		if (ImGui::Begin(windowTitle, nullptr, windowFlags))
		{
			static bool windowInit = false;
			if (!windowInit) {
				ImGui::SetWindowPos(ImVec2(static_cast<float>(windowX), static_cast<float>(windowY)));
				ImGui::SetWindowSize(ImVec2(static_cast<float>(windowW), static_cast<float>(windowH)));
				windowInit = true;
			}

			if (ImGui::BeginTabBar("tabs", ImGuiTabBarFlags_NoTooltip))
			{
				Utils::clamp(gESP.CustomFOV, 70, 130);
				Utils::clamp(gAimbot.AimFov, 1.0f, 180.0f);

				if (ImGui::BeginTabItem("aimbot"))
				{
					static const char *szKeys[]		= { "lshift", "lbutton" };
					static const char *szHitbox[]	= { "head", "body", "auto" };

					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

					if (ImGui::BeginChild("main_child", ImVec2(static_cast<float>(windowW) / 3.15f, static_cast<float>(windowH) / 2.5f), true))
					{
						ImGui::Text("main");
						ImGui::PushItemWidth(90.0f);

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Checkbox("active", &gAimbot.Active);

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Checkbox		("silent",				&gAimbot.Silent);
						ImGui::Checkbox		("autoshoot",			&gAimbot.Autoshoot);
						ImGui::Checkbox		("wait for headshot",	&gAimbot.WaitForHS);
						ImGui::Checkbox		("scoped only",			&gAimbot.ScopedOnly);
						ImGui::Combo		("key",					&gAimbot.AimKey, szKeys, IM_ARRAYSIZE(szKeys));
						ImGui::InputFloat	("fov",					&gAimbot.AimFov, 1.0f, 1.0f, 0);
						ImGui::SliderFloat	("aim time",			&gAimbot.AimTime, 0.0f, 1.0f, "%.1f", 1.0f);
						
						ImGui::PopItemWidth();
						ImGui::EndChild();
					}

					ImGui::SameLine();

					if (ImGui::BeginChild("melee_child", ImVec2(static_cast<float>(windowW) / 3.15f, static_cast<float>(windowH) / 2.5f), true))
					{
						ImGui::Text("melee");
						ImGui::PushItemWidth(90.0f);

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Checkbox("melee aim", &gAimbot.AimMelee);

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Checkbox("in range only",	&gAimbot.InRangeOnly);
						ImGui::Checkbox("aim at closest",	&gAimbot.AimAtClosest);
						ImGui::Checkbox("auto backstab",	&gAimbot.AutoBackstab);

						ImGui::PopItemWidth();
						ImGui::EndChild();
					}

					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

					if (ImGui::BeginChild("player_child", ImVec2(static_cast<float>(windowW) / 3.15f, 0.0f), true))
					{
						ImGui::Text("players");
						ImGui::PushItemWidth(90.0f);

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Checkbox("highlight target", &gAimbot.HighlightTarget);

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Checkbox("ignore cloaked",	&gAimbot.IgnoreCloaked);
						ImGui::Checkbox("ignore taunting",	&gAimbot.IgnoreTaunting);
						ImGui::Checkbox("remove disguise",	&gAimbot.RemoveDisguise);

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Combo	("hitbox",			&gAimbot.AimHitbox, szHitbox, IM_ARRAYSIZE(szHitbox));
						ImGui::Checkbox	("multipoint",		&gAimbot.Multipoint);
						ImGui::Checkbox	("hitscan",			&gAimbot.Hitscan);

						ImGui::PopItemWidth();
						ImGui::EndChild();
					}

					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("esp"))
				{
					static const char *szTextPos[]		= { "top right", "bottom left", "center" };
					static const char *szBar[]			= { "off", "vertical", "horizontal" };

					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

					if (ImGui::BeginChild("main_child", ImVec2(static_cast<float>(windowW) / 3.15f, static_cast<float>(windowH) / 3.0f), true))
					{
						ImGui::Text("main");
						ImGui::PushItemWidth(90.0f);

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Checkbox("active", &gESP.Active);

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Checkbox	("players",		&gESP.Players);
						ImGui::Checkbox	("buildings",	&gESP.Buildings);
						ImGui::Checkbox	("pickups",		&gESP.Pickups);

						ImGui::PopItemWidth();
						ImGui::EndChild();
					}

					ImGui::SameLine();

					if (ImGui::BeginChild("local_child", ImVec2(static_cast<float>(windowW) / 3.15f, static_cast<float>(windowH) / 3.0f), true))
					{
						ImGui::Text("local");
						ImGui::PushItemWidth(90.0f);

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Checkbox("spectator list",	&gESP.SpectatorList);
						ImGui::Checkbox("thirdperson",		&gESP.Thirdperson);
						ImGui::Checkbox("remove scope",		&gESP.NoScope);
						ImGui::Checkbox("remove zoom",		&gESP.NoZoom);
						ImGui::InputInt("fov override",		&gESP.CustomFOV);

						ImGui::PopItemWidth();
						ImGui::EndChild();
					}

					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

					if (ImGui::BeginChild("player_child", ImVec2(static_cast<float>(windowW) / 3.15f, 0.0f), true))
					{
						static const char *szBones[] = { "off", "esp", "white" };

						ImGui::Text("players");
						ImGui::PushItemWidth(90.0f);

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Combo("text pos",			&gESP.PlayerTextPos, szTextPos, IM_ARRAYSIZE(szTextPos));
						ImGui::Checkbox("no teammates",		&gESP.NoTeammatePlayers);
						ImGui::Checkbox("ignore cloaked",	&gESP.IgnoreCloaked);

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Checkbox	("name",		&gESP.PlayerName);
						ImGui::Checkbox	("health",		&gESP.PlayerHealth);
						ImGui::Checkbox	("class",		&gESP.PlayerClass);
						ImGui::Checkbox	("cond",		&gESP.PlayerCond);
						ImGui::Checkbox	("box",			&gESP.PlayerBox);
						ImGui::Combo	("healthbar",	&gESP.PlayerHealthBar,	szBar,		IM_ARRAYSIZE(szBar));
						ImGui::Combo	("bones",		&gESP.PlayerBones,		szBones,	IM_ARRAYSIZE(szBones));

						ImGui::PopItemWidth();
						ImGui::EndChild();
					}

					ImGui::SameLine();

					if (ImGui::BeginChild("building_child", ImVec2(static_cast<float>(windowW) / 3.15f, 0.0f), true))
					{
						ImGui::Text("buildings");
						ImGui::PushItemWidth(90.0f);

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Combo("text pos",		&gESP.BuildingTextPos, szTextPos, IM_ARRAYSIZE(szTextPos));
						ImGui::Checkbox("no teammates", &gESP.NoTeammateBuildings);

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Checkbox	("name",		&gESP.BuildingName);
						ImGui::Checkbox	("health",		&gESP.BuildingHealth);
						ImGui::Checkbox	("cond",		&gESP.BuildingCond);
						ImGui::Checkbox	("box",			&gESP.BuildingBox);
						ImGui::Combo	("healthbar",	&gESP.BuildingHealthBar, szBar, IM_ARRAYSIZE(szBar));

						ImGui::PopItemWidth();
						ImGui::EndChild();
					}

					ImGui::SameLine();

					if (ImGui::BeginChild("pickup_child", ImVec2(static_cast<float>(windowW) / 3.15f, 0.0f), true))
					{
						ImGui::Text("pickups");
						ImGui::PushItemWidth(90.0f);

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Checkbox	("name", &gESP.PickupName);

						ImGui::PopItemWidth();
						ImGui::EndChild();
					}

					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("chams"))
				{
					static const char *szChams[]	 = { "off", "shaded", "flat" };
					static const char *szChamsMode[] = { "visible", "invisible", "always" };

					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

					if (ImGui::BeginChild("main_child", ImVec2(static_cast<float>(windowW) / 3.15f, static_cast<float>(windowH) / 9.0f), true))
					{
						ImGui::Text("main");

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Checkbox("active", &gChams.Active);

						ImGui::EndChild();
					}

					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

					if (ImGui::BeginChild("player_child", ImVec2(static_cast<float>(windowW) / 3.15f, static_cast<float>(windowH) / 3.5f), true))
					{
						ImGui::Text("players");
						ImGui::PushItemWidth(90.0f);

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Checkbox("no teammates", &gChams.NoTeammatePlayers);
						ImGui::Checkbox("cosmetics",	&gChams.PlayerCosmetics);
						ImGui::Checkbox("weapons",		&gChams.PlayerWeapons);

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Combo("type",	&gChams.PlayerChams,		szChams,		IM_ARRAYSIZE(szChams));
						ImGui::Combo("mode",	&gChams.PlayerChamsMode,	szChamsMode,	IM_ARRAYSIZE(szChamsMode));

						ImGui::PopItemWidth();
						ImGui::EndChild();
					}

					ImGui::SameLine();

					if (ImGui::BeginChild("building_child", ImVec2(static_cast<float>(windowW) / 3.15f, static_cast<float>(windowH) / 3.5f), true))
					{
						ImGui::Text("buildings");
						ImGui::PushItemWidth(90.0f);

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Checkbox("no teammates", &gChams.NoTeammateBuildings);

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Combo("type", &gChams.BuildingChams,		szChams,		IM_ARRAYSIZE(szChams));
						ImGui::Combo("mode", &gChams.BuildingChamsMode, szChamsMode,	IM_ARRAYSIZE(szChamsMode));

						ImGui::PopItemWidth();
						ImGui::EndChild();
					}

					ImGui::SameLine();

					if (ImGui::BeginChild("pickup_child", ImVec2(static_cast<float>(windowW) / 3.15f, static_cast<float>(windowH) / 3.5f), true))
					{
						ImGui::Text("pickups");
						ImGui::PushItemWidth(90.0f);

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Combo("type", &gChams.PickupChams,		szChams,		IM_ARRAYSIZE(szChams));
						ImGui::Combo("mode", &gChams.PickupChamsMode,	szChamsMode,	IM_ARRAYSIZE(szChamsMode));

						ImGui::PopItemWidth();
						ImGui::EndChild();
					}

					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("misc"))
				{
					ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

					if (ImGui::BeginChild("movement_child", ImVec2(static_cast<float>(windowW) / 3.15f, static_cast<float>(windowH) / 4.0f), true))
					{
						ImGui::Text("movement");

						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
						ImGui::Separator();
						ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

						ImGui::Checkbox("bunnyhop", &gMisc.Bunnyhop);
						
						ImGui::EndChild();
					}

					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
			
			ImGui::End();
		}
	}

	if (gESP.SpectatorList 
		&& gESP.Active
		&& gInts.Engine->IsInGame()
		&& gInts.Engine->IsConnected()
		&& !gInts.Engine->Con_IsVisible()
		&& !gInts.EngineVGui->IsGameUIVisible())
	{
		std::string title = std::string("spectators (" + std::to_string(gESP.Spectators.size()) + ")###");
		if (ImGui::Begin(title.c_str(), nullptr, windowFlags)) //I just messed around until this whole thing worked xd
		{
			ImGui::SetWindowSize(ImVec2(200.0f, (44.0f + ((ImGui::GetFontSize() + 5.0f) * gESP.Spectators.size()))));
			ImGui::Columns(2);

			ImGui::Text("name");
			ImGui::NextColumn();
			ImGui::SetColumnOffset(ImGui::GetColumnIndex(), (ImGui::GetWindowWidth() / 2.0f));
			ImGui::Text("mode");

			if (gESP.Spectators.size() > 0) {
				ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.0f);
				ImGui::Separator();
			}
			
			for (size_t n = 0; n < gESP.Spectators.size(); n++)
			{
				Spectator_t v = gESP.Spectators.at(n);

				ImGui::NextColumn();
				ImGui::Text(v.name.c_str());
				ImGui::NextColumn();
				ImGui::Text(v.mode.c_str());
				
				if (n < (gESP.Spectators.size() - 1))
					ImGui::Separator();
			}

			ImGui::End();
		}
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

CMenu gMenu;