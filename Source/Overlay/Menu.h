#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <Common/Data.h>
#include <Common/Entitys.h>
#include <Common/Constant.h>
#include <DMALibrary/Memory/Memory.h>
#include <imgui/imgui.h>
#include <imgui/notify.h>

#include "RenderHelper.h"
#include <string>
#include <Utils/KmBox.h>
#include <Utils/KmBoxNet.h>
#include <Utils/Lurker.h>
#include <Utils/MoBox.h>
#include <Utils/Throttler.h>
#include <Utils/Utils.h>
#include "Common/Config.h"
#include <Utils/FNVHash.h>
#include <vector>
#include <tchar.h>
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_win32.h"
#include "../Include/imgui/imgui_internal.h"
#include "../Include/imgui/imgui_freetype.h"
#include <d3d11.h>
#include "imgui/texture.h"
#pragma comment(lib, "D3DX11.lib")
#include <D3DX11tex.h>
#include <cstdlib>
//#include "QPVerify.h"
#include "Overlay/MenuPlayerLists.h"
#include "GlobalConfig.h"
#include <algorithm>
#include <fstream>
#include <iostream>
//#include"MenuWebRadar.h"
extern int currentLanguageIndex;  // 声明全局变量
// 定义骨骼点位置和名称
struct BonePosition {
	ImVec2 pos;
	const char* name;
	int index;
};


static const BonePosition bonePositions[] = {
	{ImVec2(134, 99),  "头部",     0},
	{ImVec2(134, 123), "颈部",     1},
	{ImVec2(134, 147), "胸部",     2},
	{ImVec2(134, 177), "腹部",     3},
	{ImVec2(134, 227), "骨盆",     4},
	{ImVec2(134, 257), "大腿根",   5},
	{ImVec2(86, 152),  "左肩",     6},
	{ImVec2(65, 217),  "左上臂",   7},
	{ImVec2(52, 272),  "左前臂",   8},
	{ImVec2(186, 152), "右肩",     9},
	{ImVec2(205, 217), "右上臂",  10},
	{ImVec2(218, 272), "右前臂",  11},
	{ImVec2(104, 282), "左大腿",  12},
	{ImVec2(101, 355), "左膝盖",  13},
	{ImVec2(94, 447),  "左小腿",  14},
	{ImVec2(165, 282), "右大腿",  15},
	{ImVec2(169, 355), "右膝盖",  16},
	{ImVec2(174, 447), "右小腿",  17}
};

// 保存账号和密码到文件
inline void SaveLoginConfig(const std::string& username, const std::string& password)
{
	std::ofstream outFile("config.txt");
	if (outFile.is_open())
	{
		outFile << username << std::endl;
		outFile << password << std::endl;
		outFile.close();
	}
}

// 读取账号和密码从文件
inline bool LoadLoginConfig(std::string& username, std::string& password)
{
	std::ifstream inFile("config.txt");
	if (inFile.is_open())
	{
		std::getline(inFile, username);
		std::getline(inFile, password);
		inFile.close();
		return true; // 成功读取
	}
	return false; // 文件不存在或者读取失败
}

std::string formatTime(const std::string& input) {
	std::regex timePattern(R"((\d{4})年(\d{1,2})月(\d{1,2})日(\d{1,2})时(\d{1,2})分(\d{1,2})秒)");
	std::smatch match;

	if (std::regex_match(input, match, timePattern)) {
		if (match.size() == 7) {
			// 提取各个部分并格式化为目标格式
			std::string year = match[1];
			std::string month = match[2];
			std::string day = match[3];
			std::string hour = match[4];
			std::string minute = match[5];
			std::string second = match[6];

			return year + "-" + month + "-" + day + "-" + hour + ":" + minute + ":" + second;
		}
	}

	// 如果输入格式不符合预期，返回原始输入
	return input;
}

DWORD picker_flags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview;

void OpenLink(const char* url) {
	ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}

enum class MenuStyle
{
	Dark,
	Light
};

const char* strcasestr_custom(const char* haystack, const char* needle) {
	if (!haystack || !needle) {
		return nullptr;
	}

	while (*haystack) {
		const char* h = haystack;
		const char* n = needle;

		while (*h && *n && (std::tolower(*h) == std::tolower(*n))) {
			h++;
			n++;
		}

		if (!*n) {
			return haystack;
		}

		haystack++;
	}

	return nullptr;
}



int 玩家 = 0; int 物品 = 0; int 自瞄 = 0;int 雷达 = 0;int 设置 = 0;


inline bool Languages = 1;
float tab_size = 0.f;
float arrow_roll = 0.f;
bool tab_opening = false;


float   nickname_font_size = 12.0f;
float   info_font_size = 12.0f;
float   weapon_font_size = 13.0f;

static bool Headcheckbox = false;
static bool Healthcheckbox = false;
static bool Namecheckbox = false;
static bool Distancecheckbox = false;
static bool weaponcheckbox = false;
static bool Filterteams = false;
static bool Filterteams_map = false;
static bool Bonecheckbox = false;
static float boxtk = 1.f;
static float hptk = 1.f;
static float hdtk = 1.f;
static float bonetk = 1.f;
static float accent[4] = { 82.f / 255.f, 250.f / 255.f, 246.f / 255.f, 255.f / 255.f };// { 184.f / 255.f, 45.f / 255.f, 65.f / 255.f, 255.f / 255.f };
inline ImVec4 background = ImColor(27, 24, 29, 255);
inline ImVec4 outline_background = ImColor(27, 29, 32, 255);

RECT menuRect;
//RECT menuRect1;
inline std::vector<std::string> MenuItemTypes  {
		U8("Settings"),
		U8("AR"),
		U8("DMR"),
		U8("Sniper"),
		U8("Shotgun"),
		U8("SMG"),
		U8("LMG"),
		U8("Pistol"),
		U8("Heal"),
		U8("Gear"),
		U8("Muzzle"),
		U8("Grip"),
		U8("Mag"),
		U8("Stock"),
		U8("Scope"),
		U8("Ammo"),
		U8("Throwables"),
		U8("Misc"),

};
std::vector<std::string> itemsChinese = { 
	U8("Skull"), U8("Head"), U8("Neck"), U8("Chest"), U8("Pelvis"),
	U8("L-Shoulder"), U8("L-Elbow"), U8("R-Shoulder"), U8("R-Elbow"),
	U8("L-Hand"), U8("R-Hand"), U8("L-Pelvis"), U8("L-Hip"),
	U8("R-Pelvis"), U8("R-Hip"), U8("L-Foot"), U8("R-Foot") };

int menu_style = 0;
int text_add = 0;
int tabs = 0;
int item_tabs = 0;
MenuStyle currentMenuStyle = MenuStyle::Dark; //初始背景颜色设置

ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;





const char* top_tabs_char[] = { U8("    Aimbot"),  U8("   ESP"), U8("    Item Group"), U8("    Radar"), U8("    Settings") };
const char* top_tabs_icon_char[] = { "o", "c", "m", "M", "f" };
static float tab_alpha = 0.f; /* */ static float tab_add; /* */ static int active_tab = 0; static float anim = 0.f; static float alpha = 0.f;
static std::vector<int> comboSelections(EntityLists.size(), 0); // 初始化所有 Combo 的选项为 0
const std::string WeapType[7] = { "AR", "DMR", "SR", "LMG", "HG", "SG", "SMG" };
const char* top_label = top_tabs_char[0];
const char* top_icon = top_tabs_icon_char[0];
static bool Bones[17] = {
true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
};
static bool SecondBones[17] = {
true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
};
static bool GroggyBones[17] = {
true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
};
static bool visual_flags[11] = {
true, false, false, false, false, false, false, false, false, false, false
};
inline std::vector<WeaponType> MenuItemTypeIndexs  {
	   WeaponType::AR,
	   WeaponType::AR,
	   WeaponType::DMR,
	   WeaponType::SR,
	   WeaponType::SG,
	   WeaponType::SMG,
	   WeaponType::LMG,
	   WeaponType::HG,
	   WeaponType::Drug,
	   WeaponType::Armor,
	   WeaponType::Muzzle,
	   WeaponType::Grip,
	   WeaponType::Magazine,
	   WeaponType::GunButt,
	   WeaponType::Sight,
	   WeaponType::Bullet,
	   WeaponType::Grenade,
	   WeaponType::Other
};
namespace texture
{
	inline ID3D11ShaderResourceView* background = nullptr;
	inline ID3D11ShaderResourceView* logo = nullptr;
	inline ID3D11ShaderResourceView* playermoder = nullptr;
	inline ID3D11ShaderResourceView* weapon_image = nullptr;
	inline ID3D11ShaderResourceView* rank = nullptr;


}
class newMenu
{
public:

	

