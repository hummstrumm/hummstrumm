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
 * Defines the InvalidParam exception class.
 *
 * @file   invalidparam.hpp
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-07-26
 * @see    InvalidParam
 */

#ifndef HUMMSTRUMM_ENGINE_ERROR_INVALIDPARAM
#define HUMMSTRUMM_ENGINE_ERROR_INVALIDPARAM

namespace hummstrumm
{
namespace engine
{
namespace error
{

/**
 * The error for receiving a generic invalid parameter.
 *
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-07-26
 * @since 0.3
 */
class InvalidParam : public Error
{
  public:
    /**
     * Constructs an InvalidParam object to be thrown to an error handler.
     *
     * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2010-07-26
     * @since 0.3
     *
     * @param fileName [in] The name of the file in which the error occured.
     * @param lineNumber [in] The line of the file in which the error occured.
     * @param text [in] A human readable description of the error.
     */
    InvalidParam (const char *fileName, unsigned int lineNumber,
                  const char *text = "");
    /**
     * Destructs an InvalidParam object.
     *
     * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2010-07-26
     * @since 0.3
     */
    virtual ~InvalidParam(void);
};

}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_ERROR_INVALIDPARAM
