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

#include "cpu_sleep_patch.hpp"

#include <vector>

#include <sgd2mapi.hpp>
#include "ingame_sleep_patch/ingame_sleep_patch.hpp"

namespace sgd2csp {

std::vector<mapi::GamePatch> MakeCpuSleepPatches() {
  std::vector<mapi::GamePatch> patches;

  std::vector<mapi::GamePatch> ingame_sleep_patches;

  switch (d2::GetRunningGameVersionId()) {
    case d2::GameVersion::k1_13C: {
      ingame_sleep_patches = MakeIngameSleepPatches();

      break;
    }
  }

  patches.insert(
      patches.end(),
      std::make_move_iterator(ingame_sleep_patches.begin()),
      std::make_move_iterator(ingame_sleep_patches.end())
  );

  return patches;
}

} // namespace sgd2csp
