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

#include <string> //! std::string
#include "antara/gaming/graphics/component.color.hpp"
#include "antara/gaming/transform/component.properties.hpp"
#include "antara/gaming/transform/component.position.hpp"
#include "antara/gaming/core/safe.refl.hpp"
#include "antara/gaming/math/vector.hpp"

namespace antara::gaming::graphics
{
    struct rect
    {
        math::vec2f pos;
        math::vec2f size;
    };

    struct sprite
    {
        std::string appearance; //! texture id
        bool native_size{true}; //! take the whole size by default
        rect texture_rec{}; //! Set the sub-rectangle of the texture that the sprite will display if native_size is false
    };

    inline entt::entity blueprint_sprite(entt::registry &registry,
                                         const sprite &spr,
                                         transform::position_2d pos = math::vec2f::scalar(0.f),
                                         fill_color spr_color = graphics::white,
                                         const transform::properties &prop = {}) noexcept
    {
        auto spr_entity = registry.create();
        registry.assign<fill_color>(spr_entity, spr_color);
        registry.assign<transform::properties>(spr_entity, prop);
        registry.assign<sprite>(spr_entity, spr);
        registry.assign<transform::position_2d>(spr_entity, pos);
        return spr_entity;
    }

    inline void blueprint_sprite(entt::entity spr_entity,
                                 entt::registry &registry,
                                 const sprite &spr,
                                 transform::position_2d pos = math::vec2f::scalar(0.f),
                                 fill_color spr_color = graphics::white,
                                 const transform::properties &prop = {}) noexcept
    {
        registry.assign<fill_color>(spr_entity, spr_color);
        registry.assign<transform::properties>(spr_entity, prop);
        registry.assign<sprite>(spr_entity, spr);
        registry.assign<transform::position_2d>(spr_entity, pos);
    }
}

REFL_AUTO(type(antara::gaming::graphics::rect), field(pos), field(size))
REFL_AUTO(type(antara::gaming::graphics::sprite), field(appearance), field(native_size), field(texture_rec))

