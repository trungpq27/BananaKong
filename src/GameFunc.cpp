#include "GameFunc.h"

string longLongToString(long long x){
    stringstream ss;
    ss << x;
    string str = ss.str();
    return str;
}

void gMonkeyHandleHigherPath(int &gMonkeyState, pair<int, int> &gMonkey_Pos, pair<double, double> *PathPosX_Carry, int &FallTo_Pos, int MONKEY_JUMPING_SPEED){

    for(int ID = 1; ID <= HIGHER_PATH_COUNT; ++ID){

        if ((gMonkey_Pos.first + MONKEY_WIDTH - 20) >= PathPosX_Carry[ID].first && gMonkey_Pos.first + 50 <= PathPosX_Carry[ID].second){

            int gMonkey_HigherPath_PosY;
            if(ID <= UP_PATH2_ID) gMonkey_HigherPath_PosY = gMonkey_X1_PosY;
            else gMonkey_HigherPath_PosY = gMonkey_X2_PosY;

            if (gMonkeyState == STATE_FALLNPR || gMonkeyState == STATE_FALLPARA){

                if (gMonkey_Pos.second >= gMonkey_HigherPath_PosY && gMonkey_Pos.second <= gMonkey_HigherPath_PosY + MONKEY_JUMPING_SPEED){
                    gMonkey_Pos.second = gMonkey_HigherPath_PosY;
                    gMonkeyState = STATE_RUN;
                }
            }

        }
        else if(gMonkeyState == STATE_RUN && gMonkey_Pos.first + 50 > PathPosX_Carry[ID].second && gMonkey_Pos.first <= PathPosX_Carry[ID].second){
                if ((ID <= UP_PATH2_ID && gMonkey_Pos.second == gMonkey_X1_PosY) || (ID >= AIR_PATH1_ID && gMonkey_Pos.second == gMonkey_X2_PosY)){
                    gMonkey_Pos.second += MONKEY_JUMPING_SPEED;
                    gMonkeyState = STATE_FALLNPR;
                    //cout << ID << " ";     //debug only
                }
        }

    }

}
