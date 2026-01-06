# BomboPad is an open-source, versatile 12-key macropad featuring dual rotary encoders and display support.
# Designed with a focus on flexibility, it supports both wired and wireless configurations.
# Copyright (C) 2024-2025 Gianni Bombelli <bombo82@giannibombelli.it>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not,
# see <https://www.gnu.org/licenses/gpl-3.0.html>.

# Features configured via info.json:
# - encoder = true
# - oled = true
# - bootmagic_lite = true

LTO_ENABLE = no         # if firmware size over limit, try this option

EXTRAKEY_ENABLE = yes	# Audio control and System control
COMMAND_ENABLE = no		# Commands for debug and configuration
CONSOLE_ENABLE = no		# Console for debug
MOUSEKEY_ENABLE = no	# Mouse keys
