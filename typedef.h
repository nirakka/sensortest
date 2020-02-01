#pragma once
#include <iomanip>

#include <cstring>
#include <inttypes.h>

#include <fstream>
#include <sstream>

class Date {
private:
  union {
    uint8_t b[4];
    uint32_t l;
  } val;
public:
  uint32_t getval() const { return val.l; } 
  uint8_t getYear() const { return val.b[3]; }
  uint8_t getMonth() const { return val.b[2]; }
  uint8_t getDay() const { return val.b[1]; }
  uint8_t getDayofWeek() const { return val.b[0]; }
  Date(uint8_t y, uint8_t m, uint8_t d) {
    val.b[3] = y; val.b[2] = m; val.b[1] = d; val.b[0] = 0;
  }
  Date() { val.l = 0x63636363; } // (99,99,99,99)
  friend bool operator==(Date& d1,Date&d2) { return d1.val.l == d2.val.l; }
  friend bool operator<(Date& d1,Date&d2) { return d1.val.l < d2.val.l; }
  friend bool operator>(Date& d1,Date&d2) { return d1.val.l > d2.val.l; }
  friend bool operator<=(Date& d1,Date&d2) { return !(d1>d2); }
  friend bool operator>=(Date& d1,Date&d2) { return !(d1<d2); }
  friend bool operator!=(Date& d1,Date&d2) { return !(d1==d2); }
  std::string dec02(int v) {
	std::stringstream ss;
	ss << std::setw(2) << std::right << std::setfill('0');
	ss << v ;
	return ss.str();
  }
  std::string str() {
	std::stringstream ss;
	ss << dec02(getYear()) << "-";
	ss << dec02(getMonth()) << "-" ;
	ss << dec02(getDay());
	return ss.str();
  }
};

class Time {
private:
  union {
    uint8_t b[4];
    uint32_t l;
  } val;
public:
  uint32_t getval() const { return val.l; }
  uint8_t getHour() const { return val.b[3]; }
  uint8_t getMin() const { return val.b[2]; }
  uint8_t getSecond() const { return val.b[1]; }
  uint8_t getMilSec() const { return val.b[0]; }
  Time(uint8_t h, uint8_t m, uint8_t s) {
    val.b[3] = h; val.b[2] = m; val.b[1] = s; val.b[0] = 0;	
  }
  Time() { val.l = 0x63636363 ;} // (99,99,99,99)
  friend bool operator==(Time& t1,Time&t2)  { return t1.val.l == t2.val.l; }
  friend bool operator<(Time& t1,Time&t2) { return t1.val.l < t2.val.l; }
  friend bool operator>(Time& t1,Time&t2) { return t1.val.l > t2.val.l; }
  friend bool operator<=(Time& t1,Time&t2) { return !(t1>t2); }
  friend bool operator>=(Time& t1,Time&t2) { return !(t1<t2); }
  friend bool operator!=(Time& t1,Time&t2) { return !(t1==t2); }
  std::string dec02(int v) {
	std::stringstream ss;
	ss << std::setw(2) << std::right << std::setfill('0');
	ss << v ;
	return ss.str();
  }
  std::string str() {
	std::stringstream ss;
	ss << dec02(getHour()) << ":" ;
	ss << dec02(getMin()) << ":" ;
	ss << dec02(getSecond());
	return ss.str();
  }
};

class DateTime {
public:
  Date d;
  Time t;

  Date getDate() const { return d; }
  Time getTime() const { return t; }

  DateTime(Date date,Time time):d(date),t(time) {}
  DateTime() {}
  friend bool operator==(DateTime& dt1,DateTime& dt2) 
    { return (dt1.d == dt2.d) && (dt1.t == dt2.t) ; }
  friend bool operator<(DateTime& dt1,DateTime& dt2) 
    { return (dt1.d < dt2.d) || ((dt1.d == dt2.d) && (dt1.t < dt2.t)) ; }
  friend bool operator>(DateTime& dt1,DateTime& dt2) 
    { return (dt1.d > dt2.d) || ((dt1.d == dt2.d) && (dt1.t > dt2.t)) ; }
  friend bool operator<=(DateTime& dt1,DateTime& dt2) { return !(dt1>dt2); }
  friend bool operator>=(DateTime& dt1,DateTime& dt2) { return !(dt1<dt2); }
  friend bool operator!=(DateTime& dt1,DateTime& dt2) { return !(dt1==dt2); }
  std::string str() {
	std::stringstream ss;
	ss << "(" << d.str() << "," << t.str() << ")";
	return ss.str();
  }
};

