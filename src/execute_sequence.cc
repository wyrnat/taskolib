/**
 * \file   execute_sequence.cc
 * \author Marcus Walla
 * \date   Created on February 16, 2022
 * \brief  Implementation of the execute_sequence() free function.
 *
 * \copyright Copyright 2021-2022 Deutsches Elektronen-Synchrotron (DESY), Hamburg
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
#include "taskomat/execute_sequence.h"
#include "taskomat/execute_step.h"

namespace task {

void execute_sequence(Sequence& sequence, Context& context)
{
    // syntax check
    sequence.check_correctness_of_steps();
    
    // 'move' variable names from context to temporay set 
    VariableNames variable_names;
    for( const auto& variable: context)
        variable_names.insert(variable.first);

    for(auto& step: sequence.get_steps())
    {
        // set variables names to step for import/export
        step.set_imported_variable_names(variable_names);
        step.set_exported_variable_names(variable_names);

        execute_step(step, context);
    }
}

}