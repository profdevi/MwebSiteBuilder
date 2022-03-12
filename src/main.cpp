/*
Copyright (C) 2011-2022, Comine.com ( comine.com@gmail.com )
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
- The the names of the contributors of this project may not be used to 
  endorse or promote products derived from this software without specific 
  prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
`AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/


//v1.0 copyright Comine.com 20220312S1114
#include "MStdLib.h"
#include "MCommandArg.h"
#include "MWebSiteBuilder.h"


//******************************************************
//* Module Elements
//******************************************************
static const char *GApplicationName="MWebSiteBuilders";	// Used in Help
static const char *GApplicationVersion="1.0";	// Used in Help

////////////////////////////////////////////////////
static void GDisplayHelp(void);

////////////////////////////////////////////////////
int main(int argn,const char *argv[])
	{
	MCommandArg args(argn,argv);

	///////////////////////////////////////////////
	if(args.GetArgCount()<1)
		{
		GDisplayHelp();
		return 0;
		}

	if(args.CheckRemoveHelp()==true)
		{
		GDisplayHelp();
		return 0;
		}

	int index=0;
	const char *targetdir=NULL;
	if(args.GetNameValue("-o=",targetdir,index)==false)
		{
		GDisplayHelp();
		return 1;
		}

	if(MStdDirExists(targetdir)==false)
		{
		MStdPrintf("** Target Dir %s does not exist\n",targetdir);
		return 2;
		}

	MWebSiteBuilder builder;
	if(builder.Create(".",targetdir)==false)
		{
		MStdPrintf("**Unable to MWebSiteBuilder system\n");
		return 3;
		}

	if(builder.Build()==false)
		{
		MStdPrintf("**Unable to build files\n");
		return false;
		}
	
	return 0;
	}


////////////////////////////////////////////////////
static void GDisplayHelp(void)
	{
	MStdPrintf(	"\n"
				"   usage:  %s -o=<Target Dir> [-h]\n"
				"           v%s copyright Comine.com\n"
				"\n"
				"   Takes web page files (.htm,.html) and  replaces the  @@Symbol@@ tags from\n"
				"   files with Symbol.msym extensions and places them in the output directory\n"
				"   All other files are just copied excluding the .msym files.\n"
				"\n"
				,GApplicationName,GApplicationVersion);
	}


