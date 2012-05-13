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

#include "hummstrummengine.hpp"

#include <cstdio>
#include <cstring>


namespace hummstrumm
{
namespace engine
{
namespace system
{


Platform::Platform ()
  /* noexcept */
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
      
      std::strcpy (this->name, "Microsoft ");

      // Test for the specific product.

      if (versionInfo.dwMajorVersion == 6)
        {
          if (versionInfo.dwMinorVersion == 0)
            {
              if (versionInfo.wProductType == VER_NT_WORKSTATION)
                {
                  std::strcat (this->name, "Windows Vista ");
                }
              else
                {
                  std::strcat (this->name, "Windows Server 2008 ");
                }
            }

          if (versionInfo.dwMinorVersion == 1)
            {
              if (versionInfo.wProductType == VER_NT_WORKSTATION)
                {
                  std::strcat (this->name, "Windows 7 ");
                }
              else
                {
                  std::strcat (this->name, "Windows Server 2008 R2 ");
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
             std::strcat (this->name, "Ultimate Edition");
             break;
           case PRODUCT_PROFESSIONAL:
             std::strcat (this->name, "Professional");
             break;
           case PRODUCT_HOME_PREMIUM:
             std::strcat (this->name, "Home Premium Edition");
             break;
           case PRODUCT_HOME_BASIC:
             std::strcat (this->name, "Home Basic Edition");
             break;
           case PRODUCT_ENTERPRISE:
             std::strcat (this->name, "Enterprise Edition");
             break;
           case PRODUCT_BUSINESS:
             std::strcat (this->name, "Business Edition");
             break;
           case PRODUCT_STARTER:
             std::strcat (this->name, "Starter Edition");
             break;
           case PRODUCT_CLUSTER_SERVER:
             std::strcat (this->name, "Cluster Server Edition");
             break;
           case PRODUCT_DATACENTER_SERVER:
             std::strcat (this->name, "Datacenter Edition");
             break;
           case PRODUCT_DATACENTER_SERVER_CORE:
             std::strcat (this->name,
                           "Datacenter Edition (core installation)");
             break;
           case PRODUCT_ENTERPRISE_SERVER:
             std::strcat (this->name, "Enterprise Edition");
             break;
           case PRODUCT_ENTERPRISE_SERVER_CORE:
             std::strcat (this->name,
                           "Enterprise Edition (core installation)");
             break;
           case PRODUCT_ENTERPRISE_SERVER_IA64:
             std::strcat (this->name,
                           "Enterprise Edition for Itanium-based Systems");
             break;
           case PRODUCT_SMALLBUSINESS_SERVER:
             std::strcat (this->name, "Small Business Server");
             break;
           case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
             std::strcat (this->name,
                           "Small Business Server Premium Edition");
             break;
           case PRODUCT_STANDARD_SERVER:
             std::strcat (this->name, "Standard Edition");
             break;
           case PRODUCT_STANDARD_SERVER_CORE:
             std::strcat (this->name,
                           "Standard Edition (core installation)");
             break;
           case PRODUCT_WEB_SERVER:
             std::strcat (this->name, "Web Server Edition");
             break;
           }
        }

      if (versionInfo.dwMajorVersion == 5 &&
          versionInfo.dwMinorVersion == 2)
        {
          if (GetSystemMetrics (SM_SERVERR2))
            {
              std::strcat (this->name, "Windows Server 2003 R2, ");
            }
          else if (versionInfo.wSuiteMask & VER_SUITE_STORAGE_SERVER)
            {
              std::strcat (this->name, "Windows Storage Server 2003");
            }
          else if (versionInfo.wSuiteMask & VER_SUITE_WH_SERVER)
            {
              std::strcat (this->name, "Windows Home Server");
            }
          else if (versionInfo.wProductType == VER_NT_WORKSTATION &&
                   systemInfo.wProcessorArchitecture ==
                     PROCESSOR_ARCHITECTURE_AMD64)
            {
              std::strcat (this->name,
                            "Windows XP Professional x64 Edition");
            }
          else
            {
              std::strcat (this->name, "Windows Server 2003, ");
            }
 
          // Test for the server type.
          if (versionInfo.wProductType != VER_NT_WORKSTATION)
            {
              if (systemInfo.wProcessorArchitecture ==
                  PROCESSOR_ARCHITECTURE_IA64)
                {
                  if (versionInfo.wSuiteMask & VER_SUITE_DATACENTER)
                    {
                      std::strcat (this->name,
                        "Datacenter Edition for Itanium-based Systems");
                    }
                  else if (versionInfo.wSuiteMask & VER_SUITE_ENTERPRISE)
                    {
                      std::strcat (this->name,
                        "Enterprise Edition for Itanium-based Systems");
                    }
                }
              else if (systemInfo.wProcessorArchitecture ==
                       PROCESSOR_ARCHITECTURE_AMD64)
                {
                  if (versionInfo.wSuiteMask & VER_SUITE_DATACENTER)
                    {
                      std::strcat (this->name, "Datacenter x64 Edition");
                    }
                  else if (versionInfo.wSuiteMask & VER_SUITE_ENTERPRISE)
                    {
                      std::strcat (this->name, "Enterprise x64 Edition");
                    }
                  else
                    {
                      std::strcat (this->name, "Standard x64 Edition");
                    }
                }          
              else
                {
                  if (versionInfo.wSuiteMask & VER_SUITE_COMPUTE_SERVER)
                    {
                      std::strcat (this->name,
                                    "Compute Cluster Edition");
                    }
                  else if (versionInfo.wSuiteMask & VER_SUITE_DATACENTER)
                    {
                      std::strcat (this->name, "Datacenter Edition");
                    }
                  else if (versionInfo.wSuiteMask & VER_SUITE_ENTERPRISE)
                    {
                      std::strcat (this->name, "Enterprise Edition");
                    }
                  else if (versionInfo.wSuiteMask & VER_SUITE_BLADE)
                    {
                      std::strcat (this->name, "Web Edition");
                    }
                  else
                    {
                      std::strcat (this->name, "Standard Edition");
                    }
                }
            }
        }

     if (versionInfo.dwMajorVersion == 5 && versionInfo.dwMinorVersion == 1)
        {
          std::strcat (this->name, "Windows XP ");
          if (versionInfo.wSuiteMask & VER_SUITE_PERSONAL)
            {
              std::strcat (this->name, "Home Edition");
            }
          else
            {
              std::strcat (this->name, "Professional");
            }
        }

      if (versionInfo.dwMajorVersion == 5 && versionInfo.dwMinorVersion == 0)
        {
          std::strcat (this->name, "Windows 2000 ");

          if (versionInfo.wProductType == VER_NT_WORKSTATION)
            {
              std::strcat (this->name, "Professional");
            }
          else
            {
              if (versionInfo.wSuiteMask & VER_SUITE_DATACENTER)
                {
                  std::strcat (this->name, "Datacenter Server");
                }
              else if (versionInfo.wSuiteMask & VER_SUITE_ENTERPRISE)
                {
                  std::strcat (this->name, "Advanced Server");
                }
              else
                {
                  std::strcat (this->name, "Server");
                }
            }
        }

      // Include service pack (if any) and build number.

      if (std::strlen (versionInfo.szCSDVersion) > 0)
        {
          std::strcat (this->name, " ");
          std::strcat (this->name, versionInfo.szCSDVersion);
        }

      char buffer[80];

      std::sprintf (buffer, " (build %d)", versionInfo.dwBuildNumber);
      std::strcat (this->name, buffer);

      if (versionInfo.dwMajorVersion >= 6)
        {
         if (systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
           {
             std::strcat (this->name, ", 64-bit");
           }
         else if (systemInfo.wProcessorArchitecture ==
                  PROCESSOR_ARCHITECTURE_INTEL)
           {
             std::strcat (this->name, ", 32-bit");
           }
        }
    }
  catch (int i)
    {
      switch (i)
        {
        case 0:
        case 1:
          std::strcpy (this->name, "Microsoft Windows");
          break;
        }
    }
}


Platform::~Platform ()
{
  delete this->name;
}


char *
Platform::GetName ()
  const /* noexcept */
{
  return this->name;
}


}
}
}
