#!/bin/bash
#
# Copyright (c) 2020-2021 Advanced Robotics at the University of Washington <robomstr@uw.edu>
#
# This file is part of taproot-examples.
#
# taproot-examples is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# taproot-examples is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with taproot-examples.  If not, see <https://www.gnu.org/licenses/>.

for dir in ./rm-dev-board*/*; do
    if [[ -d "$dir" ]] && [[ "$dir" != "./taproot" ]]; then
        cd "$dir"
        lbuild build
        if [[ "$?" != 0 ]]; then
            echo "lbuild failed"
            exit 1
        fi
        scons build
        if [[ "$?" != 0 ]]; then
            echo "scons build failed"
            exit 1
        fi
        cd -
    fi
done

exit 0
