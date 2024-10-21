#include <iostream>
#include <wx/wx.h>
#include "CLEditMain.h"

CLEditFrame::CLEditFrame(const wxString & title)
: wxFrame(nullptr
          ,wxID_ANY
          ,title
          ,wxDefaultPosition
          ,wxDefaultSize
          ,wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{

//    Bind(wxEVT_KEY_DOWN, & CLEditFrame::OnKeyDown, this);

    CreateControls();

    BindEvents();

    if (Return == false)
    {
        ReturnFunction = "CreateControls ";
        ReturnCode = "3500 ";
        ReturnMessage = " Create Controls failure";
        OnTerminal();
    }

}

void CLEditFrame::CreateControls()
{

    Panel = new wxPanel(this);

    //this->Bind(wxEVT_CLOSE_WINDOW, & CLEditFrame::OnExitClicked, this);

    Command = new wxTextCtrl(Panel
                             ,wxID_ANY
                             ,"enter command here"
                             ,wxPoint(1,1)      // l-r,t-b
                             ,wxSize(1870,20)  //w,h
                             ,wxBORDER_NONE
                            );

    Command->SetMaxLength(200);

    Apply = new wxButton(Panel
                         ,wxID_ANY
                         ,"Apply"
                         ,wxPoint(1870,1)
                         ,wxSize(50,20)
                         ,wxBORDER_NONE
                        );

//    Apply->Bind(wxEVT_BUTTON, & CLEditFrame::OnApplyClicked, this);

    Line01 = new wxTextCtrl(Panel
                           ,wxID_ANY
                           ,"000010"
                           ,wxPoint(1,20)
                           ,wxSize(60,20)
                           ,wxBORDER_NONE
                           );
    Line01->SetMaxLength(6);

    Code01 = new wxTextCtrl(Panel
                           ,wxID_ANY
                           ,"If"
                           ,wxPoint(61,20)
                           ,wxSize(1200,20)
                           ,wxBORDER_NONE
                           );
    Code01->SetMaxLength(80);

    Line02 = new wxTextCtrl(Panel
                           ,wxID_ANY
                           ,"000020"
                           ,wxPoint(1,40)
                           ,wxSize(60,20)
                           ,wxBORDER_NONE
                           );
    Line02->SetMaxLength(6);

    Code02 = new wxTextCtrl(Panel
                           ,wxID_ANY
                           ,"Then"
                           ,wxPoint(61,40)
                           ,wxSize(1200,20)
                           ,wxBORDER_NONE
                           );
    Code02->SetMaxLength(80);

    Line03 = new wxTextCtrl(Panel
                           ,wxID_ANY
                           ,"000030"
                           ,wxPoint(1,60)
                           ,wxSize(60,20)
                           ,wxBORDER_NONE
                           );
    Line03->SetMaxLength(6);

    Code03 = new wxTextCtrl(Panel
                           ,wxID_ANY
                           ,"Or"
                           ,wxPoint(61,60)
                           ,wxSize(1200,20)
                           ,wxBORDER_NONE
                           );
    Code03->SetMaxLength(80);

    Line04 = new wxTextCtrl(Panel
                           ,wxID_ANY
                           ,"000040"
                           ,wxPoint(1,80)
                           ,wxSize(60,20)
                           ,wxBORDER_NONE
                           );
    Line04->SetMaxLength(6);

    Code04 = new wxTextCtrl(Panel
                           ,wxID_ANY
                           ,"Else"
                           ,wxPoint(61,80)
                           ,wxSize(1200,20)
                           ,wxBORDER_NONE
                           );
    Code04->SetMaxLength(80);

    Line05 = new wxTextCtrl(Panel
                           ,wxID_ANY
                           ,"000050"
                           ,wxPoint(1,100)
                           ,wxSize(60,20)
                           ,wxBORDER_NONE
                           );
    Line05->SetMaxLength(6);

    Code05 = new wxTextCtrl(Panel
                           ,wxID_ANY
                           ,"Ok?"
                           ,wxPoint(61,100)
                           ,wxSize(1200,20)
                           ,wxBORDER_NONE
                           );
    Code05->SetMaxLength(80);

    Progress = new wxStaticText(Panel
                           ,wxID_ANY
                           ,"Progress"
                           ,wxPoint(1260,20)
                           ,wxSize(657,1000)
                           ,wxTE_MULTILINE
                           );

    CreateStatusBar();

    Return = true;

}
void CLEditFrame::BindEvents()
{

  this->Bind(wxEVT_KEY_DOWN, & CLEditFrame::OnKeyEvent, this);

  this->Bind(wxEVT_CLOSE_WINDOW, & CLEditFrame::OnExitClicked, this);

  Apply->Bind(wxEVT_BUTTON, & CLEditFrame::OnApplyClicked, this);

}
void CLEditFrame::OnKeyEvent(wxKeyEvent & event)
{
    ReturnFunction = "OnKeyEvent ";
    ReturnCode = "0000 ";

    switch ( event.GetKeyCode() )
    {
        case WXK_NONE:
            ReturnMessage = "No Key";
        case WXK_CONTROL_F:
        case WXK_F5:
            ReturnMessage = "Find ";
        case WXK_END:
        case WXK_NUMPAD_END:
            ReturnMessage = "Bottom ";
        case WXK_HOME:
        case WXK_NUMPAD_BEGIN:
            ReturnMessage = "Home ";
        case WXK_UP:
        case WXK_F7:
        case WXK_PAGEUP:
        case WXK_NUMPAD_UP:
        case WXK_NUMPAD_PAGEUP:
            ReturnMessage = "Up ";
        case WXK_DOWN:
        case WXK_F8:
        case WXK_PAGEDOWN:
        case WXK_NUMPAD_DOWN:
        case WXK_NUMPAD_PAGEDOWN:
            ReturnMessage = "Down ";
        case WXK_HELP:
        case WXK_F1:
            ReturnMessage = "Help ";
//      case WXK_F2: split
//      case WXK_F3: return
        //      case WXK_F4: menu
        case WXK_F6:
            ReturnMessage = "Change ";
    }

    OnTerminal();

}
void CLEditFrame::OnExitClicked(wxCloseEvent & event)
{

    ReturnFunction = "OnExitClicked ";
    ReturnCode = "0000 ";
    ReturnMessage = " ";
    OnTerminal();

    event.Skip();
}
void CLEditFrame::OnApplyClicked(wxCommandEvent & event)
{

    ReturnFunction = "OnApplyClicked ";
    ReturnCode = "0000 ";
    ReturnMessage = " ";
    OnTerminal();

    Progressstr = "Apply Commanded \n";
    Progress->SetLabel(Progressstr);


    ReadScreen();


    Commandl = Command->GetLineLength(0);
    std::cout << "Length " << Commandl << std::endl;
    if  (Commandl == 0)
    {
        goto exitOnApplyClicked;
    }

    Commandstr = Command->GetLineText(0); //GetValue();

    FindPrimary();

    FindFirst();

    FindSecond();

    FindThird();

//change string tostring f6 all
    if (PrimaryCommand == "change")
    {
        Progressstr += "change begun \n";
        Progress->SetLabel(Progressstr);
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " " + ThirdParameter + " applied");
        goto exitOnApplyClicked;
    }
//copy file
    if (PrimaryCommand == "copy")
    {
        Progressstr += "copy begun \n";
        Progress->SetLabel(Progressstr);
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " " + ThirdParameter + " applied");
        goto exitOnApplyClicked;
    }
//exclude  'x all'
    if (PrimaryCommand == "exclude"
    ||  PrimaryCommand == "x")
    {
        Progressstr += "exclude begun \n";
        Progress->SetLabel(Progressstr);
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " " + ThirdParameter + " applied");
        goto exitOnApplyClicked;
    }
//exit
    if (PrimaryCommand == "exit")
    {
        Progressstr += "exit begun \n";
        Progress->SetLabel(Progressstr);
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " " + ThirdParameter + " applied");
        goto exitOnApplyClicked;
    }
//find string f5 all
    if (PrimaryCommand == "find")
    {
        Progressstr += "find begun \n";
        Progress->SetLabel(Progressstr);
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " " + ThirdParameter + " applied");
        goto exitOnApplyClicked;
    }
//open file
    if (PrimaryCommand == "open")
    {
        Progressstr += "open begun \n";
        Progress->SetLabel(Progressstr);
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " " + ThirdParameter + " applied");
        goto exitOnApplyClicked;
    }
//reset
    if (PrimaryCommand == "reset")
    {
        Progressstr += "Reset begun \n";
        Progress->SetLabel(Progressstr);
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " " + ThirdParameter + " applied");
        goto exitOnApplyClicked;
    }
//save file
    if (PrimaryCommand == "save")
    {
        Progressstr += "save begun \n";
        Progress->SetLabel(Progressstr);
        wxLogStatus(PrimaryCommand + " " + FirstParameter + " " + SecondParameter + " " + ThirdParameter + " applied");
        goto exitOnApplyClicked;
    }

    wxLogStatus("Changes Applied");

    Return = true;

