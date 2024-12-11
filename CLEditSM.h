#include <string>
class CLEditSM
{
    public:

        CLEditSM();
        virtual ~CLEditSM();

        int rowcnt;

        struct InputFile
        {
            std::string sortarea; // the sort area
            std::string IFCode; // the line of code
        };
        InputFile inputfile[25000];  // 23,000 line is the biggest single block of code I've ever seen aka "203"

        void SortSM();

    protected:

    private:

        int i;
        int j;
        int k;
        int l;
        int m;

        InputFile temp;

        void Swap();
        void Loop();
        void LoopLoop();

};
