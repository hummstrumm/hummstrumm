// -*- mode: c++; c-file-style: hummstrumm -*-
/* Humm and Strumm Video Game
 * Copyright (C) 2008-2012, the people listed in the AUTHORS file. 
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
 * @file   error/error.hpp
 * @author Patrick Michael Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-01-03
 * @see    Error
 */

#ifndef HUMMSTRUMM_ENGINE_ERROR_ERROR
#define HUMMSTRUMM_ENGINE_ERROR_ERROR


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
 * @version 0.5
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-01-31
 * @since  0.1
 *
 * @see HUMMSTRUMM_THROW
 *
 * @invariant The Error will remain immutable throughout its life time.
 */
class Error
{
  protected:
    /**
     * Constructs an Error object to be thrown to an error handler.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-22
     * @since  0.1
     *
     * @param [in] fileName The name of the file in which the error occured.
     * @param [in] lineNumber The line of the file in which the error occured.
     * @param [in] function The name of the function in which the error occured.
     * @param [in] text A human readable description of the error.
     * @param [in] description A description of the error by other error
     * classes.
     */
    Error (const char *fileName, unsigned int lineNumber,
           const char *function, const char *description,
           const char *text = "")
      /* noexcept */;
    /**
     * Destructs an Error object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-01-31
     * @since  0.1
     */
    virtual ~Error ();

  public:
    /**
     * Returns the name of the file in which the error occured.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-01-31
     * @since   0.1
     *
     * @return The file name of the Error.
     */
    const char *GetFileName ()
      const /* noexcept */;
    /**
     * Returns the line number on which the error occured.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-01-31
     * @since  0.1
     *
     * @return The line number of the Error.
     */
    unsigned int GetLineNumber ()
      const /* noexcept */;
    /**
     * Returns the description of error provided by the programmer.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-01-31
     * @since  0.1
     *
     * @return The specific description of the Error.
     */
    const char *GetText ()
      const /* noexcept */;
    /**
     * Returns the description of error provided by the type of error thrown.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2011-08-28
     * @since  0.4
     *
     * @return The general description of the Error.
     */
    const char *GetDescription ()
      const /* noexcept */;
    /**
     * Returns the name of the function provided by the programmer.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-22
     * @since  0.1
     *
     * @return The name of the function from which the Error hails.
     */
    const char *GetFunction ()
      const /* noexcept */;

  private:
    const char *fileName;         /**< The name of the file with the Error. */
    unsigned int lineNumber;      /**< The line number of the Error. */
    const char *function;         /**< The function of origin of the Error. */
    const char *text;             /**< A specific description of the Error. */
    const char *description;      /**< A general description of the Error. */
};

/**
 * Output the text of an Error to a stream.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-04-05
 * @since  0.6
 *
 * @return The stream object, after the Error has been written.
 */
std::ostream &
operator<< (std::ostream &, const Error &);

}
}
}



/**
 * @def HUMMSTRUMM_THROW
 * Throws an exception.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-01-31
 * @since 0.1
 *
 * @param [in] exceptionName The name of the Error exception to throw.  This
 * does not include any namespace prefix.
 * @param [in] text A description of the Error.
 *
 * @see Error
 */
#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
  #define HUMMSTRUMM_THROW(exceptionName, text)                       \
    MULTI_LINE_MACRO_BEGIN                                            \
      throw hummstrumm::engine::error::exceptionName (__FILE__,       \
                                                      __LINE__,       \
                                                      __FUNCSIG__,    \
                                                      text);          \
    MULTI_LINE_MACRO_END
#else // #ifdef HUMMSTRUMM_PLATFORM_WINDOWS
  #define HUMMSTRUMM_THROW(exceptionName, text)                            \
    MULTI_LINE_MACRO_BEGIN                                                 \
      throw hummstrumm::engine::error::exceptionName (__FILE__,            \
                                                      __LINE__,            \
                                                      __PRETTY_FUNCTION__, \
                                                      text);               \
    MULTI_LINE_MACRO_END
#endif // #ifdef HUMMSTRUMM_PLATFORM_WINDOWS

#endif // #ifndef HUMMSTRUMM_ENGINE_ERROR_ERROR
