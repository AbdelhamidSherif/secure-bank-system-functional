

// Include necessary libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Global Variables
const string ClientsFileName = "Clients.txt";  // Add file paths
const string UsersFileName = "Users.txt";

// Data Structures
struct sClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

struct stLoginDetails {
	string UserName;
	string Password;
	int Permissions;
	bool MarkForDelete_User = false;

};

// Global current user
stLoginDetails CurrentUser;

// Enums
enum enMainMenueOptions {
	eListClients = 1, eAddNewClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5, eTransactions = 6, eManageUsers = 7,
	eLogout = 8
};

enum enMainMenuePermissions {
	eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
	pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64
};

enum enTransactionsMenueOptions {
	eDeposit = 1, Withdraw = 2,
	eTotalBalances = 3, eMainMenue = 4
};

enum enManageMenueOptions {
	eListUsers = 1, eAddNewUser = 2,
	eDeleteUser = 3, eUpdateUser = 4,
	eFindUser = 5, eManageMainMenue = 6
};

// Function declarations
bool CheckAccessPermission(enMainMenuePermissions Permission);
void ShowMainMenue();
void GoBackToMainMenue();
void ShowTransactionsMenue();
void ShowManageUserMenue();
void ShowLoginScreen();
void GoBackToManageMenue();


// Utility Functions
vector<string> SplitString(string S1, string Delim) {
	vector<string> vString;
	short pos = 0;
	string sWord;

	while ((pos = S1.find(Delim)) != std::string::npos) {
		sWord = S1.substr(0, pos);
		if (sWord != "") {
			vString.push_back(sWord);
		}

		S1.erase(0, pos + Delim.length());
	}

	if (S1 != "") {
		vString.push_back(S1);
	}

	return vString;
}

// Client Record Functions
sClient ConvertLinetoRecord(string Line, string Seperator = "#//#") {
	sClient Client;
	vector<string> vClientData;
	vClientData = SplitString(Line, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);
	return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#") {
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}

// File Operations
void AddDataLineToFile(string FileName, string stDataLine) {
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open()) {
		MyFile << stDataLine << endl;
		MyFile.close();
	}
}

