/******************************************************************************
 * Copyright © 2013-2019 The Komodo Platform Developers.                      *
 *                                                                            *
 * See the AUTHORS, DEVELOPER-AGREEMENT and LICENSE files at                  *
 * the top-level directory of this distribution for the individual copyright  *
 * holder information and the developer policies on copyright and licensing.  *
 *                                                                            *
 * Unless otherwise agreed in a custom licensing agreement, no part of the    *
 * Komodo Platform software, including this file may be copied, modified,     *
 * propagated or distributed except according to the terms contained in the   *
 * LICENSE file                                                               *
 *                                                                            *
 * Removal or modification of this copyright notice is prohibited.            *
 *                                                                            *
 ******************************************************************************/

#pragma once

#include <cassert>
#include <windows.h> //! HMODULE, GetModuleHandleW, GetModuleFileNameW
#include <filesystem>
#include <string>

namespace antara::gaming::core::details
{
    std::filesystem::path binary_real_path() noexcept
    {
        HMODULE hModule = GetModuleHandleW(NULL);
        assert(hModule != nullptr);
        WCHAR path[MAX_PATH];
        auto result = GetModuleFileNameW(hModule, path, MAX_PATH);
        return std::filesystem::path(path);
    }

    std::filesystem::path assets_real_path() noexcept
    {
        return binary_real_path().parent_path() / "assets";
    }
}