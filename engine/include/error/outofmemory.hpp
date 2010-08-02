// -*- c++ -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2010, the people listed in the AUTHORS file. 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * Defines the OutOfMemory exception class.
 *
 * @file   outofmemory.hpp
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-01-03
 * @see    OutOfMemory
 */

#ifndef HUMMSTRUMM_ENGINE_ERROR_OUTOFMEMORY
#define HUMMSTRUMM_ENGINE_ERROR_OUTOFMEMORY

#include "error.hpp"

namespace hummstrumm
{
namespace engine
{
namespace error
{

/**
 * The error for when an operation could not be completed due to an insufficient
 * amount of memory available.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-01-31
 * @since 0.1
 */
class OutOfMemory : public Error
{
  public:
    /**
     * Constructs an OutOfMemory object to be thrown to an error handler.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2010-01-31
     * @since 0.1
     *
     * @param fileName [in] The name of the file in which the error occured.
     * @param lineNumber [in] The line of the file in which the error occured.
     * @param text [in] A human readable description of the error.
     */
    OutOfMemory (const char *fileName, unsigned int lineNumber,
                 const char *text = "");
    /**
     * Destructs an OutOfMemory object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2010-01-31
     * @since 0.1
     */
    virtual ~OutOfMemory (void);
};

}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_ERROR_OUTOFMEMORY
