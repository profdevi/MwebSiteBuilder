# MWebSiteBuilder
Source Code for a simplified static web site builder using string replacements with file contents


# Compilation Procedure

You can use cmake for building the source code.  You can compile the code quickly within the src  folder with

$ g++ *.cpp -o MWebSiteBuilder

C:> cl *.cpp -o MWebSiteBuilder


# Actions
The program is invoked with the command

$ MWebSiteBuilder -o=outfolder

1. Binary Files are copied from the current directory to target folder(outfolder)

2. Files with extensions .msym are skipped from copying to target folder

3.  Any text files are parsed for symbols with @@SymbolName@@. The contents of the file SymbolName.msym replaced for @@SymbolName@@ and written to the output directory.

# Example 1

##File Head.msym contains:

<html>
<head><title>This is a common  title</title></head>
<body>

##File Tail.msym contains:

</body>
</html>

## File index.htm contains:

@@Head@@

<emp>Hello World</emp>

@@Tail@@

##Output
The thee files Tail.msym, Head.msym, and index.html are processed.  The only file that is copied to output is index.htm. The contents of the index.htm file is the following.

<html>
<head><title>This is a common  title</title></head>
<body>

<emp>Hello World</emp>

</body>
</html>
