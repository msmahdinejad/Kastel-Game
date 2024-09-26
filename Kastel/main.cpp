#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#define green "\x1b[32m"
#define red "\x1b[31m"
#define pink "\x1b[35m"
#define base "\x1b[0m"
#define yello "\x1b[33m"
#define blink "\x1b[5m"
#define bold "\x1b[1m"
#define blue "\x1b[34m"
#define backred "\x1b[41m"
#define boldred "\x1b[1;31m"

using namespace std;

HWND console = GetConsoleWindow();
HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cursor_position;

void set_cursor_pos(int, int);
void PrintAsciiArt(string, int, int, string);
void TypeEffect(string, int, int);
void Opening();
void LoadingEffect(int, int);
void clear();
void FirstPage();
void NewGame();
void error(string);

class kart
{
private:
    int kart_point;
    string kart_type;
    string color;
public:
    kart();
    int getKartPoint();
    string getkartType();
    string getColor();
    void setVariables(int, string, string);
    bool checkNull();
    void makeNull();
    void printKart(int, int, string);
    void printKartPlus(int, int, string);
};

class player
{
private:
    string player_name;
    int player_point;
    int inFronts_num;
    int inHands_num;
    kart * inHands;
    kart * inFronts;
public:
    player();
    ~player();
    string getPlayerName();
    int getPlayerPoint();
    int getInFrontNum();
    kart * getInHands();
    kart * getInFronts();
    kart getInHand(int);
    kart getInFront(int);
    int getInHandsNum();
    void setPlayerName(string);
    void playerPointSum(int);
    void setInFrontNum(int);
    void inHandsMinus(int);
    void setInHand(int, int, string, string);
    void setInFront(int, int, string, string);
    void printInFronts(int, int, int);
    void printInHands(int, int, int);
    bool check3KartExist();
};

class kastel
{
private:
    int select_player;
    int selected_player;
    int select_inHand;
    int selected_inHand;
    int select_inFront;
    int selected_inFront;
    int player_num;
    int kart_num;
    int max_score;
    int Turn;
    player * players;
    kart * karts;
public:
    kastel();
    ~kastel();
    int getPlayerNum();
    int getKartNum();
    int getMaxScore();
    player * getPlayers();
    kart * getKarts();
    player getPlayer(int);
    kart getKart(int);
    void setPlayerNum(int);
    void kartNumMinus(int);
    void setMaxScore(int);
    void setPlayer(int, string);
    void setKart(int, int, string, string);
    void setFirstKarts();
    void shuffleTheCards();
    void setFirstInHands();
    void startGame();
    void reloadPage(bool);
    void printPlayers(int, int);
    void PrintTurn(int, int);
    bool checkEndRound();
    bool checkEndGame();
    void newRound();
    void submit();
    void setNewKartInHand();
    void checkSameKarts();
    void setNewInFrontNum();
    void calculateNewScores();
    void printScoreBoard();
    void sortPlayers();
};

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    srand(time(0));
    Opening();
    while(true)
    {
        FirstPage();
    }
    return 0;
}

void set_cursor_pos(int x, int y)
{
    cursor_position.X = x;
    cursor_position.Y = y;
    SetConsoleCursorPosition(output, cursor_position);
}

void PrintAsciiArt(string filename, int x, int y, string color = base)
{
    int k = 0;
    wstring line;
    wifstream file;
    file.open(filename);
    while(getline(file,line))
    {
        set_cursor_pos(x,k+y);
        cout << color;
        wcout << line;
        k++;
    }
    cout << endl;
    file.close();
    cout << base;
}

void TypeEffect(string MySTR, int x, int y, string color = base)
{
    set_cursor_pos(x,y);
    //PlaySound(TEXT("musics/type.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(500);
    for(int i = 0; i < MySTR.length(); i++)
    {
        Sleep(200);
        cout << color;
        cout << MySTR[i];
    }
    //PlaySound(0,0,0);
    cout << endl;
    cout << base;
}

