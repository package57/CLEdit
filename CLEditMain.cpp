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

    username = geteuid();
    password = getpwuid(username);
    userid   = password->pw_name;

    OpenLog();

    OpenErr();

    CreateControls();

    Initialize();

    if (Return == false)
    {
        ReturnFunction = "CreateControls ";
        ReturnCode = "3501 ";
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
            if  (changes)
            {
                Find();     // because things might have changed
            }
            else
            {
                FindNext();
            }
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
            if  (changes)
            {
                Change();     // because things might have changed
            }
            else
            {
                ChangeNext();
            }
            LoadScreen();
            break;
    }

    event.Skip();

}
void CLEditFrame::Find()
{

    LogFile << "Find " << std::endl;

    if (FirstParameter == "")
    {
        wxLogStatus("Find what?");
        return;
    }

// trim the ends off the file
    LogFile << "Trim File " << std::endl;
    for (i = (wfilecnt - 1); i > 1; i--)
    {
        TrimFile();
    }

    FindStr  = FirstParameter;
    FindStrl = FirstParameter.length();

    InitFF();

    FindCnt = 0;    // how many times is the string found

    LookForFF();

    if (FindCnt == 0)
    {
        wxLogStatus("Find applied " + FirstParameter + " not found");
    }
    else
    {
        wxLogStatus("Find applied " + FirstParameter + " found " + std::to_string(FindCnt) + " times");
        frstl = FF[0].index + 1;    //off by one eh
        prevf = FF[0].index;        // for find next
    }

}
void CLEditFrame::LookForFF()
{

    LogFile << "Look For FF " << std::endl;
    f = 0;  // index into find found

    for (i = 0; i < wfilecnt; i++)
    {
        if  (winputfile[i].wIFCode != "")
        {
            res = 0;
            pos = 0;
            while (res != MinusOne)
            {
                CaptureFF();
            }
        }
    }

}
void CLEditFrame::CaptureFF()
{

    LogFile << "Capture FF " << std::endl;

    res = winputfile[i].wIFCode.find(FirstParameter, pos);

    if (res == MinusOne)
    {
        return;
    }

    FF[f].index = i;
    FF[f].pos = res;
    FindCnt++;
    f++;
    pos = res + FindStrl + 1;

}
void CLEditFrame::FindNext()
{

    LogFile << "Find Next" << std::endl;
// default for no next
    frstl = FF[0].index + 1;    //off by one eh
    prevf = FF[0].index;

    for (f = 0; f < FindCnt; f++)
    {
        if (FF[f].index > prevf)    // look for the index in the after the prior one
        {
            frstl = FF[f].index + 1;    //off by one eh
            prevf = FF[f].index;
            return;
        }
    }

}
void CLEditFrame::Bottom()
{

    LogFile << "Bottom " << std::endl;

    if (changes)
    {
        return;
    }

    if (wfilecnt > 50)
    {
        lastl = wfilecnt / 50;
        lastl *= 50;
        lastl++;
        frstl = lastl;
    }

    PageofPage();

    PrimaryCommand = "Bottom";
    wxLogStatus(PrimaryCommand + " applied Page " + std::to_string(page) + " of " + std::to_string(ofpage));

}
void CLEditFrame::Home()
{

    LogFile << "Home " << std::endl;

    if (changes)
    {
        return;
    }

    frstl = 1;

    PageofPage();

    PrimaryCommand = "Home";
    wxLogStatus(PrimaryCommand + " applied Page " + std::to_string(page) + " of " + std::to_string(ofpage));

}
void CLEditFrame::Up()
{

    LogFile << "Up " << std::endl;

    if (changes)
    {
        return;
    }

    if (frstl > 50)
    {
        frstl -= 50;
    }
    else
    {
        frstl = 1;
    }

    PageofPage();

    PrimaryCommand = "Up";
    wxLogStatus(PrimaryCommand + " applied Page " + std::to_string(page) + " of " + std::to_string(ofpage));

}
void CLEditFrame::Down()
{

    LogFile << "Down " << std::endl;

    if (changes)
    {
        return;
    }

    if (wfilecnt >= (frstl + 50))
    {
        frstl += 50;
    }

    PageofPage();

    PrimaryCommand = "Down";
    wxLogStatus(PrimaryCommand + " applied Page " + std::to_string(page) + " of " + std::to_string(ofpage));

}
void CLEditFrame::Help()
{

    LogFile << "Help " << std::endl;
    LogFile << "Primary Commands  " << std::endl;
    LogFile << " 'create filename' create a file from a block of Copy code " << std::endl;
    LogFile << " 'change fromstring to string all' change a string to another string everywhere " << std::endl;
    LogFile << " 'change fromstring to string' one at a time " << std::endl;
    LogFile << " 'copy filename' into the file After a line location, insert a file " << std::endl;
    LogFile << " 'exclude' exclude all lines from view and command impact " << std::endl;
    LogFile << " 'find string' find a string, and next " << std::endl;
    LogFile << " 'open filename' open a file " << std::endl;
    LogFile << " 'save' save the current file " << std::endl;
    LogFile << " 'saveas filename' save the current file with a different name " << std::endl;
    LogFile << " 'exit' terminate the application. bye,end,quit,leave should work just as well " << std::endl;
    LogFile << " 'fromstage mydb mytable' get a file from a database name/table name " << std::endl;
    LogFile << " 'tostage mydb mytable' store the file in a database name/table name " << std::endl;
    LogFile << " 'bottom' scroll to the bottom of the file " << std::endl;
    LogFile << " 'home' scroll to the top of the file " << std::endl;
    LogFile << " 'up' page up " << std::endl;
    LogFile << " 'down' page down " << std::endl;
    LogFile << " 'help' provides these notes in the Log file " << std::endl;
    LogFile << " " << std::endl;
    LogFile << "Key Board Commands " << std::endl;
    LogFile << " ENTER: Process Screen - process what the User entered " << std::endl;
    LogFile << "    F5: Find - repeat find " << std::endl;
    LogFile << "   END: Bottom - scroll to the bottom of the file " << std::endl;
    LogFile << "  HOME: Home - scroll to the top oof the file " << std::endl;
    LogFile << "    F7: Up - page up " << std::endl;
    LogFile << "    F8: Down - page down " << std::endl;
    LogFile << "    F1: Help - provide these notes :) " << std::endl;
    LogFile << "    F6: Change - repeat change " << std::endl;
    LogFile << "    For Line Commands let’s deal with: (make a connection) " << std::endl;
    LogFile << " " << std::endl;
    LogFile << "Line Commands  " << std::endl;
    LogFile << " 'A'  place a copied line or copy block after this line(s) " << std::endl;
    LogFile << " 'B'  place a copied line or copy block after this line(s) " << std::endl;
    LogFile << " 'C'  copy a line " << std::endl;
    LogFile << " 'CC' copy a block,  CC on one line, CC on another line anywhere in the file " << std::endl;
    LogFile << " 'D'  delete a line " << std::endl;
    LogFile << " 'DD' delete a block of lines " << std::endl;
    LogFile << " 'I'  insert a line " << std::endl;
    LogFile << " 'M'  move a line after or before another line " << std::endl;
    LogFile << " 'MM' move a block of lines after or before another line " << std::endl;
    LogFile << " 'O'  overlay a line with the contents of a moved line  " << std::endl;
    LogFile << " 'OO' pverlay a block of lie with the data from a corresoponding move block " << std::endl;
    LogFile << " 'R'  repeat a line " << std::endl;
    LogFile << " 'RR' repeat a block of lines " << std::endl;
    LogFile << " '>'  shift right, tab a line 4 characters " << std::endl;
    LogFile << " '>>' shift right, tab a block of lines 4 characters " << std::endl;
    LogFile << " '<'  shift left, tab a line 4 characters " << std::endl;
    LogFile << " '<<' shift left, tab a block of lines 4 characters " << std::endl;
    LogFile << " 'X'  exclude a line from view / impact " << std::endl;
    LogFile << " 'XX' exclude a block of lines from view / impact " << std::endl;
    wxLogStatus("Help applied");

}
void CLEditFrame::Change()
{

    LogFile << "Change " << std::endl;

    if (FirstParameter == "")
    {
        wxLogStatus("Change from what?");
        return;
    }

    if (SecondParameter == "")
    {
        wxLogStatus("Change to what?");
        return;
    }

    ChangeFrom  = FirstParameter;
    ChangeFroml = FirstParameter.length();
    ChangeTo    = SecondParameter;
    ChangeTol   = SecondParameter.length();

// find line where change is requested
    ChangeFind();

    if (ChngCnt == 0)
    {
        wxLogStatus(PrimaryCommand +  " " + FirstParameter + " not found");
        return;
    }

// replace
    if (ThirdParameter == "all")
    {
        ChangeAll();
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " applied " + std::to_string(ChngCnt) + " times");
        frstl = TF[0].index + 1;     //off by one eh
        prevtf = TF[0].index;        // for find next
    }
    else
    {
        ChangeNext();
    }

}
void CLEditFrame::ChangeFind()
{

    LogFile << "Change Find " << std::endl;
// trim the ends off the file
    LogFile << "Trim File " << std::endl;

    for (i = (wfilecnt - 1); i > 1; i--)
    {
        TrimFile();
    }

    InitTF();

    ChngCnt = 0;    // how many times is the string found

    LookForTF();

}
void CLEditFrame::LookForTF()
{

    LogFile << "Look For TF " << std::endl;

    tf = 0;  // index into change from found

    for (i = 0; i < wfilecnt; i++)
    {
        if  (winputfile[i].wIFCode != "")
        {
            res = 0;
            while ((res = winputfile[i].wIFCode.find(FirstParameter, res + 1)) != MinusOne)
            {
                TF[tf].index = i;
                TF[tf].pos = res;
                ChngCnt++;
                tf++;
            }
        }
    }

}
void CLEditFrame::ChangeNext()
{

    LogFile << "Change Next " << std::endl;

    for (tf = 0; tf < ChngCnt; tf++)
    {
        if (TF[tf].index > prevtf)    // look for the index in the after the prior one
        {
            ChangeIt();
            wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " " + " next applied");
            frstl = TF[tf].index + 1;    //off by one eh
            prevtf = TF[tf].index;
            return;
        }
    }

    wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " " + " no more");

}
void CLEditFrame::ChangeAll()
{

    LogFile << "Change All Loop" << std::endl;
     for (tf = 0; tf < ChngCnt; tf++)
    {
        ChangeIt();
    }

}
void CLEditFrame::ChangeIt()
{

    LogFile << "Change All " << std::endl;

// this is where the line is
    i = TF[tf].index;
    ChangeLineF  = winputfile[i].wIFCode;
    ChangeLineFl = winputfile[i].wIFCode.length();

// new target line
    ChangeLineT  = "";
    ChangeLineTl = 0;

// start replacing here
    f = TF[tf].pos;
    ChangeOver();

//  changed line
    winputfile[i].wIFCode = ChangeLineT;
    inputfile[i].IFCode   = ChangeLineT;

}
void CLEditFrame::ChangeOver()
{

    LogFile << "Change Over " << std::endl;

// copy the bytes From To until f - the first byte for the change from string
    for (l = 0; l < f; l++)
    {
        ChangeLineT += ChangeLineF[l];
    }

    if (ChangeTol <= ChangeFroml)
// the change To string will fit completely into the From string
    {
        ChangeOverShort();
    }
    else
//  if (ChangeTol > ChangeFroml the To string is bigger than From string - need to squeeze it into the line
    {
        ChangeOverLong();
    }

}
void CLEditFrame::ChangeOverShort()
{

    LogFile << "Change Over Short";
//  from this XXXXXXFFFFXXXXXX
//    to this XXXXXXTTTTXXXXXX
//  or
//  from this XXXXXXFFFFFFXXXXXX
//    to this XXXXXXTTTTXXXXXX
// append the To string
    for (l = 0; l < ChangeTol; l++)
    {
        ChangeLineT += ChangeTo[l];
    }

    posp1 = f + ChangeFroml;
// append the rest for the From line
    for (l = posp1; l < ChangeLineFl; l++)
    {
        ChangeLineT += ChangeLineF[l];
    }

}
void CLEditFrame::ChangeOverLong()
{

    LogFile << "Change Over Long ";
//  from this XXXXXXFFFXXXXXX
//    to this XXXXXXTTTTTTXXXXXX

//  append the first part of the To string
    l = 0;
    for (pos = f; pos < ChangeFroml; pos++)
    {
        ChangeLineT += ChangeTo[l];
        l++;
        posp1 = pos + 1;  // start location of byte after changed string
    }

// append the remaining part of the To string
    for (l = l; l < ChangeTol; l++)
    {
        ChangeLineT += ChangeTo[l];
    }

// append the rest of the Line - append
    for (l = posp1; l < ChangeLineFl; l++)
    {
        ChangeLineT += ChangeLineF[l];
    }

}
void CLEditFrame::OnApplyClicked(wxCommandEvent & event)
{

    LogFile << "On Apply Clicked ";

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
    if (PrimaryCommand == "report")
    {
        Report();
        goto ExitOnApplyClicked;
    }

//create a file - or stage to a table - from a block copy
    if (PrimaryCommand == "create")
    {
        Create();
        goto ExitOnApplyClicked;
    }

//copy file
    if (PrimaryCommand == "copy")
    {
        CopyFile();  // from a to b or into after or before
        goto ExitOnApplyClicked;
    }

//find string f5 all
    if (PrimaryCommand == "find")
    {
        ProcessScreen();
        Find();
        LoadScreen();
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

//exit - terminate the application!
    if (PrimaryCommand == "exit"
    ||  PrimaryCommand == "quit"
    ||  PrimaryCommand == "bye"
    ||  PrimaryCommand == "end"
    ||  PrimaryCommand == "leave"
    ||  PrimaryCommand == "stop")
    {
        Exit();
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
        ProcessScreen();
        Bottom();
        LoadScreen();
        goto ExitOnApplyClicked;
    }

    if (PrimaryCommand == "home")
    {
        ProcessScreen();
        Home();
        LoadScreen();
        goto ExitOnApplyClicked;
    }

    if (PrimaryCommand == "up")
    {
        ProcessScreen();
        Up();
        LoadScreen();
        goto ExitOnApplyClicked;
    }

    if (PrimaryCommand == "down")
    {
        ProcessScreen();
        Down();
        LoadScreen();
        goto ExitOnApplyClicked;
    }

    if (PrimaryCommand == "help")
    {
        ProcessScreen();
        Help();
        LoadScreen();
        goto ExitOnApplyClicked;
    }

    if (PrimaryCommand == "change")
    {
        ProcessScreen();
        Change();
        LoadScreen();
        goto ExitOnApplyClicked;
    }

    if (PrimaryCommand == "reset")
    {
        ProcessScreen();
        Reset();
        LoadScreen();
        goto ExitOnApplyClicked;
    }

    if (PrimaryCommand == "exclude")
    {
        ProcessScreen();
        eXclude();
        LoadScreen();
        goto ExitOnApplyClicked;
    }

    if (PrimaryCommand == "sort")
    {
        ProcessScreen();
        SortSM();
        LoadScreen();
        goto ExitOnApplyClicked;
    }

    if (PrimaryCommand == "cancel")
    {
        Initialize();
        wxLogStatus("cancel applied");
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

    std::cout << "On Terminal " << std::endl;
    std::cout << ReturnFunction << ReturnCode << ReturnMessage << std::endl;

    exit(9999);

}
void CLEditFrame::Report()
{

    currentdatetime = std::time(nullptr);

    LogFile << "Welcome " << std::ctime(& currentdatetime);
    LogFile << "User " << userid << std::endl;
    LogFile << "Command Report" << std::endl;
    LogFile << "Parameterone " << FirstParameter << std::endl;
    LogFile << "Parametertwo " << SecondParameter << std::endl;
    LogFile << "ParameterIII " << ThirdParameter << std::endl;

    res = AR.ActReact();

    if (res != 0)
    {
        DateSeq.date = "boomboom";
        DateSeq.seq  = "9999999999";
    }
    else
    {
        DateSeq.date = AR.DateSeq.date;
        DateSeq.seq  = AR.DateSeq.seq;
    }

    LogFile << "Usage Date " << DateSeq.date << " " << DateSeq.seq << std::endl;

    start_s = std::clock();

    action = "Report ";

    LogFile << "Report " << std::endl;

    InitScreen();

    res = RP.Report();

    frstl = 1;

    LoadScreen();

    wxLogStatus(PrimaryCommand + " applied ");

    WipeCommand();

    stop_s = std::clock();

    LogFile << "Elapsed " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

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

    currentdatetime = std::time(nullptr);

    LogFile << "Welcome " << std::ctime(& currentdatetime);
    LogFile << "User " << userid << std::endl;
    LogFile << "Command CreateFile" << std::endl;
    LogFile << "Parameterone " << FirstParameter << std::endl;
    LogFile << "Parametertwo " << SecondParameter << std::endl;
    LogFile << "ParameterIII " << ThirdParameter << std::endl;

    res = AR.ActReact();

    if (res != 0)
    {
        DateSeq.date = "boomboom";
        DateSeq.seq  = "9999999999";
    }
    else
    {
        DateSeq.date = AR.DateSeq.date;
        DateSeq.seq  = AR.DateSeq.seq;
    }

    LogFile << "Usage Date " << DateSeq.date << " " << DateSeq.seq << std::endl;

    start_s = std::clock();
    action = "Create File ";

    LogFile << "Create File" << std::endl;   // need a block copy and file name

    if  (FirstParameter == "")
    {
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " file name to Create File missing");
        WipeCommand();
        return;
    }


    InitCF();

    for (i = 0; i < CCrows; i++)
    {
        WorkStr = ccinputfile[i].cIFCode;
        SetEndl();
        CF.inputfile[i].IFCode = WorkStr;
    }

    CF.fileoname = FirstParameter;
    CF.reccnt = CCrows;
    CF.DateSeq.date = DateSeq.date;
    CF.DateSeq.seq = DateSeq.seq;
    CF.Mode = "createfile";
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

    stop_s = std::clock();

    LogFile << "Elapsed " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

}
void CLEditFrame::SetEndl()
{

    WorkStrl = WorkStr.length();

    if (WorkStrl == 1)
    {
        WorkStr[0] = '\n';
        return;
    }

    for (pos = (WorkStrl - 1); pos > -1; pos--)
    {
        if (WorkStr[pos] != ' ')
        {
            if (pos == (WorkStrl -1))  // this means the line end has no space
            {
                WorkStr += '\n';
                return;
            }
            else                       // this means the line ends with a space
            {
                pos++;
                WorkStr[pos] = '\n';
                return;
            }
        }
    }

}
void CLEditFrame::CreateTable()
{

    start_s = std::clock();

    currentdatetime = std::time(nullptr);

    LogFile << "Welcome " << std::ctime(& currentdatetime);
    LogFile << "User " << userid << std::endl;
    LogFile << "Command CreateTable" << std::endl;
    LogFile << "Parameterone " << FirstParameter << std::endl;
    LogFile << "Parametertwo " << SecondParameter << std::endl;
    LogFile << "ParameterIII " << ThirdParameter << std::endl;

    res = AR.ActReact();

    if (res != 0)
    {
        DateSeq.date = "boomboom";
        DateSeq.seq  = "9999999999";
    }
    else
    {
        DateSeq.date = AR.DateSeq.date;
        DateSeq.seq  = AR.DateSeq.seq;
    }

    LogFile << "Usage Date " << DateSeq.date << " " << DateSeq.seq << std::endl;

    LogFile << "Create Table" << std::endl;   // need a block copy and file name

// the next three lines are the equivalent of an "open"
// create a driver object
// create a connection object
// create a statement object
    DB.DataBase = FirstParameter;
    DB.TableName = SecondParameter;
    DB.DateSeq.date = DateSeq.date;
    DB.DateSeq.seq = DateSeq.seq;
    res = DB.Bind();

    if (res != 0)
    {
        LoadScreen();
        wxLogStatus(PrimaryCommand + " " + FirstParameter + SecondParameter + " failed " + to_string(res));
        WipeCommand();
        return;
    }

    InitDB();

    for (i = 0; i < CCrows; i++)
    {
        WorkStr = ccinputfile[i].cIFCode;
        SetEndl();
        DB.inputfile[i].IFCode = WorkStr;
    }

    DB.rowcnt = CCrows;
    DB.Mode = "createtable";
    DB.ToStage();

// close
    DB.Free();

    LoadScreen();   //always from work input

    wxLogStatus(PrimaryCommand + " " + FirstParameter + SecondParameter + " applied");

    WipeCommand();

    stop_s = std::clock();

    action = "Create Table ";

    LogFile << "Elapsed " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

}
void CLEditFrame::SaveFile()
{

    currentdatetime = std::time(nullptr);

    LogFile << "Welcome " << std::ctime(& currentdatetime);
    LogFile << "User " << userid << std::endl;
    LogFile << "Command SaveFile" << std::endl;
    LogFile << "Parameterone " << FirstParameter << std::endl;
    LogFile << "Parametertwo " << SecondParameter << std::endl;
    LogFile << "ParameterIII " << ThirdParameter << std::endl;

    res = AR.ActReact();

    if (res != 0)
    {
        DateSeq.date = "boomboom";
        DateSeq.seq  = "9999999999";
    }
    else
    {
        DateSeq.date = AR.DateSeq.date;
        DateSeq.seq  = AR.DateSeq.seq;
    }

    LogFile << "Usage Date " << DateSeq.date << " " << DateSeq.seq << std::endl;

    start_s = std::clock();
    action = "Save File ";

    LogFile << "Save File " << std::endl;

    if (CurrentFile == "")  // means the file is on the screen - was not opened first
    {
        if (FirstParameter == "")
        {
            wxLogStatus(PrimaryCommand + " " + FirstParameter + " file name to SAVE missing");
            WipeCommand();
            return;
        }
        else
        {
            CurrentFile = FirstParameter;
        }
    }

//trim the ends off the file
    LogFile << "Trim File " << std::endl;
    for (i = (wfilecnt - 1); i > 1; i--)
    {
        TrimFile();
    }

    for (i = 0; i < wfilecnt; i++)
    {
        WorkStr = winputfile[i].wIFCode;
        SetEndl();
        CF.inputfile[i].IFCode = WorkStr;
    }

    CF.fileoname = CurrentFile;
    CF.reccnt = wfilecnt;
    CF.DateSeq.date = DateSeq.date;
    CF.DateSeq.seq = DateSeq.seq;
    CF.Mode = "savefile";
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

    stop_s = std::clock();

    LogFile << "Elapsed " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

}
void CLEditFrame::TrimFile()
{
//  LogFile << "Trim File " << std::endl;

    if (winputfile[i].wIFCode == "")
    {
        wfilecnt--;
    }
    else
    {
        i = 0; // stop loop
    }

}
void CLEditFrame::SaveAsFile()
{

    currentdatetime = std::time(nullptr);

    LogFile << "Welcome " << std::ctime(& currentdatetime);
    LogFile << "User " << userid << std::endl;
    LogFile << "Command SaveAsFile" << std::endl;
    LogFile << "Parameterone " << FirstParameter << std::endl;
    LogFile << "Parametertwo " << SecondParameter << std::endl;
    LogFile << "ParameterIII " << ThirdParameter << std::endl;

    res = AR.ActReact();

    if (res != 0)
    {
        DateSeq.date = "boomboom";
        DateSeq.seq  = "9999999999";
    }
    else
    {
        DateSeq.date = AR.DateSeq.date;
        DateSeq.seq  = AR.DateSeq.seq;
    }

    LogFile << "Usage Date " << DateSeq.date << " " << DateSeq.seq << std::endl;

    start_s = std::clock();
    action = "Save As File ";

    LogFile << "SaveAs " << std::endl;

    if  (FirstParameter == "")
    {
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " file name to Save As missing");
        WipeCommand();
        return;
    }
    else
    {
        CurrentFile = FirstParameter;
    }

//trim the ends off the file
    LogFile << "Trim File " << std::endl;
    for (i = (wfilecnt - 1); i > 1; i--)
    {
        TrimFile();
    }

    for (i = 0; i < wfilecnt; i++)
    {
        WorkStr = winputfile[i].wIFCode;
        SetEndl();
        CF.inputfile[i].IFCode = WorkStr;
    }

    CF.fileoname = CurrentFile;
    CF.reccnt = wfilecnt;
    CF.DateSeq.date = DateSeq.date;
    CF.DateSeq.seq = DateSeq.seq;
    CF.Mode = "saveasfile";
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

    stop_s = std::clock();

    LogFile << "Elapsed " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

}
void CLEditFrame::Exit()
{

    LogFile << "Exit " << std::endl;

    CloseLog();

    CloseErr();

    wxExit();

}
void CLEditFrame::Reset()
{

    LogFile << "Reset " << std::endl;

// clear all commands
    InitCC();
    InitMM();
    InitOO();
    InitRR();
    InitFF();
    InitTF();
    InitXX();
    InitCTrackers();

    for (i = 0; i < wfilecnt; i++)
    {
        inputfile[i].IFlc   = "000000";
        winputfile[i].wIFlc = "000000";
    }

    wxLogStatus(PrimaryCommand + " applied");

    WipeCommand();

}
void CLEditFrame::eXclude()
{

    LogFile << "eXclude " << std::endl;

    for (i = 0; i < wfilecnt; i++)
    {
        XX[i].excluded = true;
    }

    wxLogStatus(PrimaryCommand + " applied");

    WipeCommand();

}
void CLEditFrame::OpenFile()
{

    currentdatetime = std::time(nullptr);

    LogFile << "Welcome " << std::ctime(& currentdatetime);
    LogFile << "User " << userid << std::endl;
    LogFile << "Command OpenFile" << std::endl;
    LogFile << "Parameterone " << FirstParameter << std::endl;
    LogFile << "Parametertwo " << SecondParameter << std::endl;
    LogFile << "ParameterIII " << ThirdParameter << std::endl;

    res = AR.ActReact();

    if (res != 0)
    {
        DateSeq.date = "boomboom";
        DateSeq.seq  = "9999999999";
    }
    else
    {
        DateSeq.date = AR.DateSeq.date;
        DateSeq.seq  = AR.DateSeq.seq;
    }

    LogFile << "Usage Date " << DateSeq.date << " " << DateSeq.seq << std::endl;

    start_s = std::clock();
    action = "Open File ";

    LogFile << "Open File " << std::endl;

    if (FirstParameter == "")
    {
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " file name to OPEN missing");
        WipeCommand();
        return; //goto ExitOpenFile;
    }

    InitScreen();

    CurrentFile = FirstParameter;
    CF.fileiname = FirstParameter;
    CF.DateSeq.date = DateSeq.date;
    CF.DateSeq.seq = DateSeq.seq;
// import the file
    CF.Mode = "openfile";
    CLEditCFrc = CF.openfile(CF.fileiname);

    if  (CLEditCFrc != 0)
    {
        CLEditCFmsg();
        wfilecnt = 0;
        goto ExitOpenFile;
    }

    InitIF();

    InitWIF();

    wfilecnt = CF.reccnt;

    if (wfilecnt > 23000)
    {
        FileSizeError = true;
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " file too big ");
        goto ExitOpenFile;
    }

    haveaFile = true;

    for (i = 0; i < CF.reccnt; i++)
    {
        inputfile[i].IFlc     = "000000";
        inputfile[i].IFCode   = CF.inputfile[i].IFCode;
        winputfile[i].wIFlc   = "000000";
        winputfile[i].wIFCode = CF.inputfile[i].IFCode;
        GetEndl();
    }

    frstl = 1;

    LoadScreen();   //always from work input

    PageofPage();

    wxLogStatus(PrimaryCommand + " " + FirstParameter + " applied Page " + std::to_string(page) + " of " + std::to_string(ofpage));

ExitOpenFile:

    WipeCommand();

    stop_s = std::clock();

    LogFile << "Elapsed " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

}
void CLEditFrame::PageofPage()
{

    LogFile << "Page of Page " << std::endl;

// each page is 50 lines
// get the whole number of pages from where we are starting
    pgs = frstl / 50;

// set the page value
    page = pgs + 1;

// get the number of whole pages
    pgs = wfilecnt / 50;

// get the exact number of pages as a fraction
// C++ can only do fractions with fractions. C++ is dumb
    wfilecntf = wfilecnt;
    pgsf = wfilecntf / 50.0;

// subtract the whole number from the fraction
// to see if there is a fraction
    pgsf -= pgs;

    if (pgsf > 0)
    {
        ofpage = pgs + 1;
    }
    else
    {
        ofpage = pgs;
    }

}
void CLEditFrame::GetEndl()
{

    if (i == 0)
    {
        LogFile << "Get Endl " << std::endl;
    }

    WorkStr  = winputfile[i].wIFCode;
    WorkStrl = WorkStr.length();

    for (xpos = (WorkStrl - 1); xpos >= 0; xpos--)
    {
        if (WorkStr[xpos] == '\n')
        {
            WorkStr[xpos] = ' ';
            winputfile[i].wIFCode = WorkStr;
            return;
        }
    }

}
void CLEditFrame::CopyFile()
{

    currentdatetime = std::time(nullptr);

    LogFile << "Welcome " << std::ctime(& currentdatetime);
    LogFile << "User " << userid << std::endl;
    LogFile << "Command CopyFile" << std::endl;
    LogFile << "Parameterone " << FirstParameter << std::endl;
    LogFile << "Parametertwo " << SecondParameter << std::endl;
    LogFile << "ParameterIII " << ThirdParameter << std::endl;

    res = AR.ActReact();

    if (res != 0)
    {
        DateSeq.date = "boomboom";
        DateSeq.seq  = "9999999999";
    }
    else
    {
        DateSeq.date = AR.DateSeq.date;
        DateSeq.seq  = AR.DateSeq.seq;
    }

    LogFile << "Usage Date " << DateSeq.date << " " << DateSeq.seq << std::endl;

    start_s = std::clock();
    action = "Copy File ";

    LogFile << "Copy File " << std::endl;

    InitScreen();

    if (FirstParameter == "")
    {
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " FROM file name missing");
        WipeCommand();
        return; // goto ExitCopyFile;
    }

    if (SecondParameter == "")
    {
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " TO file name missing");
        WipeCommand();
        return; // goto ExitCopyFile;
    }

    CF.fileiname = FirstParameter;
    CF.fileoname = SecondParameter;
    CF.DateSeq.date = DateSeq.date;
    CF.DateSeq.seq = DateSeq.seq;
    CF.Mode = "copyfile";
    CLEditCFrc = CF.copyfile(CF.fileiname, CF.fileoname);

    if  (CLEditCFrc != 0)
    {
        CLEditCFmsg();
    }
    else
    {
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " applied");
    }

    WipeCommand();

    stop_s = std::clock();

    LogFile << "Elapsed " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

}
void CLEditFrame::CLEditCFmsg()
{

    LogFile << "CF msg " << std::endl;

    switch (CLEditCFrc)
    {
        case 3501:
            wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " From file unavailable");
            break;
        case 3502:
            wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " From file Open error");
            break;
        case 3503:
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " file TO Open error");
        break;
    }

}
void CLEditFrame::FromStage()
{

    currentdatetime = std::time(nullptr);

    LogFile << "Welcome " << std::ctime(& currentdatetime);
    LogFile << "User " << userid << std::endl;
    LogFile << "Command FromStage" << std::endl;
    LogFile << "Parameterone " << FirstParameter << std::endl;
    LogFile << "Parametertwo " << SecondParameter << std::endl;
    LogFile << "ParameterIII " << ThirdParameter << std::endl;

    res = AR.ActReact();

    if (res != 0)
    {
        DateSeq.date = "boomboom";
        DateSeq.seq  = "9999999999";
    }
    else
    {
        DateSeq.date = AR.DateSeq.date;
        DateSeq.seq  = AR.DateSeq.seq;
    }

    LogFile << "Usage Date " << DateSeq.date << " " << DateSeq.seq << std::endl;

    start_s = std::clock();
    action = "From Stage ";
// get the file from a table :)
    LogFile << "From Stage " << std::endl;

    InitScreen();

    if  (FirstParameter == "")
    {
        wxLogStatus(PrimaryCommand + " need Database name ");
        return;
    }

    if  (SecondParameter == "")
    {
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " need TableName ");
        return;
    }

