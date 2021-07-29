// layout_item_cache.hpp
/*
  neogfx C++ App/Game Engine
  Copyright (c) 2015, 2020 Leigh Johnston.  All Rights Reserved.
  
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
#include <neogfx/core/object.hpp>
#include <neogfx/gui/layout/i_anchor.hpp>
#include <neogfx/gui/layout/i_layout.hpp>
#include <neogfx/gui/layout/i_layout_item.hpp>
#include <neogfx/gui/layout/i_layout_item_cache.hpp>

namespace neogfx
{
    class layout_item_cache : public object<reference_counted<i_layout_item_cache>>
    {
    public:
        layout_item_cache(i_layout_item& aItem);
        layout_item_cache(i_ref_ptr<i_layout_item> const& aItem);
        layout_item_cache(const layout_item_cache& aOther);
        ~layout_item_cache();
    public:
        i_anchor& anchor_to(i_anchorable& aRhs, const i_string& aLhsAnchor, anchor_constraint_function aLhsFunction, const i_string& aRhsAnchor, anchor_constraint_function aRhsFunction) override;
        const anchor_map_type& anchors() const override;
        anchor_map_type& anchors() override;
    public:
        const i_string& id() const override;
        void set_id(const i_string& aId) override;
    public:
        bool is_layout() const override;
        const i_layout& as_layout() const override;
        i_layout& as_layout() override;
        bool is_spacer() const override;
        const i_spacer& as_spacer() const override;
        i_spacer& as_spacer() override;
        bool is_widget() const override;
        const i_widget& as_widget() const override;
        i_widget& as_widget() override;
    public:
        bool has_parent_layout_item() const override;
        const i_layout_item& parent_layout_item() const override;
        i_layout_item& parent_layout_item() override;;
    public:
        bool has_parent_layout() const override;
        const i_layout& parent_layout() const override;
        i_layout& parent_layout() override;
        void set_parent_layout(i_layout* aParentLayout);
        bool has_layout_owner() const override;
        const i_widget& layout_owner() const override;
        i_widget& layout_owner() override;
        void set_layout_owner(i_widget* aOwner) override;
        bool has_layout_manager() const override;
        const i_widget& layout_manager() const override;
        i_widget& layout_manager() override;
        bool is_layout_item_cache() const override;
        const i_layout_item_cache& as_layout_item_cache() const override;
        i_layout_item_cache& as_layout_item_cache() override;
    public:
        bool high_dpi() const override;
        dimension dpi_scale_factor() const override;
    public:
        bool device_metrics_available() const override;
        const i_device_metrics& device_metrics() const override;
    public:
        point origin() const override;
        void reset_origin() const override;
        point position() const override;
        void set_position(const point& aPosition) override;
        size extents() const override;
        void set_extents(const size& aExtents) override;
        bool has_size_policy() const noexcept override;
        neogfx::size_policy size_policy() const override;
        void set_size_policy(const optional_size_policy& aSizePolicy, bool aUpdateLayout = true) override;
        bool has_weight() const noexcept override;
        size weight() const override;
        void set_weight(optional_size const& aWeight, bool aUpdateLayout = true) override;
        bool has_minimum_size() const noexcept override;
        bool is_minimum_size_constrained() const noexcept override;
        size minimum_size(optional_size const& aAvailableSpace = optional_size{}) const override;
        void set_minimum_size(optional_size const& aMinimumSize, bool aUpdateLayout = true) override;
        bool has_maximum_size() const noexcept override;
        bool is_maximum_size_constrained() const noexcept override;
        size maximum_size(optional_size const& aAvailableSpace = optional_size{}) const override;
        void set_maximum_size(optional_size const& aMaximumSize, bool aUpdateLayout = true) override;
        bool has_fixed_size() const noexcept override;
        size fixed_size(optional_size const& aAvailableSpace = {}) const override;
        void set_fixed_size(optional_size const& aFixedSize, bool aUpdateLayout = true) override;
        bool has_transformation() const noexcept override;
        mat33 const& transformation(bool aCombineAncestorTransformations = false) const override;
        void set_transformation(optional_mat33 const& aTransformation, bool aUpdateLayout = true) override;
    public:
        bool has_padding() const noexcept override;
        neogfx::padding padding() const override;
        void set_padding(optional_padding const& aPadding, bool aUpdateLayout = true) override;
    protected:
        point unconstrained_origin() const override;
        point unconstrained_position() const override;
    protected:
        void layout_item_enabled(i_layout_item& aItem) override;
        void layout_item_disabled(i_layout_item& aItem) override;
    public:
        bool visible() const override;
    public:
        void update_layout(bool aDeferLayout = true, bool aAncestors = true) override;
        void layout_as(const point& aPosition, const size& aSize) override;
    public:
        void invalidate_combined_transformation() override;
        void fix_weightings(bool aRecalculate = true) override;
    public:
        i_layout_item& subject() const override;
        i_ref_ptr<i_layout_item>& subject_ptr() override;
    public:
        layout_item_disposition& cached_disposition() const override;
    public:
        bool operator==(const layout_item_cache& aOther) const;
    private:
        bool subject_is_layout_item_cache() const;
    private:
        ref_ptr<i_layout_item> iSubject;
        bool iSubjectIsCache;
        mutable layout_item_disposition iCachedDisposition = layout_item_disposition::Unknown;
        mutable std::pair<uint32_t, bool> iVisible;
        mutable std::pair<uint32_t, neogfx::size_policy> iSizePolicy;
        mutable std::pair<uint32_t, size> iWeight;
        mutable std::pair<uint32_t, std::pair<optional_size, size>> iMinimumSize;
        mutable std::pair<uint32_t, std::pair<optional_size, size>> iMaximumSize;
        mutable std::pair<uint32_t, std::pair<optional_size, size>> iFixedSize;
        mutable std::pair<uint32_t, mat33> iTransformation;
        mutable std::pair<uint32_t, mat33> iCombinedTransformation;
    };
}
