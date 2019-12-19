/*              _         
**  ___ ___ _ _|_|___ ___ 
** |  _| .'|_'_| |_ -|_ -|
** |_| |__,|_,_|_|___|___|
**         raxiss (c) 2019
*/

#include <stdio.h>
#include <lib.h>

#define SNOWFLAKES 20
#define SNOWFLAKESMAXSPEED 5
#define SNOWFLAKESMAXTYPE 4

#define SCROLLERSPEED 1
#define SCROLLER_START_ADDR (0xbb80 + 26 * 40)

#define SANTASPEED 15
#define SANTAPOS (2 + 12 * 40)

#define CHIMNEYSMOKEADDR (0xa000 + 35 + 71 * 40)
#define CHIMNEYSMOKESPEED 2

#define pe(addr) ((unsigned char *)addr)[0]
#define pk(addr, val)                     \
    {                                     \
        ((unsigned char *)addr)[0] = val; \
    }

void initSnowflakes();
void show();
void printSnowflakes();
void chimneySmoke();
void scroller();
void santa();

void StartMusic();
void EndMusic();
extern unsigned char pic[];
extern unsigned int MusicResetCounter;

unsigned char snowflakes[4][3] = {
    {
        8,
        20,
        8,

    },
    {
        20,
        8,
        20,

    },
    {
        0,
        8,
        0,

    },
    {
        0,
        8,
    },
};

unsigned char smoke[12] = {61, 59, 61, 59, 63, 63, 61, 59, 61, 59, 63, 63};

unsigned char charset[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    12, 12, 12, 12, 12, 0, 12, 0,
    54, 54, 54, 0, 0, 0, 0, 0,
    20, 20, 62, 20, 62, 20, 20, 0,
    8, 30, 44, 28, 26, 60, 8, 0,
    48, 50, 6, 12, 24, 54, 38, 0,
    24, 44, 44, 24, 46, 44, 30, 0,
    24, 24, 24, 0, 0, 0, 0, 0,
    12, 24, 48, 48, 48, 24, 12, 0,
    24, 12, 6, 6, 6, 12, 24, 0,
    8, 42, 28, 8, 28, 42, 8, 0,
    0, 24, 24, 62, 24, 24, 0, 0,
    0, 0, 0, 0, 0, 12, 12, 24,
    0, 0, 0, 62, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 12, 12, 0,
    0, 2, 6, 12, 24, 48, 32, 0,
    28, 50, 54, 58, 50, 50, 28, 0,
    12, 28, 12, 12, 12, 12, 30, 0,
    28, 54, 6, 12, 24, 48, 62, 0,
    62, 6, 12, 28, 6, 54, 28, 0,
    4, 12, 28, 44, 62, 12, 12, 0,
    62, 48, 60, 6, 6, 38, 28, 0,
    12, 24, 48, 60, 50, 50, 28, 0,
    62, 2, 6, 12, 24, 24, 24, 0,
    28, 50, 50, 28, 50, 50, 28, 0,
    28, 54, 54, 30, 6, 12, 24, 0,
    0, 0, 12, 0, 0, 12, 0, 0,
    0, 0, 12, 0, 0, 12, 12, 24,
    6, 12, 24, 48, 24, 12, 6, 0,
    0, 0, 62, 0, 62, 0, 0, 0,
    48, 24, 12, 6, 12, 24, 48, 0,
    28, 54, 6, 12, 12, 0, 12, 0,
    28, 50, 50, 54, 54, 48, 30, 0,
    8, 28, 50, 50, 62, 50, 50, 0,
    60, 50, 50, 60, 50, 50, 60, 0,
    28, 50, 48, 48, 48, 50, 28, 0,
    60, 50, 50, 50, 50, 50, 60, 0,
    62, 48, 48, 60, 48, 48, 62, 0,
    62, 48, 48, 60, 48, 48, 48, 0,
    30, 48, 48, 48, 54, 50, 30, 0,
    50, 50, 50, 62, 50, 50, 50, 0,
    30, 12, 12, 12, 12, 12, 30, 0,
    6, 6, 6, 6, 6, 38, 28, 0,
    50, 52, 56, 48, 56, 60, 54, 0,
    48, 48, 48, 48, 48, 48, 62, 0,
    34, 54, 58, 58, 50, 50, 50, 0,
    50, 50, 50, 58, 54, 50, 50, 0,
    28, 50, 50, 50, 50, 50, 28, 0,
    60, 34, 34, 60, 48, 48, 48, 0,
    28, 50, 50, 50, 58, 52, 26, 0,
    60, 50, 50, 60, 56, 52, 50, 0,
    28, 50, 48, 28, 6, 38, 28, 0,
    62, 24, 24, 24, 24, 24, 24, 0,
    50, 50, 50, 50, 50, 50, 28, 0,
    50, 50, 50, 50, 50, 28, 8, 0,
    50, 50, 50, 58, 58, 54, 34, 0,
    54, 54, 20, 8, 20, 54, 54, 0,
    50, 50, 20, 24, 24, 24, 24, 0,
    62, 6, 12, 24, 48, 48, 62, 0,
    60, 48, 48, 48, 48, 48, 60, 0,
    0, 32, 48, 24, 12, 6, 2, 0,
    30, 6, 6, 6, 6, 6, 30, 0,
    8, 28, 54, 34, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 63, 0,
    30, 33, 45, 41, 41, 45, 33, 30,
    0, 0, 28, 2, 30, 38, 30, 0,
    32, 32, 60, 50, 50, 50, 60, 0,
    0, 0, 30, 48, 48, 48, 30, 0,
    2, 2, 30, 38, 38, 38, 30, 0,
    0, 0, 28, 50, 62, 48, 30, 0,
    12, 18, 16, 60, 24, 24, 24, 0,
    0, 0, 28, 38, 38, 30, 6, 28,
    32, 32, 60, 50, 50, 50, 50, 0,
    8, 0, 56, 24, 24, 24, 60, 0,
    4, 0, 28, 12, 12, 12, 44, 24,
    48, 48, 50, 52, 56, 52, 50, 0,
    56, 24, 24, 24, 24, 24, 60, 0,
    0, 0, 54, 58, 58, 58, 50, 0,
    0, 0, 60, 50, 50, 50, 50, 0,
    0, 0, 28, 50, 50, 50, 28, 0,
    0, 0, 60, 50, 50, 60, 48, 48,
    0, 0, 30, 38, 38, 30, 6, 6,
    0, 0, 46, 48, 48, 48, 48, 0,
    0, 0, 30, 48, 28, 6, 60, 0,
    24, 24, 60, 24, 24, 26, 12, 0,
    0, 0, 50, 50, 50, 54, 26, 0,
    0, 0, 50, 50, 50, 28, 8, 0,
    0, 0, 50, 50, 58, 58, 54, 0,
    0, 0, 54, 20, 8, 20, 54, 0,
    0, 0, 54, 54, 54, 30, 6, 28,
    0, 0, 62, 6, 12, 24, 62, 0,
    12, 24, 24, 48, 24, 24, 12, 0,
    12, 12, 12, 12, 12, 12, 12, 12,
    24, 12, 12, 6, 12, 12, 24, 0,
    8, 28, 62, 28, 62, 8, 8, 0,
    0, 12, 22, 47, 63, 30, 12, 0};

unsigned int sfa[SNOWFLAKES] = {0};  // address
unsigned char sfs[SNOWFLAKES] = {0}; // speed
unsigned char sft[SNOWFLAKES] = {0}; // type

unsigned char i;
unsigned char isSnowEnabled = 0;

unsigned int addr;

unsigned char multi40[] = {0, 40, 2 * 40, 3 * 40, 4 * 40, 5 * 40, 6 * 40, 7 * 40, 8 * 40, 9 * 40, 10 * 40, 11 * 40, 12 * 40, 13 * 40};

char msg[] = 
"                                          \x7f \x7f \x7f"
"   May this festive season sparkle and shine, may all of your "
"wishes and dreams come true, and may you feel this happiness all "
"year round. May this wonderful time of the year touch your heart "
"in a special way. During this festive season of giving, let us take "
"time to slow down and enjoy the simple things.  Wishing you much "
"happiness not just today, but throughout the New Year. Merry Christmas!   \x7f \x7f \x7f"
"                                    raxiss (c) 2019                                     ";

unsigned int scrollerPos = 0;
unsigned char scrollerCounter = 0;

static char* logo = 
"                                        "
"                                        "
"                                        "
"                                        "
"                                        "
"                                        "
"                                        "
"                                        "
"                       .__              "
"  ____________  ___  __|__| _____ _____ "
"  \\_  __ \\__  \\ \\  \\/  /  |/ ___// ___/ "
"   |  | \\// __ \\_>    <|  |\\__ \\ \\__ \\  "
"   |__|  (____  /__/\\_ \\__/___  >___  > "
"              \\/      \\/      \\/    \\/  "
"                                        "
"                presents                "
"                                        "
"                                        "
"                                        "
"                                        ";

