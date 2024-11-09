#include <iostream>
#include <wx/wx.h>
#include "CLEditMain.h"
using namespace std;

wxBEGIN_EVENT_TABLE(CLEditFrame, wxFrame)
    EVT_KEY_DOWN(CLEditFrame::OnKeyDown)
wxEND_EVENT_TABLE()

CLEditFrame::CLEditFrame(const wxString & title)
: wxFrame(nullptr
          ,wxID_ANY
          ,title
          ,wxDefaultPosition
          ,wxDefaultSize
          ,wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{

    LogFile.open("CLEditLog.txt", std::ios::out);
    ErrFile.open("CLEditErr.txt", std::ios::out);

    CreateControls();

    Initialize();

    if (Return == false)
    {
        ReturnFunction = "CreateControls ";
        ReturnCode = "3500 ";
        ReturnMessage = " Create Controls failure";
        OnTerminal();
    }

}
void CLEditFrame::OnKeyDown(wxKeyEvent & event)
{

    switch ( event.GetKeyCode() )
    {
        case WXK_CONTROL_F:
        case WXK_F5:
            LogFile << "F5 " << std::endl;
            ProcessScreen();
            Find();
            LoadScreen();
            break;
        case WXK_END:
        case WXK_NUMPAD_END:
            LogFile << "End " << std::endl;
            ProcessScreen();
            Bottom();
            LoadScreen();
            break;
        case WXK_HOME:
        case WXK_NUMPAD_BEGIN:
            LogFile << "Home " << std::endl;
            ProcessScreen();
            Home();
            LoadScreen();
            break;
        case WXK_F7:
        case WXK_PAGEUP:
        case WXK_NUMPAD_PAGEUP:
            LogFile << "F7 " << std::endl;
            ProcessScreen();
            Up();
            LoadScreen();
            break;
        case WXK_F8:
        case WXK_PAGEDOWN:
        case WXK_NUMPAD_PAGEDOWN:
            LogFile << "F8 " << std::endl;
            ProcessScreen();
            Down();
            LoadScreen();
            break;
        case WXK_HELP:
        case WXK_F1:
            LogFile << "F1 " << std::endl;
            ProcessScreen();
            Help();
            LoadScreen();
            break;
        case WXK_F6:
            LogFile << "F6 " << std::endl;
            ProcessScreen();
            Change();
            LoadScreen();
            break;
    }

    event.Skip();

}
void CLEditFrame::Find()
{
    LogFile << "Find " << std::endl;

//  LoadScreen();   //always from work input

    wxLogStatus("Find applied");
}
void CLEditFrame::Bottom()
{
    LogFile << "Bottom " << std::endl;

    if (wfilecnt > 50)
    {
        lastl = wfilecnt / 50;
        lastl *= 50;
        lastl++;
        frstl = lastl;
//      LoadScreen();   //always from work input
        wxLogStatus("Bottom end of file");
    }
    else
    {
        frstl = 1;
//      LoadScreen();   //always from work input
        wxLogStatus("Bottom end of file");
    }
}
void CLEditFrame::Home()
{
    LogFile << "Home " << std::endl;

    frstl = 1;

//  LoadScreen();   //always from work input

    wxLogStatus("Home applied");

}
void CLEditFrame::Up()
{
    LogFile << "Up " << std::endl;

    if (frstl == 1)
    {
        wxLogStatus("Up top of file");
    }
    else
    {
        frstl -= 50;
//      LoadScreen();   //always from work input
        wxLogStatus("Up applied");
    }

}
void CLEditFrame::Down()
{
    LogFile << "Down " << std::endl;

    if (wfilecnt > 50)
    {
        frstl += 50;
//      LoadScreen();   //always from work input
        wxLogStatus("Down applied");
    }
    else
    {
        wxLogStatus("Down end of file");
    }

}
void CLEditFrame::Help()
{
    LogFile << "Help " << std::endl;

    wxLogStatus("Help applied");
}
void CLEditFrame::Change()
{
    LogFile << "Change " << std::endl;


    wxLogStatus("Change applied");
}
void CLEditFrame::OnApplyClicked(wxCommandEvent & event)
{

    LogFile << "On Apply Clicked " << std::endl;

    Commandl = Command->GetLineLength(0);
    LogFile << "Length " << Commandl << std::endl;
    if  (Commandl == 0)
    {
        goto MainProcess;
    }

    Commandstr = Command->GetLineText(0); //GetValue();

    WipeCommand();

    FindPrimary();

    if (strpos < Commandl)
    {
        FindFirst();
        if (strpos < Commandl)
        {
            FindSecond();
            if (strpos < Commandl)
            {
                FindThird();
            }
        }
    }
//create a file from a block copy
    if (PrimaryCommand == "create")
    {
        Create();
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " applied");
        goto ExitOnApplyClicked;
    }
//change string tostring f6 all
    if (PrimaryCommand == "change")
    {
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " " + ThirdParameter + " applied");
        goto ExitOnApplyClicked;
    }
//copy file
    if (PrimaryCommand == "copy")
    {
        CopyFile();
        goto ExitOnApplyClicked;
    }
//exclude  'x all'
    if (PrimaryCommand == "exclude"
    ||  PrimaryCommand == "x")
    {
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " " + ThirdParameter + " applied");
        goto ExitOnApplyClicked;
    }
//find string f5 all
    if (PrimaryCommand == "find")
    {
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " " + ThirdParameter + " applied");
        goto ExitOnApplyClicked;
    }
//open file
    if (PrimaryCommand == "open")
    {
        OpenFile();
        goto ExitOnApplyClicked;
    }
//reset - clear all the command line actions
    if (PrimaryCommand == "open")
    {
        OpenFile();
        goto ExitOnApplyClicked;
    }
//save file
    if (PrimaryCommand == "save")
    {
        SaveFile();
        goto ExitOnApplyClicked;
    }
