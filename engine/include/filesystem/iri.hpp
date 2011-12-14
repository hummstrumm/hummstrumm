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
 * Defines a class to hold IRIs (an extension of URIs, which encompass URLs and
 * URNs).
 *
 * @file   filesystem/iri.hpp
 * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date   2011-12-13
 * @see    Iri
 */

#ifndef HUMMSTRUMM_ENGINE_FILESYSTEM_IRI
#define HUMMSTRUMM_ENGINE_FILESYSTEM_IRI


namespace hummstrumm
{
namespace engine
{
namespace types
{

/**
 * Holds real number data.  Number allows all the operations of a normal IEEE
 * floating point number or a standard integer, as per the standard C++ types.
 * This allows more or less transparent integration with both C++ and the
 * ECMAScript-compatible scripting language.
 *
 * @version 0.5
 * @author  Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
 * @date    2011-12-13
 * @since   0.5
 */
class Iri : public hummstrumm::engine::core::Object
{
    HUMMSTRUMM_DECLARE_TYPE (Iri)
  public:
    /**
     * Constructs a new Iri object initialized to the current directory.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2011-12-13
     * @since  0.5
     */
    Iri (void) throw ();
    /**
     * Constructs a new Iri object initialized to a certain IRI string.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2011-12-13
     * @since  0.5
     */
    Iri (const String &iri) throw ();
    /**
     * Constructs a new Iri object initialized to an IRI composed of its
     * constitute parts.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2011-12-13
     * @since  0.5
     */
    Iri (const String &scheme,
         const String &hierarchy,
         const String &query,
         const String &fragment) throw ();
    /**
     * Destructs an Iri object.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2011-12-14
     * @since  0.5
     */
    virtual ~Iri (void) throw ();
    
    /**
     * Casts the Iri object to a String.
     *
     * @author Patrick M. Niedzielski <PatrickNiedzielski@gmail.com>
     * @date   2011-12-14
     * @since  0.5
     *
     * @return The value of this Iri in a String.
     */
    String ToString (void) const throw ();
    
  private:
    String scheme;    /**< Scheme (also called Protocol) of the IRI */
    String hierarchy; /**< Hiearchical part of the IRI */
    String query;     /**< Query part of the IRI */
    String fragment;  /**< Fragment part of the IRI */
};


}
}
}


#endif // #ifndef HUMMSTRUMM_ENGINE_FILESYSTEM_IRI