// センサ番号
#define X(n) (0x0000|(n))
#define Y(n) (0x4000|(n))
#define A(n) (0x8000|(n))
#define B(n) (0xC000|(n))
#define Number(v) ((v)&0xff)

class Sensor {
public:
  uint16_t no;

  Sensor() : no(0) {}
  Sensor(int n) : no(n) {}
  friend bool operator==(const Sensor& s1, const Sensor& s2) {
    return (s1.no == s2.no);
  }
  friend bool operator!=(const Sensor& s1, const Sensor& s2) {
    return (s1.no != s2.no);	  
  }
  operator uint16_t() const { return no; }  
  std::string str() {
	std::stringstream ss;
	int n = Number(no);
	static char ca[]="XYAB";
	int k = ((no >> 14)&0x3);
	ss << ca[k] << n ;
	return ss.str();
  }
};

typedef Sensor Actuator;

#include <initializer_list>

inline int min(int x,int y) { return (x>y)?y:x; }

template<class Elem>
class Array {
  int size;
  Elem *value;
public:
  Array(int sz):size(sz) { value = new Elem[sz]; }
  Array(std::initializer_list<Elem> list):size(list.size()) {
	value = new Elem[size];
	int i=0;
	for (auto iter = list.begin() ; iter != list.end() ; ++iter ) {
	  value[i++] = (*iter);
	}
  }
  int getSize()  const { return size;}
  Elem& operator[]( int idx ) { return value[idx]; }
  void clear() { memset(value,0,sizeof(Elem)*size); }
  friend bool operator==(Array& a1,Array &a2) {
	  int l1 = a1.size;
	  int l2 = a2.size;
	  int l = min(l1,l2);
	  for (int i=0;i<l;i++) {
		  if (!(a1[i] == a2[i])) return false;
	  }
	  return true;
  }
  friend bool operator!=(Array& a1,Array &a2) { return !(a1==a2); }
  std::string str(bool nl=false) {
	std::stringstream ss;
	ss << "[" ;
	for (int i=0;i<size;i++) {
		if (i>0) ss<<",";
		if (nl) ss << std::endl;
		ss << value[i].str();
	}
	ss << "]";
	return ss.str();
  }  
};

class Values {
public:
  int16_t val[10];
  #define SIZE (sizeof(val)/sizeof(val[0]))
  int cnt;

  void setval(int i, int16_t v) {val[i] = v;}
  int16_t getval(int i) const { return val[i]; }

  friend bool operator==(Values& x1, Values& x2) {
	  for (int i=0;i<SIZE;i++)
		if (x1.getval(i) != x2.getval(i)) return false;  
	  return true;
  }
  friend bool operator!=(Values& x1, Values& x2) { return !(x1==x2); }
  int16_t& operator[](int i) { return val[i]; }

  Values(int16_t v=0) {
	  for (int i=0;i<SIZE;i++) {
		  setval(i,v);
	  }
	  cnt = SIZE;
  }
  
  void clear() {memset(val,0,sizeof(int16_t)*SIZE); cnt = 0; }
  void add(int16_t v) { val[cnt++] = v;}

  Values(std::initializer_list<int16_t> list) {
	  clear();
	  int i=0;
	  for (auto iter = list.begin() ; iter != list.end() ; ++iter ) {
		val[i++] = (*iter);
	  }
	  cnt = i;
  }

  int size() { return SIZE; }

  std::string str() {
	std::stringstream ss;
	ss << "[";
	for (int i=0;i<SIZE;i++) {
		if (i>0) ss << ",";
		ss << val[i];
	}
	ss << "]";
	return ss.str();
  }  
};

// センサ値
class SensorValue {
public:
  DateTime dt;
  Values v01; // TODO:packing
  Values v16;

  void setv01(int n, uint8_t v) { v01.setval(n,(int16_t)v); }
  void setv16(int n, int16_t v) { v16.setval(n,v); }
  uint8_t getv01(int n) const { return (uint8_t)v01.getval(n); }
  int16_t getv16(int n) const { return v16.getval(n); }

  DateTime getDT() const { return dt; }
  Date getDate() const { return dt.d; }
  Time getTime() const { return dt.t; }

  SensorValue() {}
  SensorValue(DateTime dt0) : dt(dt0) {}
  SensorValue(int16_t v) : v01(Values(v)), v16(Values(v)) {}
  SensorValue(Values x01, Values x16) : v01(x01), v16(x16) {}
  SensorValue(DateTime dt0, Values x01, Values x16) : 
	dt(dt0), v01(x01), v16(x16) {}
  SensorValue(uint8_t *a01, int16_t *a16) {
    for (int i=0;i<v16.size();i++) {
      v01.setval(i, (int16_t)a01[i]); 
	  v16.setval(i,a16[i]);
    }
  }
  friend bool operator==(SensorValue& x1, SensorValue& x2) {
	  return (x1.v01 == x2.v01) && (x1.v16 == x2.v16);
  }
  friend bool operator!=(SensorValue& x1, SensorValue& x2) { return !(x1==x2); }
  std::string str() {
	std::stringstream ss;
	ss << "SV(" ;
	ss << "dt=" << dt.str() << "," ;
	ss << "v01=" << v01.str() << ",";
	ss << "v16=" << v16.str() ;
	ss << ")";
	return ss.str();
  }
};

typedef Array<SensorValue> SensorValueArray;

// 入力:カウンタ
class Counter {
public:
  uint16_t preset;
  uint16_t current;

  Counter():preset(0), current(0) {}
  Counter(int p, int c) : preset(p), current(c) {}
  friend bool operator==(Counter &c1,Counter&c2) {
	  return (c1.preset  == c2.preset) &&
			 (c1.current == c2.current);
  }
  friend bool operator!=(Counter &c1,Counter&c2) { return !(c1==c2); }
  std::string str() {
	std::stringstream ss;
    ss << "Counter(" << preset << "," << current << ")";
	return ss.str();
  }
};

typedef Array<Counter> CounterArray;

// 入力・出力共有
typedef SensorValue RawValue;

typedef Array<RawValue> RawValueArray;

class Collection {
public:
  Sensor sensor;
  uint16_t duration; // sec

  Collection(): sensor(Sensor(0)), duration(0) {}
  Collection(int sn, int du) :
	sensor(Sensor(sn)), duration(du) {}
  friend bool operator==(Collection &c1,Collection &c2) {
	  return (c1.sensor  == c2.sensor) &&
			 (c1.duration== c2.duration);
  }
  friend bool operator!=(Collection &c1,Collection&c2) { return !(c1==c2); }
  std::string str() {
	std::stringstream ss;
	ss << sensor.str() << "=" << duration;
	return ss.str();
  }
};

typedef Array<Collection> CollectionArray;

class Condition {
public:
  Sensor no;  // 番号
  int16_t arg; // 値
  int op;  // >(1), =(2), <(3) のどれか

  Condition() {}
  Condition(int n, int a, int o=0): no(n),arg(a),op(o) {}
  friend bool operator==(Condition& a1, Condition& a2) {
    return (a1.no == a2.no) && (a1.arg == a2.arg) && (a1.op == a2.op);
  }
  friend bool operator!=(Condition& a1, Condition& a2) {
	return !(a1==a2);
  }
  std::string str() {
	std::stringstream ss;
	static char opa[] = " >=<";
	ss << no.str() << opa[op] << arg;
	return ss.str();
  }
};
// X1>3000 => { 0x0001, 3000, 1}

class Action : public Condition {
public:
  Action() {}
  Action(int n, int a): Condition(n,a,0) {} //opは使用せず
  friend bool operator==(Action& a1, Action& a2) {
    return (a1.no == a2.no) && (a1.arg == a2.arg) ;
  }
  friend bool operator!=(Action& a1, Action& a2) {
	return !(a1==a2);
  }
  std::string str() {
	std::stringstream ss;
	ss << no.str() << "=" << arg;
	return ss.str();
  }
};
// B1 = 1 => { 0xC001, 1, 0 }
 
class Warn {
public:
  Condition *cond;
  Action *act;

  Condition *getCondition() const { return cond; }
  Action    *getAction()    const { return act; }
  uint16_t getSensorNo()    const { return cond->no;}
   int16_t getSensorArg()   const { return cond->arg;}
  uint16_t getActuatorNo()  const { return act->no; }
   int16_t getActuatorArg() const { return act->arg;}
	
  Warn(): cond(0),act(0) {}
  Warn(Condition *c, Action *a): cond(c),act(a) {}
  std::string str() {
	  std::stringstream ss;
	  ss << cond->str() << ":" << act->str();
	  return ss.str();
  }
};

class WarnValue {
public:
  Warn *warn;
  Condition cond;
  Action act;

  std::string message;
  void setWarn(Warn *w) { warn = w; }

  WarnValue() : message(""),warn(0) {}
  WarnValue(int sn,int sv,int an,int av): 
	cond(Condition(sn,sv)), act(Action(an,av)) {}
  std::string str() {
	std::stringstream ss;
	ss << "(" << cond.no.str() << "," << cond.arg << ")-";
	ss << "(" << act.no.str() << "," << act.arg << ")" ;
	return ss.str();
  }
};

typedef Array<WarnValue> WarnValueArray;

typedef SensorValue CollectedValue;

typedef Array<CollectedValue> CollectedValueArray;

// 収集間隔の変化記録
class CollectedHistory {
public:
  DateTime dt;
  CollectionArray *ary;

  Date getDate() const { return dt.d; }
  Time getTime() const { return dt.t; }

  CollectedHistory() : ary(0) {}
  CollectedHistory(DateTime dt0, CollectionArray *a=0) : dt(dt0), ary(a) {}
  std::string str() {
	std::stringstream ss;
	ss << "CH(" << dt.str() << " ";
	ss << ((ary)?ary->str():"[]") << ")";
	return ss.str();
  }
};

typedef Array<CollectedHistory> CollectedHistoryArray;

// 出力・応答共有 : 1時間毎にファイル出力

class CollectedStore {
public:
  CollectedValueArray *va;
  CollectedHistoryArray *ha;

  CollectedValue& valueOf(int k) const { return (*va)[k]; }
  CollectedHistory& historyOf(int k) const { return (*ha)[k]; }
  CollectedStore() : va(0), ha(0) {}
  CollectedStore(
	CollectedValueArray *va0, CollectedHistoryArray *ha0
	) : va(va0), ha(ha0) {}
  void clear() { va->clear(); }
  void addHistory(int k, CollectedHistory& x) { (*ha)[k] = x; }
  
  std::string str(bool nl=false) {
	std::stringstream ss;
	ss << "CS(" ;
	ss << ((va)?va->str(nl):"[]") << std::endl;
	ss << ((ha)?ha->str(nl):"[]") << std::endl;
	ss << ")";
	return ss.str();
  }
};

// ビットベクタ
class BitVector {
private:
  uint32_t val;
  static const uint32_t mask[];
public:
  void set  (int n) { val |= mask[n]; }
  void reset(int n) { val &= ~mask[n]; }
  uint32_t getval() { return val; }

  BitVector() : val(0) {}

  std::string str() {
	static char b[10];
	int v=val;
	for (int i=0;i<8;i++) {
	  b[i] = (v&mask[i])?'*':'-';
	}
	b[8] = 0;
	return std::string(b);
  }
};

// 応答
class CheckedRequest {
private:
  static const uint32_t mask[];
public:
  DateTime begin;
  DateTime end;
  uint32_t interval; // sec
  BitVector vec16; // 収集するセンサ番号のビットベクタ
  BitVector vec01; // 同上

  void setvec16(int k)   {vec16.set(k); }
  void setvec01(int k)   {vec01.set(k); }
  void resetvec16(int k) {vec16.reset(k);}
  void resetvec01(int k) {vec01.reset(k);}

  CheckedRequest() {}
  CheckedRequest(DateTime &b,DateTime &e,uint32_t v) :
	begin(b), end(e), interval(v) {}
  std::string str() {
	std::stringstream ss;
	ss << "CR(" ;
	ss << begin.str() << " " << end.str() << " " << interval << " ";
	ss << vec01.str() << " " << vec16.str() << ")";
 	return ss.str();
  }  
};

typedef CheckedRequest Request; // 別名

class FilteredCollectedStore {
public:
  std::string message;
  CollectedStore *value;
  
  FilteredCollectedStore(std::string m="",CollectedStore *v=0) 
	: message(m),value(v) {}
  std::string str(bool nl=false) {
	std::stringstream ss;
	ss << "m=" << "%" << message << "% ";
	ss << "v=" << ((value)?(value->str(nl)):"null");
	return ss.str();
  }  
};

class SensorHistory {
public:
	Values hist[10];
	int cnt;

// TODO: 上限検査
	void clear() { 
		memset(hist,0,sizeof(Values)*10); 
		cnt = 0;
	}
	
	SensorHistory(int k, int16_t *a, int n){
		for (int i=0;i<n;i++){
			hist[i][k] = a[i];
		}
		cnt = n;
	}
	Values& operator[](int i) { return hist[i]; }
	
	void add(const Values& val) { hist[cnt++] = val; }
	int  size() {return cnt; }
	
  std::string str() {
	std::stringstream ss;
	ss << "[";
	for (int i=0;i<cnt;i++) {
		if (i>0) ss << ",";
		ss << hist[i].str();
	}
	ss << "]";
	return ss.str();
  }  
};
