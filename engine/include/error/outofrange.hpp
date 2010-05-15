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
 * Defines the OutOfRange exception class.
 *
 * @file   outofmemory.hpp
 * @author Ricardo Tiago <RTiago@gmail.com>
 * @date   2010-05-09
 */

#ifndef HUMMSTRUMM_ENGINE_ERROR_OUTOFRANGE
#define HUMMSTRUMM_ENGINE_ERROR_OUTOFRANGE

#include <string>
#include "error.hpp"

namespace hummstrumm
{
namespace engine
{
namespace error
{

/**
 * Contains error related information that is thrown in an exception.  Error
 * allows an error description to be passed back to the application error
 * handler.
 *
 * In addition, a human readable error message can be made from the information
 * that the Error class contains.  This message can be then saved to a log,
 * outputted to the terminal, or displayed in a message box.
 *
 * Error uses information obtained automatically from the THROW macro, such as
 * the file name and line number from which the error was thrown.  Though you
 * can use the standard C++ throw mechanism,  it is recomended that you use the
 * THROW macro to aid in this.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-01-31
 * @since 0.1
 *
 * @see THROW
 */

class OutOfRange: public Error
{
  public:
    /**
     * Constructs an OutOfRange object to be thrown to an error handler.
     *
     * @author Ricardo Tiago <RTiago@gmail.com>
     * @date 2010-05-28
     * @since 0.2
     *
     * @param fileName [in] The name of the file in which the error occured.
     * @param lineNumber [in] The line of the file in which the error occured.
     * @param text [in] A human readable description of the error.
     */
    OutOfRange (std::string fileName, unsigned int lineNumber,
                 std::string text = "");
    /**
     * Destructs an OutOfRange object.
     *
     * @author Ricardo Tiago <RTiago@gmail.com>
     * @date 2010-05-28
     * @since 0.2
     */
    virtual ~OutOfRange (void);

};

}
}
}



#endif
