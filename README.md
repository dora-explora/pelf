# Portable Executable Linkable Format

a.k.a. PELF, a binary that can run natively on both Windows and Linux!

This project is a file format and corresponding command-line utility that combines a Windows **P**ortable **E**xecutable file (commonly know by its extension .exe) and a Linux **E**xecutable **L**inkable **F**ormat file through a shebang-less shell script to make a binary [polyglot](https://wikipedia.org/wiki/Polyglot_\(computing\)) that can run on both Windows and Linux!

## Installation

(I'll do this later...)

## Usage

Just type `pelf file` to combine `file` and `file.exe` into a .pelf, or specify the .exe file and optionally the .pelf file as the second and third argument.

## How it works

The PELF format takes advantage of the Windows DOS Stub, a tiny 128B DOS program present at the start of every .exe file that reminds any user still somehow running DOS that they cannot run this program.

A PELF overwrites this stub with an even tinier script (~53 bytes!) that takes that end of the file after a certain offset, copies it to a new file, marks that file as executable, and simultaneously runs it and deletes it.

Then, by concatenating the ELF file at the end of the PE file and setting that offset to be the point where they connect, you have yourself a working PELF!
