// -*- c++ -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2011, the people listed in the AUTHORS file.
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
 * Defines the DivisionByZero exception class.
 *
 * @file   error/divisionbyzero.hpp
 * @author Ricardo Tiago <RTiago@gmail.com>
 * @date   2010-05-09
 */

#ifndef HUMMSTRUMM_ENGINE_ERROR_DIVISIONBYZERO
#define HUMMSTRUMM_ENGINE_ERROR_DIVISIONBYZERO

namespace hummstrumm
{
namespace engine
{
namespace error
{

/**
 * The error for divisions or modulo operations in which the divisor of the
 * expression is 0.
 *
 * @author Ricardo Tiag <RTiago@gmail.com>
 * @date 2010-05-28
 * @since 0.2
 */

class DivisionByZero: public Error
{
  public:
    /**
     * Constructs an DivisionByZero object to be thrown to an error handler.
     *
     * @author Ricardo Tiago <RTiago@gmail.com>
     * @date 2010-11-22
     * @since 0.2
     *
     * @param fileName [in] The name of the file in which the error occured.
     * @param lineNumber [in] The line of the file in which the error occured.
     * @param function [in] The name of the function in which the error occured.
     * @param text [in] A human readable description of the error.
     */
    DivisionByZero (const char *fileName, unsigned int lineNumber,
                    const char *function, const char *text = "");
    /**
     * Destructs an DivisionByZero object.
     *
     * @author Ricardo Tiago <RTiago@gmail.com>
     * @date 2010-05-28
     * @since 0.2
     */
    virtual ~DivisionByZero (void);

};

}
}
}



#endif
