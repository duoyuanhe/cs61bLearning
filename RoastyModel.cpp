#include "RoastyModel.hpp"

#include <string>
#include <iostream>
using namespace std;

/*----------------Bean Function---------------- */
string const& Bean::getName() const {  //const getter                                      
  return name;
}
string& Bean::getName(){               //non-const getter                                  
  return name;
}
Bean& Bean::operator=(Bean const& other){   //copy operator                                     
  this->name = other.name;
  return *this;
}
Bean::Bean(Bean const& other){              //copy constructor                                  
  *this = other;
}
/*--------------------------------------------- */

/*----------------Ingredient Function---------------- */
Bean const& Ingredient::getBean() const {           //const getter                              
  return *bean;
}
Bean& Ingredient::getBean(){                        //non-const getter                          
  return *bean;
}

int const Ingredient::getAmount()const {             //const getter                            
  return amount;
}
int Ingredient::getAmount(){                         //non-const getter                        
  return amount;
}

Ingredient& Ingredient::operator=(Ingredient const& other){    //copy operator                  
  if(this->bean!=nullptr){delete this->bean;}     //delete old bean
  this->bean = new Bean(*other.bean);
  this->amount = other.amount;
  return *this;
}
Ingredient::Ingredient(Ingredient const& other){               //copy contructor                
  *this = other;
}
Ingredient::~Ingredient(){                          //destructor                                
  if(bean!=nullptr){
    delete bean;
    bean = nullptr;
  }
}
/*--------------------------------------------- */

/*----------------EventValue Function---------------- */
long const EventValue::getValue() const {              //const getter                        
  return value;
}
long EventValue::getValue() {                        //non-const getter                    
  return value;
}

EventValue& EventValue::operator=(EventValue const& other){  //copy operator                    
  this->value = other.value;
  return *this;
}
EventValue::EventValue(EventValue const& other){             //copy-constructor                 
  *this = other;
}
/*--------------------------------------------- */

/*----------------Event Function---------------- */

bool Event::hasValue() const{                          //Check if the event hans a EventValue
  if(eventvalue==nullptr){ return false;
  } else {
  return true;
  }
}

EventValue const* Event::getValue() const{            //EventValue getter
  return eventvalue;
}

EventValue* Event::getValue(){
  return eventvalue;
}

std::string const& Event::getType () const{                     //Type const getter             
  return type;
}
std::string& Event::getType(){                                   //Type non-const getter        
  return type;
}

long const Event::getTimestamp () const{                     //Timestamp const getter          
  return eventtimestamp;
}
long Event::getTimestamp (){                                 //Timestamp non-const getter      
  return eventtimestamp;
}


Event& Event::operator=(Event const& other){                         //copy operator            
  this->type           = other.type;
  this->eventtimestamp = other.eventtimestamp;
  if(this->hasValue()){
    delete this->eventvalue;
  }
  if(other.hasValue()){
    this->eventvalue    = new EventValue(*other.eventvalue);
  }
  return *this;
}

Event::Event(Event const& other){                               //copy-constructor              
  *this=other;
}


Event::~Event(){                                               //destructor                     
  if(this->hasValue()){
    delete eventvalue;
  }
}

/*--------------------------------------------- */

/*----------------Roast Function---------------- */

long const Roast::getId() const{                          //ID getter                          
  return ID;
}
long Roast::getId(){
  return ID;
}

long const Roast::getTimestamp() const{                   //Timestamp getter                          
  return roasttimestamp;
}
long Roast::getTimestamp(){
  return roasttimestamp;
}

Ingredient const& Roast::getIngredient(int i) const{  //Ingredient getter                 
  if(i>=0 && i<icount){
    return *ingredient[i];
  } else {
    cerr<<"cout: Ingredient ["<<i<<"] out of range"<<endl;
    exit(1);
  }
}

Ingredient& Roast::getIngredient(int i){
  if(i>=0 && i<icount){
    return *ingredient[i];
  } else {
    cerr<<"cout: Ingredient ["<<i<<"] out of range"<<endl;
    exit(1);
  }
}


int const Roast::getIngredientsCount() const{            //IngredientCount getter           
  return icount;
}
int Roast::getIngredientsCount(){
  return icount;
}

Event const& Roast::getEvent(int i) const{         //Event getter
  if(i>=0 && i<ecount){
    return *event[i];
  } else {
    cout<<"cout: Event ["<<i<<"] out of range"<<endl;
    exit(1);
  }
}
Event& Roast::getEvent(int i){
  if(i>=0 && i<ecount){
    return *event[i];
  } else {
    cout<<"cout: Event ["<<i<<"] out of range"<<endl;
    exit(1);
  }
}

int const Roast::getEventCount() const{                 //EventCount getter
  return ecount;
}
int Roast::getEventCount(){
  return ecount;
}

Roast& Roast::operator=(Roast const& other){             //copy operator                        
  for(int i=0; i<this->ecount; i++){
    delete this->event[i];
  }
  for(int i=0; i<this->icount; i++){
    delete this->ingredient[i];
  } 
  for(int i=0; i<other.getEventCount(); i++){
    this->event[i]      = new Event(*other.event[i]);
  }
  for(int i=0; i<other.icount; i++){
    this->ingredient[i] = new Ingredient(*other.ingredient[i]);
  }
  this->icount         = other.icount;
  this->ecount         = other.ecount;
  this->roasttimestamp = other.roasttimestamp;
  this->ID             = other.ID;
  return *this;
}
Roast::Roast(Roast const& other){                         //copy-constructor                    
  *this = other;
}

Roast::~Roast(){                                          //desturctor                          
  for(auto i=0; i<ecount; i++){
    delete event[i];
  }
  for(auto i=0; i<icount; i++){
    delete ingredient[i];
  }
}

void Roast::addIngredient(Ingredient const& ingre){    // add Ingredient
  if(icount<capacity){
    this->ingredient[icount] = new Ingredient(ingre);
    icount++;
    delete &ingre;
    return;
  }
}

void Roast::removeIngredientByBeanName(std::string const& beanName){  //remove Ingredient By Bean Name
  for(auto i=0; i<icount; i++){
    if(ingredient[i]->getBean().getName() == beanName){
      ingredient[i] = ingredient[icount];
      icount--;
      return;
    }
  }
}

void Roast::addEvent(Event const& eve){          //add Event
  if(ecount<capacity){
    this->event[ecount] = new Event(eve);
    ecount++;
    delete &eve;
    return;
  }
}

void Roast::removeEventByTimestamp(long const& oldTimestamp){    //remove Event By Timestamp
  for(auto i=0; i<ecount; i++){
    if(event[i]->getTimestamp() == oldTimestamp){
      event[i] = event[ecount];
      ecount--;
      return;
    }
  }
}

/*--------------------------------------------- */
