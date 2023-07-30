#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <time.h>
#include <vector>

#include "KeyClass.h"

int main()
{
    DWORD        mode;          /* Preserved console mode */
    INPUT_RECORD event;         /* Input event */
    BOOL         done = FALSE;  /* Program termination flag */
    unsigned int counter = 0;   /* No of records */

    std::vector<KeyClass> KeySequence;

    float hold_t, downdown_t, updown_t;
    // , sdowndown_t, supdown_t;
    clock_t up_t = 0, down_t = 0, sprev_t = 0, uprev_t = 0, dprev_t = 0, sup_t = 0, sdown_t = 0;

    //char str1[20], str2[15], filename[50] = "ks_";
    std::string name, filename;

    std::cout << "Enter name: ";
    std::cin >> name;


    // Derive current time stamp as session ID
    std::time_t current = std::time(NULL);
    std::tm* ts = std::localtime(&current);

    std::stringstream timestamp_sstr;

    // Convert timestamp to a string, this will form the session ID
    timestamp_sstr << ts->tm_year + 1900;
    timestamp_sstr << std::setfill('0') << std::setw(2) << ts->tm_mon + 1 << ts->tm_mday << ts->tm_hour << ts->tm_min << ts->tm_sec;
    std::string SessionID = "SS" + timestamp_sstr.str();

    std::cout << "Session ID: " << SessionID;

    // Assign file name 
    filename = "ks_" + name + timestamp_sstr.str() + ".csv";

    /* Don't use binary for text files, OK?  ;-) */
    //FILE* myfile = fopen(filename.c_str(), "w");

    /* Get the console input handle */
    HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);

    /* Preserve the original console mode */
    GetConsoleMode(hstdin, &mode);

    /* Set to no line-buffering, no echo, no special-key-processing */
    SetConsoleMode(hstdin, 0);

    /* Give the user instructions */
    printf(
        "\nPlease type the test word \".tie5Roanl\" followed by <Enter> key for at least 25 times or as many as you like\n"
        "Do not rush and just try to type normally during the typing of \".tie5Roanl\"...\n"
        "If you have missed any keys, you can abort by pressing <Enter> key and cancel the entry...\n"
        "This will ignore the bad entry and you can resume to retype the \".tie5Roanl\" again\n"
        "Please note that you can always take a break to pause and rest your fingers after each <Enter> key...\n\n"
        "To end the session, just press ESC to quit.\n\n"
    );

    BOOL shift = FALSE;
    unsigned char ch = 0;
    int count = 0;
    KeyClass* NewObj = new KeyClass();

    while (!done)
    {
        if (WaitForSingleObject(hstdin, 0) == WAIT_OBJECT_0)  /* if kbhit */
        {
            DWORD count;  /* ignored */

            /* Get the input event */
            ReadConsoleInput(hstdin, &event, 1, &count);

            if ((event.EventType == KEY_EVENT) && event.Event.KeyEvent.bKeyDown)
                switch (event.Event.KeyEvent.wVirtualKeyCode)
                {
                    // logic to parse for ".tie5Roan." pass-string
                case VK_OEM_PERIOD:      // "."

                    // Create a new object for KeyClass
                    NewObj = new KeyClass();
                    NewObj->total_presses = 0;

                    down_t = clock();      // start timer
                    dprev_t = down_t;

                    count = 0;
                    // capture key down time
                    NewObj->keydown[0] = down_t;
                    break;
                case 0x54:      // "t"
                    down_t = clock();               // start timer
                    downdown_t = (float)(down_t - dprev_t) / CLOCKS_PER_SEC;
                    dprev_t = down_t;

                    // capture key down
                    NewObj->keydown[1] = down_t;
                    break;
                case 0x49:      // "i"
                    down_t = clock();   // start timer
                    downdown_t = (float)(down_t - dprev_t) / CLOCKS_PER_SEC;
                    dprev_t = down_t;

                    // capture key down
                    NewObj->keydown[2] = down_t;
                    break;
                case 0x45:      // "e"
                    down_t = clock();   // start timer
                    downdown_t = (float)(down_t - dprev_t) / CLOCKS_PER_SEC;
                    dprev_t = down_t;

                    // capture key down
                    NewObj->keydown[3] = down_t;
                    break;
                case 0x35:      // "5"
                    down_t = clock();   // start timer
                    downdown_t = (float)(down_t - dprev_t) / CLOCKS_PER_SEC;
                    dprev_t = down_t;

                    // capture key down
                    NewObj->keydown[4] = down_t;
                    break;

                case VK_SHIFT:  // "Shift"

                    shift = TRUE;
                    break;

                case 0x52:      // "Shift R"
                    down_t = clock();   // start timer
                    downdown_t = (float)(down_t - dprev_t) / CLOCKS_PER_SEC;
                    dprev_t = down_t;

                    // capture key down
                    NewObj->keydown[5] = down_t;
                    break;
                case 0x4F:      // "o"
                    down_t = clock();   // start timer
                    downdown_t = (float)(down_t - dprev_t) / CLOCKS_PER_SEC;
                    dprev_t = down_t;

                    // capture key down
                    NewObj->keydown[6] = down_t;
                    break;
                case 0x41:      // "a"
                    down_t = clock();   // start timer
                    downdown_t = (float)(down_t - dprev_t) / CLOCKS_PER_SEC;
                    dprev_t = down_t;

                    // capture key down
                    NewObj->keydown[7] = down_t;
                    break;
                case 0x4E:      // "n"
                    down_t = clock();   // start timer
                    downdown_t = (float)(down_t - dprev_t) / CLOCKS_PER_SEC;
                    dprev_t = down_t;

                    // capture key down
                    NewObj->keydown[8] = down_t;
                    break;
                case 0x4C:      // "l"
                    down_t = clock();   // start timer
                    downdown_t = (float)(down_t - dprev_t) / CLOCKS_PER_SEC;
                    dprev_t = down_t;

                    // capture key down
                    NewObj->keydown[9] = down_t;
                    break;

                case VK_RETURN: // "Return"
                    down_t = clock();   // start timer
                    downdown_t = (float)(down_t - dprev_t) / CLOCKS_PER_SEC;

                    // capture key down
                    NewObj->keydown[10] = down_t;

                    if (NewObj->Validate())
                        KeySequence.push_back(*NewObj);
                    else
                    {
                        std::cout << " - Invalid key sequence. Skip." << std::endl;
                        //std::cout << NewObj->ToString() << std::endl;
                    }

                    break;

                default:
                    done = FALSE;
                }

            /* Only respond to key release events */
            if ((event.EventType == KEY_EVENT) && !event.Event.KeyEvent.bKeyDown)
                switch (event.Event.KeyEvent.wVirtualKeyCode)
                {
                case VK_OEM_PERIOD:      // "."
                    up_t = clock();
                    hold_t = (float)(up_t - down_t) / CLOCKS_PER_SEC;
                    uprev_t = up_t;

                    NewObj->total_presses++;
                    NewObj->keyup[0] = up_t;
                    NewObj->keypressed[0] = '.';

                   
                    std::cout << ".";
                    break;
                case 0x54:      // "t"
                    up_t = clock();
                    updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;
                    uprev_t = up_t;

                    //count++;
                    NewObj->total_presses++;
                    NewObj->keyup[1] = up_t;
                    NewObj->keypressed[1] = 't';

                    std::cout << "t";
                    break;
                case 0x49:      // "i"
                    up_t = clock();
                    updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;
                    uprev_t = up_t;

                    //count++;
                    NewObj->total_presses++;
                    NewObj->keyup[2] = up_t;
                    NewObj->keypressed[2] = 'i';

                    std::cout << "i";
                    break;
                case 0x45:      // "e"
                    up_t = clock();
                    updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;
                    uprev_t = up_t;

                   
                    NewObj->total_presses++;
                    NewObj->keyup[3] = up_t;
                    NewObj->keypressed[3] = 'e';

                    std::cout << "e";
                    break;
                case 0x35:      // "5"
                    up_t = clock();
                    updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;
                    uprev_t = up_t;

                   
                    NewObj->total_presses++;
                    NewObj->keyup[4] = up_t;
                    NewObj->keypressed[4] = '5';

                    std::cout << "5";
                    break;

                case 0x52:      // "Shift R"
                    up_t = clock();
                    updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;

                    uprev_t = up_t;
                    if (shift)
                        std::cout << "R";
                    else
                        std::cout << "r";

                    shift = FALSE;
                    //if (ch == 5) ch++
                    //count++;
                    NewObj->total_presses++;
                    NewObj->keyup[5] = up_t;
                    NewObj->keypressed[5] = 'R';

                    break;

                case VK_SHIFT:
                    // sup_t = clock();
                    // hold_t = (float)(sup_t - sdown_t) / CLOCKS_PER_SEC;
                    // fprintf(myfile, "<H.Shift:%.3f>,", hold_t);
                    if (ch == 6) ch++;
                    break;

                case 0x4F:      // "o"
                    up_t = clock();
                    updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;
                    uprev_t = up_t;

                    //count++;
                    NewObj->total_presses++;
                    NewObj->keyup[6] = up_t;
                    NewObj->keypressed[6] = 'o';

                    std::cout << "o";
                   
                    break;
                case 0x41:      // "a"
                    up_t = clock();
                    updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;
                    uprev_t = up_t;

                    //count++;
                    NewObj->total_presses++;
                    NewObj->keyup[7] = up_t;
                    NewObj->keypressed[7] = 'a';

                    std::cout << "a";
                    
                    break;

                case 0x4E:      // "n"
                    up_t = clock();
                    updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;
                    uprev_t = up_t;

                    //count++;
                    NewObj->total_presses++;
                    NewObj->keyup[8] = up_t;
                    NewObj->keypressed[8] = 'n';

                    std::cout << "n";
                   
                    break;
                case 0x4C:      // "l"
                    up_t = clock();
                    updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;
                    uprev_t = up_t;

                    //count++;
                    NewObj->total_presses++;
                    NewObj->keyup[9] = up_t;
                    NewObj->keypressed[9] = 'l';

                    std::cout << "l";
                   
                    break;

                case VK_RETURN:
                    up_t = clock();
                    updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;

                    std::cout << std::endl;
                    break;

                case VK_ESCAPE:
                    std::cout << "\nThere are " << KeySequence.size() << " valid records." << std::endl;
                    std::cout << "\nThank you so much for your participation!\n";
                    done = TRUE;
                    break;
                default:
                   
                    count++;
                  
                    done = FALSE;
                }
        }
    }

    /* All done! */
    //printf("There are %d records\n", counter);

    // Write into file
    std::fstream fs;
    fs.open(filename, std::fstream::in | std::fstream::app);

    // header line
    fs << "User,Session,H.Period,UD.period.t,H.t,UD.t.i,H.i,UD.i.e,H.e,UD.e.five,H.five,UD.five.Shift.r,H.Shift.r,UD.Shift.r.o,H.o,UD.o.a,H.a,UD.o.n,H.n,UD.n.l,H.l,UD.l.Return"  << std::endl;
    
    // Write all the captured KeyClass objects timings into file
    for (auto item = KeySequence.begin(); item != KeySequence.end(); ++item)
    {

        fs << name << "," << SessionID << ",";
        fs << (*item).ToString() << std::endl;
        //std::cout << (*item).ToString() << std::endl;
        
    }

    // Close file stream
    fs.close();

    std::cout << "Records saved into " << filename << std::endl;
    
    SetConsoleMode(hstdin, mode);
    return 0;
 }