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

#include <SFML/Audio.hpp>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

#include <refl.hpp>

#pragma clang diagnostic pop

#include "antara/gaming/sfml/event.play.sound.hpp"
#include "antara/gaming/ecs/system.hpp"

namespace antara::gaming::sfml
{


    struct component_sound
    {
        sf::Sound sound;
        std::function<void()> on_finish{[]()
                                        {}};
    };

    class audio_system final : public ecs::pre_update_system<audio_system>
    {
    public:
        //! Constructors
        audio_system(entt::registry &registry, entt::dispatcher &dispatcher) noexcept;

        void receive_sound_event(const play_sound_event &evt) noexcept;

        void update() noexcept final;
    };
}

REFL_AUTO(type(antara::gaming::sfml::audio_system));