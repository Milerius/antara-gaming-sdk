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

#include <range/v3/numeric.hpp>
#include <range/v3/action/remove_if.hpp>
#include <range/v3/view/filter.hpp>
#include "antara/gaming/ecs/system.manager.hpp"

namespace antara::gaming::ecs
{
    system_manager::system_manager(entt::registry &registry, entt::dispatcher &dispatcher) noexcept : entity_registry_(
            registry), dispatcher_(dispatcher)
    {

    }

    std::size_t system_manager::nb_systems(system_type sys_type) const noexcept
    {
        return systems_[sys_type].size();
    }

    std::size_t system_manager::nb_systems() const noexcept
    {
        return ranges::accumulate(systems_, size_t{0u}, [](size_t accumulator, auto &&vec) {
            return accumulator + vec.size();
        });
    }

    base_system &
    system_manager::add_system_(system_manager::system_ptr &&system, antara::gaming::ecs::system_type sys_type) noexcept
    {
        return *systems_[sys_type].emplace_back(std::move(system));
    }

    void system_manager::sweep_systems_() noexcept
    {
        ranges::for_each(systems_, [](auto &&vec_system) -> void {
            ranges::actions::remove_if(vec_system, &base_system::is_marked);
        });

        this->need_to_sweep_systems_ = false;
    }

    std::size_t system_manager::update() noexcept
    {
        if (!nb_systems())
            return 0u;

        size_t nb_systems_updated = 0u;
        timestep_.start_frame();
        nb_systems_updated += update_systems(system_type::pre_update);

        //LCOV_EXCL_START
        while (timestep_.is_update_required()) {
            nb_systems_updated += update_systems(system_type::logic_update);
            timestep_.perform_update();
        }
        //LCOV_EXCL_STOP

        nb_systems_updated += update_systems(system_type::post_update);

        if (need_to_sweep_systems_) {
            sweep_systems_();
        }
        return nb_systems_updated;
    }

    std::size_t system_manager::update_systems(system_type system_type_to_update) noexcept
    {
        std::size_t nb_systems_updated = 0ull;
        for (auto &&current_sys : systems_[system_type_to_update] | ranges::views::filter(&base_system::is_enabled)) {
            current_sys->update();
            nb_systems_updated += 1;
        }
        return nb_systems_updated;
    }
}