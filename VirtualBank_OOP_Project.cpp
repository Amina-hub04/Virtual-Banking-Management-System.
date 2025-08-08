//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class BankAccount
{
	int accountNumber;
	char holderName[50];
	int balance;
	char accountType;
public:
	void createAccount();	//function to get data from user
	void displayAccount() const;	//function to show data on screen
	void updateAccount();	//function to add new data
	void depositAmount(int);	//function to accept amount and add to balance amount
	void withdrawAmount(int);	//function to accept amount and subtract from balance amount
	void displayReport() const;	//function to show data in tabular format
	int getAccountNumber() const;	//function to return account number
	int getBalance() const;	//function to return balance amount
	char getAccountType() const;	//function to return type of account
};         //class ends here

void BankAccount::createAccount()
{
	cout<<"\nEnter The account Number: ";
	cin>>accountNumber;
	cout<<"\n\nEnter The Name of The account Holder: ";
	cin.ignore();
	cin.getline(holderName,50);
	cout<<"\nEnter Type of The account (C/S): ";
	cin>>accountType;
	accountType=toupper(accountType);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for Current): ";
	cin>>balance;
	cout<<"\n\n\nAccount Created.";
}

void BankAccount::displayAccount() const
{
	cout<<"\nAccount Number: "<<accountNumber;
	cout<<"\nAccount Holder Name: ";
	cout<<holderName;
	cout<<"\nType of Account: "<<accountType;
	cout<<"\nBalance amount: "<<balance;
}


void BankAccount::updateAccount()
{
	cout<<"\nAccount Number: "<<accountNumber;
	cout<<"\nUpdate Account Holder Name: ";
	cin.ignore();
	cin.getline(holderName,50);
	cout<<"\nUpdate Type of Account: ";
	cin>>accountType;
	accountType=toupper(accountType);
	cout<<"\nUpdate Balance amount: ";
	cin>>balance;
}

	
void BankAccount::depositAmount(int x)
{
	balance += x;
}
	
void BankAccount::withdrawAmount(int x)
{
	balance -= x;
}
	
void BankAccount::displayReport() const
{
	cout << accountNumber << setw(10) << " " << holderName << setw(10) << " " << accountType << setw(6) << balance << endl;
}

	
int BankAccount::getAccountNumber() const
{
	return accountNumber;
}

int BankAccount::getBalance() const
{
	return balance;
}

char BankAccount::getAccountType() const
{
	return accountType;
}


//***************************************************************
//    	function declaration
//****************************************************************
void createNewAccount();	//function to write record in binary file
void displaySpecificAccount(int);	//function to display account details given by user
void updateAccountDetails(int);	//function to modify record of file
void removeAccount(int);	//function to delete record of file
void displayAllAccounts();		//function to display all account details
void depositOrWithdraw(int, int); // function to deposit/withdraw amount for given account
void showIntro();	//introductory screen function

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
	char choice;
	int accountNumber;
	showIntro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8): ";
		cin>>choice;
		system("cls");
		switch(choice)
		{
		case '1':
			createNewAccount();
			break;
		case '2':
			cout<<"\n\n\tEnter The account Number: "; cin>>accountNumber;
			depositOrWithdraw(accountNumber, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account Number: "; cin>>accountNumber;
			depositOrWithdraw(accountNumber, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter The account Number: "; cin>>accountNumber;
			displaySpecificAccount(accountNumber);
			break;
		case '5':
			displayAllAccounts();
			break;
		case '6':
			cout<<"\n\n\tEnter The account Number: "; cin>>accountNumber;
			removeAccount(accountNumber);
			break;
		 case '7':
			cout<<"\n\n\tEnter The account Number: "; cin>>accountNumber;
			updateAccountDetails(accountNumber);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using bank management system.";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(choice!='8');
	return 0;
}


//***************************************************************
//    	function to write in file
//****************************************************************

void createNewAccount()
{
	BankAccount ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.createAccount();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(BankAccount));
	outFile.close();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void displaySpecificAccount(int n)
{
	BankAccount ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be opened! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(BankAccount)))
	{
		if(ac.getAccountNumber() == n)
		{
			ac.displayAccount();
			flag = true;
		}
	}
	inFile.close();
	if(!flag)
		cout<<"\n\nAccount number does not exist.";
}


//***************************************************************
//    	function to modify record of file
//****************************************************************

void updateAccountDetails(int n)
{
	bool found = false;
	BankAccount ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be opened! Press any Key...";
		return;
	}
	while(!File.eof() && !found)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(BankAccount));
		if(ac.getAccountNumber() == n)
		{
			ac.displayAccount();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.updateAccount();
			int pos = (-1) * static_cast<int>(sizeof(BankAccount));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(BankAccount));
			cout<<"\n\n\tRecord Updated";
			found = true;
		}
	}
	File.close();
	if(!found)
		cout<<"\n\nRecord Not Found";
}

//***************************************************************
//    	function to delete record of file
//****************************************************************

void removeAccount(int n)
{
	BankAccount ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be opened! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(BankAccount)))
	{
		if(ac.getAccountNumber() != n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(BankAccount));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted.";
}

//***************************************************************
//    	function to display all accounts deposit list
//****************************************************************

void displayAllAccounts()
{
	BankAccount ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be opened! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(BankAccount)))
	{
		ac.displayReport();
	}
	inFile.close();
}

//***************************************************************
//    	function to deposit and withdraw amounts
//****************************************************************

void depositOrWithdraw(int n, int option)
{
	int amount;
	bool found = false;
	BankAccount ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be opened! Press any Key...";
		return;
	}
	while(!File.eof() && !found)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(BankAccount));
		if(ac.getAccountNumber() == n)
		{
			ac.displayAccount();
			if(option == 1)
			{
				cout<<"\n\n\tTO DEPOSIT AMOUNT";
				cout<<"\n\nEnter The amount to be deposited: ";
				cin>>amount;
				ac.depositAmount(amount);
			}
			if(option == 2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT";
				cout<<"\n\nEnter The amount to be withdrawn: ";
				cin>>amount;
				int bal = ac.getBalance() - amount;
				if((bal < 500 && ac.getAccountType() == 'S') || (bal < 1000 && ac.getAccountType() == 'C'))
					cout<<"Insufficient balance";
				else
					ac.withdrawAmount(amount);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(BankAccount));
			cout<<"\n\n\tRecord Updated";
			found = true;
		}
	}
	File.close();
	if(!found)
		cout<<"\n\nRecord Not Found";
}


//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void showIntro()
{
	cout<<"\n\n\n\t  BANK";
	cout<<"\n\n\tMANAGEMENT";
	cout<<"\n\n\t  SYSTEM";
	cout<<"\n\n\n\nMADE BY : Your Name";
	cout<<"\n\nSCHOOL : Your School Name";
	cin.get();
}

