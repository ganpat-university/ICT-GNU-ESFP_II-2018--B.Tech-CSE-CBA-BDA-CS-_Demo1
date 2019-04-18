#include<iostream>
#include<fstream>
using namespace std;

class vendor
{
  private:
    int v_id;
    string v_passwd,v_name;

  public:
    
     void set_passwd(string pass)
         {
           v_passwd=pass;
             //set passwd in file db
         }
    
     void set_name(string name)
         {
           v_name=name;
         }

     void set_id(int id)
          {
            v_id=id;
              //set id into file db
          }
 
  string vend_save_data(string file_name)
         {
           string path="data-base/vendor/";             //it will make new file
           string full_path=path+file_name+".txt";
           fstream file;                                    //for usr
           file.open(full_path,ios::out);
             file<<v_id;
             file<<"\n";                         //with usr number (id)
             file<<v_name;
             file<<"\n";
             file<<v_passwd;
             file<<"\n########################################\n";
           file.close();
           return full_path;
         }


};

class customer
{
  private:
    int c_id;
    string c_passwd,c_name;

  public:
    
     void set_passwd(string pass)
         {
           c_passwd=pass;
         }
 
     void set_name(string name)
         {
           c_name=name;
         }

     void set_id(int id)
          {
            c_id=id;
          }
     
   string cost_save_data(string file_name)
         {
           string path="data-base/customer/";             //it will make new file
           string full_path=path+file_name+".txt";
           fstream file;                                    //for usr
           file.open(full_path,ios::out);                  //with usr number (id)
             file<<c_id;
             file<<"\n";
             file<<c_name;
             file<<"\n";
             file<<c_passwd;
             file<<"\n########################################\n";
           file.close();
           return full_path;
         }  
};


   int costumer_number()
    { 
     int p_number,next_number;
     fstream file;
     file.open("data-base/customer/COST-NUM.txt",ios::in);
     file>>p_number;
     file.close();

     file.open("data-base/customer/COST-NUM.txt",ios::out);
     next_number = p_number+1;
     file<<next_number;
     file.close(); 
     return p_number;    
    }

  int vendor_number()
    { 
     int p_number,next_number;
     fstream file;
     file.open("data-base/vendor/VEND-NUM.txt",ios::in);
     file>>p_number;
     file.close();

     file.open("data-base/vendor/VEND-NUM.txt",ios::out);
     next_number = p_number+1;
     file<<next_number;
     file.close(); 
     return p_number;    
    }


  
int login(int id,string name,string passwd)
    {
      int i=0,r;
      string passwd_from_file,path;
      cout<<"\nVerifying data........done!";

      if(id>300)
       {
       path="data-base/vendor/"+name+".txt";
       }
        if(id<300)
         {
         path="data-base/customer/"+name+".txt";
         }

        fstream file;
        file.open(path,ios::in);
        if(!file)
         {
         cout<<"\nNo match !!! 	Who r u?\n";
         }
        else     
         { 
           do{
             file>>passwd_from_file;
             i++;
             }while(i!=3);
       
           if(passwd_from_file!=passwd)
             {
             cout<<"\nWrong password";
             r=0;
             }
           else
             {
             cout<<"\nlogin successfull";
             r=1;
             }     
        }

      return r;
   }

   
 //encription
 string encrpt(string pass,int id)
  {
      int key[3],i,final_key;
      int lenth=pass.size()+1;
             key[2]=id/100;                                //convert id into encrpr key();
             key[1]=(id%100)/10;
             key[0]=id%10;
             final_key=key[0]+key[1]+key[2];
             final_key=final_key%5;

       if(final_key==0)
         {final_key=2;}
               
      for(i=0;i<lenth;i++)
        {
        pass[i]=pass[i]+final_key;
        }
      cout<<"\nEncripting password........done!";
      return pass;
  }


void product(string mode,string name)
 {
  string path,product_name;
  int price;
  path="data-base/vendor/"+name+".txt";
 
  if(mode=="ADD")
   { 
   cout<<"\nENTER PRODUCT NAME : ";
   cin>>product_name;
   cout<<"SET PRICE : ";
   cin>>price;
 
   fstream file;
   file.open(path,ios::app);
   file<<"=>>";
   file.width(15);
   file<<left<<product_name;
   file<<"  ::  ";
   file<<price;
   file<<"\n";
   file.close();
   }

 if(mode=="READ")
   {
   int i=0;
   string line;
   fstream file;
   file.open(path,ios::in);
   while(getline(file,line))
    {
    i++;
    if(i>3)
     {
     cout<<line<<endl;
     }
    }

   }
 }

     

 void vendor_list(string mode,string name,int id)
  { 
    string path="data-base/vendor/list.txt",line;
   
    if(mode=="ADD")
     {
      fstream file;
      file.open(path,ios::app);
      file<<"=> ";
      file.width(12);
      file.fill(' ');
      file<<left<<name;
      file.width(5);
      file.fill(' ');
      file<<" :: ";
      file<<id;
      file<<"\n";
      file.close();
      cout<<"\nSaving data into list........done!";
     }

    if(mode=="read")
     {
     fstream file;
     file.open(path,ios::in);
     while(getline(file,line))
          {cout<<line<<endl;}
     }
   

 }      