vector<sClient> LoadCleintsDataFromFile(string FileName) {
	vector<sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {
		string Line;
		sClient Client;

		while (getline(MyFile, Line)) {
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}

vector<sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients) {
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	string DataLine;

	if (MyFile.is_open()) {
		for (sClient C : vClients) {
			if (C.MarkForDelete == false) {
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}

		MyFile.close();
	}

	return vClients;
}

// Client Operations
bool ClientExistsByAccountNumber(string AccountNumber, string FileName) {
	vector<sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {
		string Line;
		sClient Client;

		while (getline(MyFile, Line)) {
			Client = ConvertLinetoRecord(Line);
			if (Client.AccountNumber == AccountNumber) {
				MyFile.close();
				return true;
			}
			vClients.push_back(Client);
		}

		MyFile.close();
	}
	return false;
}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient& Client) {
	for (sClient C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			Client = C;
			return true;
		}
	}
	return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient>& vClients) {
	for (sClient& C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

// Display Client Information
void PrintClientRecordLine(sClient Client) {
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintClientCard(sClient Client) {
	cout << "\nThe following are the client details:\n";
	cout << "-----------------------------------";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code     : " << Client.PinCode;
	cout << "\nName         : " << Client.Name;
	cout << "\nPhone        : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << "\n-----------------------------------\n";
}

void PrintClientRecordBalanceRecordLine(sClient Client) {
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.AccountBalance;
}

// Client Management
sClient ReadNewClient() {
	sClient Client;
	cout << "Enter Account Number? ";

	// Usage of std::ws will extract allthe whitespace character
	getline(cin >> ws, Client.AccountNumber);

	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName)) {
		cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}

void AddNewClient() {
	sClient Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewClients() {
	char AddMore = 'Y';
	do {
		//system("cls");
		cout << "Adding New Client:\n\n";

		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');
}

sClient ChangeClientRecord(string AccountNumber) {
	sClient Client;

	Client.AccountNumber = AccountNumber;

	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}

string ReadClientAccountNumber() {
	string AccountNumber = "";

	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients) {
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);

			//Refresh Clients 
			vClients = LoadCleintsDataFromFile(ClientsFileName);

			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else {
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients) {
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want update this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			for (sClient& C : vClients) {
				if (C.AccountNumber == AccountNumber) {
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}

			SaveCleintsDataToFile(ClientsFileName, vClients);

			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	else {
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}

// User Management
stLoginDetails ConvertLinetoRecord_UserDetails(string Line, string Seperator = "#//#") {
	stLoginDetails User;
	vector<string> vUserData;
	vUserData = SplitString(Line, Seperator);

	User.UserName = vUserData[0];
	User.Password = vUserData[1];
	User.Permissions = stoi(vUserData[2]);

	return User;
}

string ConvertRecordToLine_UserDetails(stLoginDetails User, string Seperator = "#//#") {
	string stUserRecord = "";
	stUserRecord += User.UserName + Seperator;
	stUserRecord += User.Password + Seperator;
	stUserRecord += to_string(User.Permissions);

	return stUserRecord;
}

bool UserExistsByUserName(string Username, string FileName) {
	vector<stLoginDetails> vUsers;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode

	if (MyFile.is_open()) {
		string Line;
		stLoginDetails User;

		while (getline(MyFile, Line)) {
			User = ConvertLinetoRecord_UserDetails(Line);
			if (User.UserName == Username) {
				MyFile.close();
				return true;
			}
			vUsers.push_back(User);
		}

		MyFile.close();
	}
	return false;
}

vector<stLoginDetails> LoadUsersDataFromFile(string FileName) {
	vector<stLoginDetails> vUsers;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode

	if (MyFile.is_open()) {
		string Line;
		stLoginDetails User;

		while (getline(MyFile, Line)) {
			User = ConvertLinetoRecord_UserDetails(Line);
			vUsers.push_back(User);
		}
		MyFile.close();
	}
	return vUsers;
}

bool FindUserByUsername(string Username, vector<stLoginDetails> vUsers, stLoginDetails& User) {
	for (stLoginDetails U : vUsers) {
		if (U.UserName == Username) {
			User = U;
			return true;
		}
	}
	return false;
}

bool MarkUserForDeleteByUsername(string Username, vector<stLoginDetails>& vUsers) {
	for (stLoginDetails& U : vUsers) {
		if (U.UserName == Username) {
			U.MarkForDelete_User = true;
			return true;
		}
	}
	return false;
}

vector<stLoginDetails> SaveUsersDataToFile(string FileName, vector<stLoginDetails> vUsers) {
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	string DataLine;

	if (MyFile.is_open()) {
		for (stLoginDetails U : vUsers) {
			if (U.MarkForDelete_User == false) {
				DataLine = ConvertRecordToLine_UserDetails(U);
				MyFile << DataLine << endl;
			}
		}

		MyFile.close();
	}

	return vUsers;
}

void PrintUserCard(stLoginDetails User) {
	cout << "\nThe following are the user details:\n";
	cout << "-----------------------------------";
	cout << "\nUsername   : " <<User.UserName;
	cout << "\nPassword   : " << User.Password;
	cout << "\nPermissions: " << User.Permissions;
	cout << "\n-----------------------------------\n";
}

void PrintUserRecordLine(stLoginDetails User)
{
	cout << "| " << setw(15) << left << User.UserName;
	cout << "| " << setw(10) << left << User.Password;
	cout << "| " << setw(40) << left << User.Permissions;
}

int ReadPermissions() {
	int Permissions = 0;
	char Answer = 'n';

	cout << "\nDo you want to give full access? Y/N? ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y') {
		return -1;
	}
	else {
		cout << "\nDo you want to give access to :\n\n";

		cout << "Show Client Liest? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += enMainMenuePermissions::pListClients;

		cout << "\nAdd New Client? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += enMainMenuePermissions::pAddNewClient;

		cout << "\nDelete Client? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += enMainMenuePermissions::pDeleteClient;

		cout << "\nUpdate Client? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += enMainMenuePermissions::pUpdateClients;

		cout << "\nFind Client? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += enMainMenuePermissions::pFindClient;

		cout << "\nTransactions? y/n? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
			Permissions += enMainMenuePermissions::pTranactions;

		cout << "\nManage Users? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
			Permissions += enMainMenuePermissions::pManageUsers;
	}

	return Permissions;
}

stLoginDetails ReadNewUser() {
	stLoginDetails User;
	cout << "Enter Username? ";

	// Usage of std::ws will extract allthe whitespace character
	getline(cin >> ws, User.UserName);

	while (UserExistsByUserName(User.UserName, UsersFileName)) {
		cout << "\nClient with [" << User.UserName << "] already exists, Enter another Username? ";
		getline(cin >> ws, User.UserName);
	}

	cout << "Enter Password? ";
	getline(cin, User.Password);

	User.Permissions = ReadPermissions();

	return User;
}

void AddNewUser() {
	stLoginDetails User;
	User = ReadNewUser();
	AddDataLineToFile(UsersFileName, ConvertRecordToLine_UserDetails(User));
}

void AddNewUsers() {
	char AddMore = 'Y';
	do {
		//system("cls");
		cout << "Adding New User:\n\n";

		AddNewUser();
		cout << "\nUser Added Successfully, do you want to add more Users? Y/N? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');
}

bool DeleteUserByUsername(string Username, vector<stLoginDetails>& vUsers) {
	stLoginDetails User;
	char Answer = 'n';
	
	if (FindUserByUsername(Username, vUsers, User)) {

		if (Username=="Admin"||Username==User.UserName)
		{
			cout << "\nYou cannot Delete This User.\n";
			GoBackToManageMenue();
		}

		PrintUserCard(User);

		cout << "\n\nAre you sure you want delete this user? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			MarkUserForDeleteByUsername(Username, vUsers);
			SaveUsersDataToFile(UsersFileName, vUsers);

			//Refresh Clients 
			vUsers = LoadUsersDataFromFile(UsersFileName);

			cout << "\n\nUser Deleted Successfully.";
			return true;
		}
	}
	else {
		cout << "\nUser with User Name (" << Username << ") is Not Found!";
		return false;
	}
}

stLoginDetails ChangeUserRecord(string Username) {
	stLoginDetails User;

	User.UserName = Username;

	cout << "\n\nEnter Password? ";
	getline(cin >> ws, User.Password);

	User.Permissions = ReadPermissions();
	
	return User;
}

bool UpdateUserByUsername(string Username, vector<stLoginDetails>& vUsers) {
	stLoginDetails User;
	char Answer = 'n';

	if (FindUserByUsername(Username, vUsers, User)) {
		PrintUserCard(User);
		cout << "\n\nAre you sure you want update this user? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			for (stLoginDetails& U : vUsers) {
				if (U.UserName == Username) {
					U = ChangeUserRecord(Username);
					break;
				}
			}

			SaveUsersDataToFile(UsersFileName, vUsers);

			cout << "\n\nUser Updated Successfully.";
			return true;
		}
	}
	else {
		cout << "\nUser with User Name (" << Username << ") is Not Found!";
		return false;
	}
}

// Authentication
string ReadUserName() {
	string UserName;
	cout << "Enter UserName? ";
	cin >> UserName;

	return UserName;
}

string ReadPassword() {
	string Password;
	cout << "Enter Password? ";
	cin >> Password;

	return Password;
}

stLoginDetails ReadLoginDetails() {
	stLoginDetails LoginDetails;

	LoginDetails.UserName = ReadUserName();
	LoginDetails.Password = ReadPassword();

	return LoginDetails;
}

bool IsValidateLogin(stLoginDetails LoginDetails, const vector<stLoginDetails>& vUserDetails) {
	for (const stLoginDetails& User : vUserDetails) {
		if (LoginDetails.UserName == User.UserName && LoginDetails.Password == User.Password) {
			CurrentUser = User;
			return true;
		}
	}

	return false;
}

// Permissions
bool CheckAccessPermission(enMainMenuePermissions Permission) {
	if (CurrentUser.Permissions == enMainMenuePermissions::eAll)
		return true;

	if ((Permission & CurrentUser.Permissions) == Permission)
		return true;
	else
		return false;
}

void ShowAccessDeniedMessage() {
	cout << "\n------------------------------------\n";
	cout << "Access Denied, \nYou dont Have Permission To Do this,\nPlease Conact Your Admin.";
	cout << "\n------------------------------------\n";
}

// Transaction Operations
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient>& vClients) {
	char Answer = 'n';

	cout << "\n\nAre you sure you want to perform this transaction? y/n ? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y') {
		for (sClient& C : vClients) {
			if (C.AccountNumber == AccountNumber) {
				C.AccountBalance += Amount;
				SaveCleintsDataToFile(ClientsFileName, vClients);
				cout << "\n\Doen Successfully, New balance is: " << C.AccountBalance;

				return true;
			}
		}

		return false;
	}
}

void ShowTotalBalance() {
	vector<sClient>vClients = LoadCleintsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\Balances List (" << vClients.size() << ") Client(s).";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	double TotalBalance = 0.0;

	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else

		for (sClient Client : vClients) {
			PrintClientRecordBalanceRecordLine(Client);
			TotalBalance += Client.AccountBalance;
			cout << endl;
		}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\n\t\t\t\t\t\tTotal Balances = " << TotalBalance << endl;
}

// Screen Functions
void ShowAllClientsScreen() {
	if (!CheckAccessPermission(enMainMenuePermissions::pListClients)) {
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
	}

	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else

		for (sClient Client : vClients) {
			PrintClientRecordLine(Client);
			cout << endl;
		}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void ShowAddNewClientsScreen() {
	if (!CheckAccessPermission(enMainMenuePermissions::pAddNewClient)) {
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
	}

	cout << "\n-----------------------------------\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n-----------------------------------\n";

	AddNewClients();
}

void ShowDeleteClientScreen() {
	if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient)) {
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
	}

	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------\n";

	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen() {
	if (!CheckAccessPermission(enMainMenuePermissions::pUpdateClients)) {
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
	}

	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Client Info Screen";
	cout << "\n-----------------------------------\n";

	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowFindClientScreen() {
	if (!CheckAccessPermission(enMainMenuePermissions::pFindClient)) {
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
	}

	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------\n";

	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	sClient Client;
	string AccountNumber = ReadClientAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
		PrintClientCard(Client);
	else
		cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

void ShowDepositScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tDeposit Screen";
	cout << "\n-----------------------------------\n";

	sClient Client;
	vector<sClient>vClients = LoadCleintsDataFromFile(ClientsFileName);

	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);

	double Amount = 0;

	cout << "\nPlease enter deposit amount? ";
	cin >> Amount;

	DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}

void ShowWithDrawScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tWithdraw Screen";
	cout << "\n-----------------------------------\n";

	sClient Client;
	vector<sClient>vClients = LoadCleintsDataFromFile(ClientsFileName);

	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);

	double Amount = 0;
	cout << "\nPlease enter withdraw amount? ";
	cin >> Amount;

	while (Amount > Client.AccountBalance) {
		cout << "Amount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
		cout << "Please enter another amount? ";
		cin >> Amount;
	}

	DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}