	static void Setting(std::string type)
	{
		auto& Config = GameData.Config.AimBot.Configs[GameData.Config.AimBot.ConfigIndex].Weapon[type];
		//auto& Config = GameData.Config.AimBot.Configs[GameData.Config.AimBot.ConfigIndex].Weapon[WeapType[item_world]];

		 ImGui::BeginGroup(); {
			
			ImGui::BeginChild(true, U8("Aimbot Control"), "o", ImVec2(306, 470));
			{
				ImGui::Checkbox(U8("Enable"), &Config.enable);

				//ImGui::Checkbox(U8("模型漏打"), &Config.LineTraceSingle);

				ImGui::Checkbox(U8("Wall Highlight"), &GameData.Config.ESP.AdjustableDistance);

				ImGui::Checkbox(U8("Auto Switch FOW"), &Config.FOVenable);

				ImGui::Checkbox(U8("Visible Check"), &Config.VisibleCheck);

				if (自瞄 == 5 || 自瞄 == 4 || 自瞄 == 0 || 自瞄 == 1 || 自瞄 == 2) {
					if (Config.VisibleCheck) {

						ImGui::Checkbox(U8("Auto Trigger"), &Config.AimAndShot);

						ImGui::SliderFloat(U8("Trigger Sens."), &Config.Threshold, 1.0f, 15.0f, "%.1f [F]");

						ImGui::SliderInt(U8("Trigger Delay"), &Config.Delay1, 1, 5000, "%d\xC2\xB0");

						ImGui::SliderInt(U8("Trigger Range"), &Config.banjiAimDistance, 1, 500, "%d\xC2\xB0");
					}

				}
				

				ImGui::Checkbox(U8("Wheel Aim"), &Config.AimWheel);

				ImGui::Checkbox(U8("Wheel FOV"), &GameData.Config.AimBot.ShowWheelFOV);

				ImGui::Checkbox(U8("Bullet Pred"), &Config.Prediction);

				ImGui::Checkbox(U8("Ignore Knocked"), &Config.IgnoreGroggy);

				ImGui::Checkbox(U8("Target Switch"), &Config.AutoSwitch);

				

				ImGui::Checkbox(U8("No Recoil"), &Config.NoRecoil);
				if (!Config.NoRecoil)
					ImGui::Checkbox(U8("Default Recoil"), &Config.OriginalRecoil);

				ImGui::Checkbox(U8("Aim Point"), &GameData.Config.AimBot.ShowPoint);

				ImGui::Checkbox(U8("Show FOV"), &GameData.Config.AimBot.ShowFOV);

				ImGui::Checkbox(U8("NoAmmoNoAim"), &Config.NoBulletNotAim);

				ImGui::Checkbox(U8("Scope Check"), &Config.bIsScoping_CP);

				ImGui::Checkbox(U8("Dynamic FOV"), &Config.DynamicFov);

				ImGui::SliderInt(U8("Recoil Control Time"), &Config.RecoilTime, 0, 20,"%d\xC2\xB0");

				ImGui::Checkbox(U8("Global Recoil"), &GameData.Config.AimBot.qjyaqiang);

				ImGui::SliderFloat(U8("Recoil Y-Axis"), &GameData.Config.AimBot.wybYSpeed, 1.0f, 10.f,"%.1f [F]");

				

				ImGui::Checkbox(U8("Merge Hotkeys"), &Config.HotkeyMerge);

				ImGui::Keybind(U8("Aimbot"), &Config.First.Key);

				ImGui::Keybind(U8("AimLock"), &Config.Second.Key);

				ImGui::Keybind(U8("AimKnocked"), &Config.Groggy.Key);

				ImGui::Keybind(U8("AimWheel(Vehicle)"), &Config.Wheel.Key);

				
				const char* aim_mode[]  { U8("  FOV"), U8("  Distance") };
				ImGui::Combo(U8("Targeting Priority"), &Config.LockMode, aim_mode, IM_ARRAYSIZE(aim_mode));

			}
			ImGui::EndChild(true);
			ImGui::SameLine(); ImGui::SetCursorPosY(GetCursorPosY() - 25);
			ImGui::BeginChild(true, U8("Aim Parameters"), "o", ImVec2(306, 470)); {

				ImGui::ColorEdit4(U8("FOV Color"), GameData.Config.AimBot.FOVColor, picker_flags);

				ImGui::ColorEdit4(U8("WheelLock FOV Color"), GameData.Config.AimBot.WheelFOVColor, picker_flags);

				ImGui::ColorEdit4(U8("AimPoint Color"), GameData.Config.AimBot.PointColor, picker_flags);

				ImGui::SliderInt(U8("AimPoint Size"), &GameData.Config.AimBot.PointSize, 1, 20, "%d\xC2\xB0");

				ImGui::SliderFloat(U8("Predict X"), &Config.AimPre_X, 0.1f, 5.0f, "%.1f [F]");

				ImGui::SliderFloat(U8("Predict Y"), &Config.AimPre_Y, 0.1f, 5.0f, "%.1f [F]");

				ImGui::SliderInt(U8("Max Aim Distance"), &Config.AimDistance, 0, 1000, "%d\xC2\xB0");

				ImGui::SliderInt(U8("Field of View"), &Config.FOV, 0, 180, "%d\xC2\xB0");

				ImGui::SliderFloat(U8("Y-Axis Sens"), &Config.YYSpeed, 0.1f, 5.0f, "%.1f [F]");

				ImGui::SliderFloat(U8("X-Axis Sens"), &Config.XXSpeed, 0.1f, 5.0f, "%.1f [F]");

				ImGui::SliderFloat(U8("Y Smoothing"), &Config.YSpeed, 0.1f, 5.0f, "%.1f [F]");

				ImGui::SliderFloat(U8("X Smoothing"), &Config.XSpeed, 0.1f, 5.0f, " % .1f[F]");

				ImGui::SliderFloat(U8("AimSnap Smoothing"), &Config.AimSpeedMaxFactor, 0.1f, 1.f, "%.1f [F]");

				ImGui::SliderInt(U8("Aim Smoothing Factor"), &Config.InitialValue, 100, 1500, "%d\xC2\xB0");

				ImGui::SliderInt(U8("Max Processing FPS"), &Config.FPS, 0, 1000, "%d\xC2\xB0");

				ImGui::SliderInt(U8("Switch Delay"), &Config.SwitchingDelay, 1, 10, "%d\xC2\xB0");

				ImGui::SliderInt(U8("WheelLock FOV"), &Config.WheelFOV, 1, 360, "%d\xC2\xB0");

				ImGui::SliderFloat(U8("AimWheel Speed"), &Config.AimWheelSpeed, 0.1f, 100.f, "%.1f [F]");
			
			}
			ImGui::EndChild(true);
			ImGui::SameLine(); ImGui::SetCursorPosY(GetCursorPosY() - 95);


			//auto& Config = GameData.Config.AimBot.Configs[GameData.Config.AimBot.ConfigIndex].Weapon[WeapType[item_world]];
			ImGui::BeginChild(true, U8("Aim Target Selection"), "o", ImVec2(295, 540));
			{


				static int combo;
				const char* comboitem[] = { U8("Aim Primary Area"),U8("Lock Area"),U8("Knocked Area") };

				ImGui::Combo(U8("Aim Bones"), &combo, comboitem, IM_ARRAYSIZE(comboitem));
				ImGui::SetCursorPos(ImVec2(12, 65));
				ImGui::Image(texture::playermoder, ImVec2(258, 463), ImVec2(0, 0), ImVec2(1, 1), ImColor(c::image.x, c::image.y, c::image.z, c::image.w));
				if (combo == 0)
				{
					ImGui::SetCursorPos(ImVec2(134, 99));
					ImGui::Checkbox_hitbox("BONE 1", &Config.First.Bones[0]);
					ImGui::SetCursorPos(ImVec2(134, 123));
					ImGui::Checkbox_hitbox("BONE 2", &Config.First.Bones[1]);
					ImGui::SetCursorPos(ImVec2(134, 147));
					ImGui::Checkbox_hitbox("BONE 3", &Config.First.Bones[2]);
					ImGui::SetCursorPos(ImVec2(134, 177));
					ImGui::Checkbox_hitbox("BONE 4", &Config.First.Bones[3]);
					ImGui::SetCursorPos(ImVec2(134, 227));
					ImGui::Checkbox_hitbox("BONE 5", &Config.First.Bones[4]);
					ImGui::SetCursorPos(ImVec2(134, 257));
					ImGui::Checkbox_hitbox("BONE 6", &Config.First.Bones[5]);
					ImGui::SetCursorPos(ImVec2(86, 152));
					ImGui::Checkbox_hitbox("BONE 7", &Config.First.Bones[6]);
					ImGui::SetCursorPos(ImVec2(65, 217));
					ImGui::Checkbox_hitbox("BONE 8", &Config.First.Bones[7]);
					ImGui::SetCursorPos(ImVec2(52, 272));
					ImGui::Checkbox_hitbox("BONE 9", &Config.First.Bones[8]);
					ImGui::SetCursorPos(ImVec2(186, 152));
					ImGui::Checkbox_hitbox("BONE 10", &Config.First.Bones[9]);
					ImGui::SetCursorPos(ImVec2(205, 217));
					ImGui::Checkbox_hitbox("BONE 11", &Config.First.Bones[10]);
					ImGui::SetCursorPos(ImVec2(218, 272));
					ImGui::Checkbox_hitbox("BONE 12", &Config.First.Bones[11]);
					ImGui::SetCursorPos(ImVec2(104, 282));
					ImGui::Checkbox_hitbox("BONE 13", &Config.First.Bones[12]);
					ImGui::SetCursorPos(ImVec2(101, 355));
					ImGui::Checkbox_hitbox("BONE 14", &Config.First.Bones[13]);
					ImGui::SetCursorPos(ImVec2(94, 447));
					ImGui::Checkbox_hitbox("BONE 15", &Config.First.Bones[14]);
					ImGui::SetCursorPos(ImVec2(165, 282));
					ImGui::Checkbox_hitbox("BONE 16", &Config.First.Bones[15]);
					ImGui::SetCursorPos(ImVec2(169, 355));
					ImGui::Checkbox_hitbox("BONE 17", &Config.First.Bones[16]);
					ImGui::SetCursorPos(ImVec2(174, 447));
					ImGui::Checkbox_hitbox("BONE 18", &Config.First.Bones[17]);
				}
				else if (combo == 1)
				{

					ImGui::SetCursorPos(ImVec2(134, 99));
					ImGui::Checkbox_hitbox("BONE 1", &Config.Second.Bones[0]);
					ImGui::SetCursorPos(ImVec2(134, 123));
					ImGui::Checkbox_hitbox("BONE 2", &Config.Second.Bones[1]);
					ImGui::SetCursorPos(ImVec2(134, 147));
					ImGui::Checkbox_hitbox("BONE 3", &Config.Second.Bones[2]);
					ImGui::SetCursorPos(ImVec2(134, 177));
					ImGui::Checkbox_hitbox("BONE 4", &Config.Second.Bones[3]);
					ImGui::SetCursorPos(ImVec2(134, 227));
					ImGui::Checkbox_hitbox("BONE 5", &Config.Second.Bones[4]);
					ImGui::SetCursorPos(ImVec2(134, 257));
					ImGui::Checkbox_hitbox("BONE 6", &Config.Second.Bones[5]);
					ImGui::SetCursorPos(ImVec2(86, 152));
					ImGui::Checkbox_hitbox("BONE 7", &Config.Second.Bones[6]);
					ImGui::SetCursorPos(ImVec2(65, 217));
					ImGui::Checkbox_hitbox("BONE 8", &Config.Second.Bones[7]);
					ImGui::SetCursorPos(ImVec2(52, 272));
					ImGui::Checkbox_hitbox("BONE 9", &Config.Second.Bones[8]);
					ImGui::SetCursorPos(ImVec2(186, 152));
					ImGui::Checkbox_hitbox("BONE 10", &Config.Second.Bones[9]);
					ImGui::SetCursorPos(ImVec2(205, 217));
					ImGui::Checkbox_hitbox("BONE 11", &Config.Second.Bones[10]);
					ImGui::SetCursorPos(ImVec2(218, 272));
					ImGui::Checkbox_hitbox("BONE 12", &Config.Second.Bones[11]);
					ImGui::SetCursorPos(ImVec2(104, 282));
					ImGui::Checkbox_hitbox("BONE 13", &Config.Second.Bones[12]);
					ImGui::SetCursorPos(ImVec2(101, 355));
					ImGui::Checkbox_hitbox("BONE 14", &Config.Second.Bones[13]);
					ImGui::SetCursorPos(ImVec2(94, 447));
					ImGui::Checkbox_hitbox("BONE 15", &Config.Second.Bones[14]);
					ImGui::SetCursorPos(ImVec2(165, 282));
					ImGui::Checkbox_hitbox("BONE 16", &Config.Second.Bones[15]);
					ImGui::SetCursorPos(ImVec2(169, 355));
					ImGui::Checkbox_hitbox("BONE 17", &Config.Second.Bones[16]);
					ImGui::SetCursorPos(ImVec2(174, 447));
					ImGui::Checkbox_hitbox("BONE 18", &Config.Second.Bones[17]);
				}
				else if (combo == 2)
				{

					ImGui::SetCursorPos(ImVec2(134, 99));
					ImGui::Checkbox_hitbox("BONE 1", &Config.Groggy.Bones[0]);
					ImGui::SetCursorPos(ImVec2(134, 123));
					ImGui::Checkbox_hitbox("BONE 2", &Config.Groggy.Bones[1]);
					ImGui::SetCursorPos(ImVec2(134, 147));
					ImGui::Checkbox_hitbox("BONE 3", &Config.Groggy.Bones[2]);
					ImGui::SetCursorPos(ImVec2(134, 177));
					ImGui::Checkbox_hitbox("BONE 4", &Config.Groggy.Bones[3]);
					ImGui::SetCursorPos(ImVec2(134, 227));
					ImGui::Checkbox_hitbox("BONE 5", &Config.Groggy.Bones[4]);
					ImGui::SetCursorPos(ImVec2(134, 257));
					ImGui::Checkbox_hitbox("BONE 6", &Config.Groggy.Bones[5]);
					ImGui::SetCursorPos(ImVec2(86, 152));
					ImGui::Checkbox_hitbox("BONE 7", &Config.Groggy.Bones[6]);
					ImGui::SetCursorPos(ImVec2(65, 217));
					ImGui::Checkbox_hitbox("BONE 8", &Config.Groggy.Bones[7]);
					ImGui::SetCursorPos(ImVec2(52, 272));
					ImGui::Checkbox_hitbox("BONE 9", &Config.Groggy.Bones[8]);
					ImGui::SetCursorPos(ImVec2(186, 152));
					ImGui::Checkbox_hitbox("BONE 10", &Config.Groggy.Bones[9]);
					ImGui::SetCursorPos(ImVec2(205, 217));
					ImGui::Checkbox_hitbox("BONE 11", &Config.Groggy.Bones[10]);
					ImGui::SetCursorPos(ImVec2(218, 272));
					ImGui::Checkbox_hitbox("BONE 12", &Config.Groggy.Bones[11]);
					ImGui::SetCursorPos(ImVec2(104, 282));
					ImGui::Checkbox_hitbox("BONE 13", &Config.Groggy.Bones[12]);
					ImGui::SetCursorPos(ImVec2(101, 355));
					ImGui::Checkbox_hitbox("BONE 14", &Config.Groggy.Bones[13]);
					ImGui::SetCursorPos(ImVec2(94, 447));
					ImGui::Checkbox_hitbox("BONE 15", &Config.Groggy.Bones[14]);
					ImGui::SetCursorPos(ImVec2(165, 282));
					ImGui::Checkbox_hitbox("BONE 16", &Config.Groggy.Bones[15]);
					ImGui::SetCursorPos(ImVec2(169, 355));
					ImGui::Checkbox_hitbox("BONE 17", &Config.Groggy.Bones[16]);
					ImGui::SetCursorPos(ImVec2(174, 447));
					ImGui::Checkbox_hitbox("BONE 18", &Config.Groggy.Bones[17]);

					struct
					{
						int Key = VK_RBUTTON;
						bool Bones[17] = {
							true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
						};
					} First;
				}
			}
			ImGui::EndChild(true);
		 }
		 ImGui::EndGroup();
		

	}
	

	
	static void newmenu(HWND hwnd) {

		ImGuiStyle* style = &ImGui::GetStyle();

		static float color[4] = { 217 / 255.f, 164 / 255.f, 88 / 255.f, 1.f };
		c::accent = { color[0], color[1], color[2], 1.f };
		style->WindowPadding = ImVec2(0, 0);
		style->ItemSpacing = ImVec2(15, 15);
		style->WindowBorderSize = 0;
		style->ScrollbarSize = 10.f;//滚动条宽度

		ImGui::SetNextWindowSize(ImVec2(c::bg::size));

		using namespace ImGui;
		ImGui::Begin("Menu", nullptr, window_flags);
		{
			if (currentMenuStyle == MenuStyle::Dark)
			{
				c::shadow = ImColor(2, 2, 2, 255);
				c::bg::background = ImColor(16, 16, 16, 255);
				c::bg::outline = ImColor(38, 38, 38, 255);
				c::bg::top_bg = ImColor(22, 22, 27, 255);
				c::child::background = ImColor(20, 20, 20, 255);
				c::child::border = ImColor(26, 26, 26, 255);
				c::child::lines = ImColor(36, 36, 36, 255);
				c::checkbox::background = ImColor(26, 26, 26, 255);
				c::checkbox::outline = ImColor(35, 35, 35, 255);
				c::checkbox::mark = ImColor(0, 0, 0, 255);
				c::slider::background = ImColor(26, 26, 26, 255);
				c::button::background = ImColor(26, 26, 26, 255);
				c::button::outline = ImColor(36, 36, 36, 255);
				c::combo::background = ImColor(26, 26, 26, 255);
				c::combo::outline = ImColor(36, 36, 36, 255);
				c::keybind::background = ImColor(26, 26, 26, 255);
				c::input::background = ImColor(26, 26, 26, 255);
				c::input::outline = ImColor(36, 36, 36, 255);
				c::picker::background = ImColor(26, 26, 26, 255);
				c::tabs::line = ImColor(36, 36, 36, 255);
				c::text::text_active = ImColor(255, 255, 255, 255);
				c::text::text_hov = ImColor(255, 255, 255, 185);
				c::text::text = ImColor(255, 255, 255, 75);
				c::scrollbar::bar_active = ImColor(255, 255, 255, 145);
				c::scrollbar::bar_hov = ImColor(255, 255, 255, 125);
				c::scrollbar::bar = ImColor(255, 255, 255, 75);
				c::popup_elements::filling = ImColor(10, 10, 10, 170);

				style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255, 255);

			}
			else if (currentMenuStyle == MenuStyle::Light)
			{
				c::shadow = ImColor(2, 2, 2, 30);
				c::bg::background = ImColor(243, 243, 243, 255);
				c::bg::outline = ImColor(223, 223, 223, 255);
				c::bg::top_bg = ImColor(223, 223, 223, 255);
				c::child::background = ImColor(234, 234, 234, 255);
				c::child::border = ImColor(230, 230, 230, 255);
				c::child::lines = ImColor(239, 239, 239, 255);
				c::checkbox::background = ImColor(251, 251, 251, 255);
				c::checkbox::outline = ImColor(229, 229, 229, 255);
				c::checkbox::mark = ImColor(255, 255, 255, 255);
				c::slider::background = ImColor(251, 251, 251, 255);
				c::button::background = ImColor(251, 251, 251, 255);
				c::button::outline = ImColor(229, 229, 229, 255);
				c::combo::background = ImColor(251, 251, 251, 255);
				c::combo::outline = ImColor(229, 229, 229, 255);
				c::keybind::background = ImColor(251, 251, 251, 255);
				c::input::background = ImColor(251, 251, 251, 255);
				c::input::outline = ImColor(229, 229, 229, 255);
				c::picker::background = ImColor(251, 251, 251, 255);
				c::tabs::line = ImColor(229, 229, 229, 255);
				c::text::text_active = ImColor(0, 0, 0, 255);
				c::text::text_hov = ImColor(0, 0, 0, 185);
				c::text::text = ImColor(0, 0, 0, 75);
				c::scrollbar::bar_active = ImColor(255, 255, 255, 145);
				c::scrollbar::bar_hov = ImColor(255, 255, 255, 125);
				c::scrollbar::bar = ImColor(255, 255, 255, 75);
				c::popup_elements::filling = ImColor(235, 235, 235, 170);

				style->Colors[ImGuiCol_Text] = ImColor(0, 0, 0, 255);

			}


			//// 设置菜单区域的坐标和大小用于穿透效果


			if (menu_style == 0)
				currentMenuStyle = MenuStyle::Dark;
			else if (menu_style == 1)
				currentMenuStyle = MenuStyle::Light;

			const ImVec2& pos = ImGui::GetWindowPos();
			const ImVec2& region = ImGui::GetContentRegionMax();

			const ImVec2 size = ImGui::GetWindowSize() ;

			const ImVec2& spacing = style->ItemSpacing;
			menuRect.left = pos.x;
			menuRect.right = size.x + pos.x;
			menuRect.top = pos.y;
			menuRect.bottom = size.y + pos.y;
			GetBackgroundDrawList()->AddShadowRect(pos, pos + ImVec2(region), ImGui::GetColorU32(c::shadow), 80, ImVec2(0, 0), NULL, c::bg::rounding);
			GetBackgroundDrawList()->AddRectFilled(pos, pos + ImVec2(region), ImGui::GetColorU32(c::bg::background), c::bg::rounding);
			GetBackgroundDrawList()->AddRectFilled(pos + ImVec2(0, 49), pos + ImVec2(region.x, 50), ImGui::GetColorU32(c::bg::outline));

			GetBackgroundDrawList()->AddText(font::icomoon_menu, 17, pos + ImVec2((region.x / 2 - (ImGui::CalcTextSize(top_label).x / 2) - ImGui::CalcTextSize(top_icon).x) - 8, 14), GetColorU32(c::text::text), top_icon);
			GetBackgroundDrawList()->AddText(font::calibri_regular, 18, pos + ImVec2((region.x / 2 - (ImGui::CalcTextSize(top_label).x / 2) + ImGui::CalcTextSize(top_icon).x) + 4, 14), GetColorU32(c::text::text), top_label);
			GetBackgroundDrawList()->AddText(font::icomoon_menu, 16.f, pos + ImVec2(20, region.y - 40), GetColorU32(c::text::text), "z");
			GetBackgroundDrawList()->AddText(font::calibri_bold, 17.f, pos + ImVec2(44, region.y - 40), GetColorU32(c::text::text), "EX / PUBG-p2k");
			GetBackgroundDrawList()->AddRectFilled(pos + ImVec2(0, region.y - 70), pos + ImVec2(region.x, region.y - 69), ImGui::GetColorU32(c::bg::outline), c::bg::rounding);

			GetBackgroundDrawList()->AddImage(texture::logo, pos + ImVec2(20, 10), pos + ImVec2(20, 10) + ImVec2(30, 23));
			GetBackgroundDrawList()->AddText(font::calibri_regular, 18, pos + ImVec2(70, 15), GetColorU32(c::text::text), "PUBG-p2k");
			GetBackgroundDrawList()->AddRectFilled(pos + ImVec2(100 + CalcTextSize("PUBG-p2k").x, 20), pos + ImVec2(101 + CalcTextSize("PUBG-p2k").x, 30), ImGui::GetColorU32(c::bg::outline));

			PushFont(font::myth_bold);

			SetCursorPos(ImVec2(region.x - 60, 15));
			ImGui::BeginGroup();

			ImGui::TextColored(c::text::text, U8("-"));

			ImGui::SameLine();

			ImGui::TextColored(c::text::text, U8("×"));

			ImGui::EndGroup();

			PopFont();

			SetCursorPos(ImVec2(region.x / 3, region.y - 60));
			BeginGroup();


			for (int i = 0; i < 5; ++i) {

				if (ImGui::Tabs(tabs == i, top_tabs_icon_char[i], top_tabs_char[i], ImVec2(75, 60))) {
					{
						tabs = i; top_label = top_tabs_char[i]; top_icon = top_tabs_icon_char[i];
					}
				}

				ImGui::SameLine(0, 10.f);

			}
			EndGroup();


			tab_alpha = ImLerp(tab_alpha, (tabs == active_tab) ? 1.f : 0.f, 15.f * ImGui::GetIO().DeltaTime);
			if (tab_alpha < 0.01f && tab_add < 0.01f) active_tab = tabs;

			anim = ImLerp(anim, (tabs == active_tab) ? 1.f : 0.f, 6.f * ImGui::GetIO().DeltaTime);


			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha * style->Alpha);
			{
				if (active_tab == 0)
				{
					ImGui::SetCursorPos(ImVec2(region.x - (tab_alpha * region.x - 18), 190 - (anim * 120)));
					ImGui::BeginChild(false, "Child", "o", ImVec2(1145, 565));
					{
						ImGui::BeginGroup();
						{
							ImGui::BeginChild(true, U8("Aimbot Controller"), "o", ImVec2(180, 540));
							{
								
								const char* youself_char[]{ U8("KMBPRO"), U8("KMNET"), U8("Lurker"), U8("Emulator") };
								ImGui::Combo(U8("Input Controller"), &GameData.Config.AimBot.Controller, youself_char, IM_ARRAYSIZE(youself_char));
								
								if (GameData.Config.AimBot.Controller == 1) {
								
									ImGui::InputTextEx("##IP/", U8("ip"), GameData.Config.AimBot.IP, sizeof(GameData.Config.AimBot.IP), ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 25), ImGuiInputTextFlags_NoLabel);
									ImGui::InputTextEx("##PORT/", U8("port"), GameData.Config.AimBot.Port, sizeof(GameData.Config.AimBot.Port), ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 25), ImGuiInputTextFlags_NoLabel);
									ImGui::InputTextEx("##UUID/", U8("uuid"), GameData.Config.AimBot.UUID, sizeof(GameData.Config.AimBot.UUID), ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 25), ImGuiInputTextFlags_NoLabel);
								}
								
								static std::vector<std::string> ports = Utils::GetCOMPorts();
								
								if (GameData.Config.AimBot.Controller != 1) {
									std::vector<std::pair<std::string, std::string>> portVector;
									for (const auto& port : ports) {
										portVector.push_back({ port, Utils::StringToUTF8(port) });
									}
									std::vector<const char*> items;
									for (const auto& port : portVector) {
										items.push_back(port.second.c_str());
									}

									if (!items.empty())
										ImGui::Combo(U8("COM Port"), &GameData.Config.AimBot.COM, items[0], items.size());
								}
								
								if (ImGui::Button(GameData.Config.AimBot.Connected ? U8("Disconnect") : U8("Connect"), ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 25))) {
									bool Connected = false;
								
									std::string extractedStr;
									if (ports.size() > 0)
								
										extractedStr = Utils::ExtractSubstring(ports[GameData.Config.AimBot.COM], R"(COM(\d+))");
									int COM = 0;
									int number = 0;
									if (extractedStr != "") {
										COM = std::stoi(extractedStr);
										number = std::stoi(extractedStr);
									}
								
									switch (GameData.Config.AimBot.Controller)
									{
									case 0:
										if (!GameData.Config.AimBot.Connected)
										{
											Connected = KmBox::Init(COM);
											if (!Connected)
											{
												ImGui::OpenPopup(U8("Connection failed"));
												//notify->AddNotification(U8("提示"), U8("连接失败"), 3000, gui->get_clr(ImColor(255, 0, 0)));
											}
										}
										else {
											KmBox::Close();
											Connected = false;
										}
										break;
									case 1:
										if (!GameData.Config.AimBot.Connected)
										{
											Connected = KmBoxNet::Init(GameData.Config.AimBot.IP, GameData.Config.AimBot.Port, GameData.Config.AimBot.UUID);
											if (!Connected)
											{
												ImGui::OpenPopup(U8("Connection failed"));
												//notify->AddNotification(U8("提示"), U8("连接失败"), 3000, gui->get_clr(ImColor(255, 0, 0)));
											}
										}
										else {
											KmBoxNet::Close();
											Connected = false;
										}
										break;
									case 2:
										if (!GameData.Config.AimBot.Connected)
										{
											Connected = Lurker::Init(COM);
											if (!Connected)
											{
												ImGui::OpenPopup(U8("Connection failed"));
												//notify->AddNotification(U8("提示"), U8("连接失败"), 3000, gui->get_clr(ImColor(255, 0, 0)));
											}
										}
										else {
											Lurker::Close();
											Connected = false;
										}
										break;
									case 3:
										if (!GameData.Config.AimBot.Connected)
										{
											Connected = MoBox::Init(COM);
											if (!Connected)
											{
												ImGui::OpenPopup(U8("Connection failed"));
												//notify->AddNotification(U8("提示"), U8("连接失败"), 3000, gui->get_clr(ImColor(255, 0, 0)));
											}
										}
										else {
											MoBox::Close();
											Connected = false;
										}
										break;
									}
								
									GameData.Config.AimBot.Connected = Connected;
								
									if (Connected)
										//notify->AddNotification(U8("提示"), U8("端口已连接"), 3000, gui->get_clr(ImColor(150, 255, 123)));
										ImGui::OpenPopup(U8("Port connected"));
									else
										//notify->AddNotification(U8("提示"), U8("连接已断开"), 3000, gui->get_clr(ImColor(150, 255, 123)));
										ImGui::OpenPopup(U8("Connection lost"));
								
								}

								if (ImGui::Button(U8("Test"), ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 25))) {
									switch (GameData.Config.AimBot.Controller)
									{
									case 0:
										KmBox::Move(0, 100);
										break;
									case 1:
										KmBoxNet::Move(0, 100);
										break;
									case 2:
										Lurker::Move(0, 100);
										break;
									case 3:
										MoBox::Move(0, 100);
										break;
									}
								}
								
							}
							ImGui::EndChild(true);
							
						}
						ImGui::EndGroup();
						ImGui::SameLine();

						ImGui::BeginGroup();
						{
							ImGui::BeginChild(true, U8("Weapon Config"), "o", ImVec2(635, 30), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
							{
								ImGui::SetCursorPosY(3);
								
								ImGui::RadioButton(U8("AR"), &自瞄, 0); ImGui::SameLine();
								ImGui::RadioButton(U8("Sniper"), &自瞄, 1); ImGui::SameLine();
								ImGui::RadioButton(U8("DMR"), &自瞄, 2); ImGui::SameLine();
								ImGui::RadioButton(U8("LMG"), &自瞄, 3); ImGui::SameLine();
								ImGui::RadioButton(U8("SMG"), &自瞄, 4); ImGui::SameLine();
								ImGui::RadioButton(U8("Shotgun"), &自瞄, 5);ImGui::SameLine();
								ImGui::RadioButton(U8("Pistol"), &自瞄, 6);ImGui::SameLine();
								ImGui::RadioButton(U8("Recoil Control"), &自瞄, 7);ImGui::SameLine();
								//ImGui::RadioButton(U8("模型绘制"), &自瞄, 8);
							}
							ImGui::EndChild(true);
							
							if (自瞄 == 0) {
								Setting(WeapType[0]);
							}
							else if (自瞄 == 1) {
								Setting(WeapType[2]);
							}
							else if (自瞄 == 2) {
							
								Setting(WeapType[1]);
							}
							else if (自瞄 == 3) {
							
								Setting(WeapType[3]);
							}
							else if (自瞄 == 4) {
							
								Setting(WeapType[6]);
							}
							else if (自瞄 == 5) {
							
								Setting(WeapType[5]);
							}
							else if (自瞄 == 6) {
							
								Setting(WeapType[4]);
							}
							else if (自瞄 == 7) {
								
								 
								ImGui::BeginChild(true, U8("Recoil control"), "o", ImVec2(306, 470));
								{
									ImGui::Checkbox(U8("Enable"), &GameData.Config.AimBot.Recoilenanlek);
							
									 ImGui::SliderInt(U8("Reddot recoil"), &GameData.Config.AimBot.yRecoil[0], 1, 50,  "%.d\xC2\xB0");
							
									 ImGui::SliderInt(U8("2x recoil"), &GameData.Config.AimBot.yRecoil[1], 1, 50, "%d\xC2\xB0");
							
									 ImGui::SliderInt(U8("3x recoil"), &GameData.Config.AimBot.yRecoil[2], 1, 50,  "%d\xC2\xB0");
							
									 ImGui::SliderInt(U8("4x recoil"), &GameData.Config.AimBot.yRecoil[3], 1, 50,  "%d\xC2\xB0");
							
									 ImGui::SliderInt(U8("6x recoil"), &GameData.Config.AimBot.yRecoil[4], 1, 50,  "%d\xC2\xB0");
							
									 ImGui::SliderInt(U8("8x recoil"), &GameData.Config.AimBot.yRecoil[5], 1, 50,  "%d\xC2\xB0");
								}
								ImGui::EndChild(true);
								ImGui::SameLine(); ImGui::SetCursorPosY(GetCursorPosY() - 25);
								ImGui::BeginChild(true, U8("Recoil delay"), "o", ImVec2(306, 470));
								{
									ImGui::SliderInt(U8("Reddot delay"), &GameData.Config.AimBot.interval[0], 1, 10, "%d\xC2\xB0");

									ImGui::SliderInt(U8("2x delay"), &GameData.Config.AimBot.interval[1], 1, 10, "%d\xC2\xB0");

									ImGui::SliderInt(U8("3x delay"), &GameData.Config.AimBot.interval[2], 1, 10,  "%d\xC2\xB0");

									ImGui::SliderInt(U8("4x delay"), &GameData.Config.AimBot.interval[3], 1, 10,  "%d\xC2\xB0");

									ImGui::SliderInt(U8("6x delay"), &GameData.Config.AimBot.interval[4], 1, 10,  "%d\xC2\xB0");

									ImGui::SliderInt(U8("8x delay"), &GameData.Config.AimBot.interval[5], 1, 10,  "%d\xC2\xB0");
								}
								ImGui::EndChild(true);
								ImGui::SameLine(); ImGui::SetCursorPosY(GetCursorPosY() - 95);
								ImGui::BeginChild(true, U8("Target selection"), "o", ImVec2(295, 540));
								{

									ImGui::SetCursorPos(ImVec2(12, 65));
									ImGui::Image(texture::playermoder, ImVec2(258, 463), ImVec2(0, 0), ImVec2(1, 1), ImColor(c::image.x, c::image.y, c::image.z, c::image.w));

									static bool hitbox[20];

									ImGui::SetCursorPos(ImVec2(134, 99));
									ImGui::Checkbox_hitbox("BONE 1", &hitbox[0]);
									ImGui::SetCursorPos(ImVec2(134, 123));
									ImGui::Checkbox_hitbox("BONE 2", &hitbox[1]);
									ImGui::SetCursorPos(ImVec2(134, 147));
									ImGui::Checkbox_hitbox("BONE 3", &hitbox[2]);
									ImGui::SetCursorPos(ImVec2(134, 177));
									ImGui::Checkbox_hitbox("BONE 4", &hitbox[3]);
									ImGui::SetCursorPos(ImVec2(134, 227));
									ImGui::Checkbox_hitbox("BONE 5", &hitbox[4]);
									ImGui::SetCursorPos(ImVec2(134, 257));
									ImGui::Checkbox_hitbox("BONE 6", &hitbox[5]);
									ImGui::SetCursorPos(ImVec2(86, 152));
									ImGui::Checkbox_hitbox("BONE 7", &hitbox[6]);
									ImGui::SetCursorPos(ImVec2(65, 217));
									ImGui::Checkbox_hitbox("BONE 8", &hitbox[7]);
									ImGui::SetCursorPos(ImVec2(52, 272));
									ImGui::Checkbox_hitbox("BONE 9", &hitbox[8]);
									ImGui::SetCursorPos(ImVec2(186, 152));
									ImGui::Checkbox_hitbox("BONE 10", &hitbox[9]);
									ImGui::SetCursorPos(ImVec2(205, 217));
									ImGui::Checkbox_hitbox("BONE 11", &hitbox[10]);
									ImGui::SetCursorPos(ImVec2(218, 272));
									ImGui::Checkbox_hitbox("BONE 12", &hitbox[11]);
									ImGui::SetCursorPos(ImVec2(104, 282));
									ImGui::Checkbox_hitbox("BONE 13", &hitbox[12]);
									ImGui::SetCursorPos(ImVec2(101, 355));
									ImGui::Checkbox_hitbox("BONE 14", &hitbox[13]);
									ImGui::SetCursorPos(ImVec2(94, 447));
									ImGui::Checkbox_hitbox("BONE 15", &hitbox[14]);
									ImGui::SetCursorPos(ImVec2(165, 282));
									ImGui::Checkbox_hitbox("BONE 16", &hitbox[15]);
									ImGui::SetCursorPos(ImVec2(169, 355));
									ImGui::Checkbox_hitbox("BONE 17", &hitbox[16]);
									ImGui::SetCursorPos(ImVec2(174, 447));
									ImGui::Checkbox_hitbox("BONE 18", &hitbox[17]);

									//okbro
								}
								ImGui::EndChild(true);
							
							}
							else if (自瞄 == 8) {
								
								/*ImGui::BeginChild(true, U8("模型绘制"), "o", ImVec2(627, 470));
								{

									ImGui::Checkbox(U8("模型绘制"), &GameData.Config.ESP.PhysXDebug);

									 ImGui::SliderInt(U8("加载距离"), &GameData.Config.ESP.PhysxLoadRadius, 200, 1000,  "%d\xC2\xB0");

									 ImGui::SliderInt(U8("静态刷新"), &GameData.Config.ESP.PhysxStaticRefreshInterval, 300, 3000, "%d\xC2\xB0");

									 ImGui::SliderInt(U8("动态刷新"), &GameData.Config.ESP.PhysxDynamicRefreshInterval, 10, 3000, "%d\xC2\xB0");

									 ImGui::SliderInt(U8("刷新阈值"), &GameData.Config.ESP.PhysxRefreshLimit, 0, 3000,  "%d\xC2\xB0");

								}
								ImGui::EndChild(true);*/
								ImGui::SameLine(); ImGui::SetCursorPosY(GetCursorPosY() - 95);
								ImGui::BeginChild(true, U8("Body Selection"), "o", ImVec2(295, 540));
								{

									ImGui::SetCursorPos(ImVec2(12, 65));
									ImGui::Image(texture::playermoder, ImVec2(258, 463), ImVec2(0, 0), ImVec2(1, 1), ImColor(c::image.x, c::image.y, c::image.z, c::image.w));

									static bool hitbox[20];

									ImGui::SetCursorPos(ImVec2(134, 99));
									ImGui::Checkbox_hitbox("BONE 1", &hitbox[0]);
									ImGui::SetCursorPos(ImVec2(134, 123));
									ImGui::Checkbox_hitbox("BONE 2", &hitbox[1]);
									ImGui::SetCursorPos(ImVec2(134, 147));
									ImGui::Checkbox_hitbox("BONE 3", &hitbox[2]);
									ImGui::SetCursorPos(ImVec2(134, 177));
									ImGui::Checkbox_hitbox("BONE 4", &hitbox[3]);
									ImGui::SetCursorPos(ImVec2(134, 227));
									ImGui::Checkbox_hitbox("BONE 5", &hitbox[4]);
									ImGui::SetCursorPos(ImVec2(134, 257));
									ImGui::Checkbox_hitbox("BONE 6", &hitbox[5]);
									ImGui::SetCursorPos(ImVec2(86, 152));
									ImGui::Checkbox_hitbox("BONE 7", &hitbox[6]);
									ImGui::SetCursorPos(ImVec2(65, 217));
									ImGui::Checkbox_hitbox("BONE 8", &hitbox[7]);
									ImGui::SetCursorPos(ImVec2(52, 272));
									ImGui::Checkbox_hitbox("BONE 9", &hitbox[8]);
									ImGui::SetCursorPos(ImVec2(186, 152));
									ImGui::Checkbox_hitbox("BONE 10", &hitbox[9]);
									ImGui::SetCursorPos(ImVec2(205, 217));
									ImGui::Checkbox_hitbox("BONE 11", &hitbox[10]);
									ImGui::SetCursorPos(ImVec2(218, 272));
									ImGui::Checkbox_hitbox("BONE 12", &hitbox[11]);
									ImGui::SetCursorPos(ImVec2(104, 282));
									ImGui::Checkbox_hitbox("BONE 13", &hitbox[12]);
									ImGui::SetCursorPos(ImVec2(101, 355));
									ImGui::Checkbox_hitbox("BONE 14", &hitbox[13]);
									ImGui::SetCursorPos(ImVec2(94, 447));
									ImGui::Checkbox_hitbox("BONE 15", &hitbox[14]);
									ImGui::SetCursorPos(ImVec2(165, 282));
									ImGui::Checkbox_hitbox("BONE 16", &hitbox[15]);
									ImGui::SetCursorPos(ImVec2(169, 355));
									ImGui::Checkbox_hitbox("BONE 17", &hitbox[16]);
									ImGui::SetCursorPos(ImVec2(174, 447));
									ImGui::Checkbox_hitbox("BONE 18", &hitbox[17]);

								
								}
								ImGui::EndChild(true);

							}
		
						}
						ImGui::EndGroup();

					}
					ImGui::EndChild();

				}
				else if (active_tab == 1)
				{

					 ImGui::SetCursorPos(ImVec2(region.x - (tab_alpha * region.x - 18), 190 - (anim * 120)));

					 ImGui::BeginChild(false, "Child", "o", ImVec2(1145, 565));
					 {
						 ImGui::BeginGroup();
						 {
							 ImGui::BeginChild(true, U8("ESP Settings"), "e", ImVec2(260, 250));//365
							 {
								 ImGui::Checkbox(U8("Enable ESP"), &GameData.Config.ESP.Enable);

								 ImGui::Checkbox(U8("Enemy Alert"), &GameData.Config.ESP.DangerWarning);

								 ImGui::Checkbox(U8("Font Shadow"), &GameData.Config.ESP.Stroke);

								 ImGui::Checkbox(U8("Hide Locked Targets"), &GameData.Config.ESP.LockedHiddenBones);
							 
								 ImGui::Checkbox(U8("Visible Check"), &GameData.Config.ESP.VisibleCheck);

								 ImGui::Checkbox(U8("TargetLock Highlight"), &GameData.Config.ESP.soudingbianse);

								 ImGui::Checkbox(U8("Highlight Official Player"), &GameData.Config.ESP.Partner);

							 }
							 ImGui::EndChild(true);

							 ImGui::BeginChild(true, U8("Value Settings"), "a", ImVec2(260, 250));//365
							 {
								 ImGui::SliderInt(U8("ESP Distance"), &GameData.Config.ESP.DistanceMax, 0, 1000,  "%d\xC2\xB0");
							 
								 ImGui::SliderInt(U8("Info Distance"), &GameData.Config.ESP.InfoDistanceMax, 0, 1000,  "%d\xC2\xB0");
							 
								 ImGui::SliderInt(U8("Weapon Distance"), &GameData.Config.ESP.WeaponDistanceMax, 0, 1000,  "%d\xC2\xB0");
							 
								 ImGui::SliderInt(U8("Skeleton Thickness"), &GameData.Config.ESP.SkeletonWidth, 1, 5, "%d\xC2\xB0");
							 
								 ImGui::SliderInt(U8("Text Size"), &GameData.Config.ESP.FontSize, 8, 28,  "%d\xC2\xB0");
							 }
							 ImGui::EndChild(true);

						 }
						 ImGui::EndGroup();

						 ImGui::SameLine();

						 ImGui::BeginGroup();
						 {

							 ImGui::BeginChild(true, U8("Color Settings"), "e", ImVec2(240, 540));//365
							 {

								 ImGui::ColorEdit4(U8("	Visible Skeleton"), GameData.Config.ESP.Color.Visible.Skeleton, picker_flags);

								 ImGui::ColorEdit4(U8("Visible Info"), GameData.Config.ESP.Color.Visible.Info, picker_flags);

								 ImGui::ColorEdit4(U8("Hidden Skeleton"), GameData.Config.ESP.Color.Default.Skeleton, picker_flags);
							 
								 ImGui::ColorEdit4(U8("Hidden Info"), GameData.Config.ESP.Color.Default.Info, picker_flags);
							 
								 ImGui::ColorEdit4(U8("Bot Skeleton"), GameData.Config.ESP.Color.AI.Skeleton, picker_flags);

								 ImGui::ColorEdit4(U8("Bot Info"), GameData.Config.ESP.Color.AI.Info, picker_flags);
							 
								 ImGui::ColorEdit4(U8("Danger Skeleton"), GameData.Config.ESP.Color.Dangerous.Skeleton, picker_flags);//危险

								 ImGui::ColorEdit4(U8("Danger Info"), GameData.Config.ESP.Color.Dangerous.Info, picker_flags);//危险
							 
								 ImGui::ColorEdit4(U8("Knocked Skeleton"), GameData.Config.ESP.Color.Groggy.Skeleton, picker_flags);

								 ImGui::ColorEdit4(U8("Knocked Info"), GameData.Config.ESP.Color.Groggy.Info, picker_flags);

								 ImGui::ColorEdit4(U8("Targeted Line"), GameData.Config.ESP.Color.Ray.Line, picker_flags);

								 ImGui::ColorEdit4(U8("Target Skeleton"), GameData.Config.ESP.Color.aim.Skeleton, picker_flags);
								 
								 ImGui::ColorEdit4(U8("Blacklist Skeleton"), GameData.Config.ESP.Color.Blacklist.Skeleton, picker_flags);

								 ImGui::ColorEdit4(U8("Blacklist Info"), GameData.Config.ESP.Color.Blacklist.Info, picker_flags);
							 
								 ImGui::ColorEdit4(U8("Whitelist Skeleton"), GameData.Config.ESP.Color.Whitelist.Skeleton, picker_flags);//没有
							
								 ImGui::ColorEdit4(U8("Whitelist Info"), GameData.Config.ESP.Color.Whitelist.Info, picker_flags);//没有


								 ImGui::ColorEdit4(U8("Official Player Skeleton"), GameData.Config.ESP.Color.Partner.Skeleton, picker_flags);

								 ImGui::ColorEdit4(U8("Official Player Info"), GameData.Config.ESP.Color.Partner.Info, picker_flags);

							 }
							 ImGui::EndChild(true);


						 }
						 ImGui::EndGroup();

						 ImGui::SameLine();

						 ImGui::BeginGroup();
						 {

							 ImGui::BeginChild(true, U8("ESP Enable"), "e", ImVec2(260, 540));//365
							 {

								 ImGui::Checkbox(U8("Health Bar"), &GameData.Config.ESP.health_bar);
								
								 ImGui::Checkbox(U8("Player Box"), &GameData.Config.ESP.DisplayFrame);
								 
								 ImGui::Checkbox(U8("Player Skeleton"), &GameData.Config.ESP.Skeleton);

								 ImGui::Checkbox(U8("Player Name"), &GameData.Config.ESP.Nickname);
								 
								 ImGui::Checkbox(U8("Team ID"), &GameData.Config.ESP.TeamID);
								 
								 ImGui::Checkbox(U8("Clan Name"), &GameData.Config.ESP.ClanName);
								 
								 ImGui::Checkbox(U8("Player Level"), &GameData.Config.ESP.等级);

								 ImGui::Checkbox(U8("Player Distance"), &GameData.Config.ESP.Dis);
								 
								 ImGui::Checkbox(U8("Player Health"), &GameData.Config.ESP.Health);

								 ImGui::Checkbox(U8("Disconnect Indicator"), &GameData.Config.ESP.ShowInfos);
							
								 ImGui::Checkbox(U8("Player Weapon"), &GameData.Config.ESP.Weapon);

								 ImGui::Checkbox(U8("Player Kills"), &GameData.Config.ESP.击杀);

								 ImGui::Checkbox(U8("Player Damage"), &GameData.Config.ESP.伤害);

								 ImGui::Checkbox(U8("Targeted Line"), &GameData.Config.ESP.TargetedRay);

								 ImGui::Checkbox(U8("Head Skeleton"), &GameData.Config.ESP.HeadDrawing);

								 ImGui::Checkbox(U8("Rank Icon"), &GameData.Config.ESP.showIcon);

								 ImGui::Checkbox(U8("Player spectate"), &GameData.Config.ESP.观战);

								 ImGui::Checkbox(U8("Player KDA"), &GameData.Config.ESP.KDA);								

								 const char* items[]{ U8("Don't check"), U8("TPP Solo"), U8("TPP Squad"), U8("FPP Solo"), U8("FPP Squad") };
								 ImGui::Combo(U8("Rank Stats"), &GameData.Config.PlayerList.RankMode, items, IM_ARRAYSIZE(items));
								 
								 
								 const char* XueTiaoWEizhi[]{ U8("On top"), U8("On left") };
								 ImGui::Combo(U8("Health bar position"), &GameData.Config.ESP.XueTiaoWEizhi, XueTiaoWEizhi, IM_ARRAYSIZE(XueTiaoWEizhi));

								 const char* HealthBarStyle[]{ U8("Rainbow"), U8("Solid color"), U8("Solid scaling"), U8("Rainbow scaling") };
								 ImGui::Combo(U8("Health bar style"), &GameData.Config.ESP.HealthBarStyle, HealthBarStyle, IM_ARRAYSIZE(HealthBarStyle));

							 }
							 ImGui::EndChild(true);
							 //okbro

						 }
						 ImGui::EndGroup();

						 ImGui::SameLine();

						 ImGui::BeginChild(true, U8("ESP Preview"), "o", ImVec2(330, 540));
						 {
							 
							 if (GameData.Config.Window.Players) ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(149.0f / 255.0f, 1.0f / 255.0f, 247.f / 255.0f, 200.f / 255.f));
							 ImGui::Keybind(U8("Rank List"), &GameData.Config.Overlay.rankList);
							 if (ImGui::Button(GameData.Config.Window.Players ? U8("Close list") : U8("Open list"), ImVec2(ImGui::GetContentRegionMax().x - 20, 20))) {
							 
							 	GameData.Config.Window.Players = !GameData.Config.Window.Players;
							 
							 };

							 ImVec2 childpos = ImGui::GetCursorScreenPos() + ImVec2(0, 20);
							 ImVec2 childsize = GetContentRegionMax();


							 /*if (skeleton)
								 GetWindowDrawList()->AddRect(childpos + ImVec2(90, 35), childpos + ImVec2(90, 35) + ImVec2(155, 310), ImColor(box_col[0], box_col[1], box_col[2]));
							 if (box)
								 GetWindowDrawList()->AddRect(childpos + ImVec2(90, 35), childpos + ImVec2(90, 35) + ImVec2(155, 310), ImColor(box_col[0], box_col[1], box_col[2]));

							 if (healthbar)
								 GetWindowDrawList()->AddRectFilled(childpos + ImVec2(88, 25), childpos + ImVec2(90, 25) + ImVec2(155, 4), ImColor(45, 255, 45));

							 if (teamid)
							 {
								 GetWindowDrawList()->AddCircleFilled(childpos + ImVec2(70, 27), 10, ImColor(175, 65, 255));
								 GetWindowDrawList()->AddText(childpos + ImVec2(67, 18), ImColor(255, 255, 255), "7");
							 }

							 if (name)
								 GetWindowDrawList()->AddText(childpos + ImVec2(148, 7), ImColor(255, 255, 255), "KAKA-PUBG");
							 if (Clan)
								 GetWindowDrawList()->AddText(childpos + ImVec2(110, 7), ImColor(255, 255, 255), "[DMA]");

							 if (rank)
							 {
								 GetWindowDrawList()->AddText(childpos + ImVec2(140, 28), ImColor(255, 255, 255), "");
								 GetWindowDrawList()->AddImage(texture::rank, childpos + ImVec2(117, -11), childpos + ImVec2(117, -11) + ImVec2(20, 20));
							 }

							 if (kda)
								 GetWindowDrawList()->AddText(childpos + ImVec2(145 + CalcTextSize("").x, -7), ImColor(255, 255, 255), "大师 6.00");

							 if (weapon_icon_b)
								 GetWindowDrawList()->AddImage(texture::weapon_image, childpos + ImVec2(120, -30), childpos + ImVec2(120, -30) + ImVec2(95, 26));

							 if (distance)
								 GetWindowDrawList()->AddText(childpos + ImVec2(150, 350), ImColor(255, 255, 255), "1337M");

							 if (health)
								 GetWindowDrawList()->AddText(childpos + ImVec2(150, 365), ImColor(255, 255, 255), "100HP");

							 if (level)
								 GetWindowDrawList()->AddText(childpos + ImVec2(148, 380), ImColor(255, 255, 255), "LV.595");
							 if (dmg)
								 GetWindowDrawList()->AddText(childpos + ImVec2(154, 395), ImColor(255, 255, 255), "S.99");
*/



						 }
						 ImGui::EndChild(true);

					 }
					 ImGui::EndChild();


				}
				 else if (active_tab == 2)
				 {

					 ImGui::SetCursorPos(ImVec2(region.x - (tab_alpha * region.x - 18), 190 - (anim * 120)));

					 ImGui::BeginChild(false, "Child", "o", ImVec2(1145, 565));
					 {
						 ImGui::BeginGroup();
						 {
							 ImGui::BeginChild(true, U8("Item ESP Settings"), "e", ImVec2(365, 215));
							 {
								 ImGui::Checkbox(U8("Item ESP"), &GameData.Config.Item.Enable);
								 
								 ImGui::Checkbox(U8("Item Stack"), &GameData.Config.Item.Combination);

								 ImGui::Checkbox(U8("Loot Filter"), &GameData.Config.Item.AccessoriesFilter);
								 
								 ImGui::Checkbox(U8("Show icon"), &GameData.Config.Item.ShowIcon);

								 ImGui::Keybind(U8("Group A"), &GameData.Config.Item.GroupAKey);

								 ImGui::Keybind(U8("Group B"), &GameData.Config.Item.GroupBKey);

								 ImGui::Keybind(U8("Group C"), &GameData.Config.Item.GroupCKey);

								 ImGui::Keybind(U8("Group D"), &GameData.Config.Item.GroupDKey);

								 ImGui::SliderInt(U8("Item Distance"), &GameData.Config.Item.DistanceMax, 0, 500, "%d\xC2\xB0");

								 ImGui::SliderInt(U8("Item Font/Icon Scale"), &GameData.Config.Item.FontSize, 1, 40, "%d\xC2\xB0");

								 ImGui::Checkbox(U8("Airdrop ESP"), &GameData.Config.AirDrop.Enable);

								 ImGui::Keybind(U8("Airdrop Keys"), &GameData.Config.AirDrop.EnableKey);

								 ImGui::Checkbox(U8("Airdrop Items"), &GameData.Config.AirDrop.ShowItems);

								 ImGui::SliderInt(U8("Airdrop Distance"), &GameData.Config.AirDrop.DistanceMax, 0, 1000, "%d\xC2\xB0");

								 ImGui::SliderInt(U8("Airdrop Font"), &GameData.Config.AirDrop.FontSize, 1, 28, "%d\xC2\xB0");

								 ImGui::Checkbox(U8("Vehicle ESP"), &GameData.Config.Vehicle.Enable);

								 ImGui::Keybind(U8("Vehicle Keys"), &GameData.Config.Vehicle.EnableKey);

								 ImGui::Checkbox(U8("Vehicle HP"), &GameData.Config.Vehicle.Health);

								 ImGui::Checkbox(U8("Vehicle Fuel"), &GameData.Config.Vehicle.Durability);

								 ImGui::SliderInt(U8("Vehicle Distance"), &GameData.Config.Vehicle.DistanceMax, 0, 1000, "%d\xC2\xB0");

								 ImGui::SliderInt(U8("Vehicle Font"), &GameData.Config.Vehicle.FontSize, 1, 28, "%d\xC2\xB0");

								 ImGui::Checkbox(U8("DeadBox ESP"), &GameData.Config.DeadBox.Enable);

								 ImGui::Keybind(U8("DeadBox Key"), &GameData.Config.DeadBox.EnableKey);

								 ImGui::Checkbox(U8("Items in Box"), &GameData.Config.DeadBox.ShowItems);

								 ImGui::SliderInt(U8("DeadBox Distance"), &GameData.Config.DeadBox.DistanceMax, 0, 200,"%d\xC2\xB0");

								 ImGui::SliderInt(U8("DeadBox FontSize"), &GameData.Config.DeadBox.FontSize, 1, 28, "%d\xC2\xB0");
							 }
							 ImGui::EndChild(true);

							 ImGui::BeginChild(true, U8("Color Settings"), "a", ImVec2(365, 285));
							 {
								
								ImGui::ColorEdit4(U8("Group A Color"), GameData.Config.Item.GroupAColor, picker_flags);
																								
								ImGui::ColorEdit4(U8("Group B Color"), GameData.Config.Item.GroupBColor, picker_flags);
																							
								ImGui::ColorEdit4(U8("Group C Color"), GameData.Config.Item.GroupCColor, picker_flags);
																								
								ImGui::ColorEdit4(U8("Group D Color"), GameData.Config.Item.GroupDColor, picker_flags);

								ImGui::ColorEdit4(U8("DeadBox Color"), GameData.Config.DeadBox.Color, picker_flags);								

								ImGui::ColorEdit4(U8("AirDrop Color"), GameData.Config.AirDrop.Color, picker_flags);

								ImGui::ColorEdit4(U8("Vehicle Color"), GameData.Config.Vehicle.Color, picker_flags);

								ImGui::ColorEdit4(U8("Vehicle Fuel Color"), GameData.Config.Vehicle.Fuelbarcolor, picker_flags);

								ImGui::ColorEdit4(U8("Vehicle HP Color"), GameData.Config.Vehicle.Healthbarcolor, picker_flags);
								//ok bro
							 }
							 ImGui::EndChild(true);

						 }
						 ImGui::EndGroup();

						 ImGui::SameLine();

						 ImGui::BeginGroup();
						 {

							 ImGui::BeginChild(true, U8("Loot Group"), "e", ImVec2(745, 58), false, ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
							 {
								 static int item_world;
								 ImGui::RadioButton(U8("Smart Loot"), &物品, 0); ImGui::SameLine();//30109433
								 ImGui::RadioButton(U8("ARs"), &物品, 1); ImGui::SameLine();
								 ImGui::RadioButton(U8("Sniper"), &物品, 2); ImGui::SameLine();
								 ImGui::RadioButton(U8("LMG/Pistols"), &物品,3); ImGui::SameLine();
								 ImGui::RadioButton(U8("SMG/Shotguns"), &物品, 4); ImGui::SameLine();
								 ImGui::RadioButton(U8("Armor/Bags"), &物品, 5); ImGui::SameLine();
								 ImGui::RadioButton(U8("Gear"), &物品, 6); ImGui::SameLine();
								 ImGui::RadioButton(U8("Heals/Nades"), &物品, 7); ImGui::SameLine();
								 ImGui::RadioButton(U8("Ammo"), &物品, 8); ImGui::SameLine();
								 ImGui::RadioButton(U8("Misc"), &物品, 9); ImGui::SameLine();

							 }
							 ImGui::EndChild(true);

							 if (物品 == 0) {

								 ImGui::BeginChild(true, U8("Smart Loot Filter"), "e", ImVec2(745, 442));
								 {
									 ImGui::BeginGroup();
									 {
 
										ImGui::Checkbox(U8("Enable"), &GameData.Config.Item.FilterEnable);
										ImGui::SliderInt(U8("Medkit"), &GameData.Config.Item.Medicalkit, 1, 8);
										ImGui::SliderInt(U8("FirstAidKit"), &GameData.Config.Item.FirstAidKit, 1, 8);
										ImGui::SliderInt(U8("Bandage"), &GameData.Config.Item.Bandage, 1, 8);
										ImGui::SliderInt(U8("Adrenaline"), &GameData.Config.Item.Epinephrine, 1, 8);
										ImGui::SliderInt(U8("PainKiller"), &GameData.Config.Item.PainKiller, 1, 8);
										ImGui::SliderInt(U8("EnergyDrink"), &GameData.Config.Item.EnergyDrink, 1, 8);
										ImGui::SliderInt(U8("Grenade"), &GameData.Config.Item.Grenade, 1, 8);
										ImGui::SliderInt(U8("Flashbang"), &GameData.Config.Item.FlashGrenade, 1, 8);
										ImGui::SliderInt(U8("Smoke"), &GameData.Config.Item.SmokeGrenade, 1, 8);
										ImGui::SliderInt(U8("Molotov"), &GameData.Config.Item.MolotovGrenade, 1, 8);
										ImGui::SliderInt(U8("Bluezone"), &GameData.Config.Item.BluezoneGrenade, 1, 8);
										// ok bro
									 }
									 ImGui::EndGroup();

								 }
								 ImGui::EndChild(true);

							 
							 }
							 else
							 {
								WeaponType Type;
								switch (物品)
								{
								case 1:
									Type = WeaponType::AR;
									break;
								case 2:
									Type = WeaponType::DMR;
									break;
								case 3:
									Type = WeaponType::LMG;
									break;
								case 4:
									Type = WeaponType::SMG;
									break;
								case 5:
									Type = WeaponType::Armor;
									break;
								case 6:
									Type = WeaponType::Sight;
									break;
								case 7:
									Type = WeaponType::Drug;
									break;
								case 8:
									Type = WeaponType::Bullet;
									break;
								case 9:
									Type = WeaponType::Other;
									break;
								}
								
								ImGui::BeginChild(true, U8("Loot Groups"), "e", ImVec2(745, 442));
								{
									static char search_buffer[256] = "";
									//ImGui::InputTextEx(U8("搜索..."), search_buffer, sizeof(search_buffer), ImVec2(330, 35), NULL, 0, 0);//func->c_page.sub_page
									size_t index =1;

									if (ImGui::BeginTable("table_title_null", 3, ImGuiTableFlags_Borders)) {

										ImGui::TableSetupColumn(U8("Loot Icon"));
										ImGui::TableSetupColumn(U8("Loot Name"));
										ImGui::TableSetupColumn(U8("Loot Groups"));
										ImGui::TableHeadersRow();

										for (int row = 0; row < index; row++) {
											for (auto& pair : GameData.Config.Item.Lists) {

												const std::string& key = pair.first;
												ItemDetail& detail = pair.second;

												if (detail.Type != Type && 物品 != 1 && 物品 != 2 && 物品 != 3 && 物品 != 4 && 物品 != 5 && 物品 != 6 && 物品 != 7 && 物品 != 8 && 物品 != 9) {
													continue;
												}
												else if (detail.Type != Type && 物品 == 6)
												{
													if (detail.Type != WeaponType::Sight && detail.Type != WeaponType::Magazine && detail.Type != WeaponType::Muzzle && detail.Type != WeaponType::GunButt && detail.Type != WeaponType::Grip)
														continue;
												}
												else if (detail.Type != Type && 物品 == 3)//机/手
												{
													if (detail.Type != WeaponType::HG && detail.Type != WeaponType::LMG)
														continue;
												}
												else if (detail.Type != Type && 物品 == 1)//步枪
												{
													if (detail.Type != WeaponType::AR)
														continue;
												}
												else if (detail.Type != Type && 物品 == 2)//狙击枪
												{
													if (detail.Type != WeaponType::DMR && detail.Type != WeaponType::SR)
														continue;
												}
												else if (detail.Type != Type && 物品 == 4)//冲/喷
												{
													if (detail.Type != WeaponType::SMG && detail.Type != WeaponType::SG)
														continue;
												}
												else if (detail.Type != Type && 物品 == 5)//防具
												{
													if (detail.Type != WeaponType::Armor)
														continue;
												}
												else if (detail.Type != Type && 物品 == 7)//药/投
												{
													if (detail.Type != WeaponType::Drug && detail.Type != WeaponType::Grenade)
														continue;
												}

												else if (detail.Type != Type && 物品 == 8)//子弹
												{
													if (detail.Type != WeaponType::Bullet)
														continue;
												}
												else if (detail.Type != Type && 物品 == 9)//其他
												{
													if (detail.Type != WeaponType::Other)
														continue;
												}


												std::string displayName = Utils::StringToUTF8(detail.DisplayName);
												std::string searchKeyword = Utils::StringToUTF8(search_buffer);

												ImGui::TableNextRow();
												ImGui::TableSetColumnIndex(0);
												{
													std::string Space = "";
													ImGui::TextUnformatted(Space.c_str());

													std::string ItemName = pair.first;
													std::string IconUrl = "Assets/image/All/" + ItemName + ".png";
													//Utils::Log(1, "GameData.WorldTimeSeconds %f", ItemName.c_str());
													SetCursorPosY(GetCursorPosY() - 22);
													if (GImGuiTextureMap[IconUrl].Width > 0) {
														ImGui::Image((ImTextureID)GImGuiTextureMap[IconUrl].Texture, ImVec2(30, 30));
													}

												}
												ImGui::SameLine();
												SetCursorPosY(GetCursorPosY() + 8);

												std::string TempBuff = search_buffer;

												if (searchKeyword.length() > 2 && displayName.find(TempBuff) == std::string::npos)
													continue;
												std::string name = displayName;
												//std::string name = displayName + "##" + std::to_string(index);
												ImGui::TableSetColumnIndex(1);
												SetCursorPosY(GetCursorPosY() + 8);
												ImGui::Text(name.c_str(), row + 1);


												ImGui::TableSetColumnIndex(2);

												ImGui::PushID(key.c_str());  // 使用物资键作为唯一ID

												const char* Group_item_chinese[] = { U8("Not selected"), U8("Group A"), U8("Group B"), U8("Group C") , U8("Group D") };
												//SetCursorPosY(GetCursorPosY() - 22);
												ImGui::SetNextItemWidth(200);
												if (ImGui::Combo_popup("##COMBO", &detail.Group, Group_item_chinese, IM_ARRAYSIZE(Group_item_chinese)));
												
												ImGui::PopID();


											}



										}
										
										ImGui::EndTable();
									}
								}
								ImGui::EndChild(true);
							 }

						 }
						 ImGui::EndGroup();

					 }
					 ImGui::EndChild();

				 }
				 else if (active_tab == 3)
				 {
					 ImGui::SetCursorPos(ImVec2(region.x - (tab_alpha * region.x - 18), 190 - (anim * 120)));
					 ImGui::BeginChild(false, "Child", "o", ImVec2(1145, 565));
					 {
						 ImGui::BeginGroup();
						 {
							 ImGui::BeginChild(true, U8("Main Radar"), "a", ImVec2(350, 500));
							 {
								 ImGui::Checkbox(U8("Show Players"), &GameData.Config.Radar.Main.ShowPlayer);
								 
								 ImGui::Checkbox(U8("Show Vehicles"), &GameData.Config.Radar.Main.ShowVehicle);
								 
								 ImGui::Checkbox(U8("Show AirDrops"), &GameData.Config.Radar.Main.ShowAirDrop);
								
								 ImGui::Checkbox(U8("Show Dead Boxes"), &GameData.Config.Radar.Main.ShowDeadBox);
								 
								 ImGui::SliderFloat(U8("Radar Zoom"), &GameData.Config.Radar.Main.Map_size, 5.0f, 14.0f,"%.1f [F]");
								 
								 ImGui::SliderInt(U8("Icon Size"), &GameData.Config.Radar.Main.FontSize, 1, 20, "%d\xC2\xB0");
								 
							 }
							 ImGui::EndChild(true);
						 }
						 ImGui::EndGroup();

						 ImGui::SameLine();

						 ImGui::BeginGroup();
						 {
							 ImGui::BeginChild(true, U8("Mini Radar"), "a", ImVec2(350, 500));
							 {
								 ImGui::Checkbox(U8("Show Players"), &GameData.Config.Radar.Mini.ShowPlayer);
								 
								 ImGui::Checkbox(U8("Show Vehicles"), &GameData.Config.Radar.Mini.ShowVehicle);
								 
								 ImGui::Checkbox(U8("Show AirDrops"), &GameData.Config.Radar.Mini.ShowAirDrop);
								 
								 ImGui::Checkbox(U8("Show Dead Boxes"), &GameData.Config.Radar.Main.ShowAirDrop);
								 
								 ImGui::SliderFloat(U8("Radar Zoom"), &GameData.Config.Radar.Mini.Map_size, 5.0f, 14.0f, "%.1f [F]");
								 
								 ImGui::SliderInt(U8("Icon Size"), &GameData.Config.Radar.Mini.FontSize, 1, 20, "%d\xC2\xB0");
								 
							 }
							 ImGui::EndChild(true);

						 }
						 ImGui::EndGroup();

						 ImGui::SameLine();

						 ImGui::BeginGroup();
						 {
							 ImGui::BeginChild(true, U8("Web Radar"), "a", ImVec2(350, 500));
							 {
								
								 char address[512];
								 snprintf(address, sizeof(address), "http://%s:7891", GameData.Config.ESP.服务器IP);

								 ImGui::TextColored(c::text::text, U8("Enter the server's public IP address)"));
								 ImGui::Separator();
								 ImGui::InputTextEx("##WIP/", U8("Server IP:"), GameData.Config.ESP.服务器IP, IM_ARRAYSIZE(GameData.Config.ESP.服务器IP), ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 25), ImGuiInputTextFlags_NoLabel);
								 ImGui::TextColored(c::text::text, U8("After running the radar server, share the generated URL with your teammates"));
								 ImGui::Separator();
								 ImGui::InputTextEx("##GIP/", U8("View URL:"), address, IM_ARRAYSIZE(GameData.Config.ESP.服务器IP), ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 25), ImGuiInputTextFlags_NoLabel);
								 // 添加链接按钮
								 if (ImGui::Button(U8("Open the browser"), ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 25))) {
									 OpenLink(address);
									 // 在这里添加打开链接的逻辑
								 }
								 ImGui::Separator();
								 ImGui::TextColored(c::text::text, U8("On the opened page, go to Settings > Server"));
								 ImGui::Separator();
								 ImGui::TextColored(c::text::text, U8("your-public-ip:7891/WS"));
							 }
							 ImGui::EndChild(true);
						 }
						 ImGui::EndGroup();

					 }
					 ImGui::EndChild();
					}
				 else if (active_tab == 4)
				 {

					 ImGui::SetCursorPos(ImVec2(region.x - (tab_alpha * region.x - 18), 190 - (anim * 120)));

					 ImGui::BeginChild(false, "Child", "o", ImVec2(1145, 565));
					 {
						 ImGui::BeginGroup();
						 {
							 ImGui::BeginChild(true, U8("Theme Color"), "e", ImVec2(220, 245), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
							 {
								 ImGui::ColorPicker4("Accent", color);
							 }
							 ImGui::EndChild(true);

							 ImGui::BeginChild(true, U8("Bot Color"), "e", ImVec2(220, 245), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
							 {
								 ImGui::ColorPicker4("Menu Model", (float*)&c::image);
							 }
							 ImGui::EndChild(true);


						 }
						 ImGui::EndGroup();

						 ImGui::SameLine();

						 ImGui::BeginGroup();
						 {
							 ImGui::BeginChild(true, U8("Grenade Warning"), "e", ImVec2(445, 295));
							 {
								 ImGui::Checkbox(U8("Explosion Alert"), &GameData.Config.Project.Enable);
								 
								 ImGui::Checkbox(U8("Explosion Radius"), &GameData.Config.Project.FOV);
								 
								 ImGui::Checkbox(U8("GrenadePrediction"), &GameData.Config.Project.GrenadePrediction);

								 ImGui::Checkbox(U8("Text Countdown"), &GameData.Config.Project.TextShowChareTime);

								 ImGui::Checkbox(U8("Grenade Timer"), &GameData.Config.Project.ShowChareTime);

								 ImGui::Checkbox(U8("Bar Timer"), &GameData.Config.Project.BarShowChareTime);
								 
								 ImGui::ColorEdit4(U8("Alert Color"), GameData.Config.Project.ChareColor, picker_flags);
								 
								 ImGui::SliderInt(U8("Font Size"), &GameData.Config.Project.ChareFontSize, 5, 20,  "%d\xC2\xB0");

							 }
							 ImGui::EndChild(true);
							 ImGui::BeginChild(true, U8("Radar Alert"), "e", ImVec2(445, 195));
							 {
								 ImGui::Checkbox(U8("Enable"), &GameData.Config.Early.Enable);

								 ImGui::Checkbox(U8("Show Distance"), &GameData.Config.Early.ShowDistance);

								 ImGui::SliderInt(U8("Max Detection Range"), &GameData.Config.Early.DistanceMax, 10, 1000, "%d\xC2\xB0");

								 ImGui::SliderInt(U8("Icon Scale"), &GameData.Config.Early.FontSize, 5, 20, "%d\xC2\xB0");
							 }
							 ImGui::EndChild(true);
						 }
						 ImGui::EndGroup();

						 ImGui::SameLine();

						 ImGui::BeginGroup();
						 {
							 
							 ImGui::BeginChild(true, U8("Advanced Settings"), "e", ImVec2(445, 530));
							 {
								 ImGui::Checkbox(U8("Aim Direction Mode"), &GameData.Config.Overlay.zhixiangmoshi);
								 
								 ImGui::Checkbox(U8("Enable V-Sync"), &GameData.Config.Overlay.VSync);

								 ImGui::Checkbox(U8("Backup Camera Cache"), &GameData.Config.Overlay.UseLastFrameCameraCache);

								 ImGui::Checkbox(U8("Enable Multithreading"), &GameData.Config.Overlay.UseThread);

								 ImGui::Checkbox(U8("Fog Filter"), &GameData.Config.ESP.miwu);	

								 if (ImGui::Checkbox(U8("Overlay Fusion Mode"), &GameData.Config.Overlay.FusionMode)) {
									 HWND Progman = FindWindowA("Progman", NULL);
									 if (GameData.Config.Overlay.FusionMode)
									 {
										 if (Progman)
										 {
											 ShowWindow(Progman, SW_HIDE);

										 }
									 }
									 else if (Progman)
									 {
										 ShowWindow(Progman, SW_SHOW);

									 }
								 }
								 
								 ImGui::Keybind(U8("Quit key"), &GameData.Config.Overlay.Quit_key);
								 
								 ImGui::Keybind(U8("Menu key"), &GameData.Config.Menu.ShowKey);
								 
								
								 ImGui::Keybind(U8("Fuser key"), &GameData.Config.Overlay.FusionModeKey);
								 
								 ImGui::Keybind(U8("Combat Mode"), &GameData.Config.ESP.FocusModeKey);

								 ImGui::Keybind(U8("FpsView"), &GameData.Config.ESP.DataSwitchkey);

								 ImGui::Keybind(U8("Show Teammates"), &GameData.Config.ESP.duiyouKey);
								 
								 ImGui::Keybind(U8("Clear Cache"), &GameData.Config.Function.ClearKey);



								 const char* style[] = { U8("Dark"),U8("Light") };
								 ImGui::Combo(U8("Menu Theme"), &menu_style, style, IM_ARRAYSIZE(style));
							 }
							 ImGui::EndChild(true);
						 }
						 ImGui::EndGroup();
					 }
					 ImGui::EndChild();
					 }
			};
			ImVec2 windowPos = ImGui::GetWindowPos();
			ImVec2 windowSize = ImGui::GetWindowSize();
			ImVec2 buttonSize = ImVec2(120, 28);

			// Lùi nút Save sang trái một chút (khoảng cách giữa 2 nút là 10px)
			ImVec2 savePos = ImVec2(windowPos.x + windowSize.x - buttonSize.x * 2 - 30, windowPos.y + windowSize.y - buttonSize.y - 20);

			// Nút Quit sát góc phải
			ImVec2 quitPos = ImVec2(windowPos.x + windowSize.x - buttonSize.x - 20, windowPos.y + windowSize.y - buttonSize.y - 20);

			// Vẽ nút Save
			ImGui::SetCursorPos(ImVec2(savePos.x - windowPos.x, savePos.y - windowPos.y));
			if (ImGui::Button("Save Config", buttonSize)) {
				if (Config::Save()) {
					ImGui::InsertNotification({ ImGuiToastType_Success, 3000, "Save OK" });
				}
				else {
					ImGui::InsertNotification({ ImGuiToastType_Error, 3000, "Save error" });
				}
			}

			// Vẽ nút Quit
			ImGui::SetCursorPos(ImVec2(quitPos.x - windowPos.x, quitPos.y - windowPos.y));
			if (ImGui::Button("Quit", buttonSize)) {
				HWND Progman = FindWindowA("Progman", NULL);
				ShowWindow(Progman, SW_SHOW);
				exit(0);
			}


		}
		ImGui::End();
		ImGui::RenderNotifications();


	
	};

};
