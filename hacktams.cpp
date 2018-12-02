#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <iomanip>
using namespace std;

int main(){
  //Choice for real time or user input time
  string timeOption;
  int weekday;
  int hour;
  int minute;
  char file_name[30];
  int menu;
  cout << "\nThis is a comprehensive list of all open businesses in the town of your choice." << endl << endl;
  do{
    cout << "************* MENU **************" << endl;
    cout << "* 1. Restaurants in Denton      *" << endl;
    cout << "* 2. Stores in Denton           *" << endl;
    cout << "* 3. Restaurants in Plano       *" << endl;
    cout << "* 4. Stores in Plano            *" << endl;
    cout << "* 5. Restaurants in Frisco      *" << endl;
    cout << "* 6. Stores in Frisco           *" << endl;// dont you love the huge database yes ofc i do :)))
    cout << "*********************************" << endl;
    cout << "Enter your choice: ";
    cin >> menu;
  }while(menu < 1 || menu > 6);
    switch(menu)
    {
      case 1:
        strcpy(file_name, "food.txt");
        break;
      case 2:
        strcpy(file_name, "dentonStores.txt");
        break;
      case 3:
        strcpy(file_name, "plano.txt");
        break;
      case 4:
        strcpy(file_name, "planoStores.txt");
        break;
      case 5:
        strcpy(file_name, "frisco.txt");
        break;
      case 6:
        strcpy(file_name, "friscoStores.txt");
        break;
    }
  do{
    cout << "\nEnter 'uwu' to use the current time or enter 'oWo' for a different time: ";
    cin >> timeOption;
    cout << endl;
  }while(timeOption != "uwu" && timeOption != "oWo");

  //current time
  if(timeOption == "uwu"){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    weekday = ltm->tm_wday;
    hour = ltm->tm_hour;
    minute =  ltm->tm_min;
    //cout << "Weekday: " << weekday << " Hour: "<< hour << " Minute: " << minute << endl;
  }
  else
  {
    if(timeOption == "oWo"){
      string ampm;
      time_t now = time(0);
      tm *ltm = localtime(&now);
      weekday = ltm->tm_wday;
      do{
      cout << "Please enter the time you wish to go visit(ex: 9:30 am): ";
      scanf("%d:%d", &hour, &minute);
      cin >> ampm;
        //Converts to military time
      }while(!(hour <= 12 && hour > 0) || (!(minute < 60 && minute >= 0)) || (!(ampm == "am" || ampm == "pm")));

        if((ampm == "pm") && (hour != 12)){
          hour = hour + 12;
        }
        else
        {
          if((hour == 12) && (ampm == "am"))
          {
            hour = 0;
          }
        }

        if(hour <= ltm->tm_hour){
          if(minute < ltm->tm_min){
            if(weekday < 6 && weekday >= 0){
              weekday = weekday + 1;
              //cout << "THE WEEKDAY IS CHANGING YEET\n" << weekday;
            }
            else if(weekday == 6){
              weekday = 0;
              //cout << "THE WEEKDAY IS ALSO CHANGING HERE\n";
            }
          }
        }
     //cout << "hour:" << hour << "minute:" << minute << endl;
      }
  }

  //opening file
  string restaurant;
  float openTime[10];
  float closeTime[10];
  int openHour;
  int closeHour;
  int openMinute;
  int closeMinute;
  ifstream inFS;
  int count = 0;
  inFS.open(file_name);
  if(inFS.fail())
  {
      cout << "Sorry. There was an error opening the file." << endl;
      exit(EXIT_FAILURE);
  }
  while(!inFS.eof())
  {
    //cout << "IM HERE"  << "WEEKDAY: " << weekday << endl;
    char input[20];
    inFS >> input;
    //cout << input << endl;
    restaurant = "";
    if(inFS.eof())
      break;
    while(strcmp(input, "mon") != 0)
    {
      restaurant = restaurant + input + " ";
      inFS >> input;
      //cout << "IM HERE" << endl;
    }
    //cout << restaurant << endl;
    switch(weekday)
    {
      //monday
      case 1:
        {
          int i = 0;
          inFS >> input;
          while(strcmp(input, "tue") != 0)
          {
            openTime[i] = atof(input);
            inFS >> closeTime[i];
            inFS >> input;
            //cout << "INPUT: " << input << endl;
            //cout.setf(ios::fixed);
            //cout.precision(2);
            //cout << restaurant << " " << openTime[i] << " to " <<  closeTime[i] << endl;
            i++;
          }
          while(inFS.get() != '\n')
          {
              if(inFS.eof())
              {
                break;
              }
          }
          for(int j = 0; j < i; j++){
            openHour = static_cast<int>(openTime[j]);
            openMinute = round((openTime[j] - static_cast<int>(openTime[j])) * 100);
            closeHour = static_cast<int>(closeTime[j]);
            closeMinute = round((closeTime[j] - static_cast<int>(closeTime[j])) * 100);
            if(((hour >= openHour) && (hour <= closeHour)))
            {
              if(hour == openHour && minute < openMinute)
              {

              }
              else
              {
                if(hour == closeHour && minute >= closeMinute){

                }
                else
                {
                  bool military = false;
                  if(closeHour > 12){
                    military = true;
                    closeHour -= 12;
                  }
                  cout.fill('0');
                  cout.setf(ios::left);
                  cout.width(2);
                  count++;
                  cout << restaurant  << "IS OPEN!" << endl;
                  if(openHour == 0 && openMinute == 0 && closeHour == 11 && closeMinute == 59)
                  {
                    cout << "\t Open 24 Hours" << endl;
                  }
                  else
                  {
                    cout << "\t Closes at " << closeHour << ":" << setw(2) << closeMinute;
                    if(military == true)
                    {
                      cout << " PM" << endl;
                    }
                    else
                    {
                      cout << " AM" << endl;
                    }
                  }
                  cout << endl;
                }
              }
            }
          }
        }
        break;
      //tuesday
      case 2:
        {
          inFS >> input;
          while(strcmp(input, "tue") != 0)
          {
            inFS >> input;
          }
          inFS >> input;
          int i = 0;
          while(strcmp(input, "wed") != 0)
          {
            openTime[i] = atof(input);
            inFS >> closeTime[i];
            inFS >> input;
            //cout << "INPUT: " << input << endl;
            //cout.setf(ios::fixed);
            //cout.precision(2);
            //cout << restaurant << " " << openTime[i] << " to " <<  closeTime[i] << endl;
            i++;
          }
          while(inFS.get() != '\n')
          {
              if(inFS.eof())
              {
                cout << "END OF FILE" << endl;
                break;
              }
          }
          for(int j = 0; j < i; j++){
            openHour = static_cast<int>(openTime[j]);
            openMinute = round((openTime[j] - static_cast<int>(openTime[j])) * 100);
            closeHour = static_cast<int>(closeTime[j]);
            closeMinute = round((closeTime[j] - static_cast<int>(closeTime[j])) * 100);
            if(((hour >= openHour) && (hour <= closeHour)))
            {
              if(hour == openHour && minute < openMinute)
              {

              }
              else
              {
                if(hour == closeHour && minute >= closeMinute){

                }
                else
                {
                  bool military = false;
                  if(closeHour > 12){
                    military = true;
                    closeHour -= 12;
                  }
                  cout.fill('0');
                  count++;
                  cout.setf(ios::left);
                  cout.width(2);
                  cout << restaurant  << "IS OPEN!" << endl;
                  if(openHour == 0 && openMinute == 0 && closeHour == 11 && closeMinute == 59)
                  {
                    cout << "\t Open 24 Hours" << endl;
                  }
                  else
                  {
                    cout << "\t Closes at " << closeHour << ":" << setw(2) << closeMinute;
                    if(military == true)
                    {
                      cout << " PM" << endl;
                    }
                    else
                    {
                      cout << " AM" << endl;
                    }
                  }
                  cout << endl;
                }
              }
            }
          }
        }
        break;
      //wednesday
      case 3:
        {
          inFS >> input;
          while(strcmp(input, "wed") != 0)
          {
            inFS >> input;
          }
          inFS >> input;
          int i = 0;
          while(strcmp(input, "thu") != 0)
          {
            openTime[i] = atof(input);
            inFS >> closeTime[i];
            inFS >> input;
            //cout << "INPUT: " << input << endl;
            //cout.setf(ios::fixed);
            //cout.precision(2);
            //cout << restaurant << " " << openTime[i] << " to " <<  closeTime[i] << endl;
            i++;
          }
          while(inFS.get() != '\n')
          {
              if(inFS.eof())
              {
                break;
              }
          }
          for(int j = 0; j < i; j++){
            openHour = static_cast<int>(openTime[j]);
            openMinute = round((openTime[j] - static_cast<int>(openTime[j])) * 100);
            closeHour = static_cast<int>(closeTime[j]);
            closeMinute = round((closeTime[j] - static_cast<int>(closeTime[j])) * 100);
            if(((hour >= openHour) && (hour <= closeHour)))
            {
              if(hour == openHour && minute < openMinute)
              {

              }
              else
              {
                if(hour == closeHour && minute >= closeMinute){

                }
                else
                {
                  bool military = false;
                  if(closeHour > 12){
                    military = true;
                    closeHour -= 12;
                  }
                  cout.fill('0');
                  cout.setf(ios::left);
                  cout.width(2);
                  cout << restaurant  << "IS OPEN!" << endl;
                  if(openHour == 0 && openMinute == 0 && closeHour == 11 && closeMinute == 59)
                  {
                    cout << "\t Open 24 Hours" << endl;
                  }
                  else
                  {
                    cout << "\t Closes at " << closeHour << ":" << setw(2) << closeMinute;
                    if(military == true)
                    {
                      cout << " PM" << endl;
                    }
                    else
                    {
                      cout << " AM" << endl;
                    }
                  }
                  cout << endl;
                }
              }
            }
          }
        }
        break;
      //thursday
      case 4:
        {
          inFS >> input;
          while(strcmp(input, "thu") != 0)
          {
            inFS >> input;
          }
          inFS >> input;
          int i = 0;
          while(strcmp(input, "fri") != 0)
          {
            openTime[i] = atof(input);
            inFS >> closeTime[i];
            inFS >> input;
            //cout << "INPUT: " << input << endl;
            //cout.setf(ios::fixed);
            //cout.precision(2);
            //cout << restaurant << " " << openTime[i] << " to " <<  closeTime[i] << endl;
            i++;
          }
          while(inFS.get() != '\n')
          {
              if(inFS.eof())
              {
                break;
              }
          }
          for(int j = 0; j < i; j++){
            openHour = static_cast<int>(openTime[j]);
            openMinute = round((openTime[j] - static_cast<int>(openTime[j])) * 100);
            closeHour = static_cast<int>(closeTime[j]);
            closeMinute = round((closeTime[j] - static_cast<int>(closeTime[j])) * 100);
            if(((hour >= openHour) && (hour <= closeHour)))
            {
              if(hour == openHour && minute < openMinute)
              {

              }
              else
              {
                if(hour == closeHour && minute >= closeMinute){

                }
                else
                {
                  bool military = false;
                  if(closeHour > 12){
                    military = true;
                    closeHour -= 12;
                  }
                  count++;
                  cout.fill('0');
                  cout.setf(ios::left);
                  cout.width(2);
                  cout << restaurant  << "IS OPEN!" << endl;
                  if(openHour == 0 && openMinute == 0 && closeHour == 11 && closeMinute == 59)
                  {
                    cout << "\t Open 24 Hours" << endl;
                  }
                  else
                  {
                    cout << "\t Closes at " << closeHour << ":" << setw(2) << closeMinute;
                    if(military == true)
                    {
                      cout << " PM" << endl;
                    }
                    else
                    {
                      cout << " AM" << endl;
                    }
                  }
                  cout << endl;
                }
              }
            }
          }
        }
        break;
      //friday
      case 5:
        {
          inFS >> input;
          while(strcmp(input, "fri") != 0)
          {
            inFS >> input;
          }
          inFS >> input;
          int i = 0;
          while(strcmp(input, "sat") != 0)
          {
            openTime[i] = atof(input);
            inFS >> closeTime[i];
            inFS >> input;
            //cout << "INPUT: " << input << endl;
            //cout.setf(ios::fixed);
            //cout.precision(2);
            //cout << restaurant << " " << openTime[i] << " to " <<  closeTime[i] << endl;
            i++;
          }
          while(inFS.get() != '\n')
          {
              if(inFS.eof())
              {
                break;
              }
          }
          for(int j = 0; j < i; j++){
            openHour = static_cast<int>(openTime[j]);
            openMinute = round((openTime[j] - static_cast<int>(openTime[j])) * 100);
            closeHour = static_cast<int>(closeTime[j]);
            closeMinute = round((closeTime[j] - static_cast<int>(closeTime[j])) * 100);
            if(((hour >= openHour) && (hour <= closeHour)))
            {
              if(hour == openHour && minute < openMinute)
              {

              }
              else
              {
                if(hour == closeHour && minute >= closeMinute){

                }
                else
                {
                  bool military = false;
                  if(closeHour > 12){
                    military = true;
                    closeHour -= 12;
                  }
                  cout.fill('0');
                  cout.setf(ios::left);
                  cout.width(2);
                  count++;
                  cout << restaurant  << "IS OPEN!" << endl;
                  if(openHour == 0 && openMinute == 0 && closeHour == 11 && closeMinute == 59)
                  {
                    cout << "\t Open 24 Hours" << endl;
                  }
                  else
                  {
                    cout << "\t Closes at " << closeHour << ":" << setw(2) << closeMinute;
                    if(military == true)
                    {
                      cout << " PM" << endl;
                    }
                    else
                    {
                      cout << " AM" << endl;
                    }
                  }
                  cout << endl;
                }
              }
            }
          }
        }
        break;
      //saturday
      case 6:
        {
          int i = 0;
          inFS >> input;
          while(strcmp(input, "sat") != 0)
          {
            inFS >> input;
          }
          inFS >> input;
          while(strcmp(input, "sun") != 0)
          {
            openTime[i] = atof(input);
            inFS >> closeTime[i];
            inFS >> input;
            //cout << "INPUT: " << input << endl;
            //cout.setf(ios::fixed);
            //cout.precision(2);
            //cout << restaurant << " " << openTime[i] << " to " <<  closeTime[i] << endl;
            i++;
          }
          while(inFS.get() != '\n')
          {
              if(inFS.eof())
              {
                break;
              }
          }
          for(int j = 0; j < i; j++){
            openHour = static_cast<int>(openTime[j]);
            openMinute = round((openTime[j] - static_cast<int>(openTime[j])) * 100);
            closeHour = static_cast<int>(closeTime[j]);
            closeMinute = round((closeTime[j] - static_cast<int>(closeTime[j])) * 100);
            //cout << "openHour: " << openHour << " closeHour: " << closeHour << " openMinute: " << openMinute << " closeMinute: " << closeMinute << endl;
            if(((hour >= openHour) && (hour <= closeHour)))
            {
              if(hour == openHour && minute < openMinute)
              {
                    //cout << "IM HERE" << endl;
              }
              else
              {
                if(hour == closeHour && minute >= closeMinute){
                    //cout << "IM HERE" << endl;
                }
                else
                {
                  //cout << "IM HERE" << endl;
                  bool military = false;
                  if(closeHour > 12){
                    military = true;
                    closeHour -= 12;
                  }
                  count++;
                  //cout << "Count: " << count << endl;
                  cout.fill('0');
                  cout.setf(ios::left);
                  cout.width(2);
                  cout << restaurant  << "IS OPEN!" << endl;
                  if(openHour == 0 && openMinute == 0 && closeHour == 11 && closeMinute == 59)
                  {
                    cout << "\t Open 24 Hours" << endl;
                  }
                  else
                  {
                    cout << "\t Closes at " << closeHour << ":" << setw(2) << closeMinute;
                    if(military == true)
                    {
                      cout << " PM" << endl;
                    }
                    else
                    {
                      cout << " AM" << endl;
                    }
                  }
                  cout << endl;
                }
              }
            }
          }
          //cout << "openHour: " << openHour << " closeHour: " << closeHour << " openMinute: " << openMinute << " closeMinute: " << closeMinute << endl;
        }
        break;
      //sunday
      case 0:
      {
        //cout << "HELLO" << endl;
        int i = 0;
        inFS >> input;
        while(strcmp(input, "sun") != 0)
        {
          //cout << "HELLO";
          inFS >> input;
        }
        inFS >> input;
        //cout << input << endl;
        while(strcmp(input, "end") != 0)
        {
          openTime[i] = atof(input);
          inFS >> closeTime[i];
          //cout << closeTime[i];
          inFS >> input;
          //cout << "INPUT: " << input << endl;
          //cout.setf(ios::fixed);
          //cout.precision(2);
          //cout << restaurant << " " << openTime[i] << " to " <<  closeTime[i] << endl;
          i++;
        }
        while(inFS.get() != '\n')
        {
            if(inFS.eof())
            {
              break;
            }
        }
        for(int j = 0; j < i; j++){
          openHour = static_cast<int>(openTime[j]);
          openMinute = round((openTime[j] - static_cast<int>(openTime[j])) * 100);
          closeHour = static_cast<int>(closeTime[j]);
          closeMinute = round((closeTime[j] - static_cast<int>(closeTime[j])) * 100);
          //cout << "openHour: " << openHour << " closeHour: " << closeHour << " openMinute: " << openMinute << " closeMinute: " << closeMinute << endl;
          if(((hour >= openHour) && (hour <= closeHour)))
          {
            if(hour == openHour && minute < openMinute)
            {
                  //cout << "IM HERE" << endl;
            }
            else
            {
              if(hour == closeHour && minute >= closeMinute){
                  //cout << "IM HERE" << endl;
              }
              else
              {
                //cout << "IM HERE" << endl;
                bool military = false;
                if(closeHour > 12){
                  military = true;
                  closeHour -= 12;
                }
                count++;
                //cout << "Count: " << count << endl;
                cout.fill('0');
                cout.setf(ios::left);
                cout.width(2);
                cout << restaurant  << "IS OPEN!" << endl;
                if(openHour == 0 && openMinute == 0 && closeHour == 11 && closeMinute == 59)
                {
                  cout << "\t Open 24 Hours" << endl;
                }
                else
                {
                  cout << "\t Closes at " << closeHour << ":" << setw(2) << closeMinute;
                  if(military == true)
                  {
                    cout << " PM" << endl;
                  }
                  else
                  {
                    cout << " AM" << endl;
                  }
                }
                cout << endl;
              }
            }
          }
        }
        //cout << "openHour: " << openHour << " closeHour: " << closeHour << " openMinute: " << openMinute << " closeMinute: " << closeMinute << endl;
    }
    break;
    }
  }
  if(count == 0)
  {
    cout << endl;
    cout << "Sorry. There is nothing open at this time." << endl;
    //cout << "WEEKDAY: " << weekday << endl;
  }
  inFS.close();
  return 0;
}
