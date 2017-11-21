// File: accountstransactions.cpp

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class account {
private:
    string owner;
    float balance;
    float withdrawfee;
   
public:
    account(string name, float fee);
    virtual void write(ostream& out);
    virtual void deposit(float amount); 
    virtual bool withdraw(float amount);
    virtual float getbalance(void);
    float getwithdrawfee(void);
};

class savingsaccount :public account {
private:
    float interestrate;  

public:
    savingsaccount(string name, float fee, float rate);
    void write(ostream& out);
    void addinterest(void);
};

class chequingaccount : public account {
private:
    int remainingfreewithdrawals;  

public:
    chequingaccount(string name, float fee, int numberfree);
    void write(ostream& out);
    bool withdraw(float amount);
};


void processtransactions(account& x);

int main(void)
{
    char type;
    savingsaccount s("joe", 0.50, 0.03);
    chequingaccount c("bob", 0.50, 2);

    cout << "Which account to process? (c or s) :";
    cin >> type;
   
    if(type == 's') processtransactions(s);
    if(type == 'c') processtransactions(c);
   
    return 0;
}

///////////////////// implementation of account ///////////////////////
account::account(string name, float fee)
{
    owner = name;
    balance = 0;
    withdrawfee = fee;
}

void account::write(ostream& out)
{
    out << "owner: " << owner << "\n";
    out << "balance: " << balance << "\n";
    out << "withdrawfee " << withdrawfee << "\n"; 
}

void account::deposit(float amount)
{
    balance = balance + amount;
}

bool account::withdraw(float amount)
{
    bool result;
    if (amount > balance-withdrawfee) { 
        cout << "Insufficient funds"; 
        result = false;
    } else { 
        balance = balance - amount - withdrawfee;
        result = true;
    }

    return result;
}

float account::getbalance(void)
{
    return balance;
}

float account::getwithdrawfee(void)
{
    return withdrawfee;
}

///////////////////// implementation of savingsaccount ///////////////////////

savingsaccount::savingsaccount(string name, float fee, float rate) :account(name, fee)
{
    interestrate = rate;
}

void savingsaccount::write(ostream &out)
{
    account::write(out);
    out << "interest rate: " << interestrate << "\n";
}

void savingsaccount::addinterest(void)
{
    float balance_TMP = account::getbalance();
    float interest = interestrate*balance_TMP;

    account::deposit(interest);
}

///////////////////// implementation of chequingaccount ///////////////////////

chequingaccount::chequingaccount(string name, float fee, int numberfree) :account(name, fee)
{
    remainingfreewithdrawals = numberfree;
}

void chequingaccount::write(ostream &out)
{
    account::write(out);
    out << "remaining free withdrawals: " << remainingfreewithdrawals << "\n";
}

bool chequingaccount::withdraw(float amount)
{
    float fee = account::getwithdrawfee();
    bool result;
    
    result = account::withdraw(amount);

    if(remainingfreewithdrawals > 0 && result){
        account::deposit(fee);
        remainingfreewithdrawals--;
    }

    return result;
}

void processtransactions(account& x)
{
   ifstream fin("transactionsin.txt");
   char type;
   float amount;
   
   while(fin >> type >> amount) {
      if(type == 'w'){
          x.withdraw(amount);
          cout << "withdraw " << amount << "\n";
      }
          
      if(type == 'd') {
         x.deposit(amount);
         cout << "deposit " << amount << "\n";
      }
      
      x.write(cout);
      cout << "\n";
   }
}

