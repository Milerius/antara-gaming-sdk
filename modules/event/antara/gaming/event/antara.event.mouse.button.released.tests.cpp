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

#include <doctest/doctest.h>
#include "antara/gaming/event/mouse.button.released.hpp"

namespace antara::gaming::event::tests
{
    TEST_SUITE ("mouse button released test suite")
    {
        TEST_CASE ("default constructible")
        {
            event::mouse_button_released mouse_button_released_evt{};
            CHECK_EQ(mouse_button_released_evt.x, 0);
            CHECK_EQ(mouse_button_released_evt.y, 0);
            CHECK_EQ(mouse_button_released_evt.window_x, 0);
            CHECK_EQ(mouse_button_released_evt.window_y, 0);
        }

        TEST_CASE ("can construct from a button and 2 positions")
        {
            event::mouse_button_released mouse_button_released_evt{input::mouse_button::right, 42, 42, 10, 11};
            CHECK_EQ(mouse_button_released_evt.x, 42);
            CHECK_EQ(mouse_button_released_evt.y, 42);
            CHECK_EQ(mouse_button_released_evt.window_x, 10);
            CHECK_EQ(mouse_button_released_evt.window_y, 11);
            CHECK_EQ(mouse_button_released_evt.button, input::mouse_button::right);
        }
    }
}