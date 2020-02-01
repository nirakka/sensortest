#include <iostream>
#include <sstream>

#include "readSensorValue.h"

// センサbの読み取りが要求されていればT(b=0..7)
inline bool required(uint8_t setting, int b){
	return setting & (1<<b);
}

//使い方
//
int readSensorValue(uint8_t settings,
	Values v01, Values v16, RawValue& rv){
	//cout << endl;

	for (int i=0;i<8;i++){
		if (i < 4){
			if( required(settings, i) ){
				rv.v16[i] = v16[i];

				//cout << "i=" << i << " ";
				//cout << "rv.v16=" << rv.v16.str() << endl;
			}
		}
	}
	return 0;
}
