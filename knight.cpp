#include "knight.h"
int MaxHP;
bool is_lancelot = false, is_arthur = false;
int is_tiny = 0, is_frog = 0;
int lv_bf_fr;
bool metAsclepius = false;
bool metMerlin = false;

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}

/* SUB FUNCTIONS*/
int calcLevelO(int i)
{
    int b = i % 10;
    return i>6?(b>5?b:5):b;
}
bool isPrime(int n)
{
    if(n<2) return false;
    if(n == 2 || n == 3) return true;
    for(int i = 2; i*i <=n;i++)
    {
        if(n%i == 0) return false;
    }
    return true;
}
bool isFibonacci(int n)
{
    if(n == 1) return true;
    int a[17];
    a[1] = 1, a[2] = 1;
    for(int i = 3; i<= 16; i++)
    {
        a[i] = a[i-1] + a[i-2]; 
        if(n==a[i]) return true;
    }
    return false;
}
string ItoS(int n)
{
    string s = "";
    while(n>0)
    {
        s = char(n%10 + 48) + s;
        n /= 10;
    }
    return s;
}
bool isEvent13(int n)
{
    string s = ItoS(n);
    if(s[0] == '1' && s[1] == '3') return true; else return false;
}
/* END: SUB FUNCTIONS*/

//Event 1 to 5:
void ev_1to5(int event_code, int event_order, int & HP, int & level, int & phoenixdown, int & rescue) 
{   
    if(!is_arthur && !is_lancelot)
    {
    ///////////
    int levelO = calcLevelO(event_order);
    if((level > levelO) && (level < 10)) {level++;}
    if(level < levelO) {
        double damage;
        switch (event_code)
        {
        case 1:
            damage = 1;
            break;
        case 2:
            damage = 1.5;
            break;
        case 3: 
            damage = 4.5;
            break;
        case 4:
            damage = 7.5;
            break;
        case 5: 
            damage = 9.5;
            break;
        }
        damage *= (levelO*10);
        HP -= damage;
    }
    if(HP <= 0)
    {
        if(phoenixdown > 0) 
        {
            phoenixdown --; 
            HP = MaxHP;
            is_tiny = 0;
        } else {
            rescue = 0;
        }
    }
    /////////////
    }
}

//Event 6:
void ev_6(int event_order, int & HP, int & level, int & remedy, int  & rescue)
{
    if(is_frog == 0 && is_tiny == 0)
    {if(!is_arthur && !is_lancelot)
    {
    ///////////   
    int levelO = calcLevelO(event_order);
    if(level > levelO) 
    {
        if(level < 8) level += 2;
        else level = 10;
    }
    if(level < levelO)  
    {
        if(remedy > 0) {remedy --; HP = (HP/5)*5;}
        else if (HP < 5) {
            HP = 1;
            is_tiny = 1;
        } else {
            HP /= 5;
            is_tiny = 1;
        }
    }
    }}
}

//Event 7:
void ev_7(int event_order, int & HP, int & level, int & maidenkiss, int  & rescue)
{
    if(is_frog == 0 && is_tiny == 0)
    {
    if(!is_arthur && !is_lancelot)
    {
    ///////////   
    int levelO = calcLevelO(event_order);
    if(level > levelO) 
    {
        if(level < 8) level += 2;
        else level = 10;
    }
    if(level < levelO)  
    {
        if(maidenkiss > 0) maidenkiss --;
        else {
            lv_bf_fr = level; 
            level = 1;
        }
    }
    }}
}

//Event 11,12,99:
void ev_11(int & HP, int & level, int & phoenixdown)
{
    int n1 = ((level+phoenixdown)%5 + 1)*3;
    int s1 = n1*(100-n1);
    HP += (s1%100);
    if(HP >= MaxHP) HP = MaxHP;
    while(!isPrime(HP) && (HP < MaxHP))
    {
        HP++;
    }
}
void ev_12(int & HP)
{
    if(HP>1) {
        while(!isFibonacci(HP)) HP--;
    }
}
void ev_99(int & level, int & rescue)
{
    if(is_arthur) level = 10; 
    else if (is_lancelot) {
        if(level >= 8) level = 10;
        else rescue = 0;
    } else {
        if (level == 10) {}
        else rescue = 0; 
    }
}
//Event 13<ms>
void ev_13(int event_code, string file_mush_ghost, int & HP, int & phoenixdown, int & rescue)  
{
    /********** READ FILE "file_mush_ghost" **************/
    int n2;
    int n2_arr[100001], x2_arr[100001];
    ifstream ifs(file_mush_ghost);
    ifs>>n2;
    cout<<"n2: "<<n2<<endl;
    for(int i = 0; i < n2; i++) ifs>>n2_arr[i];
    ifs.close();
    /* END READING FILE */
    string code = ItoS(event_code);
    code.erase(0,2);
    for(int i = 0; i < n2; i++)
    {
        cout<<"n2_arr["<<i<<"]"<<n2_arr[i]<<", ";
        cout<<endl;
        if(n2_arr[i] < 0) x2_arr[i] = -n2_arr[i];
        else x2_arr[i] = n2_arr[i];
        x2_arr[i] = (17*x2_arr[i]+9)%257;
    }
    /***********************************************/

    /****************** EVENT 13 CODE PROCESSING ***************/
        for(int i = 0; i < code.length(); i++)
        {
        if (rescue != -1) break;
        if(int(code[i] - '0') == 1){
        /*****TYPE 1 MUSHROOM ******/
            int maxi, mini;
            maxi = 0; mini = 0;
            for(int i = 1; i < n2; i++)
            {
                if(n2_arr[i] >= n2_arr[maxi]) maxi = i;
                if(n2_arr[i] <= n2_arr[mini]) mini = i; 
            }
            HP -= (maxi + mini);   
        /***************************/
        } else if (int(code[i] - '0') == 2){
        /*****TYPE 2 MUSHROOM ******/
            int mtx, mti;
            int k;
            k = 0;
            while (n2_arr[k] < n2_arr[k+1] && k < n2)
            {
            k ++; 
            mtx = n2_arr[k];
            mti = k;
            }
            while (n2_arr[k] > n2_arr[k+1] && k < n2)
            {
            k ++; 
            }
            if(k != n2) {mtx = -2; mti = -3;}
            HP -= (mtx + mti);       
        /***************************/
        } else if (int(code[i] - '0') == 3){
        /*****TYPE 3 MUSHROOM ******/
            int maxi2, mini2;
            maxi2 = 0; mini2 = 0;
            for(int i = 1; i < n2; i++)
            {
                if(x2_arr[i] > x2_arr[maxi2]) maxi2 = i;
                if(x2_arr[i] < x2_arr[mini2]) mini2 = i; 
            }
            HP -= (maxi2 + mini2);
        /***************************/
        } else {
        /*****TYPE 4 MUSHROOM ******/
                int max2_3x, max2_3i;
                if (x2_arr[0] == x2_arr[1]) 
                {
                    if(x2_arr[1] == x2_arr[2]) {max2_3x = -5; max2_3i = -7;}
                    if(x2_arr[1] < x2_arr[2]) {max2_3x = x2_arr[0]; max2_3i = 0;}
                    if(x2_arr[1] > x2_arr[2]) {max2_3x = x2_arr[2]; max2_3i = 2;}
                } else if (x2_arr[0] > x2_arr[1]) {
                    if(x2_arr[1] >= x2_arr[2]) {max2_3x = x2_arr[1]; max2_3i = 1;}
                    else {
                        if(x2_arr[0] > x2_arr[2]) {max2_3x = x2_arr[2]; max2_3i = 2;}
                        if(x2_arr[0] <= x2_arr[2]) {max2_3x = x2_arr[0]; max2_3i = 0;}
                    } 
                } else {
                    if(x2_arr[0] >= x2_arr[2]) {max2_3x = x2_arr[0]; max2_3i = 0;}
                    else {
                        if(x2_arr[1] > x2_arr[2]) {max2_3x = x2_arr[2]; max2_3i = 2;}
                        if(x2_arr[1] <= x2_arr[2]) {max2_3x = x2_arr[1]; max2_3i = 1;}
                    }
                }
                HP -= (max2_3x + max2_3i); 
        /****************************/
            }
        /**************************************************/
        if(HP <= 0) {
        if(phoenixdown > 0) {
            phoenixdown --; 
            HP = MaxHP;
            is_tiny = 0;
        } else {
            rescue = 0;
        }}
        if(HP > MaxHP) HP = MaxHP;
        }
}
//Event 19:
void ev_19(bool & metAsclepius, string file_asclepius_pack, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown)
{
if(metAsclepius == false)
{
    int r1, c1;
    int arr[101][101];
    int taken[100001];
//
    ifstream ev19(file_asclepius_pack);
    ev19>>r1>>c1;
//[r1][c1];
    for(int i = 0; i< r1; i++)
    {
        taken[i] = 0;
        for(int j = 0; j<c1; j++)
        {
            ev19>>arr[i][j];
        }
    }
    ev19.close();
    for(int i = 0; i< r1; i++)
    {
        for(int j = 0; j<c1; j++)
        {
            if(arr[i][j] == 16) {remedy ++; taken[i]++; 
            if(is_tiny && remedy > 0)
            {
                remedy--;
                HP *= 5;
                if(HP > MaxHP) HP = MaxHP;
                is_tiny = 0;
            }
            if(taken[i] == 3) break;}
            if(arr[i][j] == 17) {maidenkiss ++; taken[i]++; 
            if(is_frog && maidenkiss > 0)
            {
                maidenkiss--;
                level = lv_bf_fr;
                is_frog = 0;
            }
            if(taken[i] == 3) break;}
            if(arr[i][j] == 18) {phoenixdown ++; taken[i] ++; if(taken[i] == 3) break;}
        }
        if(remedy > 99) remedy = 99; 
        if(maidenkiss > 99) maidenkiss = 99; 
        if(phoenixdown > 99) phoenixdown = 99; 
    }
    metAsclepius = true;
}
}
//Event 18:
void ev_18(bool & metMerlin, string file_merlin_pack, int & HP)
{
if(metMerlin == false) {
    ifstream ev18(file_merlin_pack);
    int n9; 
    ev18 >> n9;
    string s[101];
    for(int i = 0; i<=n9;i++) {getline(ev18,s[i]);}
    for(int i = 1; i<=n9;i++) {
        if(s[i].find("Merlin") != -1 || s[i].find("merlin") != -1) HP += 3;
        else HP += 2;
        if(HP >= MaxHP) {HP = MaxHP; break;}
    }
    metMerlin = true;
}
}





