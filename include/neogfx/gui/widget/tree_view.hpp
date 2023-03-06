// tree_view.hpp
/*
  neogfx C++ App/Game Engine
  Copyright (c) 2020 Leigh Johnston.  All Rights Reserved.
  
  This program is free software: you can redistribute it and / or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <neogfx/neogfx.hpp>
#include <neogfx/gui/layout/vertical_layout.hpp>
#include <neogfx/gui/layout/spacer.hpp>
#include <neogfx/gui/widget/list_view.hpp>

namespace neogfx
{
    class tree_view : public list_view
    {
        meta_object(list_view)
    public:
        tree_view(bool aCreateDefaultModels = true, frame_style aFrameStyle = frame_style::SolidFrame, neogfx::scrollbar_style aScrollbarStyle = neogfx::scrollbar_style::Normal);
        tree_view(i_widget& aParent, bool aCreateDefaultModels = true, frame_style aFrameStyle = frame_style::SolidFrame, neogfx::scrollbar_style aScrollbarStyle = neogfx::scrollbar_style::Normal);
        tree_view(i_layout& aLayout, bool aCreateDefaultModels = true, frame_style aFrameStyle = frame_style::SolidFrame, neogfx::scrollbar_style aScrollbarStyle = neogfx::scrollbar_style::Normal);
        ~tree_view();
    };
}