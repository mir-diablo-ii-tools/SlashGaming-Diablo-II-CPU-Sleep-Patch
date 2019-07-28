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

#include "is_window_active.hpp"

#include <windows.h>

namespace sgd2csp {
namespace {

// Most of the code taken from StackOverflow question 1888863.
struct HandleData {
    unsigned long process_id;
    HWND window_handle;
};

HWND FindMainWindow(unsigned long process_id);
BOOL CALLBACK EnumWindowsProc(HWND handle, LPARAM lParam);
BOOL IsMainWindow(HWND handle);

HWND FindMainWindow(unsigned long process_id) {
  HandleData data;
  data.process_id = process_id;
  data.window_handle = 0;
  EnumWindows(&EnumWindowsProc, (LPARAM)&data);
  return data.window_handle;
}

BOOL CALLBACK EnumWindowsProc(HWND handle, LPARAM lParam) {
  HandleData& data = *(HandleData*)lParam;
  unsigned long process_id = 0;
  GetWindowThreadProcessId(handle, &process_id);
  if (data.process_id != process_id || !IsMainWindow(handle)) {
    return TRUE;
  }
  data.window_handle = handle;
  return FALSE;
}

BOOL IsMainWindow(HWND handle) {
  return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
}

} // namespace

bool IsWindowActive() {
  HWND window_handle = FindMainWindow(GetCurrentProcessId());
  return (window_handle == GetForegroundWindow());
}

} // namespace sgd2csp
