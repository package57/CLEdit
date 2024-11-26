// a frame is a window

        CLEditFrame(const wxString & title);

//controls
        wxPanel      * Panel;
        wxTextCtrl   * Command;
        wxButton     * Apply;

// this is the "screen"
// Line
// Code
        struct Screen
        {
            wxTextCtrl * Line;  // line command action
            wxTextCtrl * Code;  // text
        };
        Screen CL[50];

// this is captured from the "screen"
// Line
// Code
        struct Userinput
        {
            int Linel;          // line command string length
            wxString Linestr;   // line command string
            int Codel;          // Code string length
            wxString Codestr;   // Code string
        };
        Userinput Input[50];    // 50 lines on the screen
        Userinput uInput;       // a single line


        wxString    Commandstr;         // the command string
        wxString    PrimaryCommand;     // the Primary command
        wxString    FirstParameter;     // the first parameter
        wxString    SecondParameter;    // the second parameter
        wxString    ThirdParameter;     // the third parameter
        wxString    UserCodestr;        // Code string
        wxString    UserLinestr;        // line command string

