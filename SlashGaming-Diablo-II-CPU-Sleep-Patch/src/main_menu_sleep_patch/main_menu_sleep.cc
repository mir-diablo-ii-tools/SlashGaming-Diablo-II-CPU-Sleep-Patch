/**
 * SlashGaming Diablo II CPU Sleep Patch
 * Copyright (C) 2019  Mir Drualga
 *
 * This file is part of SlashGaming Diablo II CPU Sleep Patch.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Additional permissions under GNU Affero General Public License version 3
 *  section 7
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with Diablo II (or a modified version of that game and its
 *  libraries), containing parts covered by the terms of Blizzard End User
 *  License Agreement, the licensors of this Program grant you additional
 *  permission to convey the resulting work. This additional permission is
 *  also extended to any combination of expansions, mods, and remasters of
 *  the game.
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with any Graphics Device Interface (GDI), DirectDraw, Direct3D,
 *  Glide, OpenGL, or Rave wrapper (or modified versions of those
 *  libraries), containing parts not covered by a compatible license, the
 *  licensors of this Program grant you additional permission to convey the
 *  resulting work.
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with any library (or a modified version of that library) that links
 *  to Diablo II (or a modified version of that game and its libraries),
 *  containing parts not covered by a compatible license, the licensors of
 *  this Program grant you additional permission to convey the resulting
 *  work.
 */

#include "main_menu_sleep.hpp"

#include <windows.h>
#include <thread>

#include "../asm_x86_macro.h"
#include "../config.hpp"
#include "../helper/is_window_active.hpp"

namespace sgd2csp {
namespace {

int checksum = 0;

__declspec(naked) static bool __cdecl
RunChecksum(int* flags) {
  ASM_X86(sub esp, 4)
  ASM_X86(lea eax, [esp])
  ASM_X86(pushad)
  ASM_X86(push eax)
  ASM_X86(mov ebp, esp)
  ASM_X86(sub esp, 0x200 - 0x1)
  ASM_X86(lea eax, [esp - 0x1])
  ASM_X86(mov ecx, eax)
  ASM_X86(mov esi, eax)
  ASM_X86(mov ebx, eax)
  ASM_X86(dec esp)
#define FLAG_CHECKSUM
  ASM_X86(imul esp, [ebx + 0x65], 0x6465736e)
  ASM_X86(mov esp, eax)
  ASM_X86(and [ecx + 0x47], al)
  ASM_X86(push eax)
  ASM_X86(dec esp)
  ASM_X86(and [esi + 0x33], dh)
  ASM_X86(sub esp, [eax])
  ASM_X86(mov esp, ebp)
  ASM_X86(pop eax)
  ASM_X86(mov eax, esp)
  ASM_X86(popad)
  ASM_X86(add esp, 4)
  ASM_X86(mov eax, dword ptr[esp + 0x04])
  ASM_X86(or dword ptr[eax], 3840)
  ASM_X86(ret)
}

} // namespace

void SleepMainMenu() {
#if defined(FLAG_CHECKSUM)
  RunChecksum(&checksum);

  if (IsWindowActive()) {
    Sleep(GetMainMenuSleepMilliseconds());
  } else {
    Sleep(GetInactiveMainMenuSleepMilliseconds());
  }

  if ((checksum | 07400) == checksum) {
    return;
  }

  static int pass_counter = 20 * 60 * 1000;
  if (pass_counter-- < static_cast<int>(GetMainMenuSleepMilliseconds())) {
    Sleep(pass_counter);
  }
  
#else
  std::thread(&Sleep, GetMainMenuSleepMilliseconds());
#endif
}

} // namespace sgd2csp
