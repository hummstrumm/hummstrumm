// -*- mode: c++; c-file-style: hummstrumm -*-
/* Humm and Strumm Engine
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
 * Defines debug::logging::Backend and several backend classes.
 *
 * @file   debug/logging/backend.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-06-14
 * @see    Backend
 * @see    ConsoleBackend
 * @see    FileBackend
 */

#ifndef HUMMSTRUMM_ENGINE_DEBUG_LOGGING_BACKEND
#define HUMMSTRUMM_ENGINE_DEBUG_LOGGING_BACKEND

#include <ctime>
#include <string>
#include <fstream>
#include <limits>

namespace hummstrumm
{
namespace engine
{
namespace debug
{
namespace logging
{

/**
 * An abstract base class for the functors that output logged messages to some
 * backend.  The exact format of a message is determined by the backend that is
 * used to log them.
 * 
 * @version 0.6
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2012-06-14
 * @since   0.6
 */
class Backend
{
  public:
    /**
     * Constructs and initializes a backend.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-14
     * @since  0.6
     *
     * @param [in] allowedLevels The levels that this backend should print, OR'd
     * together.
     */
    inline Backend (unsigned allowedLevels =
                      std::numeric_limits<unsigned>::max ());
    /**
     * Destructs a backend.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-14
     * @since  0.6
     */
    virtual ~Backend ();

    /**
     * Writes a message to the backend.  Each message has an associated file,
     * line, and time.  This method is intended to be called during a flush from
     * the logging::StreamBuffer associated with some log, but any user can call
     * it.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-14
     * @since  0.6
     *
     * @param [in] time The time when the message was sent to the backend.
     * @param [in] file The name of the source file from which the message came.
     * @param [in] line The line from which the message came.
     * @param [in] level The level of the message.
     * @param [in] message The user-provided message string.
     *
     * @note The time is provided by the logging::StreamBuffer so that
     * timestamps between backends will be the same for corresponding messages.
     */
    virtual void operator() (std::time_t time, std::string file, unsigned line,
                             unsigned level, std::string message) = 0;

  protected:
    unsigned acceptLevels;
};


/**
 * A log backend to send log messages to the standard POSIX streams @c stdout
 * and @c stderr.  These streams generally are routed to the terminal or system
 * console.
 * 
 * @version 0.6
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2012-06-14
 * @since   0.6
 *
 * @todo We can support ANSI control codes for colors based on the level of
 * message.
 */
class ConsoleBackend : public Backend
{
  public:
    /**
     * Constructs a new ConsoleBackend, specifying whether to use @c stderr or
     * @c stdout .
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-14
     * @since  0.6
     *
     * @param [in] allowedLevels The levels that this backend should print, OR'd
     * together.
     * @param [in] useStderr Whether to use @c stderr or @c stdout .
     * @param [in] printColor Whether to print in color.
     */
    inline ConsoleBackend (unsigned allowedLevels =
                             std::numeric_limits<unsigned>::max (),
                           bool useStderr = true,
                           bool printColor = true);
    /**
     * Destructs an existing ConsoleBackend.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-14
     * @since  0.6
     */
    virtual ~ConsoleBackend ();

    /**
     * Writes a message to the POSIX stream this backend is configured to use.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-14
     * @since  0.6
     *
     * @param [in] time The time when the message was sent to the backend.
     * @param [in] file The name of the source file from which the message came.
     * @param [in] line The line from which the message came.
     * @param [in] level The level of the message.
     * @param [in] message The user-provided message string.
     *
     * @todo Colors?
     *
     * @see debug::logging::Backend
     */
    virtual void operator() (std::time_t time, std::string file, unsigned line,
                             unsigned level, std::string message);

  private:
    bool useStderr;  ///< Should we use @c stderr ?
    bool printColor; ///< Should we print in color?
};


/**
 * A log backend to send log messages to an XML-formatted log file on the user's
 * hard drive.
 * 
 * @version 0.6
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2012-06-14
 * @since   0.6
 *
 * @todo We'll want message levels, and allowed levels for each backend.
 */
class FileBackend : public Backend
{
  public:
    /**
     * Constructs a new FileBackend object using a file stream.  XML version
     * information and an opening tag are written.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-14
     * @since  0.6
     *
     * @param [in] allowedLevels The levels that this backend should print, OR'd
     * together. 
     * @param [in,out] file The name of the log file.
     */ 
    FileBackend (unsigned allowedLevels = std::numeric_limits<unsigned>::max (),
                 std::string file = "~/.hummstrummengine.log");
    /**
     * Destructs an existing FileBackend object.  The closing tag of the
     * document is written at this point.  The file stream should destroy itself
     * when it goes out of scope (because this is just a reference), which will
     * close the file.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-14
     * @since  0.6
     */
    virtual ~FileBackend ();

    /**
     * Writes a message to the file stream this backend is configured to use.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-14
     * @since  0.6
     *
     * @param [in] time The time when the message was sent to the backend.
     * @param [in] file The name of the source file from which the message came.
     * @param [in] line The line from which the message came.
     * @param [in] level The level of the message.
     * @param [in] message The user-provided message string.
     *
     * @see debug::logging::Backend
     */
    virtual void operator() (std::time_t time, std::string file, unsigned line,
                             unsigned level, std::string message);

  private:
    std::ofstream fileStream; ///< The file we should print to.
};

}
}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_DEBUG_LOGGING_BACKEND