//save as file
    if (PrimaryCommand == "saveas")
    {
        SaveAsFile();
        goto ExitOnApplyClicked;
    }
//exit - clear the screen
    if (PrimaryCommand == "exit")
    {
        Exit();
        goto ExitOnApplyClicked;
    }
//stage code from database
    if (PrimaryCommand == "fromstage")
    {
        FromStage();
        goto ExitOnApplyClicked;
    }
//stage code to database
    if (PrimaryCommand == "tostage")
    {
        ToStage();
        goto ExitOnApplyClicked;
    }
    if (PrimaryCommand == "bottom")
    {
        Find(); Bottom();
        goto ExitOnApplyClicked;
    }

    if (PrimaryCommand == "home")
    {
        Home();
        goto ExitOnApplyClicked;
    }

    if (PrimaryCommand == "up")
    {
        Up();
        goto ExitOnApplyClicked;
    }

    if (PrimaryCommand == "down")
    {
        Down();
        goto ExitOnApplyClicked;
    }

    if (PrimaryCommand == "help")
    {
        Help();
        goto ExitOnApplyClicked;
    }

    if (PrimaryCommand == "change")
    {
        Change();
        goto ExitOnApplyClicked;
    }

MainProcess:

    ProcessScreen();

// Load Screen always from index frstl
    LoadScreen();

    Return = true;

ExitOnApplyClicked:

    Command->Clear();
    Command->SetFocus();

}
void CLEditFrame::FindPrimary()
{
    LogFile << "Find Primary ";

    for (i = 0; i < Commandl; i++)
    {
        if  (Commandstr[i] == ' ')
        {
            strpos = i;
            i = 99;
            break;
        }
        else
        {
            PrimaryCommand += Commandstr[i];
        }
    }

    if (i != 99)  // stop looking
    {
        strpos = 99;
    }

    LogFile << PrimaryCommand << std::endl;

}
void CLEditFrame::FindFirst()
{

    LogFile << "Find First ";

    for (i = strpos; i < Commandl; i++)
    {
        if  (Commandstr[i] == ' ')
        {
            if  (FirstParameter == "")
            {
                Byte = ' '; //keep looking
            }
            else
            {
                strpos = i;
                i = 99;
                break;
            }
        }
        else
        {
            FirstParameter += Commandstr[i];
        }
    }

    if (i != 99)  // stop looking
    {
        strpos = 99;
    }

    LogFile << FirstParameter << std::endl;

}
void CLEditFrame::FindSecond()
{

    LogFile << "Find Second ";

    for (i = strpos; i < Commandl; i++)
    {
        if  (Commandstr[i] == ' ')
        {
            if  (SecondParameter == "")
            {
                Byte = ' '; //keep looking
            }
            else
            {
                strpos = i;
                i = 99;
                break;
            }
        }
        else
        {
            SecondParameter += Commandstr[i];
        }
    }

    if (i != 99)  // stop looking
    {
        strpos = 99;
    }

    LogFile << SecondParameter << std::endl;


}
void CLEditFrame::FindThird()
{

    LogFile << "Find Third ";

    for (i = strpos; i < Commandl; i++)
    {
        if  (Commandstr[i] == ' ')
        {
            if  (ThirdParameter == "")
            {
                Byte = ' '; //keep looking
            }
            else
            {
                strpos = i;
                i = 99;
                break;
            }
        }
        else
        {
            ThirdParameter += Commandstr[i];
        }
    }

    LogFile << ThirdParameter << std::endl;

}
void CLEditFrame::OnTerminal()
{

    ErrFile << ReturnFunction << ReturnCode << ReturnMessage << std::endl;

}
void CLEditFrame::Create()
{

    LogFile << "Create File " << std::endl;   // need a block copy and file name

}
void CLEditFrame::SaveFile()
{
    LogFile << "Save File " << std::endl;

    if (CurrentFile == "")  // means the file is on the screen - wasnt opened first
    {
        if (FirstParameter == "")
        {
            wxLogStatus(PrimaryCommand + " " + FirstParameter + " file name to SAVE missing");
            goto ExitSaveFile;
        }
        else
        {
            CurrentFile = FirstParameter;
        }
    }

    for (i = 0; i < wfilecnt; i++)
    {
        SetEndl();
        CF.inputfile[i].IFCode = winputfile[i].wIFCode;
    }

    CF.fileoname = CurrentFile;
    CLEditCFrc = CF.savefile(CF.fileoname);

    if  (CLEditCFrc != 0)
    {
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " Save file Open error");
        goto ExitSaveFile;
    }

    frstl = 1;

    LoadScreen();   //always from work input

    wxLogStatus(PrimaryCommand + " " + CurrentFile + " applied");

ExitSaveFile:

    WipeCommand();

}
void CLEditFrame::SaveAsFile()
{

    LogFile << "SaveAs " << std::endl;

    if  (FirstParameter == "")
    {
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " file name to Save As missing");
        goto ExitSaveAsFile;
    }
    else
    {
        CurrentFile = FirstParameter;
    }

    for (i = 0; i < wfilecnt; i++)
    {
        SetEndl();
        CF.inputfile[i].IFCode = winputfile[i].wIFCode;
    }

    CF.fileoname = CurrentFile;
    CF.fileoreccnt = wfilecnt;
    CLEditCFrc = CF.savefile(CF.fileoname);

    if  (CLEditCFrc != 0)
    {
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " Save As file Open error");
        goto ExitSaveAsFile;
    }

    frstl = 1;

    LoadScreen();   //always from work input

    wxLogStatus(PrimaryCommand + " " + FirstParameter + " applied");

ExitSaveAsFile:

    WipeCommand();

}
void CLEditFrame::Exit()
{
    LogFile << "Exit " << std::endl;

    Initialize();

    wxLogStatus(PrimaryCommand + " applied");

    WipeCommand();

}

