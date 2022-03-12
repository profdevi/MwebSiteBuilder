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


//v0.1 copyright Comine.com 20200722W0917
#include "MStdLib.h"
#include "MWUDirReader.h"
#include "MFilePathBuilder.h"
#include "MStringStringMap.h"
#include "MStringList.h"
#include "MStringBuilder.h"
#include "MWebSiteBuilder.h"

//******************************************************
//**  Module Elements
//******************************************************
static const char GSymbolFileExt[]=".msym";
static const char *GWebPageExts[]={".htm",".html",0};

//////////////////////////////////////////////////
static bool GGetSymbolTable(const char *srcdirectory,MStringStringMap &stringcol);
static bool GGetSymbols(const char *inputtxt,MStringList &symbollist);
static int GGetLargestSymbolSequence(const char *txt);					// Get the Largest AlphaNumeric Sequence Length in txt
static bool GGetLeftString(const char *txt,int length,MStdArray<char> &leftstr);
static bool GIsSymbolChar(char ch);						// Check if Character is a symbol name character
static bool GIsSymbolFile(const char *filepath);		// Check if file has extension of GSymbolFileExt
static bool GIsWebPageFile(const char *filepath);		// Check if file is a web page that undergoes substiutions

		
/////////////////////////////////////////////////
static bool GGetSymbolTable(const char *srcdirectory,MStringStringMap &stringcol)
	{
	MWUDirReader dirreader;
	if(dirreader.Create(srcdirectory)==false)
		{
		return false;
		}

	// Init output string string  collection
	if(stringcol.Create()==false)
		{
		return false;
		}

	while(dirreader.Read()==true)
		{
		const char *filename=dirreader.GetFullFilePath();
		const char *shortname=dirreader.GetFileName();

		// Make Sure it is a file
		if(MStdDirExists(filename)==true || MStdFileExists(filename)==false ) {continue; }

		// Skip non symbol files
		if(MStdStrEnds(filename,GSymbolFileExt)==false) { continue; }

		MStdArray<char> textcontent;
		if(MStdFileReadText(filename,textcontent)==false)
			{
			return false;
			}

		const char shortnamelength=MStdStrLen(shortname);
		MStdArray<char> buffer;
		if(buffer.Create(shortnamelength+2)==false)
			{
			return false;
			}

		MStdStrCpy(buffer.Get(),shortname);

		const int symextensionlength=MStdStrLen(GSymbolFileExt);
		MStdAssert(shortnamelength-symextensionlength>0);
		buffer[shortnamelength-symextensionlength]=0;

		if(stringcol.Add(buffer.Get(),textcontent.Get())==false)
			{
			return false;
			}
		}

	return true;
	}	


////////////////////////////////////////////////////////////////////
static bool GGetSymbols(const char *inputtxt,MStringList &symbollist)
	{
	if(symbollist.Create()==false)
		{
		return false;
		}

	for(int i=0;inputtxt[i]!=0;++i)
		{
		if(inputtxt[i]!='@') { continue; }
		if(inputtxt[i+1]!='@') { continue; }
		const int symbollength=GGetLargestSymbolSequence(inputtxt+i+2);
		if(symbollength==0) { continue; }
		if(inputtxt[i+2+symbollength]!='@') { continue; }
		if(inputtxt[i+2+symbollength+1]!='@') { continue; }
	
		//=We have a symbol		
		
		MStdArray<char> symbol;
		if(GGetLeftString(inputtxt+i+2,symbollength,symbol)==false)
			{
			return false;
			}

		if(symbollist.IsMember(symbol.Get())==false)
			{
			if(symbollist.AddString(symbol.Get())==false)
				{
				return false;
				}
			}
		}

	return true;
	}


////////////////////////////////////////////////////////////////////
static int GGetLargestSymbolSequence(const char *txt)
	{
	int count;
	for(count=0;txt[count]!=0;++count)
		{
		if(GIsSymbolChar(txt[count])==false) { break; }
		}

	return count;
	}


////////////////////////////////////////////////////////////////////
static bool GGetLeftString(const char *txt,int length,MStdArray<char> &leftstr)
	{
	MStdAssert(length>0);
	if(leftstr.Create(length+2)==false)
		{
		return false;
		}

	leftstr[length]=0;

	for(int i=0;i<length;++i)
		{
		const char ch=txt[i];
		leftstr[i]=ch;
		if(ch==0) {break; }
		}

	return true;
	}


///////////////////////////////////////////////////////////////////
static bool GIsSymbolChar(char ch)
	{
	if(MStdIsAlphaNumeric(ch)==true) { return true; }
	if(ch=='_') { return true; }
	return false;
	}