void ShowTotalBalancesScreen() {
	ShowTotalBalance();
}

void ShowAllUsersScreen() {
	vector<stLoginDetails> vUsers = LoadUsersDataFromFile(UsersFileName);

	cout << "\n\t\t\t\t\tUser List (" << vUsers.size() << ") User(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(10) << "Password";
	cout << "| " << left << setw(40) << "Permissions";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (stLoginDetails User : vUsers) {
		PrintUserRecordLine(User);
		cout << endl;
	}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void ShowAddNewUserScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tAdd New User Screen";
	cout << "\n-----------------------------------\n\n";

	AddNewUsers();
}

void ShowDeleteUserScreen() {

	cout << "\n-----------------------------------\n";
	cout << "\tDelete Users Screen";
	cout << "\n-----------------------------------\n\n";

	vector<stLoginDetails> vUsers = LoadUsersDataFromFile(UsersFileName);
	string Username = ReadUserName();
	DeleteUserByUsername(Username, vUsers);
}

void ShowUpdateUserScreen() {
	
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate User Info Screen";
	cout << "\n-----------------------------------\n\n";

	vector<stLoginDetails> vUsers = LoadUsersDataFromFile(UsersFileName);
	string Username = ReadUserName();
	UpdateUserByUsername(Username, vUsers);
}

void ShowFindUserScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tFind User Screen";
	cout << "\n-----------------------------------\n\n";

	vector<stLoginDetails> vUsers = LoadUsersDataFromFile(UsersFileName);
	stLoginDetails User;
	string Username = ReadUserName();
	if (FindUserByUsername(Username, vUsers, User))
		PrintUserCard(User);
	else
		cout << "\nUser with User Name[" << Username << "] is not found!";
}

void ShowEndScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tProgram Ends :-)";
	cout << "\n-----------------------------------\n";
}

// Menu Navigation Functions
void GoBackToMainMenue() {
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}

void GoBackToTransactionMenue() {
	cout << "\n\nPress any key to go back to Transaction Menue...";
	system("pause>0");
	ShowTransactionsMenue();
}

void GoBackToManageMenue() {
	cout << "\n\nPress any key to go back to Manage Menue...";
	system("pause>0");
	ShowManageUserMenue();
}

// Menu Option Reading
short ReadMainMenueOption() {
	cout << "Choose what do you want to do? [1 to 8]? ";
	short Choice = 0;
	cin >> Choice;

	return Choice;
}

short ReadTransactionsMenueOptions() {
	cout << "Choose what do you want to do? [1 to 4]? ";
	short Choice = 0;
	cin >> Choice;

	return Choice;
}

