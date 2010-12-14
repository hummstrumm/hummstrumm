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
#define HUMMSTRUMM_ENGINE_SOURCE
#include "hummstrummengine.hpp"

#include <cstdio>
#include <cstring>
#include <unistd.h>


namespace hummstrumm
{
namespace engine
{
namespace system
{


Processors::Processors (void)
  throw ()
  : numberOfProcessors (0),
    processorStrings (0),
    sseSupport (false),
    sse2Support (false)
{
  FILE *cpuinfo = 0;
  
  try
    {
      // We get our info from /proc/cpuinfo
      cpuinfo = fopen ("/proc/cpuinfo", "r");
      if (cpuinfo == 0)
        {
          throw 0; // Could not open the file.
        }

      // Our current line's text.
      char line[1024];

      // What strings do we want to look for?
      const char *processorLabel = "processor";
      const char *nameLabel      = "model name";
      const char *flagsLabel     = "flags";

      // Two passes: one for determining the total number of processors, the
      // next for getting the processor string and flags.  This algorithm will
      // read 1023 characters from the stream, or up to the next newline if it
      // is closer.  If we don't read up to the newline, the next cycle will
      // continue reading from this line.  Which is perfectly fine.  It will
      // finally get to a newline, even if the line is really long.
      while (true)
        {
          std::fgets (line, 1024, cpuinfo);
          if (std::feof (cpuinfo) != 0)
            {
              break;
            }
          else if (std::ferror (cpuinfo))
            {
              throw 1; // Something went wrong in reading the file.
            }
          else if (std::strncmp (processorLabel,
                                 line,
                                 std::strlen (processorLabel)) == 0)
            {
              // We've got a hit.  Add one to the processor count.
              ++this->numberOfProcessors;
              continue;
            }
        }

      // Make sure we got a processor.
      if (this->numberOfProcessors == 0)
        {
          throw 2; // We didn't find any processors...?
        }

      // Allocate a buffer to store the strings.
      this->processorStrings = new char * [this->numberOfProcessors];

      // Seek back to the beginning in preparation for another pass.
      std::rewind (cpuinfo);
      
      // Second pass...look for the name string, but only as many as we have
      // space for.  We purposely don't set a decrement; it will be decremented
      // every cycle FOR WHICH we find a name.
      for (int i = 0; i < this->numberOfProcessors;)
        {
          std::fgets (line, 1024, cpuinfo);
          if (std::feof (cpuinfo) != 0)
            {
              // We had more processors than names?  Okay...?  Let's just set
              // the names to "Unknown".
              for (; i < this->numberOfProcessors; ++i)
                {
                  SetProcessorNameToUnknown (i);
                }
              break;
            }
          else if (std::ferror (cpuinfo))
            {
              throw 1; // Something went wrong in reading the file.
            }
          else if (std::strncmp (nameLabel,
                                 line,
                                 std::strlen (nameLabel)) == 0)
            {
              // We've got a hit.  Get ourselves to the beginning of the actual
              // processor name.
              char *realName = line;
              // Ignore the label.
              realName += std::strlen (nameLabel);
              // Just increment over all the white space.
              for (; *realName != ' ' && *realName != '\t'; ++realName);
              // Make sure we did it right.
              if (*(++realName) != ':' && *(++realName) != ' ')
                {
                  // We did it wrong.  Just set the name to Unknown.
                  SetProcessorNameToUnknown (i);
                }
              else
                {
                  // Yay!  Now set the string name.
                  realName += 2; // Increment to first spot in string.
                  this->processorStrings[i] =
                    new char [std::strlen (realName) + 1];
                  std::strcpy (this->processorStrings[i], realName);
                  // let's remove the last char if it's a newline.
                  if (this->processorStrings[i][std::strlen (realName) - 1] ==
                      '\n')
                    {
                      this->processorStrings[i][std::strlen (realName) - 1] =
                        '\0';
                    }
                }
              // Increment i; we're on to the next processor!
              ++i;
              continue;
            }
          else if (std::strncmp (flagsLabel,
                                 line,
                                 std::strlen (flagsLabel)) == 0)
            {
              // We've got a hit.  Get ourselves to the beginning of the actual
              // flags
              char *realFlags = line;
              // Ignore the label.
              realFlags += std::strlen (flagsLabel);
              // Just increment over all the white space.
              for (; *realFlags != ' ' && *realFlags != '\t'; ++realFlags);
              // Make sure we did it right.
              if (*(++realFlags) != ':' && *(++realFlags) != ' ')
                {
                  // We did it wrong.  Just keep the two interesting flags off.
                }
              else
                {
                  // Yay!  Now search the string for the proper flags.
                  ++realFlags; // Increment to first spot in string.

                  // The flags we are interested in.
                  const char *sseFlag = "sse ";
                  const char *sse2Flag = "sse2 ";
                  if (std::strstr (realFlags, sseFlag))
                    {
                      this->sseSupport = true;
                    }
                  if (std::strstr (realFlags, sse2Flag))
                    {
                      this->sse2Support = true;
                    }
                }
              continue;
            }
        }
      // We're done here.
      std::fclose (cpuinfo);
    }
  catch (int i)
    {
      std::cerr << i << "\n";
      switch (i)
        {
        case 1:
        case 2:
          // First we close the file, as we won't need it anymore.
          std::fclose (cpuinfo);
        case 0:
          // We couldn't open the file, we couldn't read from it, or we got a
          // result of no processors!  Fall back to POSIX interface.
          this->numberOfProcessors = sysconf (_SC_NPROCESSORS_ONLN);
          this->processorStrings = new char * [this->numberOfProcessors];
          // Set all strings to Unknown.
          for (int i = 0; i < this->numberOfProcessors; ++i)
            {
              SetProcessorNameToUnknown (i);
            }
          
          break;
        }
    }
}


Processors::~Processors (void)
{
  for (int i = 0; i < this->numberOfProcessors; ++i)
    {
      // Delete every string we have allocated.
      delete [] this->processorStrings[i];
    }
  delete [] this->processorStrings;
}


int
Processors::GetNumberOfProcessors (void)
  const throw ()
{
  return this->numberOfProcessors;
}


const char *
Processors::GetProcessorName (int index)
  const throw ()
{
  if (index >= 0 && index < this->numberOfProcessors)
    {
      return this->processorStrings[index];
    }
  else
    {
      return 0;
    }
}


bool
Processors::HaveSseSupport (void)
  const throw ()
{
  return this->sseSupport;
}


bool
Processors::HaveSse2Support (void)
  const throw ()
{
  return this->sse2Support;
}


void
Processors::SetProcessorNameToUnknown (int index)
  throw ()
{
  if (index >= 0 && index < this->numberOfProcessors)
    {
      this->processorStrings[index] = new char [std::strlen ("Unknown") + 1];
      std::strcpy (this->processorStrings[index], "Unknown");
    }
}


}
}
}
