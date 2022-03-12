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
#ifndef MStringStringMap_h
#define MStringStringMap_h

//******************************************************
//**  MStringStringMap class
//******************************************************
class MStringStringMap
	{
	////////////////////////////////////////////////
	struct GNode *mList;								// List of nodes
	struct GNode *mReaderPos;							// Current Reader Position
	int mCount;											// Count of items
	
	////////////////////////////////////////////////
	void ClearObject(void);
	
	////////////////////////////////////////////////
	public:
	MStringStringMap(bool create=false);
	~MStringStringMap(void);
	bool Create(void);
	bool Destroy(void);
	bool Add(const char *key,const char *value);		// add a value for a given key
	bool Delete(const char *key);						// delete a key
	const char *GetValue(const char *key);				// get value for key
	int GetCount(void);									// Get count of items
	bool Print(void);									// Print out the contents of map
	
	// Reader Code
	bool ReadReset(void);								// Reset the reader
	bool Read(void);									// Read the next maping
	const char *ReadGetKey(void);						// Get Key for reader
	const char *ReadGetValue(void);						// Get Value for reader
	};

#endif // MStringStringMap_h

