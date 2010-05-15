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
 * Defines the Log class.
 *
 * @file   log.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2010-02-14
 * @see    Log
 */

#ifndef HUMMSTRUMM_ENGINE_DEBUG_LOG
#define HUMMSTRUMM_ENGINE_DEBUG_LOG

#include <string>

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
 * @version 0.2
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2010-03-04
 * @since   0.2
 */
class Log
{ 
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
      MESSAGE, ///< A normal log message, level one.
      ERROR,   ///< An error log message, level four.
      WARNING, ///< A warning log message, level two.
      SUCCESS, ///< A success log message, level three.
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
      throw ();

    /**
     * Returns if the log is XML mode.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-03-12
     * @since  0.2
     *
     * @return Whether the logged output will be in XML format.
     */
    bool IsXmlMode (void)
      const throw ();

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
     * @param text  The message to be written to the log.
     * @param level The level of the message.
     *
     * @todo Add timestamp.
     * @todo Make thread-safe.
     */
    void Write (hummstrumm::engine::types::String text, Level level) throw ();

  private:
    /**
     * Constructs a Log.  This will open a file and immediately will
     * be ready to write a message.  A header will also be written.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-03-12
     * @since  0.2
     *
     * @param fileName     The name of the file to which to write the
     * log message.
     * @param isXmlMode    Whether to write the log as an XML file.
     * @param minimumLevel The minimum level of log messages.
     */
    Log (hummstrumm::engine::types::String fileName, bool isXmlMode,
         Level minimumLevel);
    /**
     * Destructs a Log.  The log file is closed.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2010-03-12
     * @since  0.2
     */
    virtual ~Log (void);

    hummstrumm::engine::types::String fileName; ///< The name of the log file.
    bool        isXmlMode;    ///< Whether the log is in XML mode.
    FILE       *logFile;      ///< The actual file handle.
    Level       minimumLevel; ///< The minimum level of log messages.
};

#define LOG(message, level)                                     \
  do {                                                          \
    hummstrumm::engine::debug::Log::GetLog ().Write ((message), \
      hummstrumm::engine::debug::Log::level);                 \
  } while (false)

}
}
}

#endif // #ifndef HUMMSTRUMM_ENGINE_DEBUG_MODE
