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
 * Defines the WindowSystem exception class.
 *
 * @file   error/windowsystem.hpp
 * @author Ricardo Tiago <rtiago.mendes@gmail.com>
 * @date 2011-08-19
 * @see    WindowSystem
 */

#ifndef HUMMSTRUMM_ENGINE_ERROR_WINDOWSYSTEM
#define HUMMSTRUMM_ENGINE_ERROR_WINDOWSYSTEM

namespace hummstrumm
{
namespace engine
{
namespace error
{

/**
 * The error for receiving a generic window system.
 *
 * @author Ricardo Tiago <rtiago.mendes@gmail.com>
 * @date 2011-08-19
 * @since 0.4
 */
class WindowSystem : public Error
{
  public:
    /**
     * Constructs an WindowSystem object to be thrown to an error handler.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-08-19
     * @since 0.4
     *
     * @param [in] fileName The name of the file in which the error occured.
     * @param [in] lineNumber The line of the file in which the error occured.
     * @param [in] function The name of the function in which the error occured.
     * @param [in] text A human readable description of the error.
     */
    WindowSystem (const char *fileName, unsigned int lineNumber,
                  const char *function, const char *text = "");
    /**
     * Destructs an WindowSystem object.
     *
     * @author Ricardo Tiago <rtiago.mendes@gmail.com>
     * @date 2011-08-19
     * @since 0.4
     */
    virtual ~WindowSystem(void);
};

}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_ERROR_WINDOWSYSTEM
