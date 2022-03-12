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


//v1.4 copyright Comine.com 20200720M2029
#include "MStdLib.h"
#include "MStringStringMap.h"


//******************************************************
//**  Module Elements
//******************************************************
struct GNode
	{
	char *DataKey;
	char *DataValue;
	GNode *Next;
	};


//******************************************************
//**  MStringStringMap class
//******************************************************
void MStringStringMap::ClearObject(void)
	{
	mList=NULL;
	mReaderPos=NULL;
	mCount=0;
	}


////////////////////////////////////////////////
MStringStringMap::MStringStringMap(bool create)
	{
	ClearObject();
	if(create==true && Create()==false)
		{
		return;
		}
	}


////////////////////////////////////////////////
MStringStringMap::~MStringStringMap(void)
	{  Destroy();  }


////////////////////////////////////////////////
bool MStringStringMap::Create(void)
	{
	Destroy();

	// Allocate dummy first node
	mList=new(std::nothrow) GNode;
	if(mList==NULL)
		{
		Destroy();
		return false;
		}

	// Init first members
	mList->DataKey=NULL;
	mList->DataValue=NULL;
	mList->Next=NULL;

	return true;
	}


////////////////////////////////////////////////
bool MStringStringMap::Destroy(void)
	{
	GNode *p,*nextnode;
	for(p=mList;p!=NULL;p=nextnode)
		{
		nextnode=p->Next;

		if(p->DataKey!=NULL)
			{
			delete[] p->DataKey;

			p->DataKey=NULL;
			}

		if(p->DataValue!=NULL)
			{
			delete[] p->DataValue;

			p->DataValue=NULL;
			}

		delete p;
		}

	ClearObject();
	return true;
	}


////////////////////////////////////////////////
bool MStringStringMap::Add(const char *key,const char *value)
	{
	GNode *node;
	for(node=mList->Next;node!=NULL;node=node->Next)
		{
		if(MStdStrCmp(node->DataKey,key)==0)
			{
			// Change the value
			const int length=MStdStrLen(value);
			char *newdata=new(std::nothrow) char[length+1];
			if(newdata==NULL)
				{
				return false;
				}

			MStdStrCpy(newdata,value);
			
			// Release old value and set new value
			delete[] node->DataValue;

			node->DataValue = newdata;
			return true;
			}
		}

	//=The node does not exist yet
	
	// Allocate a new ndoe
	node=new(std::nothrow) GNode;
	if(node==NULL)
		{
		return false;
		}

	// Set Key
	const int length=MStdStrLen(key);
	node->DataKey = new char[length+1];
	if(node->DataKey==NULL)
		{
		delete node;

		return false;
		}

	MStdStrCpy(node->DataKey,key);

	// Set Value
	const int vallength=MStdStrLen(value);
	node->DataValue = new char[vallength+1];
	if(node->DataValue==NULL)
		{

		delete[]node->DataKey;

		delete node;

		return false;
		}

	MStdStrCpy(node->DataValue,value);

	// Link into list
	node->Next = mList->Next;
	mList->Next=node;

	// Increment add count
	mCount = mCount + 1;
	
	return true;
	}


////////////////////////////////////////////////
bool MStringStringMap::Delete(const char *key)
	{
	GNode *p;
	for(p=mList;p->Next!=NULL;p=p->Next)
		{
		if(MStdStrCmp(p->Next->DataKey,key)==0)
			{
			GNode *next=p->Next->Next;

			delete[] p->Next->DataKey;

			delete[] p->Next->DataValue;

			delete p->Next;

			p->Next=next;
			
			// decrease count
			mCount=mCount - 1;
			return true;
			}
		}

	return false;
	}


////////////////////////////////////////////////
const char *MStringStringMap::GetValue(const char *key)
	{
	GNode *p;
	for(p=mList->Next;p!=NULL;p=p->Next)
		{
		if(MStdStrCmp(p->DataKey,key)==0)
			{  return p->DataValue; }
		}

	return NULL;
	}


////////////////////////////////////////////////
int MStringStringMap::GetCount(void)
	{
	return mCount;
	}


///////////////////////////////////////////////
bool MStringStringMap::Print(void)
	{
	for(GNode *p=mList->Next;p!=NULL;p=p->Next)
		{
		MStdPrintf("%-12s : %s\n",p->DataKey,p->DataValue);
		}
	
	return true;
	}


////////////////////////////////////////////////
bool MStringStringMap::ReadReset(void)
	{
	mReaderPos=mList;
	return true;
	}


////////////////////////////////////////////////
bool MStringStringMap::Read(void)
	{
	if(mReaderPos==NULL) { return false; }
	mReaderPos=mReaderPos->Next;
	if(mReaderPos==NULL) { return false; }
	return true;
	}


////////////////////////////////////////////////
const char *MStringStringMap::ReadGetKey(void)
	{
	if(mReaderPos==NULL){ return NULL;  }
	return mReaderPos->DataKey;
	}


////////////////////////////////////////////////
const char *MStringStringMap::ReadGetValue(void)
	{
	if(mReaderPos==NULL) { return NULL; }
	return mReaderPos->DataValue;
	}