short ReadManageMenueOption() {
	cout << "Choose what do you want to do? [1 to 6]? ";
	short Choice = 0;
	cin >> Choice;

	return Choice;
}

// Menu System Functions
void PerfromMainMenueOption(enMainMenueOptions MainMenueOption) {
	switch (MainMenueOption) {
	case enMainMenueOptions::eListClients:
	{
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eAddNewClient:
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eTransactions:
		system("cls");
		ShowTransactionsMenue();
		break;

	case enMainMenueOptions::eManageUsers:
		system("cls");
		ShowManageUserMenue();
		break;

	case enMainMenueOptions::eLogout:
		system("cls");
		ShowLoginScreen();
		break;
	}
}

void PerformTransactionsMenueOptions(enTransactionsMenueOptions TransactionsMenueOptions) {
	switch (TransactionsMenueOptions) {
	case enTransactionsMenueOptions::eDeposit:
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionMenue();
		break;

	case enTransactionsMenueOptions::Withdraw:
		system("cls");
		ShowWithDrawScreen();
		GoBackToTransactionMenue();
		break;

	case enTransactionsMenueOptions::eTotalBalances:
		system("cls");
		ShowTotalBalancesScreen();
		GoBackToTransactionMenue();
		break;

	case enTransactionsMenueOptions::eMainMenue:
		//system("cls");
		ShowMainMenue();
		break;
	}
}

void PerfromManageMenueOption(enManageMenueOptions ManageMenueOptions) {
	switch (ManageMenueOptions) {
	case enManageMenueOptions::eListUsers:
	{
		system("cls");
		ShowAllUsersScreen();
		GoBackToManageMenue();
		break;
	}
	case enManageMenueOptions::eAddNewUser:
		system("cls");
		ShowAddNewUserScreen();
		GoBackToManageMenue();
		break;

	case enManageMenueOptions::eDeleteUser:
		system("cls");
		ShowDeleteUserScreen();
		GoBackToManageMenue();
		break;

	case enManageMenueOptions::eUpdateUser:
		system("cls");
		ShowUpdateUserScreen();
		GoBackToManageMenue();
		break;

	case enManageMenueOptions::eFindUser:
		system("cls");
		ShowFindUserScreen();
		GoBackToManageMenue();
		break;

	case enManageMenueOptions::eManageMainMenue:
		system("cls");
		ShowMainMenue();
		break;
	}
}

// Menu Screens
void ShowMainMenue() {
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout.\n";
	cout << "===========================================\n";
	PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

void ShowTransactionsMenue() {
	if (!CheckAccessPermission(enMainMenuePermissions::pTranactions)) {
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
	}

	system("cls");
	cout << "===========================================\n";
	cout << "\t\Transactions Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "===========================================\n";

	PerformTransactionsMenueOptions((enTransactionsMenueOptions)ReadTransactionsMenueOptions());
}

void ShowManageUserMenue() {

	if (!CheckAccessPermission(enMainMenuePermissions::pManageUsers)) {
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
	}
	system("cls");
	cout << "===========================================\n";
	cout << "\t\Manage Users Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menue.\n";
	cout << "===========================================\n";
	PerfromManageMenueOption((enManageMenueOptions)ReadManageMenueOption());
}

void ShowLoginScreen() {
	cout << "\n-----------------------------------\n";
	cout << "\tLogin Screen";
	cout << "\n-----------------------------------\n";

	stLoginDetails LoginDetails = ReadLoginDetails();
	vector<stLoginDetails>vUsers = LoadUsersDataFromFile(UsersFileName);

	while (!IsValidateLogin(LoginDetails, vUsers)) {
		system("cls");
		cout << "\n-----------------------------------\n";
		cout << "\tLogin Screen";
		cout << "\n-----------------------------------\n";
		cout << "Invalid Username/Password!\n";

		LoginDetails = ReadLoginDetails();
	}

	ShowMainMenue();
}


int main()
{

	ShowLoginScreen();
	system("pause>0");

	return 0;
}