void CLEditFrame::Reset()
{
    LogFile << "Exit " << std::endl;
// clear all line commands- especially X & XX

    for (i = 1; i < 25000; i++)
    {
        inputfile[i].IFlc   = "000000";
        winputfile[0].wIFlc = "000000";
    }

    frstl = 1;

    LoadScreen();

    wxLogStatus(PrimaryCommand + " applied");

    WipeCommand();

}

void CLEditFrame::OpenFile()
{
    LogFile << "Open File " << std::endl;

    if (FirstParameter == "")
    {
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " file name to OPEN missing");
        goto ExitOpenFile;
    }

    InitScreen();

    CurrentFile = FirstParameter;
    CF.fileiname = FirstParameter;
    CLEditCFrc = CF.openfile(CF.fileiname);

    if  (CLEditCFrc != 0)
    {
        CLEditCFmsg();
        goto ExitOpenFile;
    }

    haveaFile = true;

    InitIF();

    InitWIF();

    wfilecnt = CF.fileireccnt;

    for (i = 0; i < CF.fileireccnt; i++)
    {
        inputfile[i].IFCode   = CF.inputfile[i].IFCode;
        winputfile[i].wIFlc   = "000000";
        winputfile[i].wIFCode = CF.inputfile[i].IFCode;
        GetEndl();
    }

    wxLogStatus(PrimaryCommand + " " + FirstParameter + " applied");

    frstl = 1;

    LoadScreen();   //always from work input

ExitOpenFile:

    WipeCommand();

}
void CLEditFrame::GetEndl()
{

    winputfile[i].wIFCode.erase(std::remove(winputfile[i].wIFCode.begin(), winputfile[i].wIFCode.end(), '\n'), winputfile[i].wIFCode.cend());

}
void CLEditFrame::SetEndl()
{

    winputfile[i].wIFCode += '\n';

}
void CLEditFrame::CopyFile()
{
    LogFile << "Copy File " << std::endl;

    InitScreen();

    if (FirstParameter == "")
    {
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " FROM file name missing");
        goto ExitCopyFile;
    }

    if (SecondParameter == "")
    {
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " TO file name missing");
        goto ExitCopyFile;
    }


    CF.fileiname = FirstParameter;
    CF.fileoname = SecondParameter;
    CLEditCFrc = CF.copyfile(CF.fileiname, CF.fileoname);

    if  (CLEditCFrc != 0)
    {
        CLEditCFmsg();
    }
    else
    {
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " applied");
    }

