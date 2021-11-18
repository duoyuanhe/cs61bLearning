#pragma once

#include <string>
#include <iostream>

/*----------------Bean Class---------------- */
class Bean {
  std::string name;
public:
  Bean(std::string n):name(n){};  //consturctor                                                             
  std::string const& getName () const;  //const getter
  std::string& getName ();              //non-const getter
  Bean& operator=(Bean const&);       //copy operator
  Bean(Bean const&);                  //copy constructor
  ~Bean(){};                              //destructor
};

 /*----------------Ingredient Class---------------- */
class Ingredient{
  Bean* bean=nullptr;
  int amount=0;
public:
  Ingredient(const Bean& b, int am=0):bean(new Bean(b)), amount(am){    //constructor
    delete &b;
    if(am<0){
      std::cerr << "Ingredient Amount is not positive!"<<std::endl;
      exit(1);
    }
  };
  Bean const& getBean() const;                   //const getter Bean
  Bean& getBean();                               //non-const getter Bean
  int const getAmount() const;                    //const getter amount
  int getAmount();                                //non-const getter amount
  Ingredient& operator=(Ingredient const&);      //copy operator
  Ingredient (Ingredient const&);                //copy constructor
  ~Ingredient();                                   //destructor
};
 /*----------------EventValue Class--------------- */
class EventValue{
  long value = 0;
public:
  EventValue(long value=0):value(value){};          //constructor
  long const getValue () const;             //const getter
  long getValue();                          //non-const getter                                    
  EventValue& operator=(EventValue const&);        //copy operator
  EventValue(EventValue const&);                   //copy costructor
  ~EventValue(){};                                 //destructor
};
 /*----------------Event Class---------------- */
class Event{
  std::string type;
  long eventtimestamp;
  EventValue* eventvalue=nullptr;
public:
  //constructor
  Event(std::string type, long eventtimestamp):type(type), eventtimestamp(eventtimestamp){};
  Event(std::string type, long eventtimestamp, EventValue* eventvalue)  
    :type(type), eventtimestamp(eventtimestamp), eventvalue(eventvalue){};
  bool hasValue() const;
  EventValue const* getValue() const;
  EventValue* getValue();
  std::string const& getType () const;                          //Type const getter
  std::string& getType();                                       //Type non-const getter
  long const getTimestamp () const;                            //Timestamp const getter
  long getTimestamp ();                                        //Timestamp non-const getter
  Event& operator=(Event const&);                               //copy operator
  Event(Event const&);                                          //copy constructor
  ~Event();                                                       //destructor
};
 /*----------------Roast Class---------------- */
class Roast{
  static int const capacity = 99;
  int icount = 0;
  int ecount = 0;
  long roasttimestamp = 0;
  long ID = 0;
  Event* event[capacity];
  Ingredient* ingredient[capacity];
public:
  Roast(long ID=0, long roasttimestamp = 0)     //contructor
    :ID(ID), roasttimestamp(roasttimestamp){};
  Roast& operator=(Roast const&);                     //Copy operator
  Roast (Roast const&);                               //Copy contructor
  ~Roast();                                           //destructor
  long const getId() const;                          //ID getter
  long getId();
  long const getTimestamp() const;                   //Timestamp getter
  long getTimestamp();
  Ingredient const& getIngredient(int i) const; //Ingredient getter
  Ingredient& getIngredient(int i);
  int const getIngredientsCount() const;  //IngredientCount getter
  int getIngredientsCount();
  Event const& getEvent(int i) const;           //Event getter
  Event& getEvent(int i);
  int const getEventCount() const;                   //EventCount getter
  int getEventCount();
  void addIngredient(Ingredient const& ingre);  //add Ingredient              
  void removeIngredientByBeanName(std::string const& beanName);  //remove Ingredient By Bean Name
  void addEvent(Event const& eve);                 //add Event
  void removeEventByTimestamp(long const& oldTimestamp);  //remove Event By Timestamp
};