exitOnApplyClicked:

    Command->Clear();
    Command->SetFocus();

}
void CLEditFrame::FindPrimary()
{

    Progressstr += "Find Primary Command \n";
    Progress->SetLabel(Progressstr);

    PrimaryCommand = "";

    for (i = 0; i < Commandl; i++)
    {
        if  (Commandstr[i] == ' ')
        {
            strpos = i;
            EndLoop();
        }
        else
        {
            PrimaryCommand += Commandstr[i];
        }
    }

    Progressstr += PrimaryCommand;
    Progressstr += "\n";
    Progress->SetLabel(Progressstr);

}
void CLEditFrame::FindFirst()
{

    Progressstr += "Find First Parameter \n";
    Progress->SetLabel(Progressstr);

    FirstParameter = "";

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
                EndLoop();
            }
        }
        else
        {
            FirstParameter += Commandstr[i];
        }
    }

    Progressstr += FirstParameter;
    Progressstr += "\n";
    Progress->SetLabel(Progressstr);

}
void CLEditFrame::FindSecond()
{

    Progressstr += "Find Second Parameter \n";
    Progress->SetLabel(Progressstr);

    SecondParameter = "";

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
                EndLoop();
            }
        }
        else
        {
            SecondParameter += Commandstr[i];
        }
    }

    Progressstr += SecondParameter;
    Progressstr += "\n";
    Progress->SetLabel(Progressstr);

}
void CLEditFrame::FindThird()
{

    Progressstr += "Find Third Parameter \n";
    Progress->SetLabel(Progressstr);

    ThirdParameter = "";

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
                EndLoop();
            }
        }
        else
        {
            ThirdParameter += Commandstr[i];
        }
    }

    Progressstr += ThirdParameter;
    Progressstr += "\n";
    Progress->SetLabel(Progressstr);
}

void CLEditFrame::ReadScreen()
{

    InitUserInput();

    u = 0;
    UserLinel   = Line01->GetLineLength(0);
    UserLinestr = Line01->GetLineText(0);
    UserCodel   = Code01->GetLineLength(0);
    UserCodestr = Code01->GetLineText(0);
    LoopLine();
    LoopCode();

    u = 1;
    UserLinel   = Line02->GetLineLength(0);
    UserLinestr = Line02->GetLineText(0);
    UserCodel   = Code02->GetLineLength(0);
    UserCodestr = Code02->GetLineText(0);
    LoopLine();
    LoopCode();

    u = 2;
    UserLinel   = Line03->GetLineLength(0);
    UserLinestr = Line03->GetLineText(0);
    UserCodel   = Code03->GetLineLength(0);
    UserCodestr = Code03->GetLineText(0);
    LoopLine();
    LoopCode();

    u = 3;
    UserLinel   = Line04->GetLineLength(0);
    UserLinestr = Line04->GetLineText(0);
    UserCodel   = Code04->GetLineLength(0);
    UserCodestr = Code04->GetLineText(0);
    LoopLine();
    LoopCode();

    u = 4;
    UserLinel   = Line05->GetLineLength(0);
    UserLinestr = Line05->GetLineText(0);
    UserCodel   = Code05->GetLineLength(0);
    UserCodestr = Code05->GetLineText(0);
    LoopLine();
    LoopCode();

    LoopDump();

    Progress->SetLabel(Progressstr);

}
void CLEditFrame::InitUserInput()
{

    Input[0].Linel = 0;
    Input[0].Linestr = "";
    Input[0].Codel = 0;
    Input[0].Codestr = "";

    for (u = 1; u < 5; u++)
    {
        Input[u] = Input[0];
    }

}
void CLEditFrame::LoopLine()
{

    Input[u].Linel = UserLinel;

    for (i = 0; i < UserLinel; i++)
    {
        Input[u].Linestr += UserLinestr[i];
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
void CLEditFrame::LoopDump()
{

    for (u = 0; u < 5; u++)
    {
        Progressstr += "User Line Command ";
        Progressstr += Input[u].Linestr;
        Progressstr += " Code ";
        Progressstr += Input[u].Codestr;
        Progressstr += "\n";
    }

}
void CLEditFrame::EndLoop()
{
    i = 100;
    u = 200;
}
void CLEditFrame::OnTerminal()
{

    std::cout << ReturnFunction << ReturnCode << ReturnMessage << std::endl;

}
