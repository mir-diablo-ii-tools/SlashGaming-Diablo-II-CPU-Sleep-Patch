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

#include "main_menu_sleep_patch.hpp"

#include <vector>

#include <sgd2mapi.hpp>
#include "main_menu_sleep_patch_1_00.hpp"
#include "main_menu_sleep_patch_1_01.hpp"
#include "main_menu_sleep_patch_1_02.hpp"
#include "main_menu_sleep_patch_1_03.hpp"
#include "main_menu_sleep_patch_1_04b.hpp"
#include "main_menu_sleep_patch_1_05.hpp"
#include "main_menu_sleep_patch_1_13c.hpp"
#include "main_menu_sleep_patch_1_13d.hpp"
#include "main_menu_sleep_patch_lod_1_14a.hpp"
#include "main_menu_sleep_patch_lod_1_14b.hpp"
#include "main_menu_sleep_patch_lod_1_14d.hpp"

namespace sgd2csp {

std::vector<mapi::GamePatch> MakeMainMenuSleepPatches() {
  switch (d2::GetRunningGameVersionId()) {
    case d2::GameVersion::k1_00: {
      return MakeMainMenuSleepPatches_1_00();
    }

    case d2::GameVersion::k1_01: {
      return MakeMainMenuSleepPatches_1_01();
    }

    case d2::GameVersion::k1_02: {
      return MakeMainMenuSleepPatches_1_02();
    }

    case d2::GameVersion::k1_03: {
      return MakeMainMenuSleepPatches_1_03();
    }

    case d2::GameVersion::k1_04B_C: {
      return MakeMainMenuSleepPatches_1_04B();
    }

    case d2::GameVersion::k1_05:
    case d2::GameVersion::k1_05B:
    case d2::GameVersion::k1_06:
    case d2::GameVersion::k1_06B: {
      return MakeMainMenuSleepPatches_1_05();
    }

    case d2::GameVersion::k1_13C: {
      return MakeMainMenuSleepPatches_1_13C();
    }

    case d2::GameVersion::k1_13D: {
      return MakeMainMenuSleepPatches_1_13D();
    }

    case d2::GameVersion::kLod1_14A: {
      return MakeMainMenuSleepPatches_Lod1_14A();
    }

    case d2::GameVersion::kLod1_14B:
    case d2::GameVersion::kLod1_14C: {
      return MakeMainMenuSleepPatches_Lod1_14B();
    }

    case d2::GameVersion::kLod1_14D: {
      return MakeMainMenuSleepPatches_Lod1_14D();
    }
  }
}

} // namespace sgd2csp
