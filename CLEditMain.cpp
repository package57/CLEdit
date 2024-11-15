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
        case WXK_NUMPAD_ENTER:
        case WXK_RETURN:
            ProcessScreen();
            LoadScreen();
            break;
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
//create a file - or stage to a table - from a block copy
    if (PrimaryCommand == "create")
    {
        Create();
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
        CopyFile();  // from a to b or into after or before
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
            Commandstr[i] = tolower(Commandstr[i]);
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

    LogFile << "Create " << std::endl;   // need a block copy and file name

    if  (FirstParameter == "")
    {
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " file name to Create missing");
        goto ExitCreate;
    }

    InitCC();

    LookForLCCC();

    CaptureCC();

    if  (CCrows == 0)
    {
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " file to Create missing - need a block copy ");
        goto ExitCreate;
    }

    CurrentFile = FirstParameter;

    if (SecondParameter == "")
    {
        CreateFile();
    }
    else
    {
        CreateTable();
    }

ExitCreate:

    WipeCommand();

}
void CLEditFrame::CreateFile()
{

    LogFile << "Create File" << std::endl;   // need a block copy and file name

    InitCF();

    for (i = 0; i < CCrows; i++)
    {
        SetEndl();
        CF.inputfile[i].IFCode = ccinputfile[i].cIFCode;
    }

    CF.fileoname = CurrentFile;
    CF.fileoreccnt = CCrows;
    CLEditCFrc = CF.savefile(CF.fileoname);

    if  (CLEditCFrc != 0)
    {
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " Create file error");
        goto ExitCreateFile;
    }

    LoadScreen();   //always from work input

    wxLogStatus(PrimaryCommand + " " + FirstParameter + " applied");

ExitCreateFile:

    WipeCommand();

}
void CLEditFrame::CreateTable()
{
    LogFile << "Create Table" << std::endl;   // need a block copy and file name

    InitDB();

    for (i = 0; i < CCrows; i++)
    {
        SetEndl();
        DB.inputfile[i].IFCode = ccinputfile[i].cIFCode;
    }

    DB.DataBase = FirstParameter;

    DB.TableName = SecondParameter;
// the next three lines are the equivalent of an "open"
//create a driver object
    DB.Driver();
//create a connection object
    DB.Connect();
//create a statement object
    DB.Statement();

    DB.rowcnt = CCrows;

    DB.ToStage();
// "close" the database
    DB.Free();

    LoadScreen();   //always from work input

    wxLogStatus(PrimaryCommand + " " + FirstParameter + SecondParameter + " applied");

    WipeCommand();

}
void CLEditFrame::SaveFile()
{
    LogFile << "Save File " << std::endl;

    if (CurrentFile == "")  // means the file is on the screen - wasn't opened first
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

    for (i = 0; i < 25000; i++)
    {
        inputfile[i].IFlc   = "000000";
        winputfile[i].wIFlc = "000000";
    }

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
// import the file
    CLEditCFrc = CF.openfile(CF.fileiname);

    if  (CLEditCFrc != 0)
    {
        CLEditCFmsg();
        wfilecnt = 0;
        goto ExitOpenFile;
    }

    InitIF();

    InitWIF();

    wfilecnt = CF.fileireccnt;

    if (wfilecnt > 23000)
    {
        FileSizeError = true;
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " file too big ");
    }
    else
    {
        haveaFile = true;
        for (i = 0; i < CF.fileireccnt; i++)
        {
            inputfile[i].IFlc   = "000000";
            inputfile[i].IFCode   = CF.inputfile[i].IFCode;

            winputfile[i].wIFlc   = "000000";
            winputfile[i].wIFCode = CF.inputfile[i].IFCode;

            GetEndl();
        }
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " applied");
    }

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
// get the file from a table :)

    LogFile << "from stage " << std::endl;

    InitScreen();

    if  (FirstParameter == "")
    {
        wxLogStatus(PrimaryCommand + " need Database name ");
        return;
    }

    if  (SecondParameter == "")
    {
        wxLogStatus(PrimaryCommand + " need TableName ");
        return;
    }

    DB.DataBase = FirstParameter;
    DB.TableName = SecondParameter;

// the next three lines are the equivalent of an "open"
//create a driver object
    DB.Driver();
//create a connection object
    DB.Connect();
//create a statement object
    DB.Statement();

    rowcnt = DB.Cursor();
    LogFile << "rows " << rowcnt << std::endl;

    if (rowcnt > 23000)
    {
        FileSizeError = true;
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " file too big ");
        haveaFile = false;
        return;
    }
    else
    {
        if  (rowcnt > 0)
        {
            haveaFile = true;
            wfilecnt = rowcnt;
            InitIF();
            InitWIF();
            DB.FromStage();
            for (i = 0; i < rowcnt; i++)
            {
                inputfile[i].IFCode = DB.inputfile[i].IFCode;
                winputfile[i].wIFlc   = "000000";
                winputfile[i].wIFCode = DB.inputfile[i].IFCode;
                GetEndl();
            }
            wxLogStatus(PrimaryCommand + " " + FirstParameter + " applied ");
        }
        else
        {
            haveaFile = false;
            wfilecnt = 0;
            wxLogStatus(PrimaryCommand + " " + FirstParameter + " not found");
        }
    }
// "close" the database
    DB.Free();

    frstl = 1;

    LoadScreen();

    WipeCommand();

}
void CLEditFrame::ToStage()
{
// save the file to a Table :)

    LogFile << "To Stage " << std::endl;

    if  (FirstParameter == "")
    {
        wxLogStatus(PrimaryCommand + " need Database name ");
        return;
    }

    if  (SecondParameter == "")
    {
        wxLogStatus(PrimaryCommand + " need TableName ");
        return;
    }

    if (wfilecnt == 0)
    {
        wxLogStatus(PrimaryCommand + " no data to stage  ");
        return;
    }

    DB.DataBase = FirstParameter;
    DB.TableName = SecondParameter;

// the next three lines are the equivalent of an "open"
//create a driver object
    DB.Driver();
//create a connection object
    DB.Connect();
//create a statement object
    DB.Statement();

    if (wfilecnt > 23000)
    {
        FileSizeError = true;
        wxLogStatus(PrimaryCommand + " file too big ");
        return;
    }

    InitDB();

    for (i = 0; i < wfilecnt; i++)
    {
        SetEndl();
        DB.inputfile[i].IFCode = inputfile[i].IFCode;
    }

    DB.rowcnt = wfilecnt;

    DB.ToStage();

// "close" the database
    DB.Free();

    LoadScreen();

    wxLogStatus(PrimaryCommand + FirstParameter + SecondParameter + " applied");

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
        if (winputfile[u].wIFlc == "000000")
        {
            prettystr = ToString(u);
            CL[i].Line->ChangeValue(prettystr);
        }
        else ///don't wipe the command on the line
        {
            CL[i].Line->ChangeValue(winputfile[u].wIFlc);
        }
        CL[i].Code->ChangeValue(winputfile[u].wIFCode);
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
// capture all code where ever the block command causes the file size to change: c/CC d/DD m/MM o/OO r/RR
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
        InitCTrackers();
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
        wxLogStatus("applied");
    }