void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    ifstream ifs(file_input);
    ifs>>HP>>level>>remedy>>maidenkiss>>phoenixdown;
    rescue = -1;
    MaxHP = HP;
    int event[100001]; int index = 0;
    ifs>>event[0];
    while(event[index] != 0) {index++; ifs>>event[index];}
    ifs.close();
    

    ifstream nifs(file_input);
    string ext_files, file_mush_gosh, file_merlin_pack, file_asclepius_pack;
    getline(nifs,ext_files);
    getline(nifs,ext_files);
    getline(nifs,ext_files);
    ext_files += ',';
    file_mush_gosh = ext_files.substr(0,ext_files.find(','));
    ext_files.erase(0,ext_files.find(',')+1);
    file_asclepius_pack = ext_files.substr(0,ext_files.find(','));
    ext_files.erase(0,ext_files.find(',')+1);
    file_merlin_pack = ext_files.substr(0,ext_files.find(','));
    nifs.close();

/****** CHECK IF KNIGHT IS LANCELOT OR ARTHUR *****/
    if(MaxHP == 999) is_arthur = true;
    if(isPrime(MaxHP)) is_lancelot = true;

/************************* ADVENTURES ***********************/
    if(event[0] == 0){
        rescue = 1; 
        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);}
    else {
        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
    for(int i = 0; i < index; i++)
    {
        
        //cout<<"Event: "<<event[i]<<endl;
        //events 13:
        if(isEvent13(event[i])) ev_13(event[i], file_mush_gosh, HP, phoenixdown, rescue);
        //event 6:
        if(event[i] == 6) ev_6(i+1,HP,level,remedy,rescue);
        else if(event[i] == 7) ev_7(i+1,HP,level,maidenkiss,rescue);
        else {
        //events 15,16,17:
        if(event[i] == 15) {if(remedy < 99) remedy++;}
        if(event[i] == 16) {if(maidenkiss < 99) maidenkiss++;}
        if(event[i] == 17) {if(phoenixdown < 99) phoenixdown++;}
        //events 1-5:
        if(event[i] >= 1 && event[i] <= 5) 
            ev_1to5(event[i], i+1, HP, level, phoenixdown, rescue);
        //event 11,12:
        if(event[i] == 11) ev_11(HP, level, phoenixdown);
        if(event[i] == 12) ev_12(HP);
        if(event[i] == 19) 
            ev_19(metAsclepius, file_asclepius_pack, HP, level, remedy, maidenkiss, phoenixdown);
        if(event[i] == 18)
            ev_18(metMerlin, file_merlin_pack, HP);

/************TINY CONDITION + FROG CONDITION************/
        if(is_tiny != 0) is_tiny++;
        if(is_tiny == 4) {is_tiny = 0; HP *= 5; if(HP > MaxHP) HP = MaxHP;}
        if(is_frog != 0) is_frog++;
        if(is_frog == 4) {is_frog = 0; level = lv_bf_fr;}
/***************************************************************/
        if(HP <= 0) {
            rescue = 0;
            display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            break;} 
        if(rescue != -1) break;
        if((i == index -1) && (rescue = -1)) {rescue = 1;}
        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
    }}}
}