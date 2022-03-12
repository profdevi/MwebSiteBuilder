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


//v1.4 copyright Comine.com 20190903T0710
#include "MString.h"
#include "MBuffer.h"
#include "MIntList.h"
#include "MStringBuilder.h"


//******************************************************
//**  MStringBuilder class
//******************************************************
void MStringBuilder::ClearObject(void)
	{
	}


////////////////////////////////////////////////
MStringBuilder::MStringBuilder(void)
	{  ClearObject();  }


////////////////////////////////////////////////
MStringBuilder::~MStringBuilder(void)
	{  Destroy();  }


////////////////////////////////////////////////
bool MStringBuilder::Create(void)
	{
	Destroy();

	// Init mProgram
	if(mBuffer.Create("")==false)
		{
		Destroy();
		return false;
		}
	return true;
	}


////////////////////////////////////////////////
bool MStringBuilder::Destroy(void)
	{
	mBuffer.Destroy();	
	ClearObject();
	return true;
	}


////////////////////////////////////////////////////
bool MStringBuilder::Set(const char *val)
	{
	if(mBuffer.Create(val)==false)
		{
		return false;
		}

	return true;
	}


////////////////////////////////////////////////////
bool MStringBuilder::Set(const unsigned char val[],int size)
	{
	MBuffer buffer;
	if(buffer.Create(size+1)==false)
		{
		return false;
		}

	int i;
	for(i=0;i<size;++i)
		{
		buffer[i]=(char)val[i];
		}

	buffer[size]=0;

	//= Made a string in buffer

	if(Set(buffer.GetBuffer())==false)
		{
		//=Unable to set string
		return false;
		}

	return true;
	}


////////////////////////////////////////////////////
const char *MStringBuilder::Get(void)
	{
	return mBuffer.Get();
	}


///////////////////////////////////////////////////
bool MStringBuilder::Replace(const char *original,const char *newstr)
	{
	if(original==NULL || *original==0 || newstr==NULL)
		{
		return false;
		}

	MIntList positions;
	if(positions.Create()==false)
		{
		return false;
		}

	int bufstrlen=mBuffer.Length();
	if(MStdStrLen(original)>bufstrlen)
		{
		return true;
		}

	const char *buffer=mBuffer.Get();
	int originallen=MStdStrLen(original);
	int i;
	for(i=0;i<=bufstrlen-originallen;++i)
		{
		if(MStdMemCmp(buffer+i,original,originallen)==0)
			{
			if(positions.Add(i)==false)
				{
				return false;
				}

			// Skip substituted item
			i+=originallen-1;
			continue;
			}
		}

	if(positions.GetCount()==0)
		{
		//=We have nothing to substitute
		return true;
		}

	int newstrlen=MStdStrLen(newstr);
	MBuffer newbuffer;
	if(newbuffer.Create(bufstrlen+positions.GetCount()
				*(newstrlen-originallen)+100)==false)
		{
		return false;
		}

	char *newbufptr=newbuffer.GetBuffer();
	
	int target=0;
	for(i=0; ;++i)
		{
		if(buffer[i]==0)
			{
			newbufptr[target]=0;
			break;
			}

		if(positions.IsMember(i)==true)
			{
			i+=originallen-1;
			MStdStrCpy(newbufptr+target,newstr);
			target+=newstrlen;
			continue;
			}


		newbufptr[target]=buffer[i];
		target=target+1;
		}

	// Copy Buffer back into string
	if(mBuffer.Create(newbuffer.GetBuffer())==false)
		{
		return false;
		}
	
	return true;
	}


////////////////////////////////////////////////////////////
bool MStringBuilder::Replace(const char *original,const char *newstr,const char *extra)
	{
	MString tmp;
	if(tmp.Create(newstr)==false)
		{
		return false;
		}

	if(tmp.Append(extra)==false)
		{
		return false;
		}

	return Replace(original,tmp.Get() );
	}


//////////////////////////////////////////////////////////
bool MStringBuilder::Replace(const char *original,int value)
	{
	char buf[100];
	MStdSPrintf(buf,sizeof(buf)-1,"%d",value);
	return Replace(original,buf);
	}


//////////////////////////////////////////////////////////
bool MStringBuilder::Replace(const char *original,float value)
	{
	char buf[100];
	MStdSPrintf(buf,sizeof(buf)-1,"%g",value);
	return Replace(original,buf);
	}


//////////////////////////////////////////////////////////
bool MStringBuilder::Replace(const char *original,bool value)
	{
	if(value==true)
		{
		return Replace(original,"true");
		}
	else
		{
		return Replace(original,"false");
		}
	}


/////////////////////////////////////////////////////////////
int MStringBuilder::GetCount(const char *str)
	{
	if(str==NULL || *str==0)
		{
		return false;
		}

	int count=0;
	int bufstrlen=mBuffer.Length();
	int originallen=MStdStrLen(str);
	const char *buffer=mBuffer.Get();
	int i;
	for(i=0;i<bufstrlen-originallen;++i)
		{
		if(MStdMemCmp(buffer+i,str,originallen)==0)
			{
			count=count+1;
			// Skip substituted item
			i+=originallen-1;
			continue;
			}
		}
	
	return count;
	}

