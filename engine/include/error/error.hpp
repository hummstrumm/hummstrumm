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
 * Defines the Error class and macros that throw exceptions.
 * 
 * @file   error.hpp
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-01-03
 * @see    Error
 */

#ifndef HUMMSTRUMM_ENGINE_ERROR_ERROR
#define HUMMSTRUMM_ENGINE_ERROR_ERROR

#include <string>

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
 * @see HUMMSTRUMM_THROW
 */
class Error
{
  public:
    /**
     * Constructs an Error object to be thrown to an error handler.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2010-01-31
     * @since 0.1
     *
     * @param fileName [in] The name of the file in which the error occured.
     * @param lineNumber [in] The line of the file in which the error occured.
     * @param text [in] A human readable description of the error.
     * @param description [in] A description of the error by other error
     * classes.
     */
    Error (const char *fileName, unsigned int lineNumber,
           const char *text = "", const char *description = 0)
      throw ();
    /**
     * Destructs an Error object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2010-01-31
     * @since 0.1
     */
    virtual ~Error (void);

    /**
     * Returns the data contained within the Error in a human readable form.
     * This data can then be logged, outputted to the terminal, or displayed in
     * in a message box.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2010-01-31
     * @since 0.1
     *
     * @return A human readable string of the data in the Error object.
     */
    const char *GetHumanReadableMessage (void)
      const throw ();

    /**
     * Returns the name of the file in which the error occured.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2010-01-31
     * @since 0.1
     *
     * @return The file name of the Error.
     */
    const char *GetFileName (void)
      const throw ();
    /**
     * Returns the line number on which the error occured.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2010-01-31
     * @since 0.1
     *
     * @return The line number of the Error.
     */
    unsigned int GetLineNumber (void)
      const throw ();
    /**
     * Returns the description of error provided by the programmer.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date 2010-01-31
     * @since 0.1
     *
     * @return The description of the Error.
     */
    const char *GetText (void)
      const throw ();

  private:
    char *fileName;               /**< The name of the file with the Error. */
    unsigned int lineNumber;      /**< The line number of the Error. */
    char *text;                   /**< A description of the Error. */
};

}
}
}

/**
 * Adds support for the engine's Object/Type system to an Object.  Place this
 * macro at the top of the class's source file.
 *
 * This macro implements the members added by the HUMMSTRUMM_DECLARE_TYPE
 * macro.  You must supply the full class name (including the namespaces) and
 * the full parent class name (including the namespaces), and a template
 * definition.
 *
 * If you use this macro, you will also have to use the HUMMSTRUMM_DECLARE_TYPE
 * macro, which adds the definitions of these members.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-01-31
 * @since 0.1
 *
 * @param exceptionName [in] The name of the Error exception to throw.  This
 * does not include any namespace prefix.
 * @param text [in] A description of the Error.
 *
 * @see Error
 */
#define HUMMSTRUMM_THROW(exceptionName, text) \
  throw hummstrumm::engine::error::exceptionName (__FILE__, \
                                                  __LINE__, \
                                                  text);

#endif // #ifndef HUMMSTRUMM_ENGINE_ERROR_ERROR
