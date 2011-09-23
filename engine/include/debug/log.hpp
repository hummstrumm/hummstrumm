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
 * Defines the Log class.
 *
 * @file   debug/log.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-02-14
 * @see    Log
 */

#ifndef HUMMSTRUMM_ENGINE_DEBUG_LOG
#define HUMMSTRUMM_ENGINE_DEBUG_LOG

#include <string>
#include <cstdio>

namespace hummstrumm
{
namespace engine
{
namespace debug
{

/**
 * Provides a method by which messages can be saved to a file.  This
 * log stores information to the file immediately, so no information
 * is lost.  A log file is already created by the library, so you
 * cannot create one yourself.  The class is of the singleton
 * pattern.  The Log object can be retrieved using the Log::GetLog()
 * method.
 *
 * Log messages can either be saved in a human-readable text format,
 * with each message on a new line, or in a machine-readable XML based
 * format.
 *
 * @version 0.3
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2010-11-09
 * @since   0.3
 */
class Log
{
    /// Engine needs to create the log.  But no one else can.
    friend class hummstrumm::engine::core::Engine;
    
  public:
    /**
     * Every message has a specific level associated with it.  The
     * level is outputed with the text of the log.  Messages can also
     * be filtered by the level, going from highest to lowest level.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-03-04
     * @since  0.2
     */
    enum Level
    {
      LEVEL_MESSAGE, ///< A normal log message, level one.
      LEVEL_ERROR,   ///< An error log message, level four.
      LEVEL_WARNING, ///< A warning log message, level two.
      LEVEL_SUCCESS, ///< A success log message, level three.
    };

    /**
     * Returns the game engine Log, as per the singleton pattern.
     * 
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-03-04
     * @since  0.2
     *
     * @return The Log created by the game engine.
     */
    static Log &GetLog (void)
      throw (HUMMSTRUMM_ERRORNAME (Generic));

    /**
     * Returns the name of the file to which the log is written.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-03-12
     * @since  0.2
     *
     * @return The file name of the log output.
     */
    hummstrumm::engine::types::String GetFileName (void)
      const throw ();

    /**
     * Returns the minimum level of messages that can be written to
     * the log.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-03-12
     * @since  0.2
     *
     * @return The masking level of the log.
     */
    Level GetMinimumLevel (void)
      const throw ();

    /**
     * Outputs a message to the log file.  This message is an
     * indivisible unit; sequential calls of this method will not
     * result in one longer message.  Instead, each call to this
     * method will output a new message.
     *
     * Each message has a log level, which can be one of the Level
     * enumerated values.  The log level is also writen with each log
     * message.  Also, messages that have log levels below that of the
     * Log itself are not written.
     *
     * A timestamp is also added to each message.  This timestamp
     * comes from the high resolution timer.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-03-12
     * @since  0.2
     *
     * @param [in] text The message to be written to the log.
     * @param [in] fileName The file from which the message originates.
     * @param [in] lineNumber The line from which the message originates.
     * @param [in] function The function from which the message originates.
     * @param [in] level The level of the message.
     *
     * @todo Make timestamp user-readable/pretty.  This goes along with adding
     * the schema for log files.
     * @todo Make thread-safe.
     */
    void Write (hummstrumm::engine::types::String text,
                hummstrumm::engine::types::String fileName,
                int lineNumber,
                hummstrumm::engine::types::String function,
                Level level = LEVEL_MESSAGE)
      throw ();

  private:
    /**
     * Constructs a Log.  This will open a file and immediately will
     * be ready to write a message.  A header will also be written.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-11
     * @since  0.2
     *
     * @param [in] fileName    The name of the file to which to write the log
     * message.
     * @param [in] minimumLevel The minimum level of log messages.
     */
    Log (hummstrumm::engine::types::String fileName, Level minimumLevel)
      throw (HUMMSTRUMM_ERRORNAME(Generic));
    /**
     * Destructs a Log.  The log footer is written, and then the log file is
     * closed.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-09-11
     * @since  0.2
     */
    virtual ~Log (void);

    /**
     * Writes the XML header out to the log.  This is necessary before any of
     * the events in the log are sent out.  This method is called only from the
     * constructor; you don't have to worry about calling it yourself.
     *
     * The header consists of the <?xml ... ?> declaration, the openning tag of
     * the <log> element, and the <header> block of the file.  The <header>
     * block includes system information, information about the log level of the
     * log, and information about the time at which the run was started.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-09
     * @since  0.3
     */
    void OutputHeader (void)
      throw ();
    /**
     * Writes the XML footer out to the log.  This is necessary before the log
     * is closed.  This method is called only from the destructor; you don't
     * have to worry about calling it yourself.
     *
     * The footer consists solely of the closing </log> tag.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-09
     * @since  0.3
     */
    void OutputFooter (void)
      throw ();

    /**
     * Returns the current message ID and increments it.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-11-09
     * @since  0.3
     */
    int
    ReturnAndIncrementId (void)
      throw ();
    
    hummstrumm::engine::types::String fileName; ///< The name of the log file.
    bool        isXmlMode;    ///< Whether the log is in XML mode.
    FILE       *logFile;      ///< The actual file handle.
    Level       minimumLevel; ///< The minimum level of log messages.
    int         currentId;    ///< The ID of the last written message.
    static Log *theLog;       ///< The global Log.
};

/**
 * @def HUMMSTRUMM_LOG
 * Logs a message from the engine.
 *
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date 2010-11-09
 * @since 0.1
 *
 * @param [in] message The text to write to the log.
 * @param [in] level A constant describing the type of message.
 *
 * @see Log
 */
#ifdef HUMMSTRUMM_PLATFORM_WINDOWS
  #define HUMMSTRUMM_LOG(message, level)                          \
      MULTI_LINE_MACRO_BEGIN                                    \
      hummstrumm::engine::core::Engine::GetEngine ()->            \
        GetLog ()->Write ((message),                              \
          __FILE__,                                               \
          __LINE__,                                               \
          __FUNCSIG__,                                            \
          hummstrumm::engine::debug::Log::LEVEL_##level);         \
      MULTI_LINE_MACRO_END
#else // #ifdef HUMMSTRUMM_PLATFORM_WINDOWS
  #define HUMMSTRUMM_LOG(message, level)                          \
    do {                                                          \
      hummstrumm::engine::core::Engine::GetEngine ()->            \
        GetLog ()->Write ((message),                              \
          __FILE__,                                               \
          __LINE__,                                               \
          __PRETTY_FUNCTION__,                                    \
          hummstrumm::engine::debug::Log::LEVEL_##level);         \
    } while (false)
#endif // #ifdef HUMMSTRUMM_PLATFORM_WINDOWS

}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_DEBUG_MODE
