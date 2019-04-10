#include <Dump.h>
#include <menu/def/arduino/avr.h>
#include <menu/IO/serialOut.h>
#include <menu/comp/multiLang.h>

using namespace Menu;

using FlashText=AM5::FlashTextDef<AM5::Empty>;

//string id's
enum LangCodes:size_t {textOk=0,textCancel,langStringsCnt};

//define multilang strings table on flash
//both the table and the strings will be on flash
// using constStr=const PROGMEM char*;
const PROGMEM char ok_en[]="Ok";
const PROGMEM char ok_pt[]="Vá";
const PROGMEM char cancel_en[]="Cancel";
const PROGMEM char cancel_pt[]="Esquece";

FlashText ok_enOp(ok_en);
FlashText cancel_enOp(cancel_en);
FlashText ok_ptOp(ok_pt);
FlashText cancel_ptOp(cancel_pt);

FlashText const enLang[] PROGMEM {ok_enOp,cancel_enOp};
FlashText const ptLang[] PROGMEM {ok_ptOp,cancel_ptOp};

using MultiLang=AM5::Lang<FlashText>;
MultiLang langs(enLang);

template<LangCodes id>
using LangOp=AM5::Prompt<MultiLang::Text<langs,id,AM5::Empty>>;

template<typename O>
using WrapTitle=AM5::TitleWrapFmt<O>;

//serial output
MenuOut<AM5::SerialFmt<>::To<SerialOutDev<>>> serialOut;

//normal option
Prompt<Text> op1("Op 1");

//option using flash text
const char op2_text[] PROGMEM="Op 2";
Prompt<FlashText> op2(op2_text);

LangOp<textOk> op3;
LangOp<textCancel> op4;

//they can fit on same array
//and will preserve the composed behavior
Item* ops[]{&op1,&op2,&op3,&op4};

void setup() {
  Serial.begin(115200);
  while(!Serial);
  serialOut<<"AM5 tiny example ----"<<endl;
  for(auto o: ops) serialOut<<*o<<endl;
  Serial<<"change language ----"<<endl;
  langs.setLangTable(ptLang);
  for(auto o: ops) serialOut<<*o<<endl;
  serialOut<<"----"<<endl;
}

void loop() {}
