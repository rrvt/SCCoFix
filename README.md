# Project Title

SCCoOutpost is normally installed in "Program Files (x86)" however in order to do that the user must be an Administrator.  Some laptops in our served agencies are configured to only allow a Standard User Account (SUA) to be used by the ham radio operators.

This application is used after a version of Outpost to correct some of the configuration files.  While that corrects some of the path references it is not quite enough.  Another Kludge using the same root directory in the preparation as the final location of the files solves the final issue:
  - C:\SCCPacket\bin\        -- Executables Directory
  - C:\SCCPacket\data        -- Data Directory and SubDirectories
  - C:\SCCPacke\PacFORMS\    -- Old Forms directory, still loaded
  - C:\SCCPacke\PackItForms\ -- New Forms directory

## Getting Started

This version was created with Visual Studion 2022 (VS22).  It was compiled with the following properties:
  - Windows SDK Version: 10.0.xxxxx (latest)
  - Platfor Toolset: visual Studio 2022 (latest)
  - MFC: Use MFC in a Shared DLL
  - Character Set:  Use Unicode Character Set
  - Precompiled Header:  Not Using Precompiled Headers
  - Linker/Additional Dependencies:  Htmlhelp.lib

The HTML Help Workshop (HHW), Version 4.74.8702.0 (the last one produced) was used to prepare the help file (WixApp.chm).  It is copied into the Release directory.  I used Dreamweaver (DW) to do most of the content production of the help files that the HTML Help Workshop produces (i.e. HHW is used to produce the pages/files needed and DW is used to fill in the content).

Wix is used to create the &lt;AppName&gt;.msi file.  WixApp (one of my applications, see git) was used to produce the product.wxs file.

Note:  In order to avoid hickups during the compilation/link process make sure the VS22 dependencies are
set so the projects are produced in the proper order.

## Prerequisites

Windows 7 or above.  visual Studio 2022 or above.  The WiX Toolset must be installed in Visual Studio.
The "HTML Help Workshop" (google it) must be installed on the PC.

### Installing

This application is not installed.  The SCCoFix.exe file is copied to C:\SCCPacket\ directory.  Assisting the creation of a SUA installer for Outpost is the goal of this application.  Here are the steps to create and SUA installation application for SCC Outpost:

  - Uninstall SCC Outpost and delete any remaining copies of Outpost and Forms from the C drive.
  - Using a Administrator User Account (AUA) install the latest version of the Hospital SCC Outpost with the options:
    * Direct the Executable Files to C:\SCCPacket\bin\
    * Direct the Data Files to C:\SCCPacket\data\
  - Copy the Forms directories to C:\SCCPacket\
  - Copy SCCoFix.exe to C:\SCCPacket\
  - Copy Manifest.txt to C:\SCCPacket\
  - Execute C:\SCCPacket\SCCoFix.exe
  - Note that C:\SCCPacket\SCCoFix.ini has been created.  If the previous step needs to be repeated SCCoFix.ini must be deleted before running SCCoFix.exe
  - Using Directory Opus Pro Edition from TGP Software create an Archive file after highlighting all directories and files in the C:\SCCPacket\ directory.
    * In the first dialog box name the resulting archive SCCPacket and select the "Make self-extracting archive" check box.
    * In the second dialog box:
      - Set Name to SCCPacket
      - Set the Custom instructions to C:\SCCPacket\Manifest.txt
      - Set Default path for extraction to C:\SCCPacket
      - Set Auto-run after extraction to SCCoFix.exe (a drop down list is produced by the little v)

## Authors

SCCoFix.exe -- Robert R. Van Tuyl
SCCoOutpost -- Jim Oberhofer, KN6PE, and others

Contact:  romeo romeo victor tango alpha tango sam whisky delta echo dot charlie oscar mike

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

