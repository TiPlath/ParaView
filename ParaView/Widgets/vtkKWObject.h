/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkKWObject.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2000-2001 Kitware Inc. 469 Clifton Corporate Parkway,
Clifton Park, NY, 12065, USA.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * Neither the name of Kitware nor the names of any contributors may be used
   to endorse or promote products derived from this software without specific 
   prior written permission.

 * Modified source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
// .NAME vtkKWObject - superclass that supports basic Tcl functionality
// .SECTION Description
// vtkKWObject is the superclass for most application classes.
// It is a direct subclass of vtkObject but adds functionality for 
// invoking Tcl scripts, obtains results from those scripts, and
// obtaining a Tcl name for an instance. This class requires a 
// vtkKWApplicaiton in order to work (as do all classes).

// .SECTION See Also
// vtkKWApplication

#ifndef __vtkKWObject_h
#define __vtkKWObject_h

class vtkKWApplication;
#include "vtkObject.h"
#include "vtkKWSerializer.h"

// var args
#ifndef _WIN32
#include <unistd.h>
#endif
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "tcl.h"

class VTK_EXPORT vtkKWObject : public vtkObject
{
public:
  static vtkKWObject* New();
  vtkTypeMacro(vtkKWObject,vtkObject);

  // Description:
  // Get the name of the tcl object this instance represents.
  const char *GetTclName();

  // Description:
  // Get the application instance for this class.
  vtkGetObjectMacro(Application,vtkKWApplication);
  virtual void SetApplication (vtkKWApplication* arg);

  // Description:
  // Convienience methods to get results of Tcl commands.
  static int GetIntegerResult(vtkKWApplication *);
  static float GetFloatResult(vtkKWApplication *);

  // Description:
  // Chaining method to serialize an object and its superclasses.
  void Serialize(ostream& os, vtkIndent indent);
  virtual void SerializeRevision(ostream& os, vtkIndent indent);
  void Serialize(istream& is);
  virtual void SerializeSelf(ostream& /*os*/, vtkIndent /*indent*/) {};
  virtual void SerializeToken(istream& is, const char token[1024]);
  virtual const char *GetVersion(const char *);
  virtual void AddVersion(const char *cname, const char *version);
  void ExtractRevision(ostream& os,const char *revIn);
  int CompareVersions(const char *v1, const char *v2);

//BTX
  // Description:
  // A convienience method to invoke some tcl script code and
  // perform arguement substitution.
  void Script(const char *EventString, ...);

private:
  char *TclName;
  
protected:
  vtkKWObject();
  ~vtkKWObject();
  vtkKWObject(const vtkKWObject&) {};
  void operator=(const vtkKWObject&) {};

  vtkKWApplication *Application;

  char **Versions;
  int   NumberOfVersions;
  int   VersionsLoaded;
  
  // this instance variable holds the command functions for this class.
  int (*CommandFunction)(ClientData, Tcl_Interp *, int, char *[]);
//ETX
};

#endif
