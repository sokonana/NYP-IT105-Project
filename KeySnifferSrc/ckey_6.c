#include <stdio.h>
#include <windows.h>
#include <time.h>

int main()
{
    DWORD        mode;          /* Preserved console mode */
    INPUT_RECORD event;         /* Input event */
    BOOL         done = FALSE;  /* Program termination flag */
    unsigned int counter = 0;   /* No of records */

    float hold_t, downdown_t, updown_t;
    // , sdowndown_t, supdown_t;
    clock_t up_t=0, down_t=0, sprev_t=0, uprev_t=0, dprev_t=0, sup_t=0, sdown_t=0;

    char str1[20], str2[10], filename[50]="ks_";

    printf("Enter name: ");
    scanf("%s", str1);
    printf("Enter session number: ");
    scanf("%s", str2);

    unsigned char length = 0;
    while (filename[length] != '\0')
        ++length;
    for (unsigned char j = 0; str1[j] != '\0'; ++j, ++length)
        filename[length] = str1[j];
    for (unsigned char j = 0; str2[j] != '\0'; ++j, ++length)
        filename[length] = str2[j];
    filename[length] = '\0';

    /* Don't use binary for text files, OK?  ;-) */
    FILE* myfile = fopen(filename, "w");

    /* Get the console input handle */
    HANDLE hstdin = GetStdHandle( STD_INPUT_HANDLE );

    /* Preserve the original console mode */
    GetConsoleMode( hstdin, &mode );

    /* Set to no line-buffering, no echo, no special-key-processing */
    SetConsoleMode( hstdin, 0 );

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

    while (!done)
    {
        if (WaitForSingleObject( hstdin, 0 ) == WAIT_OBJECT_0)  /* if kbhit */
        {
            DWORD count;  /* ignored */    

            /* Get the input event */
            ReadConsoleInput( hstdin, &event, 1, &count );

            if ((event.EventType == KEY_EVENT) && event.Event.KeyEvent.bKeyDown)
                switch (event.Event.KeyEvent.wVirtualKeyCode)
                {
                    // logic to parse for ".tie5Roan." pass-string
                    case VK_OEM_PERIOD:      // "."
                        down_t = clock();      // start timer
                        // fprintf(myfile,".p:%.3f,", 0.0);  // start
                        dprev_t = down_t;
                        break;
                    case 0x54:      // "t"
                        down_t = clock();               // start timer
                        downdown_t = (float)(down_t - dprev_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "DD.period.t:%.3f,", downdown_t);
                        // updown_t = (float)(down_t - up_t) / CLOCKS_PER_SEC;
                        // fprintf(myfile, "UD.period.t:%.3f,", updown_t);
                        dprev_t = down_t;
                        break;
                    case 0x49:      // "i"
                        down_t = clock();   // start timer
                        downdown_t = (float)(down_t - dprev_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "DD.t.i:%.3f,", downdown_t);
                        // updown_t = (float)(down_t - up_t) / CLOCKS_PER_SEC;
                        // fprintf(myfile, "UD.t.i:%.3f,", updown_t);
                        dprev_t = down_t;
                        break;
                    case 0x45:      // "e"
                        down_t = clock();   // start timer
                        downdown_t = (float)(down_t - dprev_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "DD.i.e:%.3f,", downdown_t);
                        // updown_t = (float)(down_t - up_t) / CLOCKS_PER_SEC;
                        // fprintf(myfile, "UD.i.e:%.3f,", updown_t);
                        dprev_t = down_t;
                        break;
                    case 0x35:      // "5"
                        down_t = clock();   // start timer
                        downdown_t = (float)(down_t - dprev_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "DD.e.five:%.3f,", downdown_t);
                        // updown_t = (float)(down_t - up_t) / CLOCKS_PER_SEC;
                        // fprintf(myfile, "UD.e.five:%.3f,", updown_t);
                        dprev_t = down_t;
                        break;

                    case VK_SHIFT:  // "Shift"
                    //     sdown_t = clock();   // start timer
                    //     downdown_t = (float)(sdown_t - down_t) / CLOCKS_PER_SEC;
                    //     fprintf(myfile, "<DD.5.S:%.3f>,", downdown_t);
                    //     updown_t = (float)(sdown_t - up_t) / CLOCKS_PER_SEC;
                    //     fprintf(myfile, "<UD.5.S:%.3f>,", updown_t);
                    //     // sprev_t = sdown_t;     // special
                        shift = TRUE;
                        break;

                    case 0x52:      // "Shift R"
                        down_t = clock();   // start timer
                        downdown_t = (float)(down_t - dprev_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "DD.five.Shift.r:%.3f,", downdown_t);
                        // updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;
                        // fprintf(myfile, "UD.five.Shift.r:%.3f,", updown_t);
                        dprev_t = down_t;
                        break;
                    case 0x4F:      // "o"
                        down_t = clock();   // start timer
                        downdown_t = (float)(down_t - dprev_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "DD.Shift.r.o:%.3f,", downdown_t);
                        // updown_t = (float)(down_t - up_t) / CLOCKS_PER_SEC;
                        // fprintf(myfile, "UD.Shift.r.o:%.3f,", updown_t);
                        dprev_t = down_t;
                        break;
                    case 0x41:      // "a"
                        down_t = clock();   // start timer
                        downdown_t = (float)(down_t - dprev_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "DD.o.a:%.3f,", downdown_t);
                        // updown_t = (float)(down_t - up_t) / CLOCKS_PER_SEC;
                        // fprintf(myfile, "UD.o.a:%.3f,", updown_t);
                        dprev_t = down_t;
                        break;
                    case 0x4E:      // "n"
                        down_t = clock();   // start timer
                        downdown_t = (float)(down_t - dprev_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "DD.a.n:%.3f,", downdown_t);
                        // updown_t = (float)(down_t - up_t) / CLOCKS_PER_SEC;
                        // fprintf(myfile, "UD.a.n:%.3f,", updown_t);
                        dprev_t = down_t;
                        break;
                    case 0x4C:      // "l"
                        down_t = clock();   // start timer
                        downdown_t = (float)(down_t - dprev_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "DD.n.l:%.3f,", downdown_t);
                        // updown_t = (float)(down_t - up_t) / CLOCKS_PER_SEC;
                        // fprintf(myfile, "UD.n.l:%.3f,", updown_t);
                        dprev_t = down_t;
                        break;

                    case VK_RETURN: // "Return"
                        down_t = clock();   // start timer
                        downdown_t = (float)(down_t - dprev_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "DD.l.Return:%.3f,", downdown_t);
                        // updown_t = (float)(down_t - up_t) / CLOCKS_PER_SEC;
                        // fprintf(myfile, "UD.l.Return:%.3f,", updown_t);
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
                        fprintf(myfile, "H.period:%.3f,", hold_t);
                        uprev_t = up_t;
                        if (ch==0) ch++;
                        printf( "." );
                        break;
                    case 0x54:      // "t"
                        up_t = clock();
                        updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "UD.period.t:%.3f,", updown_t);
                        hold_t = (float)(up_t - down_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "H.t:%.3f,", hold_t);
                        uprev_t = up_t;
                        if (ch==1) ch++;
                        printf( "t" );
                        break;
                    case 0x49:      // "i"
                        up_t = clock();
                        updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "UD.t.i:%.3f,", updown_t);
                        hold_t = (float)(up_t - down_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "H.i:%.3f,", hold_t);
                        uprev_t = up_t;
                        if (ch==2) ch++;
                        printf( "i" );
                        break;
                    case 0x45:      // "e"
                        up_t = clock();
                        updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "UD.i.e:%.3f,", updown_t);
                        hold_t = (float)(up_t - down_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "H.e:%.3f,", hold_t);
                        uprev_t = up_t;
                        if (ch==3) ch++;
                        printf( "e" );
                        break;
                    case 0x35:      // "5"
                        up_t = clock();
                        updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "UD.e.five:%.3f,", updown_t);
                        hold_t = (float)(up_t - down_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "H.five:%.3f,", hold_t);
                        uprev_t = up_t;
                        if (ch==4) ch++;
                        printf( "5" );
                        break;

                    case 0x52:      // "Shift R"
                        up_t = clock();
                        updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "UD.five.Shift.r:%.3f,", updown_t);
                        hold_t = (float)(up_t - down_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "H.Shift.r:%.3f,", hold_t);
                        uprev_t = up_t;
                        if(shift) printf( "R" );
                        else printf( "r" );
                        shift = FALSE;
                        if (ch==5) ch++;
                        break;

                    case VK_SHIFT:
                        // sup_t = clock();
                        // hold_t = (float)(sup_t - sdown_t) / CLOCKS_PER_SEC;
                        // fprintf(myfile, "<H.Shift:%.3f>,", hold_t);
                        if (ch==6) ch++;
                        break;

                    case 0x4F:      // "o"
                        up_t = clock();
                        updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "UD.Shift.r.o:%.3f,", updown_t);
                        hold_t = (float)(up_t - down_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "H.o:%.3f,", hold_t);
                        uprev_t = up_t;
                        printf( "o" );
                        if (ch==7) ch++;
                        break;
                    case 0x41:      // "a"
                        up_t = clock();
                        updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "UD.o.a:%.3f,", updown_t);
                        hold_t = (float)(up_t - down_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "H.a:%.3f,", hold_t);
                        uprev_t = up_t;
                        printf( "a" );
                        if (ch==8) ch++;
                        break;

                    case 0x4E:      // "n"
                        up_t = clock();
                        updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "UD.a.n:%.3f,", updown_t);
                        hold_t = (float)(up_t - down_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "H.n:%.3f,", hold_t);
                        uprev_t = up_t;
                        printf( "n" );
                        if (ch==9) ch++;
                        break;
                    case 0x4C:      // "l"
                        up_t = clock();
                        updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "UD.n.l:%.3f,", updown_t);
                        hold_t = (float)(up_t - down_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "H.l:%.3f,", hold_t);
                        uprev_t = up_t;
                        printf( "l" );
                        if (ch==10) ch++;
                        break;

                    case VK_RETURN:
                        up_t = clock();
                        updown_t = (float)(down_t - uprev_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "UD.l.Return:%.3f,", updown_t);
                        hold_t = (float)(up_t - down_t) / CLOCKS_PER_SEC;
                        fprintf(myfile, "H.Return:%.3f\n", hold_t);
                        if (ch==11) {                        
                            printf("\t %d recorded", ++counter);
                            ch=0;
                        }
                        printf( "\n" );
                        break;

                    case VK_ESCAPE:
                        fprintf( myfile, "\nThere are %d valid records.\n", counter );
                        printf( "\nThank you so much for your participation!\n" );
                        done = TRUE;
                        break;
                    default:
                        printf( "?\a" );
                        ch++;
                        done = FALSE;
                }
        }
    }

    /* All done! */
    printf( "There are %d records\n", counter );
    fclose( myfile );
    SetConsoleMode( hstdin, mode );
    return 0;
}