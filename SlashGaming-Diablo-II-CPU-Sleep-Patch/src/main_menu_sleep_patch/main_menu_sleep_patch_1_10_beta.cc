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
 *  it with any Glide wrapper (or a modified version of that library),
 *  containing parts not covered by a compatible license, the licensors of
 *  this Program grant you additional permission to convey the resulting
 *  work.
 */

#include "main_menu_sleep_patch_1_10_beta.hpp"

#include "../asm_x86_macro.h"
#include "main_menu_sleep.hpp"

namespace sgd2csp {
namespace {

__declspec(naked) void InterceptionFunc() {
  ASM_X86(push ebp);
  ASM_X86(mov ebp, esp);

  ASM_X86(push eax);
  ASM_X86(push ecx);
  ASM_X86(push edx);

  ASM_X86(call ASM_X86_FUNC(SleepMainMenu));

  ASM_X86(push edx);
  ASM_X86(push ecx);
  ASM_X86(push eax);

  ASM_X86(leave);
  ASM_X86(ret);
}

}

std::vector<mapi::GamePatch> MakeMainMenuSleepPatches_1_10Beta() {
  std::vector<mapi::GamePatch> patches;

  mapi::GamePatch back_branch_patch = mapi::GamePatch::MakeGameBackBranchPatch(
      mapi::GameAddress::FromOffset(mapi::DefaultLibrary::kD2Win, 0xCC40),
      mapi::BranchType::kCall,
      &InterceptionFunc,
      0xCC5C - 0xCC40
  );

  patches.push_back(std::move(back_branch_patch));

  return patches;
}

} // namespace sgd2csp
