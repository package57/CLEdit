


// the file being processed
        struct InputFile
        {
            std::string IFlc;       // line command
            std::string IFCode;     // the line of code
        };
        InputFile inputfile[25000];  // 23,000 line is the biggest single block of code I've ever seen


// the work file being processed
        struct wInputFile
        {
            std::string wIFlc;      // line command string
            std::string wIFCode; // the line of code
        };
        wInputFile winputfile[25000];  // 23,000 line is the biggest single block of code I've ever seen


        struct cInputFile
        {
            std::string cIFCode;    // Code string
        };
// a line to be Copied
        cInputFile cinputfile;
// a block of lines to be Copied
        cInputFile ccinputfile[2000];  // a reasonable block copy would be what you can see on the current screen -


        struct mInputFile
        {
            std::string mIFCode;    // Code string
        };
// a line to be Moved
        mInputFile minputfile;
// a block of lines to be Moved
        mInputFile mminputfile[2000]; // a reasonable block move would be what you can see on the current screen


        struct oInputFile
        {
            std::string oIFCode;    // Code string
        };
// a line to be Overlaid
        oInputFile oinputfile;
// a block of lines to be Overlaid

        oInputFile ooinputfile[2000]; // a reasonable block overlay would be what you can see on the current screen



        struct rInputFile
        {
            std::string rIFCode; // the line of code
        };
// a line to be Repeated
// a block of lines to be Repeated
        rInputFile rrinputfile[2000]; // a reasonable block overlay would be what you can see on the current screen


// index to found strings - find
        struct FindFile
        {
            int index;
            int pos;
        };
        FindFile FF[25000];  // not at all likely


// index to found strings - change from
        struct ChngFile
        {
            int index;
            int pos;
        };
        ChngFile TF[25000];  // not at all likely


// index to excluded lines
        struct XXFile
        {
            bool excluded;
        };
        XXFile XX[25000];  // not at all likely

