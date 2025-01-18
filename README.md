# OpenNT 5.2 Project

The **OpenNT 5.2** project is an open-source initiative aimed at creating a modern, open, and community-driven version of the Windows NT operating system, based on the leaked **Windows Server 2003 RTM** (Release to Manufacturing) source code. This project allows developers and enthusiasts to explore, modify, and contribute to the legacy of Windows NT, with an emphasis on maintaining compatibility with the original codebase while enabling future improvements and modern features.

## Key Features

- **Windows NT 5.2 Compatibility**: Derived from the Windows Server 2003 RTM source code, ensuring compatibility with the core structure and behavior of the original operating system.
- **Open Source**: All source code and related resources are available under an open-source license, enabling anyone to use, modify, and contribute.
- **Legacy System Support**: Preserves compatibility with legacy applications designed for Windows NT 5.2, with the goal of providing a stable environment for old software.
- **Community-Driven Development**: Contributions from developers around the world, enabling continuous improvement and adaptation of the operating system.

## Installation

- *1.* Create and install Windows 10’s latest version virtual machine, with minimum 120GB disk space and 4GB memory and processor cores


- 2. Allocate D:\ disk drive for entire source code (min. 60GB)


- 3. Change CD-ROM drive to G:\ (for getting missing files if neccesary)


- 4. Disable User Account Control - needs for avoid screens of confirmation


- 5. Download source code from link below
  
   ```bash
   git clone https://github.com/tagicmi/Opennt-5.2.git
  ```
  # Important! Disable Real-Time Protection from Windows Security


- 6. Extract source code to D:\srv03rtm


- 7. Uncheck read-only from srv03rtm folder


- 8. If your host is Windows 10 1809 and later, install driver.pfx from “tools” folder for Local Machine & Current User, else if your host is up to Windows Vista delete driver.pfx, and rename driver_3des.pfx to that.


- 9. Run Command Prompt as Administrator, and switch to D:\srv03rtm.


- 10. If you’re on x64 host, run:
```bash
tools\razzle64 free offline
```
else: 
```bash
tools\razzle free offline
```


- 11. Run this for prepare to building
```bash
  tools\prebuild
```


- 12. Type this:            (-M 4 for using all 4 cores of processor)
```bash
 build /cZP -M 4
```


- 13. Type on CMD
```bash
  tools\postbuild -full
```


- 14. Then, write tools\oscdimg pro|per|srv for generating ISO file for XP Professional/Home Edition/Server 2003 Standard Edition


# Serial key located at srv03rtm\base\ntsetup\pidgen\pidgen\spidgen.cpp, and it’s 

```bash
HB9CF-JTKJF-722HV-VPBRF-9VKVM
```
