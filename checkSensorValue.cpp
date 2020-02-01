#include <iostream>
#include <sstream>

#include "checkSensorValue.h"

// va[t] = sh[t][k]
static void makeVA(int k, SensorHistory& sh, Values& va)
{
    va.clear();
    for (int t=0;t<sh.size();t++) {		
        va.add(sh[t][k]);
    }
}

void checkSensorValue(Values& val, SensorHistory& sh, Values& defected)
{
    cout << endl;
    int n = val.cnt; // # of sensors
    // k:sensor id
    for (int k=0; k<n;k++) {
        Values va;
        makeVA(k,sh,va);
        defected[k]  = checkSensorValueSub(val[k], va);
    }
}

// 0: 正常
// 1: スタック故障検知
// 2: ランダム故障検知
int checkSensorValueSub(int v, Values& h)
{	
    int c = h.cnt;
    cout << endl << "Sub:h= " << h.str() << endl;

    if (c < 5) {
        h.add(v);
        return 0;
    }

    if (checkSF(v, h)){
        return 1;
    } else if (checkRF(v,h)) {
        return 2;
    } else {
        //バッファの最も古い値を削除し、現在値をバッファに追加
        for (int t=0;t<c-1;t++){
            h[t] = h[t+1];
        }
        return 0;
    }
}

// スタック故障(Stack Failure)検知
bool checkSF(int16_t v, Values& h){
    //cout << "SF:h= " << h.str() << endl;

    int n = h.cnt;
    for (int i=0;i<n-1;i++){
        int16_t diff = abs(h[i+1] - h[i]);
        if (diff > 5)
            return false;
    }
    return true;
}

// ランダム故障(Random Failure)検知
bool checkRF(int16_t v, Values& h){
    //	cout << "RF:h= " << h.str() << endl;

    int c = 0;
    int n = h.cnt;
    for (int i=0;i<n-1;i++){
        int16_t diff = abs(h[i+1]- h[i]);
        if (diff > 100) c++;
    }
    return (c>=2);
}
