/**
 * \file   LuaState.cc
 * \author Lars Froehlich
 * \date   Created on December 3, 2021
 * \brief  Implementation of the LuaState class.
 *
 * \copyright Copyright 2021 Deutsches Elektronen-Synchrotron (DESY), Hamburg
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 2.1 of the license, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

// SPDX-License-Identifier: LGPL-2.1-or-later

#include <hlc/util/exceptions.h>
#include <lua.h>
#include <lauxlib.h>
#include "avtomat/LuaState.h"

namespace avto {


LuaState::LuaState()
{
    state_ = luaL_newstate();

    if (state_ == nullptr)
        throw hlc::Error("Unable to create new LUA state");
}

LuaState::LuaState(LuaState&& other)
    : state_{ other.state_ }
{
    other.state_ = nullptr;
}

LuaState::~LuaState() noexcept
{
    close();
}

void LuaState::close() noexcept
{
    if (state_ == nullptr)
        return;

    lua_close(state_);
    state_ = nullptr;
}

LuaState& LuaState::operator=(LuaState&& other) noexcept
{
    close();

    state_ = other.state_;
    other.state_ = nullptr;
    return *this;
}


} // namespace avto