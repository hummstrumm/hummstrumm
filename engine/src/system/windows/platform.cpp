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


namespace hummstrumm
{
namespace engine
{
namespace system
{


Platform::Platform (void)
  throw ()
  : name (new char [256])
{
  try
    {
      // Copied almost verbatim from MSDN.
      // <http://msdn.microsoft.com/en-us/library/ms724429(v=VS.85).aspx>

      OSVERSIONINFOEX versionInfo;
      SYSTEM_INFO systemInfo;
      void (WINAPI *dllGetNativeSystemInfo) (LPSYSTEM_INFO);
      BOOL (WINAPI *dllGetProductInfo) (DWORD, DWORD, DWORD, DWORD, PDWORD);
      DWORD osType;

      ZeroMemory (&systemInfo, sizeof (SYSTEM_INFO));
      ZeroMemory (&versionInfo, sizeof (OSVERSIONINFOEX));

      versionInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFOEX);

      // Fill in versionInfo.  This gives us data.
      if (!GetVersionEx ((OSVERSIONINFO *) &versionInfo))
        {
          throw 0;
        }

      // Fill in systemInfo.  From this, we will get data for our string.
      dllGetNativeSystemInfo = (void (WINAPI *) (LPSYSTEM_INFO))
        GetProcAddress (GetModuleHandle ("kernel32.dll"),
                        "GetNativeSystemInfo");
      if (dllGetNativeSystemInfo)
        {
          dllGetNativeSystemInfo (&systemInfo);
        }
      else
        {
          GetSystemInfo (&systemInfo);
        }

      // Make sure we're on a modern Windows
      if (versionInfo.dwPlatformId != VER_PLATFORM_WIN32_NT ||
          versionInfo.dwMajorVersion <= 4)
        {
          throw 1;
        }
      
      std::strncpy (this->name, "Microsoft ", 256);

      // Test for the specific product.

      if (versionInfo.dwMajorVersion == 6)
        {
          if (versionInfo.dwMinorVersion == 0)
            {
              if (versionInfo.wProductType == VER_NT_WORKSTATION)
                {
                  std::strncat (this->name, 256, "Windows Vista ");
                }
              else
                {
                  std::strncat (this->name, 256, "Windows Server 2008 ");
                }
            }

          if (versionInfo.dwMinorVersion == 1)
            {
              if (versionInfo.wProductType == VER_NT_WORKSTATION)
                {
                  std::strncat (this->name, 256, "Windows 7 ");
                }
              else
                {
                  std::strncat (this->name, 56, "Windows Server 2008 R2 ");
                }
            }
         
         dllGetProductInfo =
           (BOOL (WINAPI *)(DWORD, DWORD, DWORD, DWORD, PDWORD))
             GetProcAddress (GetModuleHandle ("kernel32.dll"), 
                             "GetProductInfo");

         dllGetProductInfo (versionInfo.dwMajorVersion,
                            versionInfo.dwMinorVersion, 0, 0, &osType);

         switch (osType)
           {
           case PRODUCT_ULTIMATE:
             std::strncat (this->name, 256, "Ultimate Edition");
             break;
           case PRODUCT_PROFESSIONAL:
             std::strncat (this->name, 256, "Professional");
             break;
           case PRODUCT_HOME_PREMIUM:
             std::strncat (this->name, 256, "Home Premium Edition");
             break;
           case PRODUCT_HOME_BASIC:
             std::strncat (this->name, 256, "Home Basic Edition");
             break;
           case PRODUCT_ENTERPRISE:
             std::strncat (this->name, 256, "Enterprise Edition");
             break;
           case PRODUCT_BUSINESS:
             std::strncat (this->name, 256, "Business Edition");
             break;
           case PRODUCT_STARTER:
             std::strncat (this->name, 256, "Starter Edition");
             break;
           case PRODUCT_CLUSTER_SERVER:
             std::strncat (this->name, 256, "Cluster Server Edition");
             break;
           case PRODUCT_DATACENTER_SERVER:
             std::strncat (this->name, 256, "Datacenter Edition");
             break;
           case PRODUCT_DATACENTER_SERVER_CORE:
             std::strncat (this->name, 256,
                           "Datacenter Edition (core installation)");
             break;
           case PRODUCT_ENTERPRISE_SERVER:
             std::strncat (this->name, 256, "Enterprise Edition");
             break;
           case PRODUCT_ENTERPRISE_SERVER_CORE:
             std::strncat (this->name, 256,
                           "Enterprise Edition (core installation)");
             break;
           case PRODUCT_ENTERPRISE_SERVER_IA64:
             std::strncat (this->name, 256,
                           "Enterprise Edition for Itanium-based Systems");
             break;
           case PRODUCT_SMALLBUSINESS_SERVER:
             std::strncat (this->name, 256, "Small Business Server");
             break;
           case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
             std::strncat (this->name, 256,
                           "Small Business Server Premium Edition");
             break;
           case PRODUCT_STANDARD_SERVER:
             std::strncat (this->name, 256, "Standard Edition");
             break;
           case PRODUCT_STANDARD_SERVER_CORE:
             std::strncat (this->name, 256,
                           "Standard Edition (core installation)");
             break;
           case PRODUCT_WEB_SERVER:
             std::strncat (this->name, 256, "Web Server Edition");
             break;
           }
        }

      if (versionInfo.dwMajorVersion == 5 &&
          versionInfo.dwMinorVersion == 2)
        {
          if (GetSystemMetrics (SM_SERVERR2))
            {
              std::strncat (this->name, 256, "Windows Server 2003 R2, ");
            }
          else if (versionInfo.wSuiteMask & VER_SUITE_STORAGE_SERVER)
            {
              std::strncat (this->name, 256, "Windows Storage Server 2003");
            }
          else if (versionInfo.wSuiteMask & VER_SUITE_WH_SERVER)
            {
              std::strncat (this->name, 256, "Windows Home Server");
            }
          else if (versionInfo.wProductType == VER_NT_WORKSTATION &&
                   systemInfo.wProcessorArchitecture ==
                     PROCESSOR_ARCHITECTURE_AMD64)
            {
              std::strncat (this->name, 256,
                            "Windows XP Professional x64 Edition");
            }
          else
            {
              std::strncat (this->name, 256, "Windows Server 2003, ");
            }
 
          // Test for the server type.
          if (versionInfo.wProductType != VER_NT_WORKSTATION)
            {
              if (systemInfo.wProcessorArchitecture ==
                  PROCESSOR_ARCHITECTURE_IA64)
                {
                  if (versionInfo.wSuiteMask & VER_SUITE_DATACENTER)
                    {
                      std::strncat (this->name, 256,
                        "Datacenter Edition for Itanium-based Systems");
                    }
                  else if (versionInfo.wSuiteMask & VER_SUITE_ENTERPRISE)
                    {
                      std::strncat (this->name, 256,
                        "Enterprise Edition for Itanium-based Systems");
                    }
                }
              else if (systemInfo.wProcessorArchitecture ==
                       PROCESSOR_ARCHITECTURE_AMD64)
                {
                  if (versionInfo.wSuiteMask & VER_SUITE_DATACENTER)
                    {
                      std::strncat (this->name, 256, "Datacenter x64 Edition");
                    }
                  else if (versionInfo.wSuiteMask & VER_SUITE_ENTERPRISE)
                    {
                      std::strncat (this->name, 256, "Enterprise x64 Edition");
                    }
                  else
                    {
                      std::strncat (this->name, 256, "Standard x64 Edition");
                    }
                }          
              else
                {
                  if (versionInfo.wSuiteMask & VER_SUITE_COMPUTE_SERVER)
                    {
                      std::strncat (this->name, 256, "Compute Cluster Edition");
                    }
                  else if (versionInfo.wSuiteMask & VER_SUITE_DATACENTER)
                    {
                      std::strncat (this->name, 256, "Datacenter Edition");
                    }
                  else if (versionInfo.wSuiteMask & VER_SUITE_ENTERPRISE)
                    {
                      std::strncat (this->name, 256, "Enterprise Edition");
                    }
                  else if (versionInfo.wSuiteMask & VER_SUITE_BLADE)
                    {
                      std::strncat (this->name, 256, "Web Edition");
                    }
                  else
                    {
                      std::strncat (this->name, 256, "Standard Edition");
                    }
                }
            }
        }

     if (versionInfo.dwMajorVersion == 5 && versionInfo.dwMinorVersion == 1)
        {
          std::strncat (this->name, 256, "Windows XP ");
          if (versionInfo.wSuiteMask & VER_SUITE_PERSONAL)
            {
              std::strncat (this->name, 256, "Home Edition");
            }
          else
            {
              std::strncat (this->name, 256, "Professional");
            }
        }

      if (versionInfo.dwMajorVersion == 5 && versionInfo.dwMinorVersion == 0)
        {
          std::strncat (this->name, 256, "Windows 2000 ");

          if (versionInfo.wProductType == VER_NT_WORKSTATION)
            {
              std::strncat (this->name, 256, "Professional");
            }
          else
            {
              if (versionInfo.wSuiteMask & VER_SUITE_DATACENTER)
                {
                  std::strncat (this->name, 256, "Datacenter Server");
                }
              else if (versionInfo.wSuiteMask & VER_SUITE_ENTERPRISE)
                {
                  std::strncat (this->name, 256, "Advanced Server");
                }
              else
                {
                  std::strncat (this->name, 256, "Server");
                }
            }
        }

      // Include service pack (if any) and build number.

      if (std::strlen (versionInfo.szCSDVersion) > 0)
        {
          std::strncat (this->name, 256, " ");
          std::strncat (this->name, 256, versionInfo.szCSDVersion);
        }

      char buffer[80];

      std::sprintf (buffer, 80, " (build %d)", versionInfo.dwBuildNumber);
      std::strncat (this->name, 256, buffer);

      if (versionInfo.dwMajorVersion >= 6)
        {
         if (systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
           {
             std::strncat (this->name, 256,", 64-bit");
           }
         else if (systemInfo.wProcessorArchitecture ==
                  PROCESSOR_ARCHITECTURE_INTEL)
           {
             std::strncat (this->name, 256, ", 32-bit");
           }
        }
    }
  catch (int i)
    {
      switch (i)
        {
        case 0:
        case 1:
          std::strncpy (this->name, 256, "Microsoft Windows");
          break;
        }
    }
}


Platform::~Platform (void)
{
  delete this->name;
}


char *
Platform::GetName (void)
  const throw ()
{
  return this->name;
}


}
}
}
