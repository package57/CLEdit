#pragma once
#include <wx/wx.h>

class CLEditFrame
: public wxFrame
{

    public:

        CLEditFrame(const wxString & title);

//controls
        wxPanel      * Panel;
        wxTextCtrl   * Command;
        wxButton     * Apply;

        wxTextCtrl   * Line01;
        wxTextCtrl   * Code01;
        wxTextCtrl   * Line02;
        wxTextCtrl   * Code02;
        wxTextCtrl   * Line03;
        wxTextCtrl   * Code03;
        wxTextCtrl   * Line04;
        wxTextCtrl   * Code04;
        wxTextCtrl   * Line05;
        wxTextCtrl   * Code05;

        wxStaticText * Progress;


// variables
// Command
        char        Byte;

        int         strpos;
        int         i;
        int         Commandl;
        wxString    Commandstr;
        wxString    PrimaryCommand;
        wxString    FirstParameter;
        wxString    SecondParameter;
        wxString    ThirdParameter;

// this is the "screen"
// Line
// Code
        int u;
        struct Userinput
        {
            int Linel;
            wxString Linestr;
            int Codel;
            wxString Codestr;
        };
        Userinput Input[5];
        int         UserLinel;
        wxString    UserLinestr;
        int         UserCodel;
        wxString    UserCodestr;

// Progress
        std::string  Progressstr;
// error / logging
        bool        Return;

        std::string ReturnFunction;
        std::string ReturnCode;
        std::string ReturnMessage;

// Logic
// event handlers
        //void OnKeyDown(wxKeyEvent & event);
        void OnApplyClicked(wxCommandEvent & event);
        void OnKeyEvent(wxKeyEvent & event);
        void OnExitClicked(wxCloseEvent & event);
// functions
        void EndLoop();
        void OnTerminal();
        void CreateControls();
        void BindEvents();

// process Command
        void FindPrimary();
        void FindFirst();
        void FindSecond();
        void FindThird();
// process screen
        void ReadScreen();
        void InitUserInput();
        void LoopLine();
        void LoopCode();
        void LoopDump();
};
