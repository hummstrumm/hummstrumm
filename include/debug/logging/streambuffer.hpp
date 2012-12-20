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
 * Defines debug::logging::StreamBuffer, which sends messages to the various
 * logging backends.
 *
 * @file   debug/logging/streambuffer.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2012-06-14
 * @see    StreamBuffer
 */

#ifndef HUMMSTRUMM_ENGINE_DEBUG_LOGGING_STREAMBUFFER
#define HUMMSTRUMM_ENGINE_DEBUG_LOGGING_STREAMBUFFER

#include <ctime>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>

namespace hummstrumm
{
namespace engine
{
namespace debug
{
namespace logging
{

// Forward declare for safety.
class Backend;

/**
 * An iostream buffer, compatible with those used in the standard library.  The
 * debug::Log class uses this buffer to dispatch messages to various backends,
 * such as a FileBackend representing a log on disk and a ConsoleBackend
 * representing the terminal output of the application.
 *
 * We derive from @c std::stringbuf so that we don't have to worry about
 * buffering.  The string will expand in size to whatever we want, no matter how
 * long the message.  Because this is the case, we don't care about overriding
 * the @c overflow() method of @c std::stringbuf , because it handles this all
 * for us.  We only override the sync() method, which is called when the user
 * requests a flush (which is when we write to our backends).
 * 
 * @version 0.7
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2012-12-19
 * @since   0.6
 *
 * @todo We'll want message levels.
 */
class StreamBuffer : public std::stringbuf
{
  public:
    /**
     * Constructs a new StreamBuffer object from given backends.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-12-19
     * @since  0.6
     */
    StreamBuffer (std::vector<std::shared_ptr<Backend>> backends);
    /**
     * Destructs an existing StreamBuffer object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-14
     * @since  0.6
     */
    inline virtual ~StreamBuffer ();

    /**
     * Changes the file name to print on the next flush.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-14
     * @since  0.6
     */
    inline void SetFile (std::string);
    /**
     * Changes the line number to print on the next flush.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-14
     * @since  0.6
     */
    inline void SetLine (unsigned);
    /**
     * Changes the message level to print on the next flush.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-15
     * @since  0.6
     */
    inline void SetLevel (unsigned);
    /**
     * Changes the streambuf's locked state.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-15
     * @since  0.6
     */
    inline void Lock ();
    /**
     * Returns whether the streambuf is in a locked state.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-15
     * @since  0.6
     *
     * @return Whether someone can try to lock us again.
     */
    inline bool IsLocked () const;

    /**
     * Sends a message to each registered backend.  Calls the @c operator() of
     * each backend with the correct parameters.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-14
     * @since  0.6
     */
    void SendToBackends ();

    /**
     * Flushes a message to all backends and then clears the @c std::stringbuf
     * buffer for the next message.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2012-06-14
     * @since  0.6
     *
     * @return An error code depending on whether all backends succeeded or
     * failed. 
     * @retval -1 On some failure.
     * @retval  0 On success.
     *
     * @warning Do not rename this function -- it is an overridden method of
     * @c std::stringbuf .
     */
    virtual int sync ();

  private:
    /// Send messages to these backends.
    std::vector<std::shared_ptr<Backend>> backends;
    /// The last update of the file name.
    std::string file;
    /// The last update of the line number.
    unsigned line;
    /// The last update of the message level.
    unsigned level;
    /// Whether we are locked.
    bool lock;
};


}
}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_DEBUG_LOGGING_STREAMBUFFER