// the next three lines are the equivalent of an "open"
// create a driver object
// create a connection object
// create a statement object
    DB.DataBase = FirstParameter;
    DB.TableName = SecondParameter;
    DB.DateSeq.date = DateSeq.date;
    DB.DateSeq.seq = DateSeq.seq;
    res = DB.Bind();

    if (res != 0)
    {
        LoadScreen();
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " failed " + to_string(res));
        WipeCommand();
        return;
    }

    rowcnt = DB.Count();

    LogFile << "rows " << rowcnt << std::endl;

    if (rowcnt > 23000)
    {
        FileSizeError = true;
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " file too big ");
        haveaFile = false;
        DB.Free();
        return;
    }

    if  (rowcnt == 0)
    {
        haveaFile = false;
        wfilecnt = 0;
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " not found");
        DB.Free();
        return;
    }

    haveaFile = true;
    wfilecnt = rowcnt;

    InitIF();

    InitWIF();

    DB.Cursor();

    DB.Mode = "fromstage";
    DB.FromStage();
// "close" the database
    DB.Free();

    for (i = 0; i < rowcnt; i++)
    {
        inputfile[i].IFCode = DB.inputfile[i].IFCode;
        winputfile[i].wIFlc   = "000000";
        winputfile[i].wIFCode = DB.inputfile[i].IFCode;
        GetEndl();
    }

    frstl = 1;

    LoadScreen();

    PageofPage();

    wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " applied Page " + std::to_string(page) + " of " + std::to_string(ofpage));

    WipeCommand();

    stop_s = std::clock();

    LogFile << "Elapsed " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

}
void CLEditFrame::ToStage()
{

    currentdatetime = std::time(nullptr);

    LogFile << "Welcome " << std::ctime(& currentdatetime);
    LogFile << "User " << userid << std::endl;
    LogFile << "Command ToStage" << std::endl;
    LogFile << "Parameterone " << FirstParameter << std::endl;
    LogFile << "Parametertwo " << SecondParameter << std::endl;
    LogFile << "ParameterIII " << ThirdParameter << std::endl;

    res = AR.ActReact();

    if (res != 0)
    {
        DateSeq.date = "boomboom";
        DateSeq.seq  = "9999999999";
    }
    else
    {
        DateSeq.date = AR.DateSeq.date;
        DateSeq.seq  = AR.DateSeq.seq;
    }

    LogFile << "Usage Date " << DateSeq.date << " " << DateSeq.seq << std::endl;

    start_s = std::clock();
    action = "To Stage ";
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


    if (wfilecnt > 23000)
    {
        FileSizeError = true;
        wxLogStatus(PrimaryCommand + " file too big ");
        return;
    }

// the next three lines are the equivalent of an "open"
// create a driver object
// create a connection object
// create a statement object
    DB.DataBase = FirstParameter;
    DB.TableName = SecondParameter;
    DB.DateSeq.date = DateSeq.date;
    DB.DateSeq.seq = DateSeq.seq;
    res = DB.Bind();

    if (res != 0)
    {
        LoadScreen();
        wxLogStatus(PrimaryCommand + " " + FirstParameter + SecondParameter + " failed " + to_string(res));
        WipeCommand();
        return;
    }

    InitDB();
 //trim the ends off the file
    LogFile << "Trim File " << std::endl;

    for (i = (wfilecnt - 1); i > 1; i--)
    {
        TrimFile();
    }

    for (i = 0; i < wfilecnt; i++)
    {
        WorkStr = winputfile[i].wIFCode;
        SetEndl();
        DB.inputfile[i].IFCode = WorkStr;
    }

    DB.rowcnt = wfilecnt;

    DB.Mode = "tostage";
    DB.ToStage();

 // "close" the database
    DB.Free();

    LoadScreen();

    wxLogStatus(PrimaryCommand + FirstParameter + SecondParameter + " applied");

    WipeCommand();

    stop_s = std::clock();

    LogFile << "Elapsed " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << std::endl;

}
void CLEditFrame::SortSM()
{

    LogFile << "Sort " << std::endl;

//trim the ends off the file
    LogFile << "Trim File " << std::endl;
    for (i = (wfilecnt - 1); i > 1; i--)
    {
        TrimFile();
    }

    for (i = 0; i < wfilecnt; i++)
    {
        SortArea();
    }

    SM.rowcnt = wfilecnt;

    SM.SortSM();

    for (i = 0; i < wfilecnt; i++)
    {
        inputfile[i].IFlc   = "000000";
        inputfile[i].IFCode   = SM.inputfile[i].IFCode;
        winputfile[i].wIFlc   = "000000";
        winputfile[i].wIFCode = SM.inputfile[i].IFCode;
    }

// binary search - for kicks
    left = 0;
    right = wfilecnt - 1;
    mid = 0;
    key = "Pierre";
    res = BiSearch();

    if (res == -1)
    {
        LogFile << "Binary Search - Pierre not found " << std::endl;
    }
    else
    {
        LogFile << "Binary Search - Pierre found here " + std::to_string(mid) << std::endl;
    }

    frstl = 1;

    LoadScreen();   //always from work input

    wxLogStatus(PrimaryCommand + " applied");

    WipeCommand();

}
void CLEditFrame::SortArea()
{

    if (i == 0)
    {
        LogFile << "SortArea " << std::endl;
    }
// we need the length of the code line
    WorkStrl = winputfile[i].wIFCode.length();
// assume we get nothing
    SM.inputfile[i].sortarea = "";
// we cant look at the line if it's shorter than what we want sorted
// pretend we want to sort the first 5 characters length
// after the first 5 characters, starting position 6
// meaning characters 6,7,8,9 & 10
    if  (WorkStrl >=  10)
    {
        WorkStr = winputfile[i].wIFCode.substr(6, 5);
        SM.inputfile[i].sortarea += WorkStr;
    }
// and we want to sort the first 5 characters after the first 20
// meaning characters 21,22,23,24 & 25
    if  (WorkStrl >=  25)
    {
        WorkStr = winputfile[i].wIFCode.substr(21, 5);
        SM.inputfile[i].sortarea += WorkStr;
    }

    SM.inputfile[i].IFCode = winputfile[i].wIFCode;

}
int CLEditFrame::BiSearch()
{

    if (mid == 0)
    {
        LogFile << "BiSearch " << std::endl;
    }

    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (winputfile[mid].wIFCode == key)
        {
            return mid;
        }
        if (winputfile[mid].wIFCode < key)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return -1;

}
void CLEditFrame::WipeCommand()
{

    LogFile << "Wipe Command " << std::endl;

    PrimaryCommand = "";
    FirstParameter = "";
    SecondParameter = "";
    ThirdParameter = "";

}
void CLEditFrame::LoadScreen()
{

    LogFile << "Load Screen " << std::endl;

    i = 0;

    LogFile << "Focus Line " << std::endl;

    for (u = (frstl - 1); i < 50; u++)
    {
        if (XX[u].excluded == false)  // exclude from view
        {
            FocusLine();
            CL[i].Code->ChangeValue(winputfile[u].wIFCode);
            i++;
        }
    }

}
void CLEditFrame::FocusLine()
{

//  LogFile << "Focus Line " << std::endl;

    if (winputfile[u].wIFlc == "000000")
    {
        prettystr = ToString(u);
        CL[i].Line->ChangeValue(prettystr);
        return;
    }

    CL[i].Line->ChangeValue(winputfile[u].wIFlc);

}
std::string CLEditFrame::ToString(int u)
{

//  LogFile << "To String " << std::endl;
// make 10 look like 000010 etc
    ostringstream os;
    prettyint = u * 5;
    os<<setfill('0')<<setw(6)<<prettyint;

    return os.str();

}
void CLEditFrame::ProcessScreen()
{

    currentdatetime = std::time(nullptr);

    LogFile << "Welcome " << std::ctime(& currentdatetime);
    LogFile << "User " << userid << std::endl;
    LogFile << "Command Process" << std::endl;

    LogFile << "Process Screen " << std::endl;
// capture everything from the screen
// capture all code where ever the block command causes the file size to change: c/CC d/DD m/MM o/OO r/RR
    ReadScreen();
 // did anything change on the screen - if not, skip the Find() on a find next F5
    LookForChanges();
 // move all the user Input into Work Input
// the index from the screen "u" to Work Input is "frstl"
// excluded lines need to offset that key
    i = frstl - 1;
    for (u = 0; u < 50; u++)
    {
        if (XX[i].excluded == false)
        {
            winputfile[i].wIFlc   = Input[u].Linestr;
            winputfile[i].wIFCode = Input[u].Codestr;
            i++;
        }
    }
// did the User enter data in blank lines
    for (i = 0; i < 25000; i++)
    {
        if (XX[i].excluded == false)
        {
            if (winputfile[i].wIFCode != "")
            {
                wfilecnt = i;
            }
        }
    }

    wfilecnt++;     // off by one eh
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

}
void CLEditFrame::LookForChanges()
{

    LogFile << "Look For Changes " << std::endl;

    changes = false;

// the index from the screen "u" to Work Input is "frstl"
// excluded lines need to offset that key
    i = frstl - 1;
    for (u = 0; u < 50; u++)
    {
        if (XX[i].excluded == false)
        {
            if (winputfile[i].wIFCode != Input[u].Codestr)
            {
                changes = true;
                return;
            }
            i++;
        }
    }

}
void CLEditFrame::ReadScreen()
{

    LogFile << "Read Screen " << std::endl;
// user input
    InitUser();
// capture everything from the text controls - Line Commands and Code
    LogFile << "What Command " << std::endl;

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

//    LogFile << "What Command " << std::endl;

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

    LogFile << "What Command A " << std::endl;

    Input[u].Linestr = "A";
    afters++;

}
void CLEditFrame::WhatCommandB()
{

    LogFile << "What Command B " << std::endl;

    Input[u].Linestr = "B";

    befores++;

}
void CLEditFrame::WhatCommandCC()
{

    LogFile << "What Command CC " << std::endl;

    if  (UserLinel > 1)
    {
        if (UserLinestr[1] == 'C')
        {
            Input[u].Linestr = "CC";
            blockCC = true;
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

    LogFile << "What Command DD " << std::endl;

    if  (UserLinel > 1)
    {
        if (UserLinestr[1] == 'D')
        {
            Input[u].Linestr = "DD";
            blockDD = true;
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

    LogFile << "What Command MM " << std::endl;

    if  (UserLinel > 1)
    {
        if (UserLinestr[1] == 'M')
        {
            Input[u].Linestr = "MM";
            blockMM = true;
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

    LogFile << "What Command OO " << std::endl;

    if  (UserLinel > 1)
    {
        if (UserLinestr[1] == 'O')
        {
            Input[u].Linestr = "OO";
            blockOO = true;
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

    LogFile << "What Command RR " << std::endl;

    if  (UserLinel > 1)
    {
        if (UserLinestr[1] == 'R')
        {
            Input[u].Linestr = "RR";
            blockRR = true;
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

    LogFile << "What Command >> " << std::endl;

//  int  SRi;      // number of characters to shift right
    if  (UserLinel > 1)
    {
        if (UserLinestr[1] == '>')
        {
            Input[u].Linestr = ">>";
            blockSR = true;
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

    LogFile << "What Command << " << std::endl;
//  int  SLi;      // number of characters to shift left

    if  (UserLinel > 1)
    {
        if (UserLinestr[1] == '<')
        {
            Input[u].Linestr = "<<";
            blockSL = true;
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

    LogFile << "What Command XX " << std::endl;

    if  (UserLinel > 1)
    {
        if (UserLinestr[1] == 'X')
        {
            Input[u].Linestr = "XX";
            blockXX = true;
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

    LogFile << "What Command I " << std::endl;

    singleI++;

    Input[u].Linestr = "I";
}
void CLEditFrame::ApplyChanges()
{

    LogFile << "Apply Changes " << std::endl;

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
// are there any block commands
// are there any line commands
    Capture();
// ranges
    Ranges();

    if (badchanges)
    {
        return;
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
    else
    {
        changes = true;
    }

    ApplyCommands();

}
void CLEditFrame::Capture()
{      LogFile << "Capture " << std::endl;
 //  are there any block commands
    LCcnt = CCcnt + MMcnt + OOcnt + RRcnt;
     if (LCcnt != 0)
    {
        CaptureLC();  // blocks
    }
    else
    {
//  are there any line commands
        LCcnt = singleC + singleM + singleO + singleR;  // these change the size of the file
        if (LCcnt != 0)
        {
            CaptureLC();  // blocks
        }
    }

}
void CLEditFrame::Ranges()
{

    LogFile << "Ranges " << std::endl;

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

}
void CLEditFrame::ApplyCommands()
{

    LogFile << "Apply Commands " << std::endl;
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

    LogFile << "LC Reasonability " << std::endl;
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
        if  (MMcnt == 2
        ||   singleM == 1)
        {
            Continue();
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
            Continue();
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
            Continue();
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
            Continue();
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
            Continue();
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
            Continue();
        }
        else
        {
            wxLogStatus("Block Shift Left can't use Before or After location(s) ");
            badchanges = true;
            return;
        }
    }

}
void CLEditFrame::Continue()
{

// do nothing C++ continue is only for loops!

}
void CLEditFrame::LCReasonabilityBlockMM()
{

    LogFile << "LC Reasonability Block MM " << std::endl;

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
            Continue();
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
            Continue();
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
            Continue();
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
    &&  singleC > 0)
    {
        wxLogStatus("line commands ambiguous ");
        badchanges = true;
        return;
    }

    if (blockMM
    &&  singleM > 0)
    {
        wxLogStatus("line commands ambiguous ");
        badchanges = true;
        return;
    }

    if (blockOO
    &&  singleO > 0)
    {
        wxLogStatus("line commands ambiguous ");
        badchanges = true;
        return;
    }

    if (blockRR
    &&  singleR > 0)
    {
        wxLogStatus("line commands ambiguous ");
        badchanges = true;
        return;
    }

    if (blockOO
    &&  singleM > 1)
    {
        wxLogStatus("line commands ambiguous ");
        badchanges = true;
        return;
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

    LogFile << "Look for LC CC " << std::endl;

    CCcnt = 0;
    CCstart = 9999;
    LogFile << "Look For CC " << std::endl;

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

    LogFile << "Look for LC DD " << std::endl;

    DDcnt = 0;
    DDstart = 9999;
    LogFile << "Look for DD " << std::endl;

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

    LogFile << "Look for LC MM " << std::endl;

    MMcnt = 0;
    MMstart = 9999;
    LogFile << "Look for MM " << std::endl;

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

    LogFile << "Look for LC OO " << std::endl;
    OOcnt = 0;
    OOstart = 9999;
    LogFile << "Look for OO " << std::endl;

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

    LogFile << "Look for LC RR " << std::endl;

    RRcnt = 0;
    RRstart = 9999;
    LogFile << "Look for RR " << std::endl;
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

    LogFile << "Look for LC SR >> " << std::endl;

    SRcnt = 0;
    SRstart = 9999;
    LogFile << "Look for >> " << std::endl;

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

    LogFile << "Look for LC SL << " << std::endl;

    SLcnt = 0;
    SLstart = 9999;
    LogFile << "Look for << " << std::endl;

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

    LogFile << "Look for LC XX " << std::endl;

    XXcnt = 0;
    XXstart = 9999;
    LogFile << "Look for XX " << std::endl;

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

//  LogFile << "Look for CC " << std::endl;

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
void CLEditFrame::ApplyCC()
{

    LogFile << "Apply CC " << std::endl;
// increases the file size
// apply the copied line - or the block of copied lines
// from input to work input
// where ever there is an After or Before line command
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

    LogFile << "Line Copy " << std::endl;

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

    LogFile << "Block Copy " << std::endl;

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

    LogFile << "Apply DD " << std::endl;
// reduces the file size
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

    LogFile << "Line Delete " << std::endl;

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

    LogFile << "Block Delete " << std::endl;

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

    LogFile << "Apply MM " << std::endl;
 // the file will be the same size
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

    LogFile << "Line Move " << std::endl;

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

    LogFile << "Block Move " << std::endl;

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

    LogFile << "Apply OO " << std::endl;
// this will make the file smaller
    if (singleO == 1)
    {
// move everything from the Move Line into the Overlay Line where ever there is a space
        LineOver();
    }
    else
    {
        if  (singleM == 1
        &&   OOcnt == 2)
        {
            MoveOverOver();
        }
        else
        {
// move everything from the Move block into the Overlay block where ever there is a space
            BlockOver();
        }
    }

    InitWIF();

    oldwfilecnt = wfilecnt;
    wi = 0; // this is the index to the new smaller work file
    pos = 0; // this is the index to the Overlay Block

    for (i = 0; i < oldwfilecnt; i++)
    {
        if (singleM == 1
        &&  singleO == 1) // one line to Move Over another
        {
//      push the Overlay Line into work input and pull the Move Line
            LinePushOver();  // like a line copy
        }
        else
//      this is a Block Overlay
        {
            if (haveaMM
            &&  haveaOO)
//          push the Overlay block into work input and pull the Move Block
            {
                BlockPushOver();  // like a block copy
            }
            else
            {
//          push the Overlay block into work input and pull the Move line
                MMstart = haveaM;
                MMend   = haveaM;
                BlockPushOver();  // like a block copy
            }
        }
    }
 // refresh input with smaller work input
    RefreshInput();

    changesapplied = true;

    if (singleM > 0) // this is the Line Move Overlay
    {
        wxLogStatus("Line Move Overlay applied ");
    }
    else // this is a Block Move
    {
        wxLogStatus("Block Move Overlay applied ");
    }

}
void CLEditFrame::LineOver()
{

    LogFile << "Line Over " << std::endl;
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

    LogFile << "Block Over " << std::endl;

    for (l = 0; l < MMrows; l++)
    {
        BlockMoveOver();
    }

}
void CLEditFrame::MoveOverOver()
{

    LogFile << "Move Over Over " << std::endl;
// move one line over a block of lines
    for (l = 0; l < OOrows; l++)
    {
        MoveBlockOver();
    }

}
void CLEditFrame::BlockMoveOver()
{

    LogFile << "Block Move Over " << std::endl;
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
// Mstrl is bigger than Ostrl - get what you have
    for (pos = 0; pos < Ostrl; pos++)
    {
        posp1 = pos + 1;
        if (ooinputfile[l].oIFCode[pos] == ' ')     // blank
        {
            ooinputfile[l].oIFCode[pos] = mminputfile[l].mIFCode[pos];
        }
    }
// Mstrl is bigger than Ostrl - pad the rest
    for (pos = posp1; pos < Mstrl; pos++)
    {
        ooinputfile[l].oIFCode += mminputfile[l].mIFCode[pos];
    }

}
void CLEditFrame::MoveBlockOver()
{

    LogFile << "Move Block Over " << std::endl;
// byte by byte where there is a blank
    Mstrl = minputfile.mIFCode.length();    // only one move line

    if (Mstrl == 0) // this means the Move Line is blank, do nothing to the Overlay line
    {
        return;
    }

    Ostrl = ooinputfile[l].oIFCode.length();

    if (Ostrl == 0) // this means the Overlay line is blank - clobber it
    {
        ooinputfile[l].oIFCode = minputfile.mIFCode;  // only one move line
        return;
    }

    if (Mstrl <= Ostrl)
    {
        for (pos = 0; pos < Mstrl; pos++)
        {
            if (ooinputfile[l].oIFCode[pos] == ' ')     // overlay the blanks
            {
                ooinputfile[l].oIFCode[pos] = minputfile.mIFCode[pos];  // only one move line
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
            ooinputfile[l].oIFCode[pos] = minputfile.mIFCode[pos];    // only one  move line
        }
    }
//Mstrl is bigger than Ostrl - pad the rest
   for (pos = posp1; pos < Mstrl; pos++)
    {
        ooinputfile[l].oIFCode += minputfile.mIFCode[pos];   // only one move line
    }

}
void CLEditFrame::LinePushOver()
{

    LogFile << "Line Push Over " << std::endl;

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

    LogFile << "Block Push Over " << std::endl;

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

    LogFile << "Apply RR " << std::endl;
// increases the file size
// apply the repeated line - or the block of repeated lines
// from input to work input
// after the line command or after the last line of the block
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

    if (singleR > 0) // these are the lines to repeat
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

    LogFile << "Line Repeat " << std::endl;

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

    LogFile << "Block Repeat " << std::endl;

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

    LogFile << "Apply >> " << std::endl;
// the file size stays the same
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

    LogFile << "Line SR " << std::endl;

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

    LogFile << "Block SR " << std::endl;

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

    LogFile << "Shift Right " << std::endl;

    winputfile[wi].wIFlc = "000000";
    winputfile[wi].wIFCode = "    ";
    winputfile[wi].wIFCode += inputfile[i].IFCode;
    wi++;

}
void CLEditFrame::ApplySL()
{

    LogFile << "Apply SL " << std::endl;
// the file size stays the same
    InitWIF();
// std::string::iterator it = inputfile[0].IFCode.begin();
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

    LogFile << "Line SL " << std::endl;

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

    LogFile << "Block SL " << std::endl;

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

    LogFile << "Shift Left " << std::endl;

    winputfile[wi].wIFlc = "000000";
    SLl = inputfile[i].IFCode.length();
    SLl -= 4;
    winputfile[wi].wIFCode = inputfile[i].IFCode.substr(4, SLl);
    wi++;

}
void CLEditFrame::ApplyXX()
{

    LogFile << "Apply XX " << std::endl;
 // no change to the file size - just the view
    for (i = 0; i < wfilecnt; i++)
    {
        if (inputfile[i].IFlc == "X"
        ||  inputfile[i].IFlc == "XX")
        {
            inputfile[i].IFlc      = "000000";
            winputfile[i].wIFlc   = "000000";
            winputfile[i].wIFCode = inputfile[i].IFCode;
            XX[i].excluded = true;
        }
    }
// impact is to Load Screen - impact the view

}
void CLEditFrame::ApplyI()
{

    LogFile << "Apply I " << std::endl;
// increases the file size
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

    LogFile << "Line Insert " << std::endl;

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

    LogFile << "Copy The Line " << std::endl;

    winputfile[wi].wIFlc   = "000000";
    winputfile[wi].wIFCode = inputfile[i].IFCode;
    wi++;

}
void CLEditFrame::RefreshInput()
{

    LogFile << "Refresh Input " << std::endl;

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
 // screen
    InitScreen();
// variables
    haveaFile = false;
    CurrentFile = "";       // the name of the file currently being edite
    Byte        = ' ';      // do nothing - like a continue
    ypos        = 0;        // Y position
    pos         = 0;        // search position
    strpos      = 0;        // start position
    Mstrl       = 0;        // length of Move string
    Ostrl       = 0;        // length of Overlay string
    posp1       = 0;        // string position plus 1 - next byte
    str         = "";       // common string
    i           = 0;        // index into string
    wi          = 0;        // index into work string
    l           = 0;        // index other
// find
    FindStr     = "";       // find string
    res         = 0;        // result of STD::STRING::FIND
    FindCnt     = 0;        // number of times string found
    MinusOne    = -1;       // a constant
    f           = 0;        // index into found string locations
    prevf       = 0;        // previously found string location
    page        = 0;        // page number
    ofpage      = 0;        // number of pages
    pgs         = 0;        // whole number of pages
    pgsf        = 0.0f;     // fractional pages
// change
    ChangeFrom  = "";       // change from string
    ChangeFroml = 0;        // change from string length
    ChangeLineT  = "";      // change line to string
    ChangeLineTl = 0;       // change line to string length
    ChangeLineF  = "";      // change line from string
    ChangeLineFl = 0;       // change line from string length
    ChngCnt     = 0;        // number of times change from string found
    tf          = 0;        // index into change from found string locations
    prevtf      = 0;        // previously found string location
    ChangeTo    = "";       // change to string
    ChangeTol   = 0;        // change to string length
// Command
    Commandl    = 0;        // the length of the command line string
    Commandstr      = "";   // the command string
    PrimaryCommand  = "";   // the Primary command
    FirstParameter  = "";   // the first parameter
    SecondParameter = "";   // the second parameter
    ThirdParameter  = "";   // the third parameter
// for binary search
    left = 0;               // lower bound of array
    right = 0;              // upper bound of array
    mid = 0;                // location of 'key' if found
    key = "";               // key value to search for
// this is the "screen" 50 lines of visible code ( line command area 6 bytes / line of code 80 bytes)
    InitUser();
// to make the line command area pretty "000010"
// ostringstream os;     defined local because otherwise it concatenates
    prettyint = 0;      // STD::OSTRINGSTREAM::SETW number to output
    prettystr = "";     // result string from STD::OSTRINGSTREAM::SETW
// error / logging
    Return = true;          // return
    ReturnFunction = "";    // the name of the function running
    ReturnCode = "";        // a return code
    ReturnMessage = "";     // a meaningful return message
// file to and from file functions
//  InitCF();
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
// index to found strings - find
    InitFF();
// index to found strings - change from
    InitTF();
// index to excluded lines
    InitXX();

}
void CLEditFrame::InitCF()
{

    LogFile << "Init CF File " << std::endl;
// file to or from file functions
    CF.inputfile[0].IFCode = "";    // Code string

    for (i = 1; i < 25000; i++)
    {
        CF.inputfile[i] = CF.inputfile[0];
    }

}
void CLEditFrame::InitDB()
{

    LogFile << "Init DB File " << std::endl;
// file to or from stage database functions
    DB.inputfile[0].IFCode = "";    // Code string
    for (i = 1; i < 25000; i++)
    {
        DB.inputfile[i] = DB.inputfile[0];
    }

}
void CLEditFrame::InitFF()
{

    LogFile << "Init FF " << std::endl;

    FF[0].index = 0;    // where in the winput is the string found - an index
    FF[0].pos = 0;      // what position - an index

    for (f = 1; f < 25000; f++)
    {
        FF[f] = FF[0];
    }

}
void CLEditFrame::InitTF()
{

    LogFile << "Init TF " << std::endl;

    TF[0].index = 0;    // where in the winput is the string change from found - an index
    TF[0].pos = 0;      // what position - an index

    for (tf = 1; tf < 25000; tf++)
    {
        TF[tf] = TF[0];
    }

}
void CLEditFrame::InitCTrackers()
{

    LogFile << "Init CT Trackers " << std::endl;
    changes = false;            // did anything on the screen change - effects scrolling
    changesapplied = true;      // did the changes get applied - might be incomplete request
    badchanges = false;         // requested changes didn't make sense
    afters = 0;                 // number of After requests
    befores = 0;                // number of Before requests
    LCcnt = 0;                  // number of line commands requested

    CCcnt   = 0;        // number of block Copy lines requests
    CCstart = 0;        // index to the first CC line in the block
    CCend   = 0;        // index to the last CC line in the block
    CCrows  = 0;        // how many rows in the Copy block
    singleC = 0;        // Copy a line - need Before(s) or After(s)
    blockCC = false;    // Copy a block - need Before(s) or After(s) - can be used in a Create

    DDcnt   = 0;        // number of block Delete line requests
    DDstart = 0;        // index to the first DD line in the block
    DDend   = 0;        // index to the last DD line in the block
//  DDrows  = 0;             // how many rows in the Delete Block - no need to capture them, we just need to know where they are, they are being disguarded
    singleD = 0;        // Delete a line
    blockDD = false;    // Delete a block of lines

    singleI = 0;        // insert a single line

    MMcnt   = 0;        // number of Move line requests
    MMstart = 0;        // index to the first MM line in the block
    MMend   = 0;        // index to the last MM line in the block
    MMrows  = 0;        // how many rows in the Move block
    singleM = 0;        // Move a line - need Before(s) or After(s)
    blockMM = false;    // Move a block of lines - need Before(s) or After(s)

    OOcnt   = 0;        // number of Move Overlay line requests
    OOstart = 0;        // index to the last OO line in the block
    OOend   = 0;        // index to the last OO line in the block
    OOrows  = 0;        // how many rows in the Overlay block
    singleO = 0;        // Overlay a line - needs single Move
    blockOO = false;    // Overlay a block of lines - needs a block Move

    RRcnt   = 0;        // number of Repeat line requests
    RRstart = 0;        // index to the last RR line in the block
    RRend   = 0;        // index to the last RR line in the block
    RRrows  = 0;
    singleR = 0;        // Repeat a line
    blockRR = false;    // Repeat a block of lines

    SRcnt    = 0;       // number of Shift Right line requests
    SRstart  = 0;       // index to the last SR line in the block
    SRend    = 0;       // index to the last SR line in the block
//  SRrows   = 0;       // how many rows in the Shift Right block - no need to capture them, we just need to know where they are, they are being Shifted Right
    singleSR = 0;       // Right Shift a line ">" - needs a number of characters (default is one space)
    SRi      = 4;       // number of characters to Shift Right
    blockSR  = false;   // Right Shift a block of lines ">>" - needs a number of characters (default is one space)
    SRl      = 0;       // length of the string to be Shifted Right

    SLcnt    = 0;       // number of Shift Left line requests
    SLstart  = 0;       // index to the last SL line in the block
    SLend    = 0;       // index to the last SL line in the block
//  SLrows   = 0;       // how many rows in the Shift Left block - no need to capture them, we just need to know where they are, they are being Shifted Left
    singleSL = 0;       // left shift a line "<" - needs a number of characters (default is one space)
    SLi      = 4;       // number of characters to shift left
    blockSL  = false;   // left shift a block of lines - needs a number of characters (default is one space)
    SLl      = 0;       // length of the string to be Shifted Left

    XXcnt   = 0;        // number of Exclude line requests
    XXstart = 0;        // index to the last XX line in the block
    XXend   = 0;        // index to the last XX line in the block
//  XXrows   = 0;       // how many rows in the Exclude block - no need to capture them, we just need to know where they are, they are being Excluded from view & changes
    singleX = 0;        // Exclude a line
    blockXX = false;    // Exclude a block of lines

}
void CLEditFrame::InitScreen()
{

    LogFile << "Init Screen " << std::endl;

    for (u =0; u < 50; u++)
    {
        CL[u].Line->ChangeValue("000000");  // line command string
        CL[u].Code->ChangeValue("");        // Code string
    }

}
void CLEditFrame::InitUser()
{

    LogFile << "Init User " << std::endl;
// this is the input from the user screen
// 50 lines on the screen
    u = 0;
    Input[0].Linel   = 0;       // line command string length
    Input[0].Linestr = "";      // line command string
    Input[0].Codel   = 0;       // Code string length
    Input[0].Codestr = "";      // Code string

    for (i = 1; i < 50; i++)
    {
        Input[i] = Input[0];
    };
 // a single line
    uInput.Linel   = 0;     // line command string length
    uInput.Linestr = "";    // line command string
    uInput.Codel   = 0;     // Code string length
    uInput.Codestr = "";    // Code string
 // a line of user input from the screen
    UserLinel = 0;          // line command string length
    UserLinestr = "";       // line command string
    UserCodel = 0;          // Code string length
    UserCodestr = "";       // Code string

}
void CLEditFrame::InitIF()
{

    LogFile << "Init IF " << std::endl;
// the file being processed
    FileSizeError = false;      // file size error - exceeds 25000 lines
    inputfile[0].IFlc = "000000";   // line command string
    inputfile[0].IFCode = "";       // Code string

    for (i = 1; i < 25000; i++)
    {
        inputfile[i] = inputfile[0];
    }

}
void CLEditFrame::InitWIF()
{

    LogFile << "Init WIF " << std::endl;
// the work file being processed
//  wfilecnt = 0;       // NO! do not set to zero!
//  oldwfilecnt = 0;    // NO! do not set to zero!
    winputfile[0].wIFlc = "000000";     // line command string
    winputfile[0].wIFCode = "";         // Code string

    for (i = 1; i < 25000; i++)
    {
        winputfile[i] = winputfile[0];
    }

}
void CLEditFrame::InitCC()
{

    LogFile << "Init CC " << std::endl;
 // a line to be Copied
    haveaCC = false;
    ccinputfile[0].cIFCode = "";    // Code string

    for (i = 1; i < 2000; i++)
    {
        ccinputfile[i] = ccinputfile[0];
    }

    cinputfile.cIFCode = "";
    singleC = 0;        // Copy a line - need Before(s) or After(s)
    blockCC = false;    // Copy a block - need Before(s) or After(s) - can be used in a Create
    haveaC = 0;

}
void CLEditFrame::InitMM()
{

    LogFile << "Init MM " << std::endl;

    singleM = 0;  // Move a line - need Before(s) or After(s)
    blockMM = false;  // Move a block of lines - need Before(s) or After(s)
// a line to be moved
    haveaM = 0;
    minputfile.mIFCode = "";    // Code string
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

    LogFile << "Init OO " << std::endl;

    singleO = 0;  // Overlay a line - needs single Move
    blockOO = false;  // Overlay a block of lines - needs a block Move
// a line to be overlaid
    haveaO = 0;
    oinputfile.oIFCode = "";        // Code string
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

    LogFile << "Init RR " << std::endl;

    singleR = 0;  // Repeat a line
    blockRR = false;  // Repeat a block of lines
// a line to be Repeated
    haveaR = 0;
// a block of lines to be Repeated
    haveaRR = false;
    rrinputfile[0].rIFCode = "";    // Code string
    for (i = 1; i < 2000; i++)
    {
        rrinputfile[i] = rrinputfile[0];
    }

}
void CLEditFrame::InitXX()
{

    LogFile << "Init XX " << std::endl;

    for (i = 1; i < 25000; i++)
    {
        XX[i].excluded = false;
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
        CL[u].Line = new wxTextCtrl(Panel
                                   ,wxID_ANY
                                   ,"000000"
                                   ,wxPoint(1,ypos)
                                   ,wxSize(60,20),wxBORDER_NONE);
        CL[u].Line->SetMaxLength(6);
        CL[u].Code = new wxTextCtrl(Panel
                                   ,wxID_ANY
                                   ,""
                                   ,wxPoint(61,ypos)
                                   ,wxSize(1610,20)
                                   ,wxBORDER_NONE);
        CL[u].Code->SetMaxLength(200);
        ypos += 20;
    }

    CreateStatusBar();

    wxLogStatus("Hello ");

    Return = true;  // not the C++ return, a wx 'return' yuck

}
void CLEditFrame::OpenLog()
{

    LogFile.open("CLEditLog.txt", std::ios::out | ios_base::app);

    if  (!LogFile.is_open())
    {
        ReturnFunction = "Open Log ";
        ReturnCode = "3502 ";
        ReturnMessage = " Log File Open error ";
        OnTerminal();
    }

    bytecnt = LogFile.tellg();

    if  (bytecnt > FILE_SIZE)
    {
        CloseLog();
        ETL.fileiname = "CLEditLog.txt";
        rc = ETL.ETL();
        OpenLogn();
    }

    LogFile << "Log file size " << to_string(bytecnt) << std::endl;

}
void CLEditFrame::OpenLogn()
{

    LogFile.open("CLEditLog.txt", std::ios::out);

    if  (!LogFile.is_open())
    {
        ReturnFunction = "Open Log New ";
        ReturnCode = "3503 ";
        ReturnMessage = " Log File Open error ";
        OnTerminal();
    }

}
void CLEditFrame::CloseLog()
{

    LogFile.close();

}
void CLEditFrame::OpenErr()
{

    ErrFile.open("CLEditErr.txt", std::ios::out | ios_base::app);

    if  (!ErrFile.is_open())
    {
        ReturnFunction = "Open Error ";
        ReturnCode = "3504 ";
        ReturnMessage = " Error File Open error ";
        OnTerminal();
    }

    bytecnt = ErrFile.tellg();

    if  (bytecnt > FILE_SIZE)
    {
        CloseErr();
        OpenErrn();
    }

    LogFile << "Error file size " << to_string(bytecnt) << std::endl;

}
void CLEditFrame::OpenErrn()
{

    ErrFile.open("CLEditErr.txt", std::ios::out);

    if  (!ErrFile.is_open())
    {
        ReturnFunction = "Open Error new ";
        ReturnCode = "3505 ";
        ReturnMessage = " Error File Open error ";
        OnTerminal();
    }

}
void CLEditFrame::CloseErr()
{

    ErrFile.close();

}

