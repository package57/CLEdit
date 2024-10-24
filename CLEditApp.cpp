#include <iostream>
#include <wx/wx.h>
#include "CLEditApp.h"
#include "CLEditMain.h"
using namespace std;
IMPLEMENT_APP(CLEditApp);

bool CLEditApp::OnInit()
{

    CLEditFrame * frame = new CLEditFrame("CLEdit @yourCommand");

    frame->SetClientSize(1920,1020);

    frame->Center();

    wxFont myFont(10, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    frame->SetFont(myFont);

    frame->Show();

    return true;

}
