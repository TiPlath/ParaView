/*****************************************************************************
*
* Copyright (c) 2000 - 2007, The Regents of the University of California
* Produced at the Lawrence Livermore National Laboratory
* All rights reserved.
*
* This file is part of VisIt. For details, see http://www.llnl.gov/visit/. The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or materials provided with the distribution.
*  - Neither the name of the UC/LLNL nor  the names of its contributors may be
*    used to  endorse or  promote products derived from  this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED.  IN  NO  EVENT  SHALL  THE  REGENTS  OF  THE  UNIVERSITY OF
* CALIFORNIA, THE U.S.  DEPARTMENT  OF  ENERGY OR CONTRIBUTORS BE  LIABLE  FOR
* ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

#include <ColorTableAttributes.h>
#include <DataNode.h>
#include <ColorControlPoint.h>
#include <map>
#include <ColorControlPointList.h>
#include <snprintf.h>

namespace pointsprite {
// Type map format string
const char *ColorTableAttributes::TypeMapFormatString = "s*a*ss";

// ****************************************************************************
// Method: ColorTableAttributes::ColorTableAttributes
//
// Purpose:
//   Constructor for the ColorTableAttributes class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

ColorTableAttributes::ColorTableAttributes() :
    AttributeSubject(ColorTableAttributes::TypeMapFormatString)
{
    activeContinuous = "hot";
    activeDiscrete = "levels";
}

// ****************************************************************************
// Method: ColorTableAttributes::ColorTableAttributes
//
// Purpose:
//   Copy constructor for the ColorTableAttributes class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

ColorTableAttributes::ColorTableAttributes(const ColorTableAttributes &obj) :
    AttributeSubject(ColorTableAttributes::TypeMapFormatString)
{
    AttributeGroupVector::const_iterator pos;

    names = obj.names;
    // *** Copy the colorTables field ***
    // Delete the AttributeGroup objects and clear the vector.
    for(pos = colorTables.begin(); pos != colorTables.end(); ++pos)
        delete *pos;
    colorTables.clear();
    if(obj.colorTables.size() > 0)
        colorTables.reserve(obj.colorTables.size());
    // Duplicate the colorTables from obj.
    for(pos = obj.colorTables.begin(); pos != obj.colorTables.end(); ++pos)
    {
        ColorControlPointList *oldColorControlPointList = (ColorControlPointList *)(*pos);
        ColorControlPointList *newColorControlPointList = new ColorControlPointList(*oldColorControlPointList);
        colorTables.push_back(newColorControlPointList);
    }

    activeContinuous = obj.activeContinuous;
    activeDiscrete = obj.activeDiscrete;

    SelectAll();
}

// ****************************************************************************
// Method: ColorTableAttributes::~ColorTableAttributes
//
// Purpose:
//   Destructor for the ColorTableAttributes class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

ColorTableAttributes::~ColorTableAttributes()
{
    AttributeGroupVector::iterator pos;

    // Destroy the colorTables field.
    for(pos = colorTables.begin(); pos != colorTables.end(); ++pos)
        delete *pos;
}

// ****************************************************************************
// Method: ColorTableAttributes::operator =
//
// Purpose:
//   Assignment operator for the ColorTableAttributes class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

ColorTableAttributes&
ColorTableAttributes::operator = (const ColorTableAttributes &obj)
{
    if (this == &obj) return *this;
    AttributeGroupVector::const_iterator pos;

    names = obj.names;
    // *** Copy the colorTables field ***
    // Delete the AttributeGroup objects and clear the vector.
    for(pos = colorTables.begin(); pos != colorTables.end(); ++pos)
        delete *pos;
    colorTables.clear();
    if(obj.colorTables.size() > 0)
        colorTables.reserve(obj.colorTables.size());
    // Duplicate the colorTables from obj.
    for(pos = obj.colorTables.begin(); pos != obj.colorTables.end(); ++pos)
    {
        ColorControlPointList *oldColorControlPointList = (ColorControlPointList *)(*pos);
        ColorControlPointList *newColorControlPointList = new ColorControlPointList(*oldColorControlPointList);
        colorTables.push_back(newColorControlPointList);
    }

    activeContinuous = obj.activeContinuous;
    activeDiscrete = obj.activeDiscrete;

    SelectAll();
    return *this;
}

// ****************************************************************************
// Method: ColorTableAttributes::operator ==
//
// Purpose:
//   Comparison operator == for the ColorTableAttributes class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

bool
ColorTableAttributes::operator == (const ColorTableAttributes &obj) const
{
    unsigned int i;

    bool colorTables_equal = (obj.colorTables.size() == colorTables.size());
    for(i = 0; (i < colorTables.size()) && colorTables_equal; ++i)
    {
        // Make references to ColorControlPointList from AttributeGroup *.
        const ColorControlPointList &colorTables1 = *((const ColorControlPointList *)(colorTables[i]));
        const ColorControlPointList &colorTables2 = *((const ColorControlPointList *)(obj.colorTables[i]));
        colorTables_equal = (colorTables1 == colorTables2);
    }

    // Create the return value
    return ((names == obj.names) &&
            colorTables_equal &&
            (activeContinuous == obj.activeContinuous) &&
            (activeDiscrete == obj.activeDiscrete));
}

// ****************************************************************************
// Method: ColorTableAttributes::operator !=
//
// Purpose:
//   Comparison operator != for the ColorTableAttributes class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

bool
ColorTableAttributes::operator != (const ColorTableAttributes &obj) const
{
    return !(this->operator == (obj));
}

// ****************************************************************************
// Method: ColorTableAttributes::TypeName
//
// Purpose:
//   Type name method for the ColorTableAttributes class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

const std::string
ColorTableAttributes::TypeName() const
{
    return "ColorTableAttributes";
}

// ****************************************************************************
// Method: ColorTableAttributes::CopyAttributes
//
// Purpose:
//   CopyAttributes method for the ColorTableAttributes class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

bool
ColorTableAttributes::CopyAttributes(const AttributeGroup *atts)
{
    if(TypeName() != atts->TypeName())
        return false;

    // Call assignment operator.
    const ColorTableAttributes *tmp = (const ColorTableAttributes *)atts;
    *this = *tmp;

    return true;
}

// ****************************************************************************
// Method: ColorTableAttributes::CreateCompatible
//
// Purpose:
//   CreateCompatible method for the ColorTableAttributes class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

AttributeSubject *
ColorTableAttributes::CreateCompatible(const std::string &tname) const
{
    AttributeSubject *retval = 0;
    if(TypeName() == tname)
        retval = new ColorTableAttributes(*this);
    // Other cases could go here too.

    return retval;
}

// ****************************************************************************
// Method: ColorTableAttributes::NewInstance
//
// Purpose:
//   NewInstance method for the ColorTableAttributes class.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

AttributeSubject *
ColorTableAttributes::NewInstance(bool copy) const
{
    AttributeSubject *retval = 0;
    if(copy)
        retval = new ColorTableAttributes(*this);
    else
        retval = new ColorTableAttributes;

    return retval;
}

// ****************************************************************************
// Method: ColorTableAttributes::SelectAll
//
// Purpose:
//   Selects all attributes.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

void
ColorTableAttributes::SelectAll()
{
    Select(0, (void *)&names);
    Select(1, (void *)&colorTables);
    Select(2, (void *)&activeContinuous);
    Select(3, (void *)&activeDiscrete);
}

// ****************************************************************************
// Method: ColorTableAttributes::CreateSubAttributeGroup
//
// Purpose:
//   This class contains the list of colortables.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

AttributeGroup *
ColorTableAttributes::CreateSubAttributeGroup(int)
{
    return new ColorControlPointList;
}

///////////////////////////////////////////////////////////////////////////////
// Persistence methods
///////////////////////////////////////////////////////////////////////////////

// ****************************************************************************
// Method: ColorTableAttributes::CreateNode
//
// Purpose:
//   This method creates a DataNode representation of the object so it can be saved to a config file.
//
// Note:       Autogenerated by classwriter.
//
// Programmer: classwriter
// Creation:   Mon Jun 11 10:41:36 PDT 2001
//
// Modifications:
//   Brad Whitlock, Mon Jun 18 22:03:23 PST 2001
//   Custom coded this method since classwriter's resulting output format
//   was ridiculous.
//
//   Brad Whitlock, Wed Nov 20 12:24:43 PDT 2002
//   I made it work with discrete colortables.
//
//   Brad Whitlock, Tue May 20 10:21:14 PDT 2003
//   I made it saved out only what needs to be saved out.
//
//   Brad Whitlock, Mon Jul 7 16:51:05 PST 2003
//   I prevented it from saving out colortables that are external.
//
//   Brad Whitlock, Wed Dec 17 12:21:24 PDT 2003
//   I added another bool argument.
//
//   Brad Whitlock, Tue Mar 13 10:40:04 PDT 2007
//   Updated due to code generator changes.
//
// ****************************************************************************

bool
ColorTableAttributes::CreateNode(DataNode *parentNode, bool, bool)
{
    if(parentNode == 0)
        return true;

    // Create a node for ColorTableAttributes.
    DataNode *node = new DataNode("ColorTableAttributes");
    node->AddNode(new DataNode("activeContinuous", activeContinuous));
    node->AddNode(new DataNode("activeDiscrete", activeDiscrete));

    // Add each color table specially.
    char tmp[100];
    ColorControlPointList defaultObject;
    int index = 0;
    for(unsigned int i = 0; i < colorTables.size(); ++i)
    {
        const ColorControlPointList &ccpl = GetColorTables(i);
        if(!ccpl.GetExternalFlag())
        {
            SNPRINTF(tmp, 100, "table%02d", index++);
            DataNode *ctNode = new DataNode(tmp);
            // Add the color table attributes to the ctNode.
            ctNode->AddNode(new DataNode("ctName", names[i]));
            if(!ccpl.FieldsEqual(1, &defaultObject))
                ctNode->AddNode(new DataNode("equal", ccpl.GetEqualSpacingFlag()));
            if(!ccpl.FieldsEqual(2, &defaultObject))
                ctNode->AddNode(new DataNode("smooth", ccpl.GetSmoothingFlag()));
            if(!ccpl.FieldsEqual(3, &defaultObject))
                ctNode->AddNode(new DataNode("discrete", ccpl.GetDiscreteFlag()));

            // Add the control points to the vector that we'll save out.
            floatVector fvec;
            for(int j = 0; j < ccpl.GetNumControlPoints(); ++j)
            {
                const ColorControlPoint &cp = ccpl.operator[](j);
                fvec.push_back(cp.GetPosition());
                fvec.push_back(float(cp.GetColors()[0]));
                fvec.push_back(float(cp.GetColors()[1]));
                fvec.push_back(float(cp.GetColors()[2]));
            }
            ctNode->AddNode(new DataNode("controlPts", fvec));
            node->AddNode(ctNode);
        }
    }

    node->AddNode(new DataNode("Ntables", index));

    // Add the node to the parent node.
    parentNode->AddNode(node);

    return true;
}
// ****************************************************************************
// Method: ColorTableAttributes::SetFromNode
//
// Purpose:
//   This method sets attributes in this object from values in a DataNode representation of the object.
//
// Note:       Autogenerated by classwriter.
//
// Programmer: classwriter
// Creation:   Mon Jun 11 10:41:36 PDT 2001
//
// Modifications:
//   Brad Whitlock, Mon Jun 18 23:43:59 PST 2001
//   I rewrote it so it matches the format that is written in CreateNode.
//
//   Brad Whitlock, Wed Nov 20 12:26:24 PDT 2002
//   I made it work with discrete color tables.
//
// ****************************************************************************

void
ColorTableAttributes::SetFromNode(DataNode *parentNode)
{
    if(parentNode == 0)
        return;

    DataNode *searchNode = parentNode->GetNode("ColorTableAttributes");
    if(searchNode == 0)
        return;

    // Look for the number of color tables.
    DataNode *node = 0;
    if((node = searchNode->GetNode("Ntables")) != 0)
    {
        char tmp[100];
        int  ntables = node->AsInt();

        // Look for ntables color table nodes.
        for(int i = 0; i < ntables; ++i)
        {
            SNPRINTF(tmp, 100, "table%02d", i);
            if((node = searchNode->GetNode(tmp)) != 0)
            {
                DataNode *nameNode = node->GetNode("ctName");
                DataNode *pointNode = node->GetNode("controlPts");

                // If we have the name node and the pointNode, we can add a
                // color table.
                if(nameNode && pointNode)
                {
                    ColorControlPointList ccpl;

                    // Try and set the equal flag.
                    DataNode *tmpNode;
                    if((tmpNode = node->GetNode("equal")) != 0)
                        ccpl.SetEqualSpacingFlag(tmpNode->AsBool());
                    // Try and set the smooth flag.
                    if((tmpNode = node->GetNode("smooth")) != 0)
                        ccpl.SetSmoothingFlag(tmpNode->AsBool());
                    if((tmpNode = node->GetNode("discrete")) != 0)
                        ccpl.SetDiscreteFlag(tmpNode->AsBool());

                    // Set the color control points.
                    floatVector fvec = pointNode->AsFloatVector();
                    for(unsigned int j = 0; j < fvec.size() / 4; ++j)
                    {
                        // Create a control point based on the values
                        // in the float vector.
                        int index = j * 4;
                        ColorControlPoint cpt(fvec[index],
                                              (unsigned char)(fvec[index+1]),
                                              (unsigned char)(fvec[index+2]),
                                              (unsigned char)(fvec[index+3]),
                                              255);
                        ccpl.AddControlPoints(cpt);
                    }

                    // If the color table is already in the list, remove it.
                    // Then add the new color table to the list.
                    RemoveColorTable(nameNode->AsString());
                    AddColorTable(nameNode->AsString(), ccpl);
                }
            }
        } // end for i
    }

    if((node = searchNode->GetNode("activeContinuous")) != 0)
        SetActiveContinuous(node->AsString());

    if((node = searchNode->GetNode("activeDiscrete")) != 0)
        SetActiveDiscrete(node->AsString());

    // For older version compatibility...
    if((node = searchNode->GetNode("activeColorTable")) != 0)
        SetActiveContinuous(node->AsString());
}
///////////////////////////////////////////////////////////////////////////////
// Set property methods
///////////////////////////////////////////////////////////////////////////////

void
ColorTableAttributes::SetNames(const stringVector &names_)
{
    names = names_;
    Select(0, (void *)&names);
}

void
ColorTableAttributes::SetActiveContinuous(const std::string &activeContinuous_)
{
    activeContinuous = activeContinuous_;
    Select(2, (void *)&activeContinuous);
}

void
ColorTableAttributes::SetActiveDiscrete(const std::string &activeDiscrete_)
{
    activeDiscrete = activeDiscrete_;
    Select(3, (void *)&activeDiscrete);
}

///////////////////////////////////////////////////////////////////////////////
// Get property methods
///////////////////////////////////////////////////////////////////////////////

const stringVector &
ColorTableAttributes::GetNames() const
{
    return names;
}

stringVector &
ColorTableAttributes::GetNames()
{
    return names;
}

const AttributeGroupVector &
ColorTableAttributes::GetColorTables() const
{
    return colorTables;
}

AttributeGroupVector &
ColorTableAttributes::GetColorTables()
{
    return colorTables;
}

const std::string &
ColorTableAttributes::GetActiveContinuous() const
{
    return activeContinuous;
}

std::string &
ColorTableAttributes::GetActiveContinuous()
{
    return activeContinuous;
}

const std::string &
ColorTableAttributes::GetActiveDiscrete() const
{
    return activeDiscrete;
}

std::string &
ColorTableAttributes::GetActiveDiscrete()
{
    return activeDiscrete;
}

///////////////////////////////////////////////////////////////////////////////
// Select property methods
///////////////////////////////////////////////////////////////////////////////

void
ColorTableAttributes::SelectNames()
{
    Select(0, (void *)&names);
}

void
ColorTableAttributes::SelectColorTables()
{
    Select(1, (void *)&colorTables);
}

void
ColorTableAttributes::SelectActiveContinuous()
{
    Select(2, (void *)&activeContinuous);
}

void
ColorTableAttributes::SelectActiveDiscrete()
{
    Select(3, (void *)&activeDiscrete);
}

///////////////////////////////////////////////////////////////////////////////
// AttributeGroupVector convenience methods.
///////////////////////////////////////////////////////////////////////////////

// ****************************************************************************
// Method: ColorTableAttributes::AddColorTables
//
// Purpose:
//   This class contains the list of colortables.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

void
ColorTableAttributes::AddColorTables(const ColorControlPointList &obj)
{
    ColorControlPointList *newColorControlPointList = new ColorControlPointList(obj);
    colorTables.push_back(newColorControlPointList);

    // Indicate that things have changed by selecting it.
    Select(1, (void *)&colorTables);
}

// ****************************************************************************
// Method: ColorTableAttributes::ClearColorTables
//
// Purpose:
//   This class contains the list of colortables.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

void
ColorTableAttributes::ClearColorTables()
{
    AttributeGroupVector::iterator pos;

    for(pos = colorTables.begin(); pos != colorTables.end(); ++pos)
        delete *pos;
    colorTables.clear();

    // Indicate that things have changed by selecting the list.
    Select(1, (void *)&colorTables);
}

// ****************************************************************************
// Method: ColorTableAttributes::RemoveColorTables
//
// Purpose:
//   This class contains the list of colortables.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

void
ColorTableAttributes::RemoveColorTables(int index)
{
    AttributeGroupVector::iterator pos = colorTables.begin();

    // Iterate through the vector "index" times.
    for(int i = 0; i < index; ++i)
        ++pos;

    // If pos is still a valid iterator, remove that element.
    if(pos != colorTables.end())
    {
        delete *pos;
        colorTables.erase(pos);
    }

    // Indicate that things have changed by selecting the list.
    Select(1, (void *)&colorTables);
}

// ****************************************************************************
// Method: ColorTableAttributes::GetNumColorTables
//
// Purpose:
//   This class contains the list of colortables.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

int
ColorTableAttributes::GetNumColorTables() const
{
    return static_cast<int>(colorTables.size());
}

// ****************************************************************************
// Method: ColorTableAttributes::GetColorTables
//
// Purpose:
//   This class contains the list of colortables.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

ColorControlPointList &
ColorTableAttributes::GetColorTables(int i)
{
    return *((ColorControlPointList *)colorTables[i]);
}

// ****************************************************************************
// Method: ColorTableAttributes::GetColorTables
//
// Purpose:
//   This class contains the list of colortables.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

const ColorControlPointList &
ColorTableAttributes::GetColorTables(int i) const
{
    return *((ColorControlPointList *)colorTables[i]);
}

// ****************************************************************************
// Method: ColorTableAttributes::operator []
//
// Purpose:
//   This class contains the list of colortables.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

ColorControlPointList &
ColorTableAttributes::operator [] (int i)
{
    return *((ColorControlPointList *)colorTables[i]);
}

// ****************************************************************************
// Method: ColorTableAttributes::operator []
//
// Purpose:
//   This class contains the list of colortables.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

const ColorControlPointList &
ColorTableAttributes::operator [] (int i) const
{
    return *((ColorControlPointList *)colorTables[i]);
}

///////////////////////////////////////////////////////////////////////////////
// Keyframing methods
///////////////////////////////////////////////////////////////////////////////

// ****************************************************************************
// Method: ColorTableAttributes::GetFieldName
//
// Purpose:
//   This method returns the name of a field given its index.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

std::string
ColorTableAttributes::GetFieldName(int index) const
{
    switch (index)
    {
        case 0:  return "names";
        case 1:  return "colorTables";
        case 2:  return "activeContinuous";
        case 3:  return "activeDiscrete";
        default:  return "invalid index";
    }
}

// ****************************************************************************
// Method: ColorTableAttributes::GetFieldType
//
// Purpose:
//   This method returns the type of a field given its index.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

AttributeGroup::FieldType
ColorTableAttributes::GetFieldType(int index) const
{
    switch (index)
    {
        case 0:  return FieldType_stringVector;
        case 1:  return FieldType_attVector;
        case 2:  return FieldType_string;
        case 3:  return FieldType_string;
        default:  return FieldType_unknown;
    }
}

// ****************************************************************************
// Method: ColorTableAttributes::GetFieldTypeName
//
// Purpose:
//   This method returns the name of a field type given its index.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

std::string
ColorTableAttributes::GetFieldTypeName(int index) const
{
    switch (index)
    {
        case 0:  return "stringVector";
        case 1:  return "attVector";
        case 2:  return "string";
        case 3:  return "string";
        default:  return "invalid index";
    }
}

// ****************************************************************************
// Method: ColorTableAttributes::FieldsEqual
//
// Purpose:
//   This method compares two fields and return true if they are equal.
//
// Note:       Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Tue Mar 13 10:49:53 PDT 2007
//
// Modifications:
//
// ****************************************************************************

bool
ColorTableAttributes::FieldsEqual(int index_, const AttributeGroup *rhs) const
{
    unsigned int i;

    const ColorTableAttributes &obj = *((const ColorTableAttributes*)rhs);
    bool retval = false;
    switch (index_)
    {
    case 0:
        {  // new scope
        retval = (names == obj.names);
        }
        break;
    case 1:
        {  // new scope
        bool colorTables_equal = (obj.colorTables.size() == colorTables.size());
        for(i = 0; (i < colorTables.size()) && colorTables_equal; ++i)
        {
            // Make references to ColorControlPointList from AttributeGroup *.
            const ColorControlPointList &colorTables1 = *((const ColorControlPointList *)(colorTables[i]));
            const ColorControlPointList &colorTables2 = *((const ColorControlPointList *)(obj.colorTables[i]));
            colorTables_equal = (colorTables1 == colorTables2);
        }

        retval = colorTables_equal;
        }
        break;
    case 2:
        {  // new scope
        retval = (activeContinuous == obj.activeContinuous);
        }
        break;
    case 3:
        {  // new scope
        retval = (activeDiscrete == obj.activeDiscrete);
        }
        break;
    default: retval = false;
    }

    return retval;
}

///////////////////////////////////////////////////////////////////////////////
// User-defined methods.
///////////////////////////////////////////////////////////////////////////////

// ****************************************************************************
// Method: ColorTableAttributes::GetColorTableIndex
//
// Purpose:
//   Returns the index of the specified color table.
//
// Arguments:
//   name : The name of the color table that we want.
//
// Returns:    The index or -1 if the color table is not in the list.
//
// Note:
//
// Programmer: Brad Whitlock
// Creation:   Sat Jun 16 20:32:23 PST 2001
//
// Modifications:
//
// ****************************************************************************

int
ColorTableAttributes::GetColorTableIndex(const std::string &name) const
{
    int retval = -1;
    for(unsigned int i = 0; i < names.size(); ++i)
    {
        if(names[i] == name)
        {
            retval = i;
            break;
        }
    }

    return retval;
}

// ****************************************************************************
// Method: ColorTableAttributes::GetColorControlPoints
//
// Purpose:
//   Returns a pointer to the color control points for the specified color
//   table index.
//
// Arguments:
//   index : The index for which we want the color control points.
//
// Returns:    The color control points or NULL.
//
// Note:
//
// Programmer: Brad Whitlock
// Creation:   Sat Jun 16 20:33:22 PST 2001
//
// Modifications:
//
// ****************************************************************************

const ColorControlPointList *
ColorTableAttributes::GetColorControlPoints(int index) const
{
    if(index >= 0 && index < static_cast<int>(colorTables.size()))
        return ((ColorControlPointList *)colorTables[index]);
    else
        return 0;
}

// ****************************************************************************
// Method: ColorTableAttributes::GetColorControlPoints
//
// Purpose:
//   Returns a pointer to the color control points for the specified color
//   table index.
//
// Arguments:
//   name : The name of the color table for which we want the color control
//          points.
//
// Returns:    The color control points or NULL.
//
// Note:
//
// Programmer: Brad Whitlock
// Creation:   Sat Jun 16 20:33:22 PST 2001
//
// Modifications:
//
// ****************************************************************************

const ColorControlPointList *
ColorTableAttributes::GetColorControlPoints(const std::string &name) const
{
    int index = GetColorTableIndex(name);

    if(index >= 0 && index < static_cast<int>(colorTables.size()))
        return ((ColorControlPointList *)colorTables[index]);
    else
        return 0;
}

// ****************************************************************************
// Method: ColorTableAttributes::AddColorTable
//
// Purpose:
//   Adds a new color table to the list.
//
// Arguments:
//   name : The name of the new color table.
//   cpts : The color control points for the new color table.
//
// Programmer: Brad Whitlock
// Creation:   Sat Jun 16 20:35:43 PST 2001
//
// Modifications:
//   Brad Whitlock, Mon Nov 25 12:00:52 PDT 2002
//   I added code to sort the color table using a map.
//
//   Brad Whitlock, Mon Mar 13 17:14:55 PST 2006
//   Make sure that a pre-existing color table with the same name is removed
//   before adding the new color table.
//
// ****************************************************************************

void
ColorTableAttributes::AddColorTable(const std::string &name,
    const ColorControlPointList &cpts)
{
    // Remove the color table if it already exists in the list.
    int index = GetColorTableIndex(name);
    if(index != -1)
        RemoveColorTable(index);

    // Append the color table to the list.
    names.push_back(name);
    AddColorTables(cpts);

    // Store the name, colortable pairs into a map.
    std::map<std::string, AttributeGroup *> sortMap;
    unsigned int i;
    for(i = 0; i < names.size(); ++i)
        sortMap[names[i]] = colorTables[i];

    // Traverse the map, it will be sorted. Store the names and color table
    // pointer back into the old vectors.
    std::map<std::string, AttributeGroup *>::iterator pos;
    for(i = 0, pos = sortMap.begin(); pos != sortMap.end(); ++pos, ++i)
    {
        names[i] = pos->first;
        colorTables[i] = pos->second;
    }

    Select(0, (void *)&names);
}

// ****************************************************************************
// Method: ColorTableAttributes::RemoveColorTable
//
// Purpose:
//   Removes the named color table from the list.
//
// Arguments:
//   name : The name of the color table to remove.
//
// Programmer: Brad Whitlock
// Creation:   Sat Jun 16 20:36:30 PST 2001
//
// Modifications:
//
// ****************************************************************************

void
ColorTableAttributes::RemoveColorTable(const std::string &name)
{
    int index = GetColorTableIndex(name);
    RemoveColorTable(index);
}

// ****************************************************************************
// Method: ColorTableAttributes::RemoveColorTable
//
// Purpose:
//   Removes the color table at the specified list index.
//
// Arguments:
//   index : The index of the color table we want to remove.
//
// Programmer: Brad Whitlock
// Creation:   Sat Jun 16 20:37:03 PST 2001
//
// Modifications:
//   Brad Whitlock, Wed Nov 20 12:08:18 PDT 2002
//   Made it work with the new discrete color tables.
//
// ****************************************************************************

void
ColorTableAttributes::RemoveColorTable(int index)
{
    if(index >= 0 && index < static_cast<int>(names.size()))
    {
        // Determine if the color table is active.
        bool isActiveContinuous, isActiveDiscrete;
        isActiveContinuous = (names[index] == activeContinuous);
        isActiveDiscrete = (names[index] == activeDiscrete);

        // Iterate through the vector "index" times.
        stringVector::iterator pos = names.begin();
        for(int i = 0; i < index; ++i)
            ++pos;

        // If pos is still a valid iterator, remove that element.
        if(pos != names.end())
        {
            names.erase(pos);
        }

        // Indicate that things have changed by selecting the list.
        Select(0, (void *)&names);

        // erase the color table from the vector.
        RemoveColorTables(index);

        // If it is the active color table that was removed, reset the
        // active color table to the first element.
        if(isActiveContinuous)
        {
            if(names.size() > 0)
                SetActiveContinuous(names[0]);
            else
                SetActiveContinuous(std::string(""));
        }
        if(isActiveDiscrete)
        {
            if(names.size() > 0)
                SetActiveDiscrete(names[0]);
            else
                SetActiveDiscrete(std::string(""));
        }
    }
}

}