// XX
// X

}
void CLEditFrame::ReadScreen()
{

    LogFile << "Read Screen " << std::endl;
// user input
    InitUser();
// capture everything from the text controls - Line Commands and Code

    for (u = 0; u < 50; u++)
    {
        UserLinel   = CL[u].Line->GetLineLength(0);
        UserLinestr = CL[u].Line->GetLineText(0);
        UserCodel   = CL[u].Code->GetLineLength(0);
        UserCodestr = CL[u].Code->GetLineText(0);
        Input[u].Linel = UserLinel;
        WhatCommand();
        Input[u].Codel = UserCodel;
        Input[u].Codestr = UserCodestr;
        if (!haveaFile)   // means we're starting from a blank screen not an open, from stage or copy after
        {
            wfilecnt = u;
            wfilecnt++;    // off by one eh
        }
    }

    if (!haveaFile)   // means we're starting from a blank screen not an open, from stage or copy after
    {
        haveaFile = true;
        frstl = 1;
    }

}
void CLEditFrame::WhatCommand()
{

    if (u == 0)
    {
        LogFile << "WhatCommand " << std::endl;
    }

// uppercase
    UserLinestr[0] = toupper(UserLinestr[0]);
    UserLinestr[1] = toupper(UserLinestr[1]);

// look for line commands in the first position only
    if (UserLinestr[0] == 'A')
    {
        WhatCommandA(); return;
    }

    if (UserLinestr[0] == 'B')
    {
        WhatCommandB(); return;
    }

    if (UserLinestr[0] == 'C')
    {
        WhatCommandCC(); return;
    }

    if (UserLinestr[0] == 'D')
    {
        WhatCommandDD(); return;
    }

    if (UserLinestr[0] == 'M')
    {
        WhatCommandMM(); return;
    }

    if (UserLinestr[0] == 'O')
    {
        WhatCommandOO(); return;
    }

    if (UserLinestr[0] == 'R')
    {
        WhatCommandRR(); return;
    }

    if (UserLinestr[0] == '>')
    {
        WhatCommandSR(); return;
    }

    if (UserLinestr[0] == '<')
    {
        WhatCommandSL(); return;
    }

    if (UserLinestr[0] == 'X')
    {
        WhatCommandXX(); return;
    }

    if (UserLinestr[0] == 'I')
    {
        WhatCommandI(); return;
    }

    Input[u].Linestr = UserLinestr;

}
void CLEditFrame::WhatCommandA()
{

    LogFile << "WhatCommand A " << std::endl;

    Input[u].Linestr = "A";

    afters++;

}
void CLEditFrame::WhatCommandB()
{

    LogFile << "WhatCommand B " << std::endl;

    Input[u].Linestr = "B";

    befores++;

}
void CLEditFrame::WhatCommandCC()
{

    LogFile << "WhatCommand CC " << std::endl;

    if  (UserLinel > 1)
    {
        if (UserLinestr[1] == 'C')
        {
            Input[u].Linestr = "CC";
            blockCC = true;
        }
        else
        {
            return;
        }
    }
    else
    {
        singleC++;
        haveaC = u;
        Input[u].Linestr = "C";
    }

}
void CLEditFrame::WhatCommandDD()
{

    LogFile << "WhatCommand DD " << std::endl;

    if  (UserLinel > 1)
    {
        if (UserLinestr[1] == 'D')
        {
            Input[u].Linestr = "DD";
            blockDD = true;
        }
        else
        {
            return;
        }
    }
    else
    {
        singleD++;
        Input[u].Linestr = "D";
    }

}
void CLEditFrame::WhatCommandMM()
{

    LogFile << "WhatCommand MM " << std::endl;

    if  (UserLinel > 1)
    {
        if (UserLinestr[1] == 'M')
        {
            Input[u].Linestr = "MM";
            blockMM = true;
        }
        else
        {
            return;
        }
    }
    else
    {
        singleM++;
        haveaM = u;
        Input[u].Linestr = "M";
    }

}
void CLEditFrame::WhatCommandOO()
{

    LogFile << "WhatCommand OO " << std::endl;

    if  (UserLinel > 1)
    {
        if (UserLinestr[1] == 'O')
        {
            Input[u].Linestr = "OO";
            blockOO = true;
        }
        else
        {
            return;
        }
    }
    else
    {
        singleO++;
        haveaO = u;
        Input[u].Linestr = "O";
    }

}
void CLEditFrame::WhatCommandRR()
{

    LogFile << "WhatCommand RR " << std::endl;

    if  (UserLinel > 1)
    {
        if (UserLinestr[1] == 'R')
        {
            Input[u].Linestr = "RR";
            blockRR = true;
        }
        else
        {
            return;
        }
    }
    else
    {
        singleR++;
        haveaR = u;
        Input[u].Linestr = "R";
    }

}
void CLEditFrame::WhatCommandSR()
{

    LogFile << "WhatCommand >> " << std::endl;

//        int  SRi;      // number of characters to shift right

    if  (UserLinel > 1)
    {
        if (UserLinestr[1] == '>')
        {
            Input[u].Linestr = ">>";
            blockSR = true;
        }
        else
        {
            return;
        }
    }
    else
    {
        singleSR++;
        Input[u].Linestr = ">";
    }

}
void CLEditFrame::WhatCommandSL()
{

    LogFile << "WhatCommand << " << std::endl;

//   int  SLi;      // number of characters to shift left

    if  (UserLinel > 1)
    {
        if (UserLinestr[1] == '<')
        {
            Input[u].Linestr = "<<";
            blockSL = true;
        }
        else
        {
            return;
        }
    }
    else
    {
        singleSL++;
        Input[u].Linestr = "<";
    }

}
void CLEditFrame::WhatCommandXX()
{

    LogFile << "WhatCommand XX " << std::endl;

    if  (UserLinel > 1)
    {
        if (UserLinestr[1] == 'X')
        {
            Input[u].Linestr = "XX";
            blockXX = true;
        }
        else
        {
            return;
        }
    }
    else
    {
        singleX++;
        Input[u].Linestr = "X";
    }

}
void CLEditFrame::WhatCommandI()
{

    LogFile << "WhatCommand I " << std::endl;

    singleI++;
    Input[u].Linestr = "I";

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
        LCcnt = singleC + singleM + singleO + singleR;  // these change the size of the file
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

// are there any line commands to apply?
    LCcnt = CCcnt + DDcnt + MMcnt + OOcnt + RRcnt + SRcnt + SLcnt + XXcnt;
    LCcnt = LCcnt + singleC + singleD + singleM + singleO + singleR + singleSR + singleSL + singleX + singleI;

    if (LCcnt == 0)
    {
        changesapplied = false;
        return;
    }

    ApplyBlockCommands();

}
void CLEditFrame::ApplyBlockCommands()
{

    LogFile << "ApplyBlockCommands " << std::endl;

// insert the lines to be copied where ever there is an After or a Before
// makes input file bigger
    if (CCcnt == 2
    ||  singleC > 0)
    {
        ApplyCC();
        return;
    }

// makes input file smaller
    if (DDcnt == 2
    ||  singleD > 0)
    {
        ApplyDD();
        return;
    }

// input file stays the same size - Move after or before
    if  (MMcnt == 2
    ||  singleM > 0)
    {
        if (OOcnt == 0
        &&  singleO == 0)
        {
            ApplyMM();  // this is a simple Move
            return;
        }
    }
// input file becomes smaller by the size of the Overlay
    if (OOcnt == 2
    ||  singleO > 0)
    {
        if  (MMcnt == 2
        ||   singleM > 0)
        {
            ApplyOO();      // this is the Move/Overlay
            return;
        }
    }

// makes input file bigger
    if (RRcnt == 2
    ||  singleR > 0)
    {
        ApplyRR();
        return;
    }

// no change to input file size
    if (SRcnt == 2
    ||  singleSR > 0)
    {
        ApplySR();
        return;
    }

// no change to input file size
    if (SLcnt == 2
    ||  singleSL > 0)
    {
        ApplySL();
        return;
    }

// no change to input file size
// changes what can bee seen on the screen
    if  (XXcnt == 2
    ||  singleX > 0)
    {
        ApplyXX();
        return;
    }

// make the file bigger
    if (singleI > 0)
    {
        ApplyI();
        return;
    }

}
void CLEditFrame::LCReasonability()
{

    LogFile << "LCReasonability " << std::endl;
// multiple blocks and or multiple types os blocks are ambiguous
// especially ones that cause file size changes

    LCReasonabilityBlock();

    if  (badchanges)
    {
        return;
    }

    LCReasonabilityLine();

    if  (badchanges)
    {
        return;
    }

    LCReasonabilityOverall();

    if  (badchanges)
    {
        return;
    }

}
void CLEditFrame::LCReasonabilityBlock()
{

    LogFile << "LC Reasonability Block" << std::endl;

    LCcnt = CCcnt + DDcnt + MMcnt + RRcnt;

    if (LCcnt > 2)
    {
        wxLogStatus("Block command ambiguous ");
        badchanges = true;
        return;
    }
    LCcnt = MMcnt + OOcnt;

    if (LCcnt > 4)
    {
        wxLogStatus("Block command ambiguous ");
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
            wxLogStatus("Block Move missing for overlay ");
            badchanges = true;
            return;
        }
    }

    if (blockCC)
    {
        if (afters == 0
        &&  befores == 0)
        {
            wxLogStatus("Block Copy command missing Before or After location(s) ");
            badchanges = true;
            return;
        }
    }

    if (blockMM
    &&  !blockOO)  // not an overlay
    {
        LCReasonabilityBlockMM();
        if (badchanges)
        {
            return;
        }
    }

    if (blockOO)
    {
        if (afters == 0
        &&  befores == 0)
        {
            badchanges = false;
        }
        else
        {
            wxLogStatus("Block Overlay command can't use Before or After location(s)");
            badchanges = true;
            return;
        }
    }

    if (blockMM
    &&  blockOO)  // is an overlay
    {
        if (MMrows == OOrows)
        {
            badchanges = false;
        }
        else
        {
            wxLogStatus("Block Move/Overlay block sizes not the same");
            badchanges = true;
            return;
        }
    }

    if (blockRR)
    {
        if (afters > 0
        ||  befores > 0)
        {
            wxLogStatus("Block Repeat command can't use Before or After location(s) ");
            badchanges = true;
            return;
        }
    }

    if (blockXX)
    {
        if (afters == 0
        &&  befores == 0)
        {
            badchanges = false;
        }
        else
        {
            wxLogStatus("Block Exclude command can't use Before or After location(s) ");
            badchanges = true;
            return;
        }
    }

    if (blockSR)
    {
        if (afters == 0
        &&  befores == 0)
        {
            badchanges = false;
        }
        else
        {
            wxLogStatus("Block Shift Right command can't use Before or After location(s) ");
            badchanges = true;
            return;
        }
    }

    if (blockSL)
    {
        if (afters == 0
        &&  befores == 0)
        {
            badchanges = false;
        }
        else
        {
            wxLogStatus("Block Shift Left can't use Before or After location(s) ");
            badchanges = true;
            return;
        }
    }

}
void CLEditFrame::LCReasonabilityBlockMM()
{

    if (afters == 0
    &&  befores == 0)
    {
        wxLogStatus("Block Move command missing a Before or After location ");
        badchanges = true;
        return;
    }

    if (afters == 1)
    {
        if  (befores == 0)
        {
            badchanges = false;
        }
        else
        {
            wxLogStatus("Block Move command with Before and After location ");
            badchanges = true;
            return;
        }
    }

    if (befores == 1)
    {
        if  (afters == 0)
        {
            badchanges = false;
        }
        else
        {
            wxLogStatus("Block Move command with Before and After location ");
            badchanges = true;
            return;
        }
    }

}
void CLEditFrame::LCReasonabilityLine()
{

    LogFile << "LC Reasonability Line " << std::endl;

    LCcnt = singleC + singleD + singleM + singleR;

    if (LCcnt > 1)
    {
        wxLogStatus("line commands ambiguous ");
        badchanges = true;
        return;
    }

    if (LCcnt > 0
    &&  singleI > 0)
    {
        wxLogStatus("line commands ambiguous ");
        badchanges = true;
        return;
    }

    LCcnt = singleM + singleO;

    if (LCcnt > 2)
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
            wxLogStatus("line Move missing for line Overlay ");
            badchanges = true;
            return;
        }
    }

    if (singleC > 1)
    {
        wxLogStatus("Copy line command ambiguous ");
        badchanges = true;
        return;
    }

    if (singleC == 1)
    {
        if (afters == 0
        &&  befores == 0)
        {
            wxLogStatus("Copy line command missing Before or After loaction(s) ");
            badchanges = true;
            return;
        }
    }

    if (singleM > 1)
    {
        wxLogStatus("Move line command ambiguous ");
        badchanges = true;
        return;
    }

    if (singleO > 1)
    {
        wxLogStatus("Overlay line command ambiguous ");
        badchanges = true;
        return;
    }

    if (singleR > 0)
    {
        if (afters > 0
        ||  befores > 0)
        {
            wxLogStatus("Line Repeat command can't use Before or After location(s) ");
            badchanges = true;
            return;
        }
    }

}
void CLEditFrame::LCReasonabilityOverall()
{

    LogFile << "LC Reasonability Overall " << std::endl;

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
            wxLogStatus("line commands ambiguous ");
            badchanges = true;
            return;
        }
    }

}
void CLEditFrame::LookForLC()
{

    LogFile << "Look for LC " << std::endl;

    if (wfilecnt == 0)
    {
        return;
    }

    LookForLCCC();

    if (badchanges)
    {
        return;
    }

    LookForLCDD();

    if (badchanges)
    {
        return;
    }

    LookForLCMM();

    if (badchanges)
    {
        return;
    }

    LookForLCOO();

    if (badchanges)
    {
        return;
    }

    LookForLCRR();

    if (badchanges)
    {
        return;
    }

    LookForLCSR();

    if (badchanges)
    {
        return;
    }

    LookForLCSL();

    if (badchanges)
    {
        return;
    }

    LookForLCXX();

    if (badchanges)
    {
        return;
    }

}
void CLEditFrame::LookForLCCC()
{

    LogFile << "Look for CC " << std::endl;

    CCcnt = 0;
    CCstart = 9999;
    for (i = 0; i < wfilecnt; i++)
    {
        LookForCC();
    }

    if  (CCcnt > 2)
    {
        wxLogStatus("multiple Block Copy");
        badchanges = true;
        return;
    }

    if  (CCcnt == 1)
    {
        wxLogStatus("missing Block Copy pair");
        badchanges = true;
        return;
    }

}
void CLEditFrame::LookForLCDD()
{

    LogFile << "Look for DD " << std::endl;
    DDcnt = 0;
    DDstart = 9999;
    for (i = 0; i < wfilecnt; i++)
    {
        LookForDD();
    }

    if  (DDcnt > 2)
    {
        wxLogStatus("multiple Block Delete");
        badchanges = true;
        return;
    }

    if  (DDcnt == 1)
    {
        wxLogStatus("missing Block Delete pair");
        badchanges = true;
        return;
    }

}
void CLEditFrame::LookForLCMM()
{

    LogFile << "Look for MM " << std::endl;

    MMcnt = 0;
    MMstart = 9999;
    for (i = 0; i < wfilecnt; i++)
    {
        LookForMM();
    }

    if  (MMcnt > 2)
    {
        wxLogStatus("multiple Block Move");
        badchanges = true;
        return;
    }

    if  (MMcnt == 1)
    {
        wxLogStatus("missing Block Move pair");
        badchanges = true;
        return;
    }

}
void CLEditFrame::LookForLCOO()
{

    LogFile << "Look for OO " << std::endl;

    OOcnt = 0;
    OOstart = 9999;
    for (i = 0; i < wfilecnt; i++)
    {
        LookForOO();
    }

    if  (OOcnt > 2)
    {
        wxLogStatus("multiple Block Overlay");
        badchanges = true;
        return;
    }

    if  (OOcnt == 1)
    {
        wxLogStatus("missing Block Overlay pair");
        return;
    }

}
void CLEditFrame::LookForLCRR()
{

    LogFile << "Look for RR " << std::endl;

    RRcnt = 0;
    RRstart = 9999;
    for (i = 0; i < wfilecnt; i++)
    {
        LookForRR();
    }

    if  (RRcnt > 2)
    {
        wxLogStatus("multiple Block Repeat");
        badchanges = true;
        return;
    }

    if  (RRcnt == 1)
    {
        wxLogStatus("missing Block Repeat pair");
        badchanges = true;
        return;
    }

}
void CLEditFrame::LookForLCSR()
{
    LogFile << "Look for >> " << std::endl;

    SRcnt = 0;
    SRstart = 9999;
    for (i = 0; i < wfilecnt; i++)
    {
        LookForSR();
    }

    if  (SRcnt > 2)
    {
        wxLogStatus("multiple Block Shift Right");
        badchanges = true;
        return;
    }

    if  (SRcnt == 1)
    {
        wxLogStatus("missing Block Shift Right pair");
        badchanges = true;
        return;
    }

}
void CLEditFrame::LookForLCSL()
{

    LogFile << "Look for << " << std::endl;

    SLcnt = 0;
    SLstart = 9999;
    for (i = 0; i < wfilecnt; i++)
    {
        LookForSL();
    }

    if  (SLcnt > 2)
    {
        wxLogStatus("multiple Block Shift Left");
        badchanges = true;
        return;
    }

    if  (SLcnt == 1)
    {
        wxLogStatus("missing Block Shift Left pair");
        badchanges = true;
        return;
    }

}
void CLEditFrame::LookForLCXX()
{

    LogFile << "Look for XX " << std::endl;

    XXcnt = 0;
    XXstart = 9999;
    for (i = 0; i < wfilecnt; i++)
    {
        LookForXX();
    }

    if  (XXcnt > 2)
    {
        wxLogStatus("multiple Block Exclude");
        badchanges = true;
        return;
    }

    if  (XXcnt == 1)
    {
        wxLogStatus("missing Block Exclude pair");
        badchanges = true;
        return;
    }

}
void CLEditFrame::CaptureLC()
{

    LogFile << "Capture LC " << std::endl;

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

    if (RRcnt == 2)
    {
        CaptureRR();
    }

}
void CLEditFrame::LookForCC()
{

//  LogFile << "Look for CC " << std::endl

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
        for (i = CCstart; i <= CCend; i++)
        {
            ccinputfile[l].cIFCode = winputfile[i].wIFCode;
            CCrows++;
            l++;
        }
    }

}
void CLEditFrame::LookForDD()
{

//  LogFile << "Look for DD " << std::endl;

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

void CLEditFrame::LookForMM()
{

//  LogFile << "Look for MM " << std::endl;

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
        for (i = MMstart; i <= MMend; i++)
        {
            mminputfile[l].mIFCode = winputfile[i].wIFCode;
            MMrows++;
            l++;
        }
    }

}
void CLEditFrame::LookForOO()
{

//  LogFile << "Look for OO " << std::endl;

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
        for (i = OOstart; i <= OOend; i++)
        {
            ooinputfile[l].oIFCode = winputfile[i].wIFCode;
            OOrows++;
            l++;
        }
    }

}
void CLEditFrame::LookForRR()
{

//  LogFile << "Look for RR " << std::endl;

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

//  if (singleR > 0)  no need to capture Repeated lines because they repeat in place not before or after any line

    l = 0;
    for (i = RRstart; i <= RRend; i++)
    {
        rrinputfile[l].rIFCode = winputfile[i].wIFCode;
        RRrows++;
        l++;
    }

}
void CLEditFrame::LookForSR()
{

//  LogFile << "Look for >> " << std::endl;

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
void CLEditFrame::LookForSL()
{

//  LogFile << "Look for << " << std::endl;

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
void CLEditFrame::LookForXX()
{

//  LogFile << "Look for XX " << std::endl;

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
void CLEditFrame::ApplyCC()
{
// increases the file size
// apply the copied line - or the block of copied lines
// from input to work input
// where ever there is an After or Before line command

    LogFile << "Apply CC " << std::endl;

    InitWIF();

    oldwfilecnt = wfilecnt;
    wi = 0; // this is the index to the soon to be larger work file
    for (i = 0; i < oldwfilecnt; i++)
    {
        if (singleC > 0) // this is the one and only one line to Copy to After(s) and Before(s) locations
        {
            LineCopy();  // this is a Line Copy
        }
        else
        {
            BlockCopy();  // this is a Block Copy
        }
        if (wfilecnt > 23000)
        {
            FileSizeError = true;
            break;
        }
    }

// refresh input with larger work input
    RefreshInput();

    changesapplied = true;

    if (singleC > 0) // this is the one and only one line to copy After(s) and Before(s) locations
    {
        wxLogStatus("line Copy applied ");
//      wxLogStatus("line Copy applied " + afters + " + " + befores + " places");
    }
    else // this is a block delete
    {
        wxLogStatus("Block Copy applied ");
//      wxLogStatus("Block Copy applied " + afters + " + " + befores + " places");
    }

}
void CLEditFrame::LineCopy()
{

    if (inputfile[i].IFlc == "A")
    {
        // copy the current line as is
        CopyTheLine();
        // add the Copy Line - after
        winputfile[wi].wIFlc   = "000000";
        winputfile[wi].wIFCode = cinputfile.cIFCode;
        wfilecnt++;   // increase the file size
        wi++;
    }
    else
    {
        if (inputfile[i].IFlc == "B")
        {
            // add the Copy Line - before
            winputfile[wi].wIFlc   = "000000";
            winputfile[wi].wIFCode = cinputfile.cIFCode;
            wfilecnt++; // increase the file size
            wi++;
            // copy the current line as is from input to work
            CopyTheLine();
        }
        else
        {
            // copy the current line as is from input to work
            CopyTheLine();
        }
    }

}
void CLEditFrame::BlockCopy()
{

    if (inputfile[i].IFlc == "A")
    {
        // copy the current line as is from input to work
        CopyTheLine();
        // add the Block of Copy lines - after - in a loop
        for (l = 0; l < CCrows; l++)
        {
            winputfile[wi].wIFlc   = "000000";
            winputfile[wi].wIFCode = ccinputfile[l].cIFCode;
            wfilecnt++; // increase the file size
            wi++;
        }
    }
    else
    {
        if (inputfile[i].IFlc == "B")
        {
            // add the Block Copy - before - in a loop
            for (l = 0; l < CCrows; l++)
            {
                winputfile[wi].wIFlc   = "000000";
                winputfile[wi].wIFCode = ccinputfile[l].cIFCode;
                wfilecnt++; // increase the file size
                wi++;
            }
            // copy the current line as is from input to work
            CopyTheLine();
        }
        else
        {
            // copy the current line as is from input to work
            CopyTheLine();
        }
    }

}
void CLEditFrame::ApplyDD()
{
// reduces the file size
    LogFile << "Apply DD " << std::endl;

    InitWIF();

    oldwfilecnt = wfilecnt;
    wi = 0; // this is the index to the soon to be smaller work file
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

// refresh input with smaller work input
    RefreshInput();

    changesapplied = true;

    if (singleD > 0) // this is the number of line deletes
    {
        wxLogStatus("Line Delete(s) applied ");
    }
    else // this is a block delete
    {
        wxLogStatus("Block Delete applied ");
    }

}
void CLEditFrame::LineDelete()
{

    if (inputfile[i].IFlc == "D")
    {
        wfilecnt--;  // skip the record - decrease the file size
    }
    else
    {
        // copy the current line as is from input to work
        CopyTheLine();
    }

}
void CLEditFrame::BlockDelete()
{

    if (i >= DDstart
    &&  i <= DDend)
    {
        wfilecnt--;  // skip the record - decrease the file size
    }
    else
    {
        // copy the current line as is from input to work
        CopyTheLine();
    }

}
void CLEditFrame::ApplyMM()
{
// the file will be the same size
    LogFile << "Apply MM " << std::endl;

    InitWIF();

    oldwfilecnt = wfilecnt;
    wi = 0; // this is the index to the work file
    for (i = 0; i < oldwfilecnt; i++)
    {
        if (singleM > 0) // this is the one and only one line to Move to the After or Before location
        {
            LineMove();  // like a line copy
        }
        else // this is a Block Move
        {
            BlockMove();  // like a block copy
        }
    }
// refresh input with work input
    RefreshInput();

    changesapplied = true;

    if (singleM > 0) // this is the Line Move
    {
        wxLogStatus("Line Move applied ");
    }
    else // this is a Block Move
    {
        wxLogStatus("Block Move applied ");
    }

}
void CLEditFrame::LineMove()
{

    if (inputfile[i].IFlc == "A")
    {
        // copy the current line as is from input to work
        CopyTheLine();
        // add the Move Line - after
        winputfile[wi].wIFlc   = "000000";
        winputfile[wi].wIFCode = minputfile.mIFCode;
        wi++;
    }
    else
    {
        if (inputfile[i].IFlc == "B")
        {
            // add the Move Line - before
            winputfile[wi].wIFlc   = "000000";
            winputfile[wi].wIFCode = minputfile.mIFCode;
            wi++;
            // copy the current line as is from input to work
            CopyTheLine();
        }
        else
        {
            if (inputfile[i].IFlc == "M")
            {
                return; // skip it
            }
            else
            {
                // copy the current line as is from input to work
                CopyTheLine();
            }
        }
    }

}
void CLEditFrame::BlockMove()
{

    if (inputfile[i].IFlc == "A")
    {
        // copy the current line as is from input to work
        CopyTheLine();
        // add the Move Block - after - in a loop
        for (l = 0; l < MMrows; l++)
        {
            winputfile[wi].wIFlc   = "000000";
            winputfile[wi].wIFCode = mminputfile[l].mIFCode;
            wi++;
        }
    }
    else
    {
        if (inputfile[i].IFlc == "B")
        {
            // add the Move Block - before - in a loop
            for (l = 0; l < MMrows; l++)
            {
                winputfile[wi].wIFlc   = "000000";
                winputfile[wi].wIFCode = mminputfile[l].mIFCode;
                wi++;
            }
            // copy the current line as is from input to work
            CopyTheLine();
        }
        else
        {
            if (i >= MMstart
            &&  i <= MMend)
            {
                return;  //skip it
            }
            else
            {
                // copy the current line as is from input to work
                CopyTheLine();
            }
        }
    }

}
void CLEditFrame::ApplyOO()
{
// this will make the file smaller

    LogFile << "Apply OO " << std::endl;

    if (singleO == 1)
    {
// move everything from the Move Line into the Overlay Line where ever there is a space
        LineOver();
    }
    else
    {
// move everything from the Move block into the Overlay block where ever there is a space
        BlockOver();
    }

    InitWIF();

    oldwfilecnt = wfilecnt;
    wi = 0; // this is the index to the new smaller work file
    pos = 0; // this is the index to the Overlay Block
    for (i = 0; i < oldwfilecnt; i++)
    {
        if (singleM > 0) // this is the one and only one line to Move
        {
            // push the Overlay Line into work input and pull the Move Line
            LinePushOver();  // like a line copy
        }
        else // this is a Block Move
        {
            // push the Overlay block into work input and pull the Move Block
            BlockPushOver();  // like a block copy
        }
    }

// refresh input with smaller work input
    RefreshInput();

    changesapplied = true;

    if (singleM > 0) // this is the Line Move
    {
        wxLogStatus("Line Move applied ");
    }
    else // this is a Block Move
    {
        wxLogStatus("Block Move applied ");
    }

}
void CLEditFrame::LineOver()
{
// byte by byte where there is a blank

    Mstrl = minputfile.mIFCode.length();

    if (Mstrl == 0) // this means the Move Line is blank, do nothing to the Overlay line
    {
        return;
    }

    Ostrl = oinputfile.oIFCode.length();

    if (Ostrl == 0) // this means the Overlay line is blank - clobber it
    {
        oinputfile.oIFCode = minputfile.mIFCode;
        return;
    }

    if (Mstrl <= Ostrl)
    {
        for (pos = 0; pos < Mstrl; pos++)
        {
            if (oinputfile.oIFCode[pos] == ' ')     // overlay the blanks
            {
                oinputfile.oIFCode[pos] = minputfile.mIFCode[pos];
            }
        }
        return;
    }

//Mstrl is bigger than Ostrl - get what you have
    for (pos = 0; pos < Ostrl; pos++)
    {
        posp1 = pos + 1;
        if (oinputfile.oIFCode[pos] == ' ')     // blank
        {
            oinputfile.oIFCode[pos] = minputfile.mIFCode[pos];
        }
    }

//Mstrl is bigger than Ostrl - pad the rest
    for (pos = posp1; pos < Mstrl; pos++)
    {
        oinputfile.oIFCode += minputfile.mIFCode[pos];
    }

}
void CLEditFrame::BlockOver()
{

    for (l = 0; l < MMrows; l++)
    {
        BlockMoveOver();
    }

}
void CLEditFrame::BlockMoveOver()
{
// byte by byte where there is a blank

    Mstrl = mminputfile[l].mIFCode.length();

    if (Mstrl == 0) // this means the Move Line is blank, do nothing to the Overlay line
    {
        return;
    }

    Ostrl = ooinputfile[l].oIFCode.length();

    if (Ostrl == 0) // this means the Overlay line is blank - clobber it
    {
        ooinputfile[l].oIFCode = mminputfile[l].mIFCode;
        return;
    }

    if (Mstrl <= Ostrl)
    {
        for (pos = 0; pos < Mstrl; pos++)
        {
            if (ooinputfile[l].oIFCode[pos] == ' ')     // overlay the blanks
            {
                ooinputfile[l].oIFCode[pos] = mminputfile[l].mIFCode[pos];
            }
        }
        return;
    }

//Mstrl is bigger than Ostrl - get what you have
    for (pos = 0; pos < Ostrl; pos++)
    {
        posp1 = pos + 1;
        if (ooinputfile[l].oIFCode[pos] == ' ')     // blank
        {
            ooinputfile[l].oIFCode[pos] = mminputfile[l].mIFCode[pos];
        }
    }

//Mstrl is bigger than Ostrl - pad the rest
   for (pos = posp1; pos < Mstrl; pos++)
    {
        ooinputfile[l].oIFCode += mminputfile[l].mIFCode[pos];
    }

}
void CLEditFrame::LinePushOver()
{

    if (inputfile[i].IFlc == "M")
    {
        // skip the record - decrease the file size
        wfilecnt--;
    }
    else
    {
        if (inputfile[i].IFlc == "O")
        {
            winputfile[wi].wIFlc   = "000000";
            winputfile[wi].wIFCode = oinputfile.oIFCode;
            wi++;
        }
        else
        {
            // copy the current line as is from input to work
            CopyTheLine();
        }
    }

}
void CLEditFrame::BlockPushOver()
{

    if (i >= MMstart
    &&  i <= MMend)
    {
        // skip the record - decrease the file size
        wfilecnt--;
    }
    else
    {
        if (i >= OOstart
        &&  i <= OOend)
        {
            winputfile[wi].wIFlc   = "000000";
            winputfile[wi].wIFCode = ooinputfile[pos].oIFCode;
            pos++;
            wi++;
        }
        else
        {
            // copy the current line as is from input to work
            CopyTheLine();
        }
    }

}
void CLEditFrame::ApplyRR()
{
// increases the file size
// apply the repeated line - or the block of repeated lines
// from input to work input
// after the line command or after the last line of the block

    LogFile << "Apply RR " << std::endl;

    InitWIF();

    oldwfilecnt = wfilecnt;
    wi = 0; // this is the index to the soon to be larger work file
    for (i = 0; i < oldwfilecnt; i++)
    {
        if (singleR > 0) // these are the lines to repeat
        {
            LineRepeat();
        }
        else // this is a block repeat
        {
            BlockRepeat();
        }
        if (wfilecnt > 23000)
        {
            FileSizeError = true;
            break;   // fatal
        }
    }

// refresh input with larger work input
    RefreshInput();

    changesapplied = true;

    if (singleC > 0) // these are the lines to repeat
    {
        wxLogStatus("line Repeat applied ");
    }
    else // this is a block delete
    {
        wxLogStatus("Block Repeat applied ");
    }

}
void CLEditFrame::LineRepeat()
{

    if (inputfile[i].IFlc == "R")
    {
        // copy the current line as is from input to work
        CopyTheLine();
        // and repeat the line
        CopyTheLine();
        wfilecnt++;   // increase the file size
    }
    else
    {
        // copy the current line as is from input to work
        CopyTheLine();
     }

}
void CLEditFrame::BlockRepeat()
{

    if (inputfile[i].IFlc == "RR")
    {
        // copy the current line as is from input to work
        CopyTheLine();
        if (i == RRend)
        // add the Block of Repeat lines - after the last RR - in a loop
        {
            for (l = 0; l < RRrows; l++)
            {
                winputfile[wi].wIFlc   = "000000";
                winputfile[wi].wIFCode = rrinputfile[l].rIFCode;
                wfilecnt++; // increase the file size
                wi++;

            }
        }
    }
    else
    {
        // copy the current line as is from input to work
        CopyTheLine();
    }

}
void CLEditFrame::ApplySR()
{
// the file size stays the same
    LogFile << "Apply >> " << std::endl;

    InitWIF();

    oldwfilecnt = wfilecnt;
    wi = 0; // this is the index to the work file
    for (i = 0; i < oldwfilecnt; i++)
    {
        if (singleSR > 0) // this is the number of lines to be shifted
        {
            LineSR();
        }
        else // this is a block to shift
        {
            BlockSR();
        }
    }

// refresh input with work input
    RefreshInput();

    changesapplied = true;

    if (singleSR > 0) // this is the number of lines to be shifted
    {
        wxLogStatus("Line Shift Right(s) applied ");
    }
    else // this is a block delete
    {
        wxLogStatus("Block Shift Right applied ");
    }

}
void CLEditFrame::LineSR()
{

    if (inputfile[i].IFlc == ">")
    {
        SRl = inputfile[i].IFCode.length();
        if (SRl < 196)
        {
            ShiftRight();
        }
        else
        {
            CopyTheLine();
        }
    }
    else
    {
        // copy the current line as is from input to work
        CopyTheLine();
    }

}
void CLEditFrame::BlockSR()
{

    if (i >= SRstart
    &&  i <= SRend)
    {
        SRl = inputfile[i].IFCode.length();
        if (SRl < 196)
        {
            ShiftRight();
        }
        else
        {
            // copy the current line as is from input to work
            CopyTheLine();
        }
    }
    else
    {
        // copy the current line as is from input to work
        CopyTheLine();
    }

}
void CLEditFrame::ShiftRight()
{

    winputfile[wi].wIFlc = "000000";

    winputfile[wi].wIFCode = "    ";
    winputfile[wi].wIFCode += inputfile[i].IFCode;

    wi++;

}
void CLEditFrame::ApplySL()
{
// the file size stays the same
    LogFile << "Apply << " << std::endl;

    InitWIF();

//    std::string::iterator it = inputfile[0].IFCode.begin();

    oldwfilecnt = wfilecnt;
    wi = 0; // this is the index to the work file
    for (i = 0; i < oldwfilecnt; i++)
    {
        if (singleSL > 0) // this is the number of lines to be shifted
        {
            LineSL();
        }
        else // this is a block to shift
        {
            BlockSL();
        }
    }

// refresh input with work input
    RefreshInput();

    changesapplied = true;

    if (singleSL > 0) // this is the number of lines to be shifted
    {
        wxLogStatus("Line Shift Left(s) applied ");
    }
    else // this is a block delete
    {
        wxLogStatus("Block Shift Left applied ");
    }

}
void CLEditFrame::LineSL()
{

    if (inputfile[i].IFlc == "<")
    {
        str = inputfile[i].IFCode.substr(0, 4);
        if (str == "    ")
        {
            ShiftLeft();
        }
        else
        {
            // copy the current line as is from input to work
            CopyTheLine();
        }
    }
    else
    {
        // copy the current line as is from input to work
        CopyTheLine();
    }

}
void CLEditFrame::BlockSL()
{

    if (i >= SLstart
    &&  i <= SLend)
    {
        str = inputfile[i].IFCode.substr(0, 4);
        if (str == "    ")
        {
            ShiftLeft();
        }
        else
        {
            // copy the current line as is from input to work
            CopyTheLine();
        }
    }
    else
    {
        // copy the current line as is from input to work
        CopyTheLine();
    }

}
void CLEditFrame::ShiftLeft()
{

    winputfile[wi].wIFlc = "000000";

    SLl = inputfile[i].IFCode.length();
    SLl -= 4;

    winputfile[wi].wIFCode = inputfile[i].IFCode.substr(4, SLl);

    wi++;

}
void CLEditFrame::ApplyXX()
{

    LogFile << "Look for XX " << std::endl;

}
void CLEditFrame::ApplyI()
{
// increases the file size

    LogFile << "Apply I " << std::endl;

    InitWIF();

    oldwfilecnt = wfilecnt;
    wi = 0; // this is the index to the soon to be larger work file
    for (i = 0; i < oldwfilecnt; i++)
    {
        LineInsert();
        if (wfilecnt > 23000)
        {
            FileSizeError = true;
            break;   // fatal
        }
    }

// refresh input with larger work input
    RefreshInput();

    changesapplied = true;

    wxLogStatus("Insert(s) applied ");

}
void CLEditFrame::LineInsert()
{

    if (inputfile[i].IFlc == "I")
    {
        // copy the current line as is from input to work
        CopyTheLine();
        // insert a blank line
        winputfile[wi].wIFlc   = "000000";
        winputfile[wi].wIFCode = "";
        wi++;
        wfilecnt++;   // increase the file size
    }
    else
    {
        // copy the current line as is from input to work
        CopyTheLine();
     }

}
void CLEditFrame::CopyTheLine()
{

    winputfile[wi].wIFlc   = "000000";
    winputfile[wi].wIFCode = inputfile[i].IFCode;
    wi++;

}
void CLEditFrame::RefreshInput()
{

    InitIF();

    for (i = 0; i < wfilecnt; i++)
    {
        inputfile[i].IFlc   = winputfile[i].wIFlc;
        inputfile[i].IFCode = winputfile[i].wIFCode;
    }

}
void CLEditFrame::Initialize()
{

    LogFile << "Initialize " << std::endl;

    FileSizeError = false;
// screen
    InitScreen();
// variables
    CurrentFile     = "";
    Byte            = ' ';
    strpos          = 0;
    Mstrl           = 0;
    Ostrl           = 0;
    posp1           = 0;
    LeftPos         = 0;
    RightPos        = 0;
    str             = "";

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

// file to and from file functions
    InitCF();
// files to and from stage database
    InitDB();
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
void CLEditFrame::InitCF()
{

    LogFile << "Init CF File " << std::endl;
// file to or from file functions

    CF.inputfile[0].IFCode = "";
    for (i = 1; i < 25000; i++)
    {
        CF.inputfile[i] = CF.inputfile[0];
    }

}
void CLEditFrame::InitDB()
{
    LogFile << "Init DB File " << std::endl;
// file to or from stage database functions

    DB.inputfile[0].IFCode = "";
    for (i = 1; i < 25000; i++)
    {
        DB.inputfile[i] = DB.inputfile[0];
    }

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
    CCrows  = 0;
    singleC = 0;        // Copy a line - need Before(s) or After(s)
    blockCC = false;    // Copy a block - need Before(s) or After(s) - can be used in a Create

    DDcnt   = 0;
    DDstart = 0;
    DDend   = 0;
    singleD = 0;        // Delete a line
    blockDD = false;    // Delete a block of lines

    singleI = 0;        // insert a single line

    MMcnt   = 0;
    MMstart = 0;
    MMend   = 0;
    MMrows  = 0;
    singleM = 0;        // Move a line - need Before(s) or After(s)
    blockMM = false;    // Move a block of lines - need Before(s) or After(s)

    OOcnt   = 0;
    OOstart = 0;
    OOend   = 0;
    OOrows  = 0;
    singleO = 0;        // Overlay a line - needs single Move
    blockOO = false;    // Overlay a block of lines - needs a block Move

    RRcnt   = 0;
    RRstart = 0;
    RRend   = 0;
    RRrows  = 0;
    singleR = 0;        // Repeat a line
    blockRR = false;    // Repeat a block of lines

    SRcnt    = 0;
    SRstart  = 0;
    SRend    = 0;
    singleSR = 0;       // right shift a line ">" - needs a number of characters (default is one space)
    SRi      = 4;       // number of characters to shift right
    blockSR  = false;   // right shift a block of lines ">>" - needs a number of characters (default is one space)
    SRl      = 0;       // length of the string

    SLcnt    = 0;
    SLstart  = 0;
    SLend    = 0;
    singleSL = 0;       // left shift a line "<" - needs a number of characters (default is one space)
    SLi      = 4;       // number of characters to shift left
    blockSL  = false;   // left shift a block of lines - needs a number of characters (default is one space)
    SLl      = 0;       // length of the string

    XXcnt   = 0;
    XXstart = 0;
    XXend   = 0;
    singleX = 0;        // exclude (hide) a line
    blockXX = false;    // exclude (hide) a block of lines

    singleI = 0;

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

}
void CLEditFrame::InitIF()
{

    LogFile << "Init Input File " << std::endl;
// this is the file that the user opened

    inputfile[0].IFlc = "000000";
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

    winputfile[0].wIFlc = "000000";
    winputfile[0].wIFCode = "";
    for (i = 1; i < 25000; i++)
    {
        winputfile[i] = winputfile[0];
    }

}
void CLEditFrame::InitCC()
{

    LogFile << "Init Copy / Block Copy " << std::endl;
    singleC = 0;  // Copy a line - need Before(s) or After(s)
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
    singleM = 0;  // Move a line - need Before(s) or After(s)
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
    singleO = 0;  // Overlay a line - needs single Move
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
    singleR = 0;  // Repeat a line
    blockRR = false;  // Repeat a block of lines
// a line to be Repeated
    haveaR = 0;
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