main()
{
    text();
    paper(0);
    ink(7);

    //hide cursor
    pk(0x26a, 10);

    //font
    memcpy((void *)0xb500, (void *)charset, sizeof(charset));
    
    memcpy((void *)(0xbb80), (void *)logo, 40*20);
    for (addr = 0; addr < 30000; ++addr);
        
    //invert msg
    for (addr = 0; addr < sizeof(msg); ++addr)
    {
        msg[addr] = msg[addr] | 128;
    }

    // supress ugly lines during hires switch
    memset((void *)0x9900, 0, 0xc000-0x9900);
    hires();
    //hires font
    memcpy((void *)0x9900, (void *)charset, sizeof(charset));
    
    //hide cursor
    pk(0x26a, 10);
    
    //set scroller bg & double text
    memset(SCROLLER_START_ADDR - 40, 23, 40 * 3);
    pk(SCROLLER_START_ADDR, 10 | 128);
    pk(SCROLLER_START_ADDR + 40, 10 | 128);

    //show pic
    memcpy((void *)0xa000, (void *)pic, 8000);

    StartMusic();

    initSnowflakes();

    //do magic
    while (key() != 27)
    {
        show();
    }

    //exit
    EndMusic;
    text();
}

void initSnowflakes()
{
    for (i = 0; i < SNOWFLAKES; ++i)
    {

        sfa[i] = 0xa000 + rand() % 39 + (rand() % 160 * 40);
        sfs[i] = rand() % SNOWFLAKESMAXSPEED + 2;
        sft[i] = rand() % SNOWFLAKESMAXTYPE;
    }
}

void show()
{

    if (isSnowEnabled == 0 && MusicResetCounter < 3300)
    {
        isSnowEnabled = 1;
        for (i = 0; i < SNOWFLAKES; ++i)
        {
            printSnowflakes();
        }
    }

    for (i = 0; i < SNOWFLAKES; ++i)
    {
        printSnowflakes();
        if (isSnowEnabled == 1)
        {
            if (sfa[i] > 0xbfdf - 800)
            {
                sfa[i] = rand() % 39 + 0xa000;
                sfs[i] = rand() % SNOWFLAKESMAXSPEED + 2;
                sft[i] = rand() % SNOWFLAKESMAXTYPE;
            }

            //scroll down
            sfa[i] += multi40[sfs[i]];
        }

        printSnowflakes();
    }

    scroller();
    chimneySmoke();
    santa();
}

void printSnowflakes()
{
    unsigned char tmp, type;
    unsigned char *typeAddr;

    if (isSnowEnabled == 0)
    {
        //wait
        for (tmp = 0; tmp < 25; ++tmp)
        {
            ;
        }

        return;
    }

    addr = sfa[i];
    type = sft[i];

    typeAddr = &snowflakes[type][0];

    // first
    tmp = pe(addr);
    pk(addr, tmp ^ *typeAddr);
    addr += 40;

    //second
    tmp = pe(addr);
    ++typeAddr;
    pk(addr, tmp ^ *typeAddr);
    addr += 40;

    //third
    tmp = pe(addr);
    ++typeAddr;
    pk(addr, tmp ^ *typeAddr);
    addr += 40;
}

void chimneySmoke()
{
    static unsigned char counter = 0;
    static unsigned char state = 0;
    unsigned char n, i;

    ++counter;

    // check speed counter
    if (counter < CHIMNEYSMOKESPEED)
    {
        return;
    }

    counter = 0;

    addr = CHIMNEYSMOKEADDR;

    n = state + 6;

    // print
    for (i = state; i < n; ++i)
    {
        pk(addr, smoke[i]);
        addr += 40;
    }

    ++state;

    //reset state
    if (state > 5)
    {
        state = 0;
    }
}

void scroller()
{
    ++scrollerCounter;

    // check speed counter
    if (scrollerCounter < SCROLLERSPEED)
    {
        return;
    }

    scrollerCounter = 0;

    //first & second row
    memcpy((void *)(SCROLLER_START_ADDR + 1), &(msg[scrollerPos]), 38);
    memcpy((void *)(SCROLLER_START_ADDR + 41), &(msg[scrollerPos]), 38);
    ++scrollerPos;

    // check for end of msg
    if (scrollerPos > sizeof(msg) - 38)
    {
        scrollerPos = 0;
    }
}

void santa()
{
    static unsigned char santaOffset = 0;
    static unsigned char santaCounter = 0;

    unsigned int santaAddr, screenAddr;

    // check speed counter
    ++santaCounter;
    if (santaCounter < SANTASPEED)
    {
        return;
    }

    santaCounter = 0;

    // offset
    santaOffset = santaOffset == 1 ? 0 : 1;

    //calc src and des location
    screenAddr = SANTAPOS + 0xA000 + (santaOffset ? 0 : 40);
    santaAddr = SANTAPOS + (unsigned int)&pic;

    // show rows
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
    memcpy((void *)(screenAddr), (void *)(santaAddr), 18);
    screenAddr += 40;
    santaAddr += 40;
}
