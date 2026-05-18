# Hardware Information CLI Tool

## Why this tool?
This tool was created to provide a quick and easy way to check essential hardware components of a Windows PC directly from the command line. It focuses on:
- **Core Hardware:** CPU architecture and core count.
- **Memory:** Total physical RAM available.
- **GPU:** Information about installed graphics adapters and dedicated memory.
- **Monitors:** Details about connected displays, including resolution and refresh rates.

It's useful for developers, system administrators, or anyone who needs to verify hardware specs without navigating through complex Windows GUI menus.

## How to use
1. **Compilation:**
   Run the provided `build.bat` script to compile the tool using Microsoft Visual C++ compiler.
   ```cmd
   build.bat
   ```
2. **Running:**
   After compilation, run `hwcheck.exe` in your terminal.
   ```cmd
   hwcheck.exe
   ```

## Requirements
- Windows OS
- MSVC Build Tools (for compilation)
