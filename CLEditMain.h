#ifndef CLEDITMAIN_H
#define CLEDITMAIN_H

// the purpose of this program is to Edit a file in manner similar to IBM TSO Edit with some twists taken from B.I. Moyle
#include "CLEditCF.h"
#include "CLEditDB.h"
#include "CLEditSM.h"
#include "CLEditRP.h"
#include "CLEditAR.h"
#include "CLEditXETL.h"
#include <wx/wx.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <pwd.h>
#include <chrono>
#define FILE_SIZE 1000
// FILE_SIZE 102400
using namespace std;
class CLEditFrame : public wxFrame
{

    public:

#include "wxparts.h"
#include "variables.h"
#include "structures.h"
#include "trackers.h"
#include "functions.h"
#include "objects.h"

    protected:

    private:

        wxDECLARE_EVENT_TABLE();

};

#endif // CLEDITMAIN_H