ExitCopyFile:

    WipeCommand();

}
void CLEditFrame::CLEditCFmsg()
{

    switch (CLEditCFrc)
    {
        case 3500:
            wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " file Out Open error");
            break;
        case 3501:
            wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " file In Open error");
            break;
    }

}
void CLEditFrame::FromStage()
{

    LogFile << "from stage " << std::endl;

    InitScreen();
// the next three lines are the equivalent of an "open"
//create a driver object
    DB.Driver();
//create a connection object
    DB.Connect();
//create a statement object
    DB.Statement();

    rowcnt = DB.Cursor();
    LogFile << "rows " << rowcnt << std::endl;

    if  (rowcnt > 0)
    {
        wfilecnt = rowcnt;
        InitIF();
        InitWIF();
        DB.Process();
        for (i = 0; i < rowcnt; i++)
        {
            inputfile[i].IFCode = DB.inputfile[i].IFCode;
            winputfile[i].wIFlc   = "000000";
            winputfile[i].wIFCode = DB.inputfile[i].IFCode;
            SetEndl();
        }
    }
// "close" the database
    DB.Free();

    frstl = 1;

    LoadScreen();

    wxLogStatus(PrimaryCommand + " applied");

    WipeCommand();

}
void CLEditFrame::ToStage()
{
    LogFile << "To Stage " << std::endl;

    InitScreen();
// the next three lines are the equivalent of an "open"
//create a driver object
    DB.Driver();
//create a connection object
    DB.Connect();
//create a statement object
    DB.Statement();

    rowcnt = DB.Cursor();
    LogFile << "rows " << rowcnt << std::endl;

    if  (rowcnt > 0)
    {
        wfilecnt = rowcnt;
        InitIF();
        InitWIF();
        DB.Process();
        for (i = 0; i < rowcnt; i++)
        {
            inputfile[i].IFCode = DB.inputfile[i].IFCode;
            winputfile[i].wIFlc   = "000000";
            winputfile[i].wIFCode = DB.inputfile[i].IFCode;
            GetEndl();
        }
    }
// "close" the database
    DB.Free();

    frstl = 1;

    LoadScreen();

    wxLogStatus(PrimaryCommand + " applied");

    WipeCommand();

}
void CLEditFrame::WipeCommand()
{

    PrimaryCommand = "";
    FirstParameter = "";
    SecondParameter = "";
    ThirdParameter = "";

}
void CLEditFrame::LoadScreen()
{
    LogFile << "Load Screen " << std::endl;

    i = 0;
    for (u = (frstl - 1); i < 50; u++)
    {
        if (winputfile[u].wIFlc[1] == '0')
        {
            prettystr = ToString(u);
            CL[u].Line->ChangeValue(prettystr);
        }
        else ///don't wipe the command on the line
        {
            CL[u].Line->ChangeValue(winputfile[u].wIFlc);
        }
        CL[u].Code->ChangeValue(winputfile[u].wIFCode);
        i++;
    }

}
// make 10 look like 000010 etc
std::string CLEditFrame::ToString(int u)
{
    ostringstream os;

    prettyint = u * 5;

    os<<setfill('0')<<setw(6)<<prettyint;

    return os.str();
}
void CLEditFrame::ProcessScreen()
{
// capture everything from the screen
// capture all commands
    ReadScreen();

// move all the user Input into Work Input
// the index from the screen "u" to Work Input is "frstl"
    i = frstl - 1;
    for (u = 0; u < 50; u++)
    {
        winputfile[i].wIFlc   = Input[u].Linestr;
        winputfile[i].wIFCode = Input[u].Codestr;
        i++;
    }

// init Input File
    InitIF();

// copy Work Input to Input File
// applying any changes - if possible - adjust wfilecnt
// once all changes are applied - init all the command trackers and structures CC DD MM RR OO
    badchanges = false;
    ApplyChanges();

    if (badchanges)
    {
        return;
    }

    if  (changesapplied)
    {
        InitCC();
        InitMM();
        InitOO();
        InitRR();
        InitCTrackers();
    }
    else
    {
        return;
    }

// copy from Input File back to Work Input
    for (i = 0; i < wfilecnt; i++)
    {
        if (inputfile[i].IFlc == "X")     // this needs thought!
        {
            winputfile[i].wIFlc   = "X";
            winputfile[i].wIFCode = "----";
        }
        else
        {
            if (inputfile[i].IFlc == "XX")  // this needs thought!
            {
                winputfile[i].wIFlc   = "X";
                winputfile[i].wIFCode = "----";
            }
            else
            {
                winputfile[i].wIFlc   = "000000";
                winputfile[i].wIFCode = inputfile[i].IFCode;
            }
        }
    }

}
void CLEditFrame::ReadScreen()
{

    LogFile << "Read Screen " << std::endl;
// user input
    InitUser();
// capture everything from the text controls - line Command and line of Code
    for (u = 0; u < 50; u++)
    {
        UserLinel   = CL[u].Line->GetLineLength(0);
        UserLinestr = CL[u].Line->GetLineText(0);
        UserCodel   = CL[u].Code->GetLineLength(0);
        UserCodestr = CL[u].Code->GetLineText(0);
        LoopLine();
        LoopCode();
        if (!haveaFile)   // means we're starting from a blank screen not an open, from stage or copy after
        {
            if (UserCodestr != "")
            {
                wfilecnt = u;
                wfilecnt++;    // off by one eh
            }
        }
    }

}
void CLEditFrame::LoopLine()
{

    Input[u].Linel = UserLinel;

    for (i = 0; i < UserLinel; i++)
    {
        Input[u].Linestr += UserLinestr[i];
        WhatCommand();
    }

}
void CLEditFrame::WhatCommand()
{

    if (UserLinestr[i] == 'A')
    {
        Input[u].Linestr = "A";
        afters++;
        i = 7; // stop looking
        return;
    }

    if (UserLinestr[i] == 'B')
    {
        Input[u].Linestr = "B";
        befores++;
        i = 7; // stop looking
        return;
    }

    if (UserLinestr[i] == 'C')
    {
        if  (UserLinel > 1)
        {
            posp1 = i + 1;
            if (UserLinestr[posp1] == 'C')
            {
                Input[u].Linestr = "CC";
                blockCC = true;
                i = 7; // stop looking
                return;
            }
            else
            {
                i = 7; // stop looking
                return;
            }
        }
        else
        {
            singleC++;
            haveaC = u;
            Input[u].Linestr = "C";
            return;
        }
    }

    if (UserLinestr[i] == 'D')
    {
        if  (UserLinel > 1)
        {
            posp1 = i + 1;
            if (UserLinestr[posp1] == 'D')
            {
                Input[u].Linestr = "DD";
                blockDD = true;
                return;
            }
            else
            {
                i = 7; // stop looking
                return;
            }
        }
        else
        {
            singleD++;
            Input[u].Linestr = "D";
            return;
        }
    }

/*
        int singleI;  // insert a single line - can have a count
        int  Ii;       // number of lines to insert
*/

    if (UserLinestr[i] == 'M')
    {
        if  (UserLinel > 1)
        {
            posp1 = i + 1;
            if (UserLinestr[posp1] == 'M')
            {
                Input[u].Linestr = "MM";
                blockMM = true;
                return;
            }
            else
            {
                i = 7; // stop looking
                return;
            }
        }
        else
        {
            singleM++;
            haveaM = u;
            Input[u].Linestr = "M";
            return;
        }
    }

    if (UserLinestr[i] == 'O')
    {
        if  (UserLinel > 1)
        {
            posp1 = i + 1;
            if (UserLinestr[posp1] == 'O')
            {
                Input[u].Linestr = "OO";
                blockOO = true;
                i = 7; // stop looking
                return;
            }
            else
            {
                i = 7; // stop looking
                return;
            }
        }
        else
        {
            singleO++;
            haveaO = u;
            Input[u].Linestr = "O";
            return;
        }
    }

    if (UserLinestr[i] == 'R')
    {
        if  (UserLinel > 1)
        {
            posp1 = i + 1;
            if (UserLinestr[posp1] == 'R')
            {
                Input[u].Linestr = "RR";
                blockRR = true;
                i = 7; // stop looking
                return;
            }
            else
            {
                i = 7; // stop looking
                return;
            }
        }
        else
        {
            singleSR++;
            haveaR = u;
            Input[u].Linestr = "R";
            return;
        }
    }

//        int  SRi;      // number of characters to shift right
    if (UserLinestr[i] == '>')
    {
        if  (UserLinel > 1)
        {
            posp1 = i + 1;
            if (UserLinestr[posp1] == '>')
            {
                Input[u].Linestr = ">>";
                blockSR = true;
                return;
            }
        }
        else
        {
            singleSR++;
            Input[u].Linestr = ">";
            return;
        }
    }

//   int  SLi;      // number of characters to shift left
    if (UserLinestr[i] == '<')
    {
        if  (UserLinel > 1)
        {
            posp1 = i + 1;
            if (UserLinestr[posp1] == '<')
            {
                Input[u].Linestr = "<<";
                blockSL = true;
                return;
            }
        }
        else
        {
            singleSL++;
            Input[u].Linestr = "<";
            return;
        }
    }

    if (UserLinestr[i] == 'X')
    {
        if  (UserLinel > 1)
        {
            posp1 = i + 1;
            if (UserLinestr[posp1] == 'X')
            {
                Input[u].Linestr = "XX";
                blockXX = true;
                i = 7; // stop looking
                return;
            }
            else
            {
                i = 7; // stop looking
                return;
            }
        }
        else
        {
            singleX++;
            Input[u].Linestr = "X";
            return;
        }
    }

}
void CLEditFrame::LoopCode()
{

    Input[u].Codel = UserCodel;

    for (i = 0; i < UserCodel; i++)
    {
        Input[u].Codestr += UserCodestr[i];
    }

}
void CLEditFrame::ApplyChanges()
{
    LogFile << "ApplyChanges " << std::endl;

    LookForLC();

    if (badchanges)
    {
        return;
    }

    LCReasonability();

    if (badchanges)
    {
        return;
    }

    LCcnt = CCcnt + MMcnt + OOcnt + RRcnt;

    if (LCcnt != 0)
    {
        CaptureLC();  // blocks
    }
    else
    {
        LCcnt = haveaC + haveaM + haveaO + haveaR;
        if (LCcnt != 0)
        {
            CaptureLC();  // blocks
        }
    }

// ranges
    if (blockMM
    &&  blockOO)
    {
        if (OOstart < MMstart
        &&  OOend < MMstart)
        {
            badchanges = false;
        }
        else
        {
            if (OOstart > MMend
            &&  OOend > MMend)
            {
                badchanges = false;
            }
            else
            {
                wxLogStatus("block move / overlay overlapping ranges ");
                badchanges = true;
                return;
            }
        }
    }

// at the very lease - copy work to input - as is - without command line changes applied - yet

    for (i = 0; i < wfilecnt; i++)
    {
        inputfile[i].IFlc   = winputfile[i].wIFlc;
        inputfile[i].IFCode = winputfile[i].wIFCode;
    }

// is there anything to apply?
    LCcnt = CCcnt + + DDcnt + MMcnt + OOcnt + RRcnt + SRcnt + SLcnt + XXcnt;
    LCcnt = LCcnt + singleC + singleD + singleM + + singleO + singleR + singleSR + singleSR + singleX;

    if (LCcnt == 0)
    {
        changesapplied = false;
        return;
    }

// insert the lines to be copied where ever there is an After or a Before
// block copy create - ! tbd
// makes input file bigger
    if (CCcnt == 2)
    {
        ApplyCC();
    }

// makes input file smaller
    if (DDcnt == 2
    ||  singleD > 0)
    {
        ApplyDD();
    }

// input file stays the same size
    if  (MMcnt == 2)
    {
        ApplyMM();
    }

// input file becomes smaller by the InptOO size
    if (OOcnt == 2)
    {
        ApplyOO();
    }

// makes input file bigger
    if (RRcnt == 2)
    {
        ApplyRR();
    }

// no change to input file size
    if (SRcnt == 2)
    {
        ApplySR();
    }

// no change to input file size
    if (SLcnt == 2)
    {
        ApplySL();
    }

// no change to input file size
// changes what can bee seen on the screen
    if  (XXcnt == 2)
    {
        ApplyXX();
    }

//    wxLogStatus("changes applied");

}
void CLEditFrame::LCReasonability()
{

    LogFile << "LCReasonability " << std::endl;
// multiple blocks and or multiple types os blocks are ambiguous
// especially ones that cause file size changes
    LCcnt = CCcnt + MMcnt + OOcnt + RRcnt;

    if (LCcnt > 2)
    {
        wxLogStatus("block command ambiguous ");
        badchanges = true;
        return;
    }

    if  (OOcnt == 2)
    {
        if  (MMcnt == 2)
        {
            badchanges = false;
        }
        else
        {
            wxLogStatus("block move missing for overlay ");
            badchanges = true;
            return;
        }
    }

    LCcnt = singleC + singleM + singleO + singleR;

    if (LCcnt > 1)
    {
        wxLogStatus("line commands ambiguous ");
        badchanges = true;
        return;
    }

    if  (singleO == 1)
    {
        if  (singleM == 1)
        {
            badchanges = false;
        }
        else
        {
            wxLogStatus("line move missing for line overlay ");
            badchanges = true;
            return;
        }
    }

    if (singleC > 1)
    {
        wxLogStatus("copy line command ambiguous ");
        badchanges = true;
        return;
    }

    if (singleM > 1)
    {
        wxLogStatus("move line command ambiguous ");
        badchanges = true;
        return;
    }

    if (singleO > 1)
    {
        wxLogStatus("overlay line command ambiguous ");
        badchanges = true;
        return;
    }

    if (singleR > 1)
    {
        wxLogStatus("repeat line command ambiguous ");
        badchanges = true;
        return;
    }

    if (blockCC
    ||  blockMM
    ||  blockOO
    ||  blockRR)
    {
        if  (singleC > 0
        ||   singleM > 0
        ||   singleO > 0
        ||   singleR > 0)
        {
            wxLogStatus("repeat line command ambiguous ");
            badchanges = true;
            return;
        }
    }

}
void CLEditFrame::LookForLC()
{

    CCcnt = 0;
    for (i = 0; i < wfilecnt; i++)
    {
        LookForCC();
    }

    if  (CCcnt > 2)
    {
        wxLogStatus("multiple block copies");
        badchanges = true;
        return;
    }

    if  (CCcnt == 1)
    {
        wxLogStatus("missing block copy pair");
        badchanges = true;
        return;
    }

    DDcnt = 0;
    for (i = 0; i < wfilecnt; i++)
    {
        LookForDD();
    }

    if  (DDcnt > 2)
    {
        wxLogStatus("multiple block delete");
        badchanges = true;
        return;
    }

    if  (DDcnt == 1)
    {
        wxLogStatus("missing block delete pair");
        badchanges = true;
        return;
    }

    MMcnt = 0;
    for (i = 0; i < wfilecnt; i++)
    {
        LookForMM();
    }

    if  (MMcnt > 2)
    {
        wxLogStatus("multiple block move");
        badchanges = true;
        return;
    }

    if  (MMcnt == 1)
    {
        wxLogStatus("missing block move pair");
        badchanges = true;
        return;
    }

    OOcnt = 0;
    for (i = 0; i < wfilecnt; i++)
    {
        LookForOO();
    }

    if  (OOcnt > 2)
    {
        wxLogStatus("multiple block overlay");
        badchanges = true;
        return;
    }

    if  (OOcnt == 1)
    {
        wxLogStatus("missing block overlay pair");
        return;
    }

    RRcnt = 0;
    for (i = 0; i < wfilecnt; i++)
    {
        LookForRR();
    }

    if  (RRcnt > 2)
    {
        wxLogStatus("multiple block repeat");
        badchanges = true;
        return;
    }

    if  (RRcnt == 1)
    {
        wxLogStatus("missing block repeat pair");
        badchanges = true;
        return;
    }

    SRcnt = 0;
    for (i = 0; i < wfilecnt; i++)
    {
        LookForSR();
    }

    if  (SRcnt > 2)
    {
        wxLogStatus("multiple block shift right");
        badchanges = true;
        return;
    }

    if  (SRcnt == 1)
    {
        wxLogStatus("missing block shift right pair");
        badchanges = true;
        return;
    }

    SLcnt = 0;
    for (i = 0; i < wfilecnt; i++)
    {
        LookForSL();
    }

    if  (SLcnt > 2)
    {
        wxLogStatus("multiple block shift left");
        badchanges = true;
        return;
    }

    if  (SLcnt == 1)
    {
        wxLogStatus("missing block shift left pair");
        badchanges = true;
        return;
    }

    XXcnt = 0;
    for (i = 0; i < wfilecnt; i++)
    {
        LookForXX();
    }

    if  (XXcnt > 2)
    {
        wxLogStatus("multiple block exclude");
        badchanges = true;
        return;
    }

    if  (XXcnt == 1)
    {
        wxLogStatus("missing block exclude pair");
        badchanges = true;
        return;
    }
}
void CLEditFrame::CaptureLC()
{

    if (CCcnt == 2 || singleC == 1)
    {
        CaptureCC();
    }

    if (MMcnt == 2 || singleM == 1)
    {
        CaptureMM();
    }

    if (OOcnt == 2 || singleO == 1)
    {
        CaptureOO();
    }

    if (RRcnt == 2 || singleR == 1)
    {
        CaptureRR();
    }

}
void CLEditFrame::LookForCC()
{

    LogFile << "Look for CC " << std::endl;

    CCstart = 9999;
    if (winputfile[i].wIFlc == "CC")
    {
        CCcnt++;
        CCend = i;
        if (CCstart == 9999)
        {
            CCstart = i;
        }
    }

}
void CLEditFrame::CaptureCC()
{

    LogFile << "Capture CC " << std::endl;

    if (singleC == 1)
    {
        cinputfile.cIFCode = winputfile[haveaC].wIFCode;
    }
    else
    {
        l = 0;
        for (i = CCstart; i > CCend; i++)
        {
            ccinputfile[l].cIFCode = winputfile[i].wIFCode;
            l++;
        }
    }

}
void CLEditFrame::LookForDD()
{

    LogFile << "Look for DD " << std::endl;

    DDstart = 9999;
    if (winputfile[i].wIFlc == "DD")
    {
        DDcnt++;
        DDend = i;
        if (DDstart == 9999)
        {
            DDstart = i;
        }
    }

}
/*
void CLEditFrame::CaptureDD()
{

    LogFile << "Capture DD " << std::endl;

}
*/
void CLEditFrame::LookForMM()
{

    LogFile << "Look for MM " << std::endl;

    MMstart = 9999;
    if (winputfile[i].wIFlc == "MM")
    {
        MMcnt++;
        MMend = i;
        if (MMstart == 9999)
        {
            MMstart = i;
        }
    }

}
void CLEditFrame::CaptureMM()
{

    LogFile << "Capture MM " << std::endl;

    if (singleM == 1)
    {
        minputfile.mIFCode = winputfile[haveaM].wIFCode;
    }
    else
    {
        l = 0;
        for (i = MMstart; i > MMend; i++)
        {
            mminputfile[l].mIFCode = winputfile[i].wIFCode;
            l++;
        }
    }

}
void CLEditFrame::LookForOO()
{

    LogFile << "Look for OO " << std::endl;

    OOstart = 9999;
    if (winputfile[i].wIFlc == "OO")
    {
        OOcnt++;
        OOend = i;
        if (OOstart == 9999)
        {
            OOstart = i;
        }
    }

}
void CLEditFrame::CaptureOO()
{

    LogFile << "Capture OO " << std::endl;

    if (singleO == 1)
    {
        oinputfile.oIFCode = winputfile[haveaO].wIFCode;
    }
    else
    {
        l = 0;
        for (i = OOstart; i > OOend; i++)
        {
            ooinputfile[l].oIFCode = winputfile[i].wIFCode;
            l++;
        }
    }

}
void CLEditFrame::LookForRR()
{

    LogFile << "Look for RR " << std::endl;

    RRstart = 9999;
    if (winputfile[i].wIFlc == "RR")
    {
        RRcnt++;
        RRend = i;
        if (RRstart == 9999)
        {
            RRstart = i;
        }
    }

}
void CLEditFrame::CaptureRR()
{

    LogFile << "Capture RR " << std::endl;

    if (singleR == 1)
    {
        rinputfile.rIFCode = winputfile[haveaR].wIFCode;
    }
    else
    {
        l = 0;
        for (i = RRstart; i > RRend; i++)
        {
            mminputfile[l].mIFCode = winputfile[i].wIFCode;
            l++;
        }
    }

}
void CLEditFrame::LookForSR()
{

    LogFile << "Look for >> " << std::endl;

    SRstart = 9999;
    if (winputfile[i].wIFlc == ">>")
    {
        SRcnt++;
        SRend = i;
        if (SRstart == 9999)
        {
            SRstart = i;
        }
    }

}
/*
void CLEditFrame::CaptureSR()
{

    LogFile << "Capture SR " << std::endl;

}
*/
void CLEditFrame::LookForSL()
{

    LogFile << "Look for << " << std::endl;

    SLstart = 9999;
    if (winputfile[i].wIFlc == "<<")
    {
        SLcnt++;
        SLend = i;
        if (SLstart == 9999)
        {
            SLstart = i;
        }
    }

}
/*
void CLEditFrame::CaptureSL()
{

    LogFile << "Capture SL " << std::endl;

}
*/
void CLEditFrame::LookForXX()
{

    LogFile << "Look for XX " << std::endl;

    XXstart = 9999;
    if (winputfile[i].wIFlc == "XX")
    {
        XXcnt++;
        XXend = i;
        if (XXstart == 9999)
        {
            XXstart = i;
        }
    }

}
/*
void CLEditFrame::CaptureXX()
{

    LogFile << "Capture XX " << std::endl;

}
*/
void CLEditFrame::ApplyCC()
{

    LogFile << "Apply CC " << std::endl;
}
void CLEditFrame::ApplyDD()
{
// reduces the file size
    LogFile << "Apply DD " << std::endl;

    oldwfilecnt = wfilecnt;

    InitWIF();

    for (i = 0; i < oldwfilecnt; i++)
    {
        if (singleD > 0) // this is the number of line deletes
        {
            LineDelete();
        }
        else // this is a block delete
        {
            BlockDelete();
        }
    }

    changesapplied = true;

}
void CLEditFrame::LineDelete()
{

    if (inputfile[i].IFlc == "D")
    {
        wfilecnt--;  // skip the record
    }
    else
    {
        winputfile[i].wIFlc   = inputfile[i].IFlc;
        winputfile[i].wIFCode = inputfile[i].IFCode;
    }

}
void CLEditFrame::BlockDelete()
{

    if (i >= DDstart
    &&  i <= DDend)
    {
        wfilecnt--;  // skip the record
    }
    else
    {
        winputfile[i].wIFlc   = inputfile[i].IFlc;
        winputfile[i].wIFCode = inputfile[i].IFCode;
    }

}
void CLEditFrame::ApplyMM()
{

    LogFile << "Apply MM " << std::endl;
}
void CLEditFrame::ApplyOO()
{

    LogFile << "Apply OO " << std::endl;
}
void CLEditFrame::ApplyRR()
{

    LogFile << "Apply RR " << std::endl;
}
void CLEditFrame::ApplySR()
{

    LogFile << "Apply >> " << std::endl;
}
void CLEditFrame::ApplySL()
{

    LogFile << "Apply <<  " << std::endl;
}
void CLEditFrame::ApplyXX()
{

    LogFile << "Look for XX " << std::endl;
}
void CLEditFrame::Initialize()
{

    LogFile << "Initialize " << std::endl;

// screen
    InitScreen();
// variables
    CurrentFile     = "";
    Byte            = ' ';
    strpos          = 0;
    i               = 0;
// Command
    Commandl        = 0;
    Commandstr      = "";
    PrimaryCommand  = "";
    FirstParameter  = "";
    SecondParameter = "";
    ThirdParameter  = "";

// this is the "screen" 50 lines of visible code ( line command area 6 bytes / line of code 80 bytes)
    InitUser();
// to make the line command area pretty "000010"
//      ostringstream os;     defined local because otherwise it concatenates
    prettyint = 0;
    prettystr = "";
// error / logging
    Return = true;
    ReturnFunction = "";
    ReturnCode = "";
    ReturnMessage = "";

// the file open by the user
    InitIF();
// the work file being processed
    InitWIF();
// a line or block being Copied
    InitCC();
// a line or block to be Moved
    InitMM();
// a line or block to be Overlaid
    InitOO();
// a line or block to be Repeated
    InitRR();
// line command trackers
    InitCTrackers();

}
void CLEditFrame::InitCTrackers()
{

    changesapplied = true;
    badchanges = false;
    afters = 0;
    befores = 0;
    LCcnt = 0;

    CCcnt   = 0;
    CCstart = 0;
    CCend   = 0;
    singleC = 0;  // Copy a line - need Before(s) or After(s)
    blockCC = false;  // Copy a block - need Before(s) or After(s) - can be used in a Create

    DDcnt   = 0;
    DDstart = 0;
    DDend   = 0;
    singleD = 0;  // Delete a line
    blockDD = false;  // Delete a block of lines

    singleI = 0;  // insert a single line - can have a count
    Ii = 0;           // number of lines to insert

    MMcnt   = 0;
    MMstart = 0;
    MMend   = 0;
    singleM = 0;  // Move a line - need Before(s) or After(s)
    blockMM = false;  // Move a block of lines - need Before(s) or After(s)

    OOcnt   = 0;
    OOstart = 0;
    OOend   = 0;
    singleO = 0;  // Overlay a line - needs single Move
    blockOO = false;  // Overlay a block of lines - needs a block Move

    RRcnt   = 0;
    RRstart = 0;
    RRend   = 0;
    singleR = 0;  // Repeat a line
    blockRR = false;  // Repeat a block of lines

    SRcnt    = 0;
    SRstart = 0;
    SRend   = 0;
    singleSR = 0; // right shift a line ">" - needs a number of characters (default is one space)
    SRi      = 0;          // number of characters to shift right
    blockSR  = false;  // right shift a block of lines ">>" - needs a number of characters (default is one space)

    SLcnt    = 0;
    SLstart = 0;
    SLend   = 0;
    singleSL = 0; // left shift a line "<" - needs a number of characters (default is one space)
    SLi      = 0;          // number of characters to shift left
    blockSL  = false;  // left shift a block of lines - needs a number of characters (default is one space)

    XXcnt   = 0;
    XXstart = 0;
    XXend   = 0;
    singleX = 0;  // exclude (hide) a line
    blockXX = false;  // exclude (hide) a block of lines

}
void CLEditFrame::InitScreen()
{
    LogFile << "Init Screen " << std::endl;

    for (u =0; u < 50; u++)
    {
        CL[u].Line->ChangeValue("000000");
        CL[u].Code->ChangeValue("");
    }

}
void CLEditFrame::InitUser()
{

    LogFile << "Init User Input " << std::endl;

/// this is the input from the user screen
    Input[0].Linel   = 0;
    Input[0].Linestr = "";
    Input[0].Codel   = 0;
    Input[0].Codestr = "";
    for (i = 1; i < 50; i++)
    {
        Input[i] = Input[0];
    };

    uInput.Linel   = 0;
    uInput.Linestr = "";
    uInput.Codel   = 0;
    uInput.Codestr = "";

// a line of user input from the screen
    UserLinel = 0;
    UserLinestr = "";
    UserCodel = 0;
    UserCodestr = "";

// frstl is the index to the file in process - it is where we start the display
    frstl = 1;
    lastl = 0;

}
void CLEditFrame::InitIF()
{

    LogFile << "Init Input File " << std::endl;
// this is the file that the user opened
    haveaFile = false;

    inputfile[0].IFlc = "";
    inputfile[0].IFCode = "";

    for (i = 1; i < 25000; i++)
    {
        inputfile[i] = inputfile[0];
    }

}
void CLEditFrame::InitWIF()
{

    LogFile << "Init Work File " << std::endl;
// the work file being processed - this is the impact of user input
// data will go from file input & User Input = Work input
// then back to file input
//  wfilecnt = 0;    // NO! do not set to zero!
//  oldwfilecnt = 0;    // NO! do not set to zero!

    winputfile[0].wIFlc = "";
    winputfile[0].wIFCode = "";
    for (i = 1; i < 25000; i++)
    {
        winputfile[i] = winputfile[0];
    }

}
void CLEditFrame::InitCC()
{

    LogFile << "Init Copy / Block Copy " << std::endl;
    singleC = false;  // Copy a line - need Before(s) or After(s)
    blockCC = false;  // Copy a block - need Before(s) or After(s) - can be used in a Create
// a line being copied
    haveaC = 0;
    cinputfile.cIFCode = "";
// a block of lines to be copied
    haveaCC = false;
    ccinputfile[0].cIFCode = "";
    for (i = 1; i < 2000; i++)
    {
        ccinputfile[i] = ccinputfile[0];
    }
}
void CLEditFrame::InitMM()
{

    LogFile << "Init Move / Block Move " << std::endl;
    singleM = false;  // Move a line - need Before(s) or After(s)
    blockMM = false;  // Move a block of lines - need Before(s) or After(s)
// a line to be moved
    haveaM = 0;
    minputfile.mIFCode = "";
// a block of lines to be moved
    haveaMM = false;
    mminputfile[0].mIFCode = "";
    for (i = 1; i < 2000; i++)
    {
        mminputfile[i] = mminputfile[0];
    }

}
void CLEditFrame::InitOO()
{

    LogFile << "Init Overlay / Block Overlay " << std::endl;
    singleO = false;  // Overlay a line - needs single Move
    blockOO = false;  // Overlay a block of lines - needs a block Move
// a line to be overlaid
    haveaO = 0;
    oinputfile.oIFCode = "";
// a block of lines to be overlaid
    haveaOO = false;
    ooinputfile[0].oIFCode = "";
    for (i = 1; i < 2000; i++)
    {
        ooinputfile[i] = ooinputfile[0];
    }

}
void CLEditFrame::InitRR()
{

    LogFile << "Init Repeat / Block Repeat " << std::endl;
    singleR = false;  // Repeat a line
    blockRR = false;  // Repeat a block of lines
// a line to be Repeated
    haveaR = 0;
    rinputfile.rIFCode = "";
// a block of lines to be Repeated
    haveaRR = false;
    rrinputfile[0].rIFCode = "";
    for (i = 1; i < 2000; i++)
    {
        rrinputfile[i] = rrinputfile[0];
    }

}
void CLEditFrame::CreateControls()
{

    LogFile << "Create Controls " << std::endl;

    wxPanel * Panel = new wxPanel(this);

    Panel->Bind(wxEVT_CHAR_HOOK, & CLEditFrame::OnKeyDown, this);

    Command = new wxTextCtrl(Panel
                             ,wxID_ANY
                             ,"enter command here"
                             ,wxPoint(1,1)      // l-r,t-b
                             ,wxSize(1670,20)  //w,h
                             ,wxBORDER_NONE
                            );

    Command->SetMaxLength(200);

    Apply = new wxButton(Panel
                         ,wxID_ANY
                         ,"Apply"
                         ,wxPoint(1620,1)
                         ,wxSize(50,20)
                         ,wxBORDER_NONE
                        );

    Apply->Bind(wxEVT_BUTTON, & CLEditFrame::OnApplyClicked, this);

    ypos = 20;
    for (u = 0; u < 50; u++)
    {
        CL[u].Line = new wxTextCtrl(Panel,wxID_ANY,"000000",wxPoint(1,ypos),wxSize(60,20),wxBORDER_NONE);
        CL[u].Line->SetMaxLength(6);
        CL[u].Code = new wxTextCtrl(Panel,wxID_ANY,"",wxPoint(61,ypos),wxSize(1610,20),wxBORDER_NONE);
        CL[u].Code->SetMaxLength(200);
        ypos += 20;
    }

    CreateStatusBar();

    wxLogStatus("Hello ");

    Return = true;

}