void LoadingEffect(int x, int y, string color = base)
{
    set_cursor_pos(x,y);
    cout << "┌────────────────────────┐";
    set_cursor_pos(x,y+1);
    cout << "│";
    set_cursor_pos(x+25,y+1);
    cout << "│";
    set_cursor_pos(x,y+2);
    cout << "└────────────────────────┘";
    for(int i = 0; i < 24; i++)
    {
        set_cursor_pos(x+1+i,y+1);
        cout << color << "█";
        Sleep(390);
    }
    cout << endl;
    cout << base;
}

void clear()
{
    system("CLS");
}

void Opening()
{
    PlaySound(TEXT("musics/logo.wav"), NULL, SND_FILENAME | SND_ASYNC);
    TypeEffect("WELCOME TO...", 45, 10, green);
    LoadingEffect(38, 12, blue);
    clear();
    PrintAsciiArt("files/kastel.txt", 25, 10, red);
    Sleep(4000);
    clear();
}

void error(string error = "Please select one of the available options")
{
    set_cursor_pos(31,1);
    cout << backred << error << base;
}

void FirstPage()
{
    clear();
    PlaySound(TEXT("musics/first.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    PrintAsciiArt("files/kastel2.txt", 40, 8, "\x1b[31;5m");
    set_cursor_pos(43,12);
    cout << green << "1.New game" << base;
    set_cursor_pos(43,13);
    cout << green << "2.Exit" << base;
    char input;
    do
    {
        input = getch();
        switch (input)
        {
            case '1':
                NewGame();
                break;
            case '2':
                exit(0);
                break;
            default:
                error();
                break;
        }
    }while(input != '1' && input != '2');
}

void NewGame()
{
    kastel ThisGame;
    bool check_error = false;
    int num;
    do
    {
        clear();
        if(check_error)
            error("Number of players must be between 2 and 6");
        PrintAsciiArt("files/kastel2.txt", 40, 8, "\x1b[31;5m");
        set_cursor_pos(40,12);
        cout << green << "Number of players: " << base;
        cin >> num;
        if(num < 2 || num > 6)
            check_error = true;
    }while(num < 2 || num > 6);
    ThisGame.setPlayerNum(num);
    for(int i = 0; i < num; i++)
    {
        clear();
        PrintAsciiArt("files/kastel2.txt", 40, 8, "\x1b[31;5m");
        set_cursor_pos(40,12);
        cout << green << "Name of player " << i+1 << " : " << base;
        string name;
        cin >> name;
        ThisGame.setPlayer(i, name);
    }
    clear();
    PrintAsciiArt("files/kastel2.txt", 40, 8, "\x1b[31;5m");
    set_cursor_pos(43,12);
    cout << green << "Max score: " << base;
    cin >> num;
    ThisGame.setMaxScore(num);
    ThisGame.startGame();
}

void kart::setVariables(int kart_point, string kart_type, string color)
{
    this->kart_point = kart_point;
    this->kart_type = kart_type;
    this->color = color;
}
int kart::getKartPoint()
{
    return this->kart_point;
}
string kart::getkartType()
{
    return this->kart_type;
}
string kart::getColor()
{
    return this->color;
}
bool kart::checkNull()
{
    if(this->kart_point == 0)
        return true;
    return false;
}
void kart::makeNull()
{
    this->kart_point = 0;
}
void kart::printKart(int x, int y, string color = "")
{
    if(!this->checkNull())
    {
        if(color == "")
            color = this->color;
        PrintAsciiArt("files/kart.txt", x, y, color);
        set_cursor_pos(x+7, y+4);
        cout << color << this->kart_point << base;
        set_cursor_pos(x+(15 - this->kart_type.length())/2, y+2);
        cout << color << this->kart_type << base;
    }
}
void kart::printKartPlus(int x, int y, string color = "")
{
    if(color == "")
        color = blue;
    PrintAsciiArt("files/kartplus.txt", x, y, color);
}
kart::kart()
{
    this->kart_point = 0;
}
string player::getPlayerName()
{
    return this->player_name;
}
int player::getPlayerPoint()
{
    return  this->player_point;
}
int player::getInFrontNum()
{
    return this->inFronts_num;
}
kart * player::getInHands()
{
    return this->inHands;
}
kart * player::getInFronts()
{
    return this->inFronts;
}
kart player::getInHand(int i)
{
    return this->inHands[i];
}
kart player::getInFront(int i)
{
    return this->inFronts[i];
}
int player::getInHandsNum()
{
    return this->inHands_num;
}
void player::setPlayerName(string name)
{
    this->player_name = name;
}
void player::playerPointSum(int num)
{
    this->player_point += num;
}
void player::setInFrontNum(int num)
{
    this->inFronts_num = num;
}
void player::inHandsMinus(int num)
{
    this->inHands_num -= num;
}
void player::setInHand(int i, int kart_point, string kart_type, string color)
{
    this->inHands[i].setVariables(kart_point, kart_type, color);
}
void player::setInFront(int i, int kart_point, string kart_type, string color)
{
    this->inFronts[i].setVariables(kart_point, kart_type, color);
}
void player::printInFronts(int x, int y, int selected_kart = -1)
{
    int i;
    for(i = 0; i < this->inFronts_num; i++)
    {
        if(i == selected_kart)
            this->inFronts[i].printKart(x+i*15, y, backred);
        else
            this->inFronts[i].printKart(x+i*15, y);
    }
    if(i == selected_kart)
        this->inFronts[i].printKartPlus(x+i*15, y, backred);
    else
        this->inFronts[i].printKartPlus(x+i*15, y);
}
void player::printInHands(int x, int y, int selected_kart = -1)
{
    for(int i = 0; i < 3; i++)
    {
        if(i == selected_kart)
            this->inHands[i].printKart(x+i*15, y, backred);
        else
            this->inHands[i].printKart(x+i*15, y);
    }
}
bool player::check3KartExist()
{
    bool kalekadoo = false, goorbegoor = false, kohnepich = false;
    for(int i = 0; i < this->inFronts_num; i++)
    {
        if(this->inFronts[i].getkartType() == "KaleKadoo")
            kalekadoo = true;
        else if(this->inFronts[i].getkartType() == "GoorBeGoor")
            goorbegoor = true;
        else if(this->inFronts[i].getkartType() == "KohnePich")
            kohnepich = true;
    }
    if(kalekadoo && goorbegoor && kohnepich)
        return true;
    return false;
}
player::player()
{
    this->player_point = 0;
    this->inFronts_num = 0;
    this->inHands_num = 3;
    this->inHands = new kart[3];
    this->inFronts = new kart[6];
}
player::~player()
{
    delete [] this->inHands;
    delete [] this->inFronts;
}
int kastel::getPlayerNum()
{
    return this->player_num;
}
int kastel::getKartNum()
{
    return this->kart_num;
}
int kastel::getMaxScore()
{
    return this->max_score;
}
player * kastel::getPlayers()
{
    return this->players;
}
kart * kastel::getKarts()
{
    return this->karts;
}
player kastel::getPlayer(int i)
{
    return this->players[i];
}
kart kastel::getKart(int i)
{
    return this->karts[i];
}
void kastel::setPlayerNum(int num)
{
    this->player_num = num;
    this->players = new player[num];
    this->setFirstInHands();
}
void kastel::kartNumMinus(int num)
{
    this->kart_num -= num;
}
void kastel::setMaxScore(int num)
{
    this->max_score = num;
}
void kastel::setPlayer(int i, string name)
{
    this->players[i].setPlayerName(name);
}
void kastel::setKart(int i, int kart_point, string kart_type, string color)
{
    this->karts[i].setVariables(kart_point, kart_type, color);
}
kastel::kastel()
{
    this->kart_num = 90;
    this->karts = new kart[90];
    this->setFirstKarts();
    this->shuffleTheCards();
    this->select_inHand = 0;
    this->selected_inHand = -1;
    this->select_inFront = 0;
    this->selected_inFront = -1;
    this->Turn = 0;
    this->select_player = 0;
    this->selected_player = -1;
}
kastel::~kastel()
{
    delete [] this->karts;
    delete [] this->players;
}
void kastel::setFirstKarts()
{
    for(int i = 0; i < 6; i++)
        this->karts[i].setVariables(1, "KaleKadoo", yello);
    for(int i = 6; i < 12; i++)
        this->karts[i].setVariables(9, "KaleKadoo", yello);
    for(int i = 12; i < 18; i++)
        this->karts[i].setVariables(11, "KaleKadoo", yello);
    for(int i = 18; i < 24; i++)
        this->karts[i].setVariables(15, "KaleKadoo", yello);
    for(int i = 24; i < 30; i++)
        this->karts[i].setVariables(4, "KaleKadoo", yello);
    for(int i = 30; i < 36; i++)
        this->karts[i].setVariables(2, "KohnePich", base);
    for(int i = 36; i < 42; i++)
        this->karts[i].setVariables(5, "KohnePich", base);
    for(int i = 42; i < 48; i++)
        this->karts[i].setVariables(7, "KohnePich", base);
    for(int i = 48; i < 54; i++)
        this->karts[i].setVariables(14, "KohnePich", base);
    for(int i = 54; i < 60; i++)
        this->karts[i].setVariables(12, "KohnePich", base);
    for(int i = 60; i < 66; i++)
        this->karts[i].setVariables(3, "GoorBeGoor", green);
    for(int i = 66; i < 72; i++)
        this->karts[i].setVariables(6, "GoorBeGoor", green);
    for(int i = 72; i < 78; i++)
        this->karts[i].setVariables(10, "GoorBeGoor", green);
    for(int i = 78; i < 84; i++)
        this->karts[i].setVariables(8, "GoorBeGoor", green);
    for(int i = 84; i < 90; i++)
        this->karts[i].setVariables(13, "GoorBeGoor", green);
}
void kastel::shuffleTheCards()
{
    for(int i = 0; i < 90; i++)
    {
        swap(karts[i], karts[rand() % 90]);
    }
}
void kastel::setFirstInHands()
{
    for(int i = 0; i < this->player_num; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            int k;
            do
            {
                k = rand() % 90;
            }while(karts[k].checkNull());
            this->players[i].setInHand(j, karts[k].getKartPoint(), karts[k].getkartType(), karts[k].getColor());
            karts[k].makeNull();
        }
    }
    this->kartNumMinus(this->player_num*3);
}
void kastel::printPlayers(int x = 1, int y = 3)
{
    for(int i = 0; i < this->player_num; i++)
    {
        if(i == 5)
        {
            set_cursor_pos(89, y+4*9);
            cout << this->players[i].getPlayerName() << " : ";
            if(i == this->select_player)
                this->players[i].printInFronts(89, y+4*9+1, this->select_inFront);
            else
                this->players[i].printInFronts(89, y+4*9+1);
        }
        else
        {
            set_cursor_pos(x, y+i*9);
            cout << this->players[i].getPlayerName() << " : ";
            if(i == this->select_player)
                this->players[i].printInFronts(x, y+i*9+1, this->select_inFront);
            else
                this->players[i].printInFronts(x, y+i*9+1);
        }
    }
}
void kastel::PrintTurn(int x = 93, int y = 4)
{
    set_cursor_pos(x,y-1);
    cout << this->players[Turn].getPlayerName() << " : ";
    this->players[Turn].printInHands(x, y, this->select_inHand);
}
void kastel::reloadPage(bool check_error)
{
    clear();
    if(check_error)
        error();
    this->printPlayers();
    this->PrintTurn();
}
bool kastel::checkEndRound()
{
    for(int i = 0; i < this->player_num; i++)
        if(this->players[i].getInFrontNum() == 6)
            return true;
    if(this->kart_num == 0)
    {
        int sum = 0;
        for(int i = 0; i < this->player_num; i++)
            sum += players[i].getInHandsNum();
        if(sum == 0)
            return true;
    }
    return false;
}
bool kastel::checkEndGame()
{
    for(int i = 0; i < this->player_num; i++)
        if(this->players[i].getPlayerPoint() >= this->max_score)
            return true;
    return false;
}
void kastel::newRound()
{
    delete [] this->karts;
    for(int i = 0; i < this->player_num; i++)
    {
        this->players[i].setInFrontNum(0);
        for(int j = 0; j < 6; j++)
            this->players[i].getInFronts()[j].makeNull();
    }
    this->kart_num = 90;
    this->karts = new kart[90];
    this->setFirstKarts();
    this->shuffleTheCards();
    this->select_inHand = 0;
    this->selected_inHand = -1;
    this->select_inFront = 0;
    this->selected_inFront = -1;
    this->Turn = 0;
    this->select_player = 0;
    this->selected_player = -1;
    this->setFirstInHands();
}
void kastel::checkSameKarts()
{
    for(int i = 0; i < this->players[this->selected_player].getInFrontNum(); i++)
    {
        for(int j = i+1; j < this->players[this->selected_player].getInFrontNum(); j++)
        {
            if(this->players[this->selected_player].getInFront(i).getKartPoint() == this->players[this->selected_player].getInFront(j).getKartPoint()
                    &&
                    this->players[this->selected_player].getInFront(i).getkartType() == this->players[this->selected_player].getInFront(j).getkartType())
                for(int k = j; k < 5; k++)
                    this->players[this->selected_player].getInFronts()[k] = this->players[Turn].getInFronts()[k+1];
        }
    }
}
void kastel::setNewInFrontNum()
{
    int num = 0;
    for(int i = 0; i < 6; i++)
        if(!this->players[this->selected_player].getInFronts()[i].checkNull())
            num++;
    this->players[this->selected_player].setInFrontNum(num);
}
void kastel::calculateNewScores()
{
    for(int i = 0; i < this->player_num; i++)
    {
        if(this->players[i].check3KartExist())
        {
            int sum = 0;
            for(int j = 0; j < this->players[i].getInFrontNum(); j++)
            {
                sum += this->players[i].getInFronts()[j].getKartPoint();
            }
            this->players[i].playerPointSum(sum);
        }
    }
}
void kastel::printScoreBoard()
{
    this->sortPlayers();
    clear();
    for(int i = 0; i < this->player_num; i++)
    {
        set_cursor_pos(50,5+i*2);
        cout << green << this->players[i].getPlayerName() << "\t" << red << this->players[i].getPlayerPoint() << endl;
    }
    getch();
}
void kastel::sortPlayers()
{
    for(int j = 0; j < this->player_num - 1; j++)
        for(int i = 0; i < this->player_num - j - 1; i++)
            if(this->players[i].getPlayerPoint() < this->players[i+1].getPlayerPoint())
                swap(this->players[i], this->players[i+1]);
}
void kastel::setNewKartInHand()
{
    if(this->kart_num > 0)
    {
        int k;
        for(int i = 0; i < 90; i++)
        {
            if(!this->karts[i].checkNull())
            {
                k = i;
                break;
            }
        }
        this->players[Turn].setInHand(this->selected_inHand, karts[k].getKartPoint(), karts[k].getkartType(), karts[k].getColor());
        this->karts[k].makeNull();
        this->kartNumMinus(1);
    }
    else
    {
        this->players[Turn].getInHands()[this->selected_inHand].makeNull();
        this->players[Turn].inHandsMinus(1);
    }
}
void kastel::submit()
{
    if(this->players[this->selected_player].getInFronts()[this->selected_inFront].checkNull()
            ||
            this->players[this->selected_player].getInFronts()[this->selected_inFront].getkartType() == this->players[this->Turn].getInHand(this->selected_inHand).getkartType())
    {
        this->players[this->selected_player].getInFronts()[this->selected_inFront] = this->players[this->Turn].getInHand(this->selected_inHand);
        this->setNewInFrontNum();
        this->setNewKartInHand();
        this->checkSameKarts();
        this->setNewInFrontNum();
        if(this->Turn < this->player_num-1)
            this->Turn++;
        else
            this->Turn = 0;
    }
    this->select_inHand = 0;
    this->selected_inHand = -1;
    this->select_inFront = 0;
    this->selected_inFront = -1;
    this->select_player = 0;
    this->selected_player = -1;
}
void kastel::startGame()
{
    bool check_error = false;
    clear();
    while(!this->checkEndRound())
    {
        this->reloadPage(check_error);
        check_error = false;
        if(this->selected_inHand == -1)
        {
            char input;
            input = getch();
            if(input == -32)
            {
                input = getch();
                switch(input)
                {
                    case 77:
                        if(this->select_inHand < this->players[Turn].getInHandsNum() - 1)
                            this->select_inHand ++;
                        break;
                    case 75:
                        if(this->select_inHand > 3 - this->players[Turn].getInHandsNum())
                            this->select_inHand --;
                        break;
                    default:
                        check_error = true;
                        break;
                }
            }
            else if(input != ' ')
            {
                check_error = true;
            }
            else
            {
                this->selected_inHand = this->select_inHand;
            }
        }
        else if(this->selected_inFront == -1)
        {
            char input;
            input = getch();
            if(input == -32)
            {
                input = getch();
                switch(input)
                {
                    case 72:
                        if(this->select_player > 0)
                        {
                            this->select_player --;
                            this->select_inFront = 0;
                        }
                        break;
                    case 80:
                        if(this->select_player < this->player_num-1)
                        {
                            this->select_player ++;
                            this->select_inFront = 0;
                        }
                        break;
                    case 77:
                        if(this->select_inFront < this->players[this->select_player].getInFrontNum())
                            this->select_inFront ++;
                        break;
                    case 75:
                        if(this->select_inFront > 0)
                            this->select_inFront --;
                        break;
                    default:
                        check_error = true;
                        break;
                }
            }
            else if(input != ' ')
            {
                check_error = true;
            }
            else
            {
                this->selected_player = this->select_player;
                this->selected_inFront = this->select_inFront;
            }
        }
        if(this->selected_inHand != -1 && this->selected_inFront != -1)
        {
            this->submit();
        }
    }
    this->calculateNewScores();

    while(!this->checkEndGame())
    {
        this->newRound();
        clear();
        while(!this->checkEndRound())
        {
            this->reloadPage(check_error);
            check_error = false;
            if(this->selected_inHand == -1)
            {
                char input;
                input = getch();
                if(input == -32)
                {
                    input = getch();
                    switch(input)
                    {
                        case 77:
                            if(this->select_inHand < 2)
                                this->select_inHand ++;
                            break;
                        case 75:
                            if(this->select_inHand > 0)
                                this->select_inHand --;
                            break;
                        default:
                            check_error = true;
                            break;
                    }
                }
                else if(input != ' ')
                {
                    check_error = true;
                }
                else
                {
                    this->selected_inHand = this->select_inHand;
                }
            }
            else if(this->selected_inFront == -1)
            {
                char input;
                input = getch();
                if(input == -32)
                {
                    input = getch();
                    switch(input)
                    {
                        case 72:
                            if(this->select_player > 0)
                                this->select_player --;
                            break;
                        case 80:
                            if(this->select_player < this->player_num-1)
                                this->select_player ++;
                            break;
                        case 77:
                            if(this->select_inFront < this->players[this->select_player].getInFrontNum())
                                this->select_inFront ++;
                            break;
                        case 75:
                            if(this->select_inFront > 0)
                                this->select_inFront --;
                            break;
                        default:
                            check_error = true;
                            break;
                    }
                }
                else if(input != ' ')
                {
                    check_error = true;
                }
                else
                {
                    this->selected_player = this->select_player;
                    this->selected_inFront = this->select_inFront;
                }
            }
            if(this->selected_inHand != -1 && this->selected_inFront != -1)
            {
                this->submit();
            }
        }
        this->calculateNewScores();
    }
    this->printScoreBoard();
}