///////////////////////////////////////////////////////////////////
static bool GIsSymbolFile(const char *filepath)
	{
	const char *fileext=MStdPathGetExtension(filepath);
	if(fileext==NULL) { return false; }
	if(MStdStrICmp(fileext,GSymbolFileExt)!=0) { return false; }
	return true;
	}


//////////////////////////////////////////////////////
static bool GIsWebPageFile(const char *filepath)
	{
	const char *fileextension=MStdPathGetExtension(filepath);
	if(fileextension==NULL) { return false; }

	for(int i=0;GWebPageExts[i]!=0;++i)
		{
		if(MStdStrICmp(fileextension,GWebPageExts[i])==0) { return true; }
		}

	return false;
	}


//******************************************************
//**  MWebSiteBuilder class
//******************************************************
void MWebSiteBuilder::ClearObject(void)
	{
	}


////////////////////////////////////////////////
MWebSiteBuilder::MWebSiteBuilder(void)
	{  ClearObject();  }


////////////////////////////////////////////////
MWebSiteBuilder::~MWebSiteBuilder(void)
	{  Destroy();  }


////////////////////////////////////////////////
bool MWebSiteBuilder::Create(const char *srcdir,const char *targetdir)
	{
	Destroy();
	
	if(MStdPathGetAbsolute(srcdir,mSourceDir)==false 
			|| MStdPathGetAbsolute(targetdir,mTargetDir)==false)
		{
		Destroy();
		return false;
		}

	if(MStdDirExists(mSourceDir.Get())==false || MStdDirExists(mTargetDir.Get())==false)
		{
		Destroy();
		return false;
		}		
	return true;
	}


////////////////////////////////////////////////
bool MWebSiteBuilder::Destroy(void)
	{
	ClearObject();
	return true;
	}


///////////////////////////////////////////////
bool MWebSiteBuilder::Build(void)
	{
	// Load up the msym files
	MStringStringMap symbolmap;
	if(GGetSymbolTable(mSourceDir.Get(),symbolmap)==false)
		{
		return false;
		}

	// Process Every Directory
	MWUDirReader dirreader;
	if(dirreader.Create(mSourceDir.Get())==false)
		{
		return false;
		}

	MFilePathBuilder pathbuilder;
	if(pathbuilder.Create(mTargetDir.Get())==false)
		{
		return false;
		}

	while(dirreader.Read()==true)
		{
		const char *fullfilepath=dirreader.GetFullFilePath();
		const char *shortfilename=dirreader.GetFileName();
		MStdAssert(fullfilepath!=NULL && shortfilename!=NULL);
		if(MStdDirExists(fullfilepath)==true) { continue; }
		if(MStdFileExists(fullfilepath)==false) { continue; }

		if(GIsSymbolFile(fullfilepath)==true)
			{ 
			MStdPrintf("-skipped Symbol File %s\n",shortfilename);
			continue;
			}		

		//** Get target file path
		if(pathbuilder.Push(shortfilename)==false)
			{
			return false;
			}

		MBuffer fulltargetfilepath;
		if(pathbuilder.GetFullPath(fulltargetfilepath)==false)
			{
			return false;
			}

		// Clean up the pushing
		pathbuilder.Pop();
		
		if(GIsWebPageFile(fullfilepath)==false)
			{
			//Copy file to target location
			if(MStdFileCopy(fullfilepath,fulltargetfilepath.GetBuffer())==false)
				{
				return false;
				}

			MStdPrintf("-copied %s\n",shortfilename);
			continue;
			}

		//=We have a web page file that needs to be substituted
		MStdArray<char> srcfiletext;
		if(MStdFileReadText(fullfilepath,srcfiletext)==false)
			{
			return false;
			}
	
		// Get Symbols from file
		MStringList symbollist;
		if(GGetSymbols(srcfiletext.Get(),symbollist)==false)
			{
			return false;
			}

		MStringBuilder builder;
		if(builder.Create()==false || builder.Set(srcfiletext.Get())==false)
			{
			return false;
			}
		
		// Process each symbol
		symbollist.ReadReset();
		const char *symbol;
		while((symbol=symbollist.ReadString())!=0)
			{
			const char *valuestring=symbolmap.GetValue(symbol);
			if(valuestring==NULL) { continue; }

			// Build backup @@symbol@@
			MBuffer paddedsymbol(1000);
			MStdSPrintf(paddedsymbol.GetBuffer(),paddedsymbol.GetSize()-2,"@@%s@@",symbol);

			if(builder.Replace(paddedsymbol.GetBuffer(),valuestring)==false)
				{
				return false;
				}
			}

		// Now Write to target file
		if(MStdFileWriteText(fulltargetfilepath.GetBuffer(),builder.Get())==false)
			{
			return false;
			}

		MStdPrintf("-created %s\n",shortfilename);
		}

	return true;
	}




