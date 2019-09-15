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

#include <antara/gaming/ecs/component.layer.hpp>
#include "antara/gaming/world/world.app.hpp"
#include "antara/gaming/ecs/component.position.hpp"
#include "antara/gaming/sfml/component.drawable.hpp"
#include "antara/gaming/sfml/graphic.system.hpp"
#include "antara/gaming/sfml/input.system.hpp"

class my_world : public antara::gaming::world::app
{
public:
    my_world() noexcept
    {
        auto& graphic_system = this->system_manager_.create_system<antara::gaming::sfml::graphic_system>();
        this->system_manager_.create_system<antara::gaming::sfml::input_system>(graphic_system.get_window());

        //! Construct dummy entity
        auto& window_info = entity_registry_.ctx<antara::gaming::ecs::component_window>();
        auto dummy_entity = entity_registry_.create();
        auto& circle_cmp = entity_registry_.assign<antara::gaming::sfml::circle>(dummy_entity, sf::CircleShape(50.f));
        entity_registry_.assign<antara::gaming::ecs::layer<1>>(dummy_entity);
        circle_cmp.drawable.setFillColor(sf::Color(100, 250, 50));
        entity_registry_.assign<antara::gaming::ecs::component_position>(dummy_entity, window_info.width / 2, window_info.height / 2);
    }
};

int main()
{
    my_world game_app;
    return game_app.run();
}