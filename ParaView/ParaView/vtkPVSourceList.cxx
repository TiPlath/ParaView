/*=========================================================================

  Program:   ParaView
  Module:    vtkPVSourceList.cxx
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
#include "vtkPVSourceList.h"

#include "vtkCollectionIterator.h"
#include "vtkKWEntry.h"
#include "vtkKWMenu.h"
#include "vtkKWTkUtilities.h"
#include "vtkObjectFactory.h"
#include "vtkPVApplication.h"
#include "vtkPVData.h"
#include "vtkPVRenderView.h"
#include "vtkPVSource.h"
#include "vtkPVSourceCollection.h"
#include "vtkPVWindow.h"
#include "vtkString.h"

vtkStandardNewMacro(vtkPVSourceList);
vtkCxxRevisionMacro(vtkPVSourceList, "1.31");

vtkCxxSetObjectMacro(vtkPVSourceList,Sources,vtkPVSourceCollection);

/* 
 * This part was generated by ImageConvert from image:
 *    eye_open.png (zlib, base64)
 */
#define image_eye_open_width         18
#define image_eye_open_height        11
#define image_eye_open_pixel_size    4
#define image_eye_open_buffer_length 236

static unsigned char image_eye_open[] = 
  "eNqVkgENxCAMRbGAhVnAAhawgAUszAIWZgELs1ALWNhxySNpFnrkfvKzdmv/Pi3ObREGIz"
  "zcf8iDbfBZsA/WjWYaFDQytd+ewlOIb/TyQuPkWzK8FeLK+4q/tNAI5IXYUzfPFPEyceHR"
  "U//WbeQdzakzvek5POr/grbWCa/5Cn1V7VFU7lSPPnvGSyOPxF55rcauutqJGLtqypsFz8"
  "zFuDu3setfONQ9jrviDwWJR9s=";

/* 
 * This part was generated by ImageConvert from image:
 *    eye_gray.png (zlib, base64)
 */
#define image_eye_gray_width         18
#define image_eye_gray_height        11
#define image_eye_gray_pixel_size    4
#define image_eye_gray_buffer_length 244

static unsigned char image_eye_gray[] = 
  "eNqFklERxCAMRGsBC7WABSxgAQtYOAtYOAt88lsLsYCFHjfzmMl0SPnYadJutkuW1trR3u"
  "EHAjjbnq+RBurAvUAfKBvNOCBoJLj/mcxTqC/00kLjw7doeMvUhfcFf3Gh4ekztYM3zxTw"
  "Mue+eHTwn7qVvqM5daY3vYdb/V/Q1jr+sV9hrqgcRfWHmtFnT3ip9IHaKa/FyKqrTMTIqi"
  "pvVu6OnYtxdy4j6zec6h6HHf8H2ZoMbw==";

/* 
 * This part was generated by ImageConvert from image:
 *    eye_novis.png (zlib, base64)
 */
#define image_eye_novis_width         7
#define image_eye_novis_height        7
#define image_eye_novis_pixel_size    4
#define image_eye_novis_buffer_length 80

static unsigned char image_eye_novis[] = 
  "eNr7//8/AxAkAPEOIP4KpRP+I8TnA7E7EHNB6flI6t1B6mAYKg8zhwtNjgvJfFz6cNr3H4"
  "87AaNaOEo=";

#if 0
/* 
 * This part was generated by ImageConvert from image:
 *    eye_empty.png (zlib, base64)
 */
#define image_eye_empty_width         18
#define image_eye_empty_height        11
#define image_eye_empty_pixel_size    4
#define image_eye_empty_buffer_length 28

static unsigned char image_eye_empty[] = 
  "eNr7//8/w/9RPIpHMQoGAMmpT80=";
#endif

// This constant must be adjusted to be the largest width of the icons
// to be used on the left size of a label.

#define image_icon_max_width         image_eye_open_width

//----------------------------------------------------------------------------
vtkPVSourceList::vtkPVSourceList()
{
  this->Sources = NULL;

  this->LastY = 0;
  this->CurrentY = 0;
}

//----------------------------------------------------------------------------
vtkPVSourceList::~vtkPVSourceList()
{
  this->SetSources(0);
}

//----------------------------------------------------------------------------
void vtkPVSourceList::ChildCreate()
{ 
  // Set up bindings for the canvas (cut and paste).

  this->Script("bind %s <Enter> {focus %s}", this->Canvas->GetWidgetName(), 
               this->Canvas->GetWidgetName());

  // Bitmaps used to show which parts of the tree can be opened.

  /*
  // Unique names ?
  char str[1024];
  char str2[1024];

  sprintf(str, "{%s \n%s \n%s \n%s}",
          "#define open_width 9\n#define open_height 9",
          "static unsigned char closed_bits[] = {",
          "0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x7d, 0x01, 0x01, 0x01,",
          "0x01, 0x01, 0x01, 0x01, 0xff, 0x01};");
  sprintf(str2, "{%s \n%s \n%s \n%s}",
          "#define solid_width 9\n#define solid_height 9",
          "static unsigned char closed_bits[] = {",
          "0xff, 0x01, 0xff, 0x01, 0xff, 0x01, 0xff, 0x01, 0xff, 0x01, 0xff, 0x01,",
          "0xff, 0x01, 0xff, 0x01, 0xff, 0x01};");
  this->Script("image create bitmap openbm -data %s -maskdata %s -foreground black -background white", str, str2);
  
  sprintf(str, "{%s \n%s \n%s \n%s}",
          "#define closed_width 9\n#define closed_height 9",
          "static unsigned char closed_bits[] = {",
          "0xff, 0x01, 0x01, 0x01, 0x11, 0x01, 0x11, 0x01, 0x7d, 0x01, 0x11, 0x01,",
          "0x11, 0x01, 0x01, 0x01, 0xff, 0x01};");
  this->Script("image create bitmap closedbm -data %s -maskdata %s -foreground black -background white", str, str2);
  */

  // Lets try eyes

  /*
  sprintf(str, "{%s \n%s \n%s \n%s}",
          "#define open_eye_width 13\n#define open_eye_height 9",
          "static unsigned char open_eye_bits[] = {",
          "0x48, 0x02, 0xf2, 0x09, 0xec, 0x06, 0x12, 0x09, 0x51, 0x11, 0x12, 0x09,",
          "0xec, 0x06, 0xf0, 0x01, 0x00, 0x00};");
  this->Script("image create bitmap visonbm -data %s -foreground black -background white", str, str2);
  this->Script("image create bitmap vispartbm -data %s -foreground gray80 -background white", str, str2);
  sprintf(str, "{%s \n%s \n%s \n%s}",
          "#define closed_eye_width 13\n#define closed_eye_height 9",
          "static unsigned char open_eye_bits[] = {",
          "0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x02, 0x08",
          "0x0c, 0x06, 0xf2, 0x09, 0x48, 0x02};");
  this->Script("image create bitmap visoffbm -data %s -foreground black -background white", str, str2);  
  */

  // Create non-unique photos name (use the widget name as prefix) since
  // each photo will be blended to the current canvas background color

  ostrstream vison;
  vison << this->GetWidgetName() << ".visonimg" << ends;
  if (!vtkKWTkUtilities::UpdatePhoto(this->Application->GetMainInterp(),
                                     vison.str(), 
                                     image_eye_open, 
                                     image_eye_open_width, 
                                     image_eye_open_height, 
                                     image_eye_open_pixel_size,
                                     image_eye_open_buffer_length,
                                     this->Canvas->GetWidgetName()))
    {
    vtkWarningMacro(<< "Error creating photo (eye open)");
    }
  vison.rdbuf()->freeze(0);

  ostrstream visoff;
  visoff << this->GetWidgetName() << ".visoffimg" << ends;
  if (!vtkKWTkUtilities::UpdatePhoto(this->Application->GetMainInterp(),
                                     visoff.str(), 
                                     image_eye_gray, 
                                     image_eye_gray_width, 
                                     image_eye_gray_height, 
                                     image_eye_gray_pixel_size,
                                     image_eye_gray_buffer_length,
                                     this->Canvas->GetWidgetName()))
    {
    vtkWarningMacro(<< "Error creating photo (eye gray)");
    }
  visoff.rdbuf()->freeze(0);

  ostrstream visnovis;
  visnovis << this->GetWidgetName() << ".visnovisimg" << ends;
  if (!vtkKWTkUtilities::UpdatePhoto(this->Application->GetMainInterp(),
                                     visnovis.str(), 
                                     image_eye_novis, 
                                     image_eye_novis_width, 
                                     image_eye_novis_height, 
                                     image_eye_novis_pixel_size,
                                     image_eye_novis_buffer_length,
                                     this->Canvas->GetWidgetName()))
    {
    vtkWarningMacro(<< "Error creating photo (eye novis)");
    }
  visnovis.rdbuf()->freeze(0);
}

//----------------------------------------------------------------------------
void vtkPVSourceList::Pick(int compIdx)
{
  vtkPVSource *comp;

  comp = vtkPVSource::SafeDownCast(
    this->Sources->GetItemAsObject(compIdx));
  // I believe just setting the current source shows its properties.
  if (comp)
    {
    comp->GetPVWindow()->SetCurrentPVSourceCallback(comp);
    }
}

//----------------------------------------------------------------------------
void vtkPVSourceList::ToggleVisibility(int compIdx, char* id, int )
{
  vtkPVSource *comp;

  comp = vtkPVSource::SafeDownCast(
    this->Sources->GetItemAsObject(compIdx));
  if (comp && !comp->GetHideDisplayPage())
    {
    // Toggle visibility
    if (comp->GetPVOutput()->GetVisibility())
      {
      comp->GetPVOutput()->VisibilityOff();
      }
    else
      {
      comp->GetPVOutput()->VisibilityOn();
      }
    
    this->UpdateVisibility(comp, id);

    vtkPVRenderView* renderView 
      = vtkPVRenderView::SafeDownCast(comp->GetView());
    if ( renderView )
      {
      renderView->EventuallyRender();
      }
    }
}


//----------------------------------------------------------------------------
void vtkPVSourceList::EditColor(int )
{
}

//----------------------------------------------------------------------------
void vtkPVSourceList::ChildUpdate(vtkPVSource* current)
{
  vtkPVSource *comp;
  int y, in;
  
  vtkPVApplication* app = vtkPVApplication::SafeDownCast(this->Application);
  vtkPVWindow* window = app->GetMainWindow();
  vtkPVSourceCollection* col = window->GetSourceList("Sources");
  
  this->SetSources(col);
  if (this->Sources == NULL)
    {
    vtkErrorMacro("Sources is NULL");
    return;
    }
 
  int start = 30;
  y = start;
  in = 10;
  vtkCollectionIterator* it = col->NewIterator();
  it->InitTraversal();
  int lasty = 0, thisy = 0;
  while ( !it->IsDoneWithTraversal() )
    {
    comp = vtkPVSource::SafeDownCast(it->GetObject());
    if ( current == comp )
      {
      lasty = y;
      }
    y = this->UpdateSource(comp, y, in, (current == comp));
    if ( current == comp )
      {
      thisy = y;
      }
    it->GoToNextItem();
    }
  it->Delete();
  if ( thisy == 0 )
    {
    lasty = y;
    y = this->UpdateSource(current, y, in, 1);
    thisy = y;
    }

  this->StartY = start;
  this->LastY = lasty;
  this->CurrentY = thisy;
}

//----------------------------------------------------------------------------
void vtkPVSourceList::PostChildUpdate()
{
  int bbox[4];
  this->CalculateBBox(this->Canvas, "all", bbox);
  if ( this->LastY < this->CurrentY )
    {
    int midy = this->LastY - this->StartY - ( this->CurrentY - this->LastY )/2;
    if ( midy < 0 )
      {
      midy = 0;
      }
    
    this->Script("%s yview moveto %f",
                 this->Canvas->GetWidgetName(), 
                 (static_cast<float>(midy) / static_cast<float>(bbox[3])));
    
    }
}

//----------------------------------------------------------------------------
void vtkPVSourceList::UpdateVisibility(vtkPVSource *comp,
                                      const char *id)
{
  // Draw the icon indicating visibility.

  if (comp->GetHideDisplayPage())
    {
    this->Script("%s itemconfigure %s -image %s.visnovisimg",
                 this->Canvas->GetWidgetName(), id, 
                 this->GetWidgetName());
    }
  else
    {
    if (comp->GetPVOutput() == NULL)
      {
      this->Script("%s itemconfigure %s -image %s.visonimg",
                   this->Canvas->GetWidgetName(), id, 
                   this->GetWidgetName());
      }
    else
      {
      switch (comp->GetPVOutput()->GetVisibility())
        {
        case 0:
          this->Script("%s itemconfigure %s -image %s.visoffimg",
                       this->Canvas->GetWidgetName(), id, 
                       this->GetWidgetName());
          break;
        case 1:
          this->Script("%s itemconfigure %s -image %s.visonimg",
                       this->Canvas->GetWidgetName(), id, 
                       this->GetWidgetName());
          break;
        }
      }
    }
}

//----------------------------------------------------------------------------
int vtkPVSourceList::UpdateSource(vtkPVSource *comp, int y, int in,int current)
{
  int compIdx, x, yNext; 
  static const char *font = "-adobe-helvetica-medium-r-normal-*-14-100-100-100-p-76-iso8859-1";
  char *result = 0;
  int bbox[4];
  char *tmp;

  compIdx = this->Sources->IsItemPresent(comp) - 1;

  yNext = y + 17;

  // Create an image on the left of the label (updated by UpdateVisibility())
  // Bind ToggleVisibility.

  this->Script("%s create image %d %d", this->Canvas->GetWidgetName(), 
               in + image_icon_max_width / 2, y);
  if (this->Application->GetMainInterp()->result)
    {
    char *tmp = 
      vtkString::Duplicate(this->Application->GetMainInterp()->result);
    this->Script("%s bind %s <ButtonPress-1> {%s ToggleVisibility %d %s 1}",
                 this->Canvas->GetWidgetName(), tmp,
                 this->GetTclName(), compIdx, tmp);
    this->Script("%s bind %s <ButtonPress-3> {%s ToggleVisibility %d %s 3}",
                 this->Canvas->GetWidgetName(), tmp,
                 this->GetTclName(), compIdx, tmp);
    this->UpdateVisibility(comp, tmp);
    delete [] tmp;
    }

  // Add some space between the icon and the label

  x = in + image_icon_max_width + 4;

  // Draw the name of the assembly.
  char *text = this->GetTextRepresentation(comp);
  this->Script("%s create text %d %d -text {%s} -font %s -anchor w -tags x",
               this->Canvas->GetWidgetName(), x, y, text, font);
  delete [] text;

  // Make the name hot for picking.
  result = this->Application->GetMainInterp()->result;
  tmp = new char[strlen(result)+1];
  strcpy(tmp,result);
  if (this->CreateSelectionBindings)
    {
    this->Script("%s bind %s <ButtonPress-1> {%s Pick %d}",
                 this->Canvas->GetWidgetName(), tmp,
                 this->GetTclName(), compIdx);
    this->Script("%s bind %s <ButtonPress-3> "
                 "{%s DisplayModulePopupMenu %s %%X %%Y }",
                 this->Canvas->GetWidgetName(), tmp,
                 this->GetTclName(), comp->GetTclName());
    }
  
  // Get the bounding box for the name. We may need to highlight it.
  this->Script( "%s bbox %s",this->Canvas->GetWidgetName(), tmp);
  delete [] tmp;
  tmp = NULL;
  result = this->Application->GetMainInterp()->result;
  sscanf(result, "%d %d %d %d", bbox, bbox+1, bbox+2, bbox+3);
  
  // Highlight the name based on the picked status. 
  //if (comp->GetPVWindow()->GetCurrentPVSource() == comp)
  if (current)
    {
    this->Script("%s create rectangle %d %d %d %d -fill yellow -outline {}",
                 this->Canvas->GetWidgetName(), 
                 bbox[0], bbox[1], bbox[2], bbox[3]);
    tmp = vtkString::Duplicate(this->Application->GetMainInterp()->result);
    this->Script( "%s lower %s",this->Canvas->GetWidgetName(), tmp);
    delete [] tmp;
    tmp = NULL;
    }

  return yNext;
}

//----------------------------------------------------------------------------
void vtkPVSourceList::PrepareForDelete()
{
  this->SetSources(0);
}

//----------------------------------------------------------------------------
void vtkPVSourceList::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
}