int main()
{
 
  int mode,mode2,mode4,id,replayforcust,replayforvend,temp_number,cus_id,vend_id;
  char mode3;
  string name,passwd,passwd_temp,encrpt_passwd,path,decrpt_passwd;
  customer cust[200];
  vendor vend[200];
  
  menu:
  cout<<"[1] Login as vendor\n";
  cout<<"[2] Login as customer\n";
  cout<<"[3] Creat new account\n";
  cout<<"SELECT ONE OF THEM\n";
  cout<<">>";
  cin>>mode;

               switch(mode)
               {
                case 1:
                    
                    cout<<"Enter username >>";
                    cin>>name;
                    cout<<"Enter userid >>";
                    cin>>id;
                    cout<<"Enter password >>";
                    cin>>passwd;
                    encrpt_passwd = encrpt(passwd,id);
                    replayforvend=login(id,name,encrpt_passwd);
          
                break;
                case 2: 

                    cout<<"Enter username >>";
                    cin>>name;
                    cout<<"Enter userid >>";
                    cin>>id;
                    cout<<"Enter password >>";
                    cin>>passwd;
                    encrpt_passwd = encrpt(passwd,id);
                    replayforcust=login(id,name,encrpt_passwd);
          
                break;
                case 3: 

                    cout<<"[1] Creat account as customer\n";
                    cout<<"[2] Creat account as vendor\n";
                    cout<<"SELECT ONE OF THEM\n";
                    cout<<">>";
                    cin>>mode2;
  
                     cout<<"Enter name : ";                            //   _                                   
                     cin>>name; cout<<"\n";                          //  _/ 1x+2y   
                     pass_pbrl:                                     //
                     cout<<"Enter password : ";                                
                     cin>>passwd; cout<<"\n";                                
                     cout<<"confirm password: ";
                     cin>>passwd_temp;
                     cout<<"\n";
                     
                           if(passwd_temp != passwd)
                           {
                            cout<<"password does not match!!!\n";
                            goto pass_pbrl;
                           }

                      if(mode2==1)
                      {
                       temp_number=costumer_number();                                                                  
                       cus_id=temp_number+100;           //for 3 digit id for customer
                       cust[temp_number].set_id(cus_id);
                       cust[temp_number].set_name(name);
                       encrpt_passwd= encrpt(passwd_temp,cus_id);
                       cust[temp_number].set_passwd(encrpt_passwd);
                       cout<<"\nYOUR ID : "<<cus_id;
                       cout<<"\nYOUR NUMBER : "<<temp_number<<"\n";
                       cust[temp_number].cost_save_data(name);
                       cout<<"auto-logout";
                       goto menu;
                      }

                     if(mode2==2)
                      {
                       temp_number=vendor_number();                                                                  
                       vend_id=temp_number+300;           //for 3 digit id for vender
                       vend[temp_number].set_id(vend_id);
                       vend[temp_number].set_name(name);
                       encrpt_passwd= encrpt(passwd_temp,vend_id);
                       vend[temp_number].set_passwd(encrpt_passwd);
                       cout<<"\nYOUR ID : "<<vend_id;
                       cout<<"\nYOUR NUMBER : "<<temp_number<<"\n";
                       vend[temp_number].vend_save_data(name);
                       vendor_list("ADD",name,vend_id);
                       cout<<"ato-logout\n";
                       goto menu;
                      }

                        
                 break;

                 default:     
                     cout<<"Wrong input\n";
                     goto menu;                                                       
                
               }
     
    if(replayforcust==1)
    {
      path="data-base/customer/"+name+".txt";
      fstream file;
      file.open(path,ios::in);
      file>>cus_id;
                   
      cout<<"\nUsername:"<<name<<"   "<<"Id:"<<cus_id<<"\n\n";   
      menu4:   
      cout<<"[1] Do you want to see vendors list? [Y/N]";
      cin>>mode3;
      if(mode3=='Y'|| mode3=='y')
       {
       vendor_list("read",name,cus_id);
       cout<<"\nSELECT VENDOR NAME : ";
       cin>>name;
       product("READ",name);
       cout<<"########################################\n";
       goto menu4;
       }
       else//(mode3!='Y' || mode3!='y')
       {
       cout<<"No problem ! see u again.../\n";
       goto menu;
       }
 	
    }
   
    if(replayforvend==1)
     {
      path="data-base/vendor/"+name+".txt";
      fstream file;
      file.open(path,ios::in);
      file>>vend_id;
                    
      cout<<"\n\nusername:"<<name<<"   "<<"id:"<<vend_id<<"\n\n"; 
      menu2:
      cout<<"[1] List product\n";
      cout<<"[2] Add product\n";
      cout<<"[3] Logout\n";
      cout<<"SELECT ONE OF THEM\n";
      cout<<">>";
      cin>>mode4;
       if(mode4==1)
        {
         product("READ",name);
         cout<<"########################################\n\n";
         goto menu2;
        }
       if(mode4==2)
        { 
         product("ADD",name);
         cout<<"########################################\n\n";
         goto menu2;
        }
       if(mode4==3)
        {
         goto menu;
        }
       if(mode4!=1 && mode4!=2)
        {
        cout<<"Invalid input\n";
        goto menu2;
        }     
     }

}
