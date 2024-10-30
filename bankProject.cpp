#include <iostream>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <vector>
#include <iomanip>
using namespace std;

struct stClient
{
    string accNum;
    string pin;
    string name;
    int phone;
    int balance;
};
struct stUser
{
    string username;
    string password;
    short permissions = 0;
};

// Global Variables
stUser ACTIVE_USER;
const int SHOW_CLIENT_LIST = 0b1;
const int ADD_NEW_CLIENT = 0b10;
const int DELETE_CLIENT = 0b100;
const int UPDATE_CLIENT = 0b1000;
const int FIND_CLIENT = 0b10000;
const int TRANSACTIONS = 0b100000;
const int MANAGE_USERS = 0b1000000;

void mainMenu(vector<stClient> &vClients);
void manageUsersMenu(vector<stUser> &vUsers);
void transactionsMenu(vector<stClient> &vClients);
void updateVectorClient(vector<stClient> &vClients);
void loginScreen(vector<stUser> &vUsers, stUser &activeUser);

void printClient(vector<stClient> &vClient, string accNum)
{
    for (stClient i : vClient)
    {
        if (i.accNum == accNum)
        {
            char choice;
            printf("the following are the client details:\n");
            printf("----------------------------------------\n");
            cout << "Account Number: " << i.accNum << '\n';
            cout << "Pin Code: " << i.pin << '\n';
            cout << "Name: " << i.name << '\n';
            printf("Phone: %i\n", i.phone);
            printf("Balance: %i\n", i.balance);
            printf("----------------------------------------\n");
        }
    }
}
void printUser(vector<stUser> &vUsers, string username)
{
    for (stUser i : vUsers)
    {
        if (i.username == username)
        {
            char choice;
            printf("the following are the user details:\n");
            printf("----------------------------------------\n");
            cout << "Username: " << i.username << '\n';
            cout << "Password: " << i.password << '\n';
            cout << "Permissions: " << i.permissions << '\n';
            printf("----------------------------------------\n");
        }
    }
}
void updateVectorUsers(vector<stUser> &vUsers)
{
    fstream Users;
    Users.open("Users.txt", ios::out);
    if (Users.is_open())
    {
        for (stUser user : vUsers)
        {
            Users << user.username << '\\';
            Users << user.password << '\\';
            Users << user.permissions << '\\';
            Users << '\n';
        }
    }
}
void updateVectorClient(vector<stClient> &vClients)
{
    fstream Clients;
    Clients.open("Clients.txt", ios::out);
    if (Clients.is_open())
    {
        for (stClient client : vClients)
        {
            Clients << client.accNum << '\\';
            Clients << client.pin << '\\';
            Clients << client.name << '\\';
            Clients << client.phone << '\\';
            Clients << client.balance << '\\';
            Clients << '\n';
        }
    }
}
void transactionDeposit(vector<stClient> &vClients)
{
    system("CLS");
    string accNum;
    printf("----------------------------------------\n");
    printf("              Deposit Screen            \n");
    printf("----------------------------------------\n");
    printf("\nDeposit to a client...\n");
    cout << "\n\nEnter Client Account Number : ";
    cin >> accNum;
    accNum = "A" + accNum;
    bool found = false;
    auto iter = std::find_if(vClients.begin(), vClients.end(), [&](stClient const &vClient)
                             { return vClient.accNum == accNum; });
    if (iter != vClients.end())
    {
        found = true;
        char yn;
        int amount = 0;
        printClient(vClients, accNum);
        cout << "\nDeposit amount: ";
        cin >> amount;
        cout << "\n\nsure to deposit " << amount << " to " << iter->name << "? y/n: ";
        cin >> yn;
        if (yn == 'y')
        {
            iter->balance += amount;
            cout << "\n\ndeposited " << amount << " Succesfully!!!\n\n\n";
            updateVectorClient(vClients);
        }
    }
    else
    {
        cout << "\n\nclient not found\n";
    }
    cout << "\n\nPress any key to go back to transactions menu...";
    system("pause>nul");
    transactionsMenu(vClients);
}
void transactionWithdraw(vector<stClient> &vClients)
{
    system("CLS");
    string accNum;
    printf("----------------------------------------\n");
    printf("              Withdraw Screen            \n");
    printf("----------------------------------------\n");
    printf("\nWithdraw from a client...\n");
    cout << "\n\nEnter Client Account Number : ";
    cin >> accNum;
    accNum = "A" + accNum;
    bool found = false;
    auto iter = std::find_if(vClients.begin(), vClients.end(), [&](stClient const &vClient)
                             { return vClient.accNum == accNum; });
    if (iter != vClients.end())
    {
        found = true;
        char yn;
        int amount = 0;
        printClient(vClients, accNum);
        cout << "\nWithdraw amount: ";
        cin >> amount;
        cout << "\n\nsure to withdraw " << amount << " from " << iter->name << "? y/n: ";
        cin >> yn;
        if (yn == 'y')
        {
            iter->balance -= amount;
            cout << "\n\nwithdrew " << amount << " Succesfully!!!\n\n\n";
            updateVectorClient(vClients);
        }
        cout << "\n\nPress any key to go back to transactions menu...";
        system("pause>nul");
        transactionsMenu(vClients);
    }
    else
    {
        cout << "\n\nclient not found\n";
        cout << "\n\nPress any key to go back to transactions menu...";
        system("pause>nul");
        transactionsMenu(vClients);
    }
}
void transactionBalances(vector<stClient> &vClients)
{
    system("CLS");
    printf("                            Client List (%d) Client(s)                                  \n", vClients.size());
    printf("----------------------------------------------------------------------------------\n");
    printf("| Account Number  | Client Name               | Balance\n");
    for (stClient i : vClients)
    {
        cout << "| " << left << setw(16) << i.accNum << "| " << left << setw(26) << i.name << "| " << setw(13) << i.balance << endl;
    }
    printf("----------------------------------------------------------------------------------\n\n");
    cout << "Press any key to go back to transaction menu...";
    system("pause>nul");
    transactionsMenu(vClients);
}
void findClient(vector<stClient> &vClient)
{
    system("CLS");
    if ((ACTIVE_USER.permissions & FIND_CLIENT) == FIND_CLIENT)
    {
        string accNum;
        printf("----------------------------------------\n");
        printf("               Find Client            \n");
        printf("----------------------------------------\n");
        printf("\nFinding a client...\n");
        cout << "\nEnter Client Number to Find: ";
        cin >> accNum;
        accNum = "A" + accNum;
        bool found = false;
        for (stClient i : vClient)
        {
            if (i.accNum == accNum)
            {
                found = true;
                printClient(vClient, accNum);
            }
        }
        if (!found)
        {
            cout << "\nClient not found!!!\n\n";
        }
    }
    else
    {
        cout << "--------------------------------------------\n";
        cout << "Access Denied...\n";
        cout << "Please Contact Your Admin...\n";
        cout << "Wa Khalas.\n";
        cout << "--------------------------------------------\n";
    }

    system("pause");
}
void findUser(vector<stUser> &vUsers)
{
    system("CLS");
    string username;
    printf("----------------------------------------\n");
    printf("                 Find User              \n");
    printf("----------------------------------------\n");
    printf("\nFinding a user...\n");
    cout << "\nEnter Username to Find: ";
    cin >> username;
    bool found = false;
    for (stUser i : vUsers)
    {
        if (i.username == username)
        {
            found = true;
            printUser(vUsers, username);
        }
    }
    if (!found)
    {
        cout << "\nUser not found!!!\n\n";
    }
    system("pause");
    manageUsersMenu(vUsers);
}

void updateClient(vector<stClient> &vClient)
{
    system("CLS");
    if ((ACTIVE_USER.permissions & UPDATE_CLIENT) == UPDATE_CLIENT)
    {
        string accNum;
        printf("----------------------------------------\n");
        printf("              Update Client            \n");
        printf("----------------------------------------\n");
        printf("\nUpdating a client...\n");
        cout << "\n\nEnter Client Account Number : ";
        cin >> accNum;
        accNum = "A" + accNum;
        cout << endl;
        bool found = false;
        auto iter = std::find_if(vClient.begin(), vClient.end(), [&](stClient const &vClient)
                                 { return vClient.accNum == accNum; });
        if (iter != vClient.end())
        {
            string fname;
            string lname;
            found = true;
            cout << "Update PinCode: ";
            cin >> iter->pin;
            cout << "\nUpdate First Name: ";
            cin >> fname;
            cout << "\nUpdate Last Name: ";
            cin >> lname;
            iter->name = fname + " " + lname;
            cout << "\nUpdate Phone: ";
            cin >> iter->phone;
            cout << "\nUpdate Balance: ";
            cin >> iter->balance;
            cout << "\n\nClient Updated Succesfully!!!\n\n\n";
            updateVectorClient(vClient);
        }
        if (!found)
        {
            cout << "\n\nClient not found!!!\n";
        }
    }
    else
    {
        cout << "--------------------------------------------\n";
        cout << "Access Denied...\n";
        cout << "Please Contact Your Admin...\n";
        cout << "Wa Khalas.\n";
        cout << "--------------------------------------------\n";
    }

    system("pause");
}
void updateUser(vector<stUser> &vUsers)
{
    system("CLS");
    string username;
    printf("----------------------------------------\n");
    printf("                Update User             \n");
    printf("----------------------------------------\n");
    printf("\nUpdating a user...\n");
    cout << "\n\nEnter Username: ";
    cin >> username;
    cout << endl;
    bool found = false;
    auto iter = std::find_if(vUsers.begin(), vUsers.end(), [&](stUser const &vUsers)
                             { return vUsers.username == username; });
    if (iter != vUsers.end())
    {
        found = true;
        char fullAccess;
        cout << "\nUpdate Password: ";
        cin >> iter->password;
        cout << "\nUpdate Permissions: \n\n";
        cout << "do you want to give this user full access? [y/n] :";
        cin >> fullAccess;
        if (fullAccess == 'y')
        {
            iter->permissions = -1;
        }
        else
        {
            char choice;
            iter->permissions = 0;
            cout << "do you want to give access to: \n";
            cout << "\n\nshow client list? [y/n]: ";
            cin >> choice;
            if (choice == 'y')
                iter->permissions |= SHOW_CLIENT_LIST;
            cout << "\n\nadd new client? [y/n]: ";
            cin >> choice;
            if (choice == 'y')
                iter->permissions |= ADD_NEW_CLIENT;
            cout << "\n\ndelete client? [y/n]: ";
            cin >> choice;
            if (choice == 'y')
                iter->permissions |= DELETE_CLIENT;
            cout << "\n\nupdate client? [y/n]: ";
            cin >> choice;
            if (choice == 'y')
                iter->permissions |= UPDATE_CLIENT;
            cout << "\n\nfind client? [y/n]: ";
            cin >> choice;
            if (choice == 'y')
                iter->permissions |= FIND_CLIENT;
            cout << "\n\ntransactions? [y/n]: ";
            cin >> choice;
            if (choice == 'y')
                iter->permissions |= TRANSACTIONS;
            cout << "\n\nmanage users? [y/n]: ";
            cin >> choice;
            if (choice == 'y')
                iter->permissions |= MANAGE_USERS;
        }
        cout << "\n\nUser Updated Succesfully!!!\n\n\n";
        updateVectorUsers(vUsers);
    }
    if (!found)
    {
        cout << "\n\nClient not found!!!\n";
    }
    system("pause");
    manageUsersMenu(vUsers);
}
void deleteClient(vector<stClient> &vClient)
{
    system("CLS");
    if ((ACTIVE_USER.permissions & DELETE_CLIENT) == DELETE_CLIENT)
    {
        string accNum;
        char choice;
        printf("----------------------------------------\n");
        printf("             Deleting Client            \n");
        printf("----------------------------------------\n");
        printf("\nDeleting a client...\n");
        cout << "\nPlease enter account number: ";
        cin >> accNum;
        cout << endl;
        cout << endl;
        bool found = false;
        for (stClient i : vClient)
        {
            if (i.accNum == accNum)
            {
                found = true;
                printClient(vClient, accNum);
                printf("\nsure to delete this client? y/n: ");
                cin >> choice;

                if (choice == 'y')
                {

                    int index = 0;
                    for (stClient i : vClient)
                    {
                        if (i.accNum == accNum)
                        {
                            vClient.erase(vClient.begin() + index);
                        }

                        index++;
                    }
                    cout << "\nClient deleted Succesfully!!!\n\n\n";
                    updateVectorClient(vClient);
                    char choose;
                    cout << "wanna delete another client? y/n : ";
                    cin >> choose;
                    if (choose == 'y')
                    {
                        deleteClient(vClient);
                    }
                }
            }
        }
        if (!found)
        {
            cout << "\nClient Not Found!!!\n\n";
        }
    }
    else
    {
        cout << "--------------------------------------------\n";
        cout << "Access Denied...\n";
        cout << "Please Contact Your Admin...\n";
        cout << "Wa Khalas.\n";
        cout << "--------------------------------------------\n";
    }
    system("pause");
    system("CLS");
}
void deleteUser(vector<stUser> &vUsers)
{
    system("CLS");
    string username;
    char choice;
    printf("----------------------------------------\n");
    printf("               Deleting User            \n");
    printf("----------------------------------------\n");
    printf("\nDeleting a user...\n");
    cout << "\nPlease enter username: ";
    cin >> username;
    if (username == "admin")
    {
        cout << "\nYou cannot delete an admin...\n";
        system("pause");
        manageUsersMenu(vUsers);
    };

    cout << endl;
    cout << endl;
    bool found = false;
    for (stUser i : vUsers)
    {
        if (i.username == username)
        {
            found = true;
            printUser(vUsers, username);
            printf("\nsure to delete this user? y/n: ");
            cin >> choice;

            if (choice == 'y')
            {

                int index = 0;
                for (stUser i : vUsers)
                {
                    if (i.username == username)
                    {
                        vUsers.erase(vUsers.begin() + index);
                    }

                    index++;
                }
                cout << "\nUser deleted Succesfully!!!\n\n\n";
                updateVectorUsers(vUsers);
                char choose;
                cout << "wanna delete another user? y/n : ";
                cin >> choose;
                if (choose == 'y')
                {
                    deleteUser(vUsers);
                }
            }
        }
    }
    if (!found)
    {
        cout << "\nUser Not Found!!!\n\n";
    }
    system("pause");
    system("CLS");
    manageUsersMenu(vUsers);
}
void showClientList(vector<stClient> &vClients)
{
    system("CLS");
    if ((ACTIVE_USER.permissions & SHOW_CLIENT_LIST) == SHOW_CLIENT_LIST)
    {
        printf("                            Client List (%d) Client(s)                                  \n", vClients.size());
        printf("----------------------------------------------------------------------------------\n");
        printf("| Account Number  | Pin Code  | Client Name               | Phone        | Balance\n");
        for (stClient i : vClients)
        {
            cout << "| " << left << setw(16) << i.accNum << "| " << left << setw(10) << i.pin << "| " << left << setw(26) << i.name << "| " << setw(13) << i.phone << "| " << i.balance << endl;
        }
        printf("----------------------------------------------------------------------------------\n\n");
        system("pause");
        system("CLS");
    }
    else
    {
        cout << "--------------------------------------------\n";
        cout << "Access Denied...\n";
        cout << "Please Contact Your Admin...\n";
        cout << "Wa Khalas.\n";
        cout << "--------------------------------------------\n";
        system("pause");
        system("CLS");
    }
}
void showUserList(vector<stUser> &vUsers)
{
    system("CLS");
    printf("                            Users List (%d) Users(s)                                  \n", vUsers.size());
    printf("----------------------------------------------------------------------------------\n");
    printf("| Username        | Password  | Permissions               \n");
    for (stUser i : vUsers)
    {
        cout << "| " << left << setw(16) << i.username << "| " << left << setw(10) << i.password << "| " << left << setw(26) << i.permissions << endl;
    }
    printf("----------------------------------------------------------------------------------\n\n");
    system("pause");
    system("CLS");
    manageUsersMenu(vUsers);
}
void addNewClient(vector<stClient> &vClients)
{
    system("CLS");
    if ((ACTIVE_USER.permissions & ADD_NEW_CLIENT) == ADD_NEW_CLIENT)
    {
        string tempFName;
        string tempLName;
        system("CLS");
        stClient stTempClient;
        printf("----------------------------------------\n");
        printf("              Add New Client            \n");
        printf("----------------------------------------\n");
        printf("\nAdding new client...\n");
        cout << "Enter Account Number: ";
        cin >> stTempClient.accNum;
        stTempClient.accNum = "A" + stTempClient.accNum;
        cout << endl;
        cout << "Enter PinCode: ";
        cin >> stTempClient.pin;
        cout << endl;
        cout << "Enter First Name: ";
        cin >> tempFName;
        cout << endl;
        cout << "Enter Last Name: ";
        cin >> tempLName;
        stTempClient.name = tempFName + " " + tempLName;
        cout << endl;
        cout << "Enter Phone: ";
        cin >> stTempClient.phone;
        cout << endl;
        cout << "Enter Balance: ";
        cin >> stTempClient.balance;
        cout << endl;
        vClients.push_back(stTempClient);
        updateVectorClient(vClients);
        char choice;
        cout << "\nClient added succesfully, add another one? y/n : ";
        cin >> choice;
        if (choice == 'y')
        {
            addNewClient(vClients);
        }
        else
            system("CLS");
    }
    else
    {
        cout << "--------------------------------------------\n";
        cout << "Access Denied...\n";
        cout << "Please Contact Your Admin...\n";
        cout << "Wa Khalas.\n";
        cout << "--------------------------------------------\n";
        system("pause");
        system("CLS");
    }
}
void addNewUser(vector<stUser> &vUsers)
{
    string tempUserName;
    system("CLS");
    stUser stTempUser;
    char fullAccess;
    short permissions = 0;
    printf("----------------------------------------\n");
    printf("               Add New User             \n");
    printf("----------------------------------------\n");
    printf("\nAdding new user...\n");
    cout << "Enter Username: ";
    cin >> tempUserName;
    cout << endl;
    bool found;
    do
    {
        found = false;
        for (stUser i : vUsers)
        {
            if (tempUserName == i.username)
            {
                found = true;
                cout << "User Exists...Add Another User\n";
                cout << "Enter Username: ";
                cin >> tempUserName;
                break;
            }
        }
    } while (found);
    stTempUser.username = tempUserName;
    cout << "Enter Password: ";
    cin >> stTempUser.password;
    cout << endl;
    cout << "do you want to give this user full access? [y/n] :";
    cin >> fullAccess;
    if (fullAccess == 'y')
    {
        stTempUser.permissions = -1;
    }
    else
    {
        char choice;
        cout << "do you want to give access to: \n";
        cout << "\n\nshow client list? [y/n]: ";
        cin >> choice;
        if (choice == 'y')
            stTempUser.permissions |= SHOW_CLIENT_LIST;
        cout << "\n\nadd new client? [y/n]: ";
        cin >> choice;
        if (choice == 'y')
            stTempUser.permissions |= ADD_NEW_CLIENT;
        cout << "\n\ndelete client? [y/n]: ";
        cin >> choice;
        if (choice == 'y')
            stTempUser.permissions |= DELETE_CLIENT;
        cout << "\n\nupdate client? [y/n]: ";
        cin >> choice;
        if (choice == 'y')
            stTempUser.permissions |= UPDATE_CLIENT;
        cout << "\n\nfind client? [y/n]: ";
        cin >> choice;
        if (choice == 'y')
            stTempUser.permissions |= FIND_CLIENT;
        cout << "\n\ntransactions? [y/n]: ";
        cin >> choice;
        if (choice == 'y')
            stTempUser.permissions |= TRANSACTIONS;
        cout << "\n\nmanage users? [y/n]: ";
        cin >> choice;
        if (choice == 'y')
            stTempUser.permissions |= MANAGE_USERS;
    }
    vUsers.push_back(stTempUser);
    updateVectorUsers(vUsers);
    char choice;
    cout << "\nClient added succesfully, add another one? y/n : ";
    cin >> choice;
    if (choice == 'y')
    {
        addNewUser(vUsers);
    }
    else
        system("CLS");
    manageUsersMenu(vUsers);
}
void transactionsMenu(vector<stClient> &vClients)
{
    system("CLS");
    if ((ACTIVE_USER.permissions & TRANSACTIONS) == TRANSACTIONS)
    {
        short choice;
        cout << "=======================================\n";
        cout << "            Transaction Menu           \n";
        cout << "=======================================\n";
        cout << "         [1] Deposit.         \n";
        cout << "         [2] Withdraw.           \n";
        cout << "         [3] Total Balances.            \n";
        cout << "         [4] Main Menu.            \n";
        cout << "Choose what do you want to do? [1 to 4]? : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            transactionDeposit(vClients);
            break;
        case 2:
            transactionWithdraw(vClients);
            break;
        case 3:
            transactionBalances(vClients);
            break;
        case 4:
            system("CLS");
            break;
        default:
            transactionsMenu(vClients);
            break;
        }
    }
    else
    {
        cout << "--------------------------------------------\n";
        cout << "Access Denied...\n";
        cout << "Please Contact Your Admin...\n";
        cout << "Wa Khalas.\n";
        cout << "--------------------------------------------\n";
        system("pause");
        system("CLS");
    }
}
void manageUsersMenu(vector<stUser> &vUsers)
{
    system("CLS");
    if ((ACTIVE_USER.permissions & MANAGE_USERS) == MANAGE_USERS)
    {
        short choice;
        cout << "=======================================\n";
        cout << "            Manage Users Menu           \n";
        cout << "=======================================\n";
        cout << "            [1] List Users.         \n";
        cout << "            [2] Add New Users.           \n";
        cout << "            [3] Delete User.            \n";
        cout << "            [4] Update User.            \n";
        cout << "            [5] Find User.            \n";
        cout << "            [6] Main Menu.            \n";
        cout << "Choose what do you want to do? [1 to 6]? : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            showUserList(vUsers);
            break;
        case 2:
            addNewUser(vUsers);
            break;
        case 3:
            deleteUser(vUsers);
            break;
        case 4:
            updateUser(vUsers);
            break;
        case 5:
            findUser(vUsers);
            break;
        case 6:
            break;
        default:
            manageUsersMenu(vUsers);
            break;
        }
    }
    else
    {
        cout << "--------------------------------------------\n";
        cout << "Access Denied...\n";
        cout << "Please Contact Your Admin...\n";
        cout << "Wa Khalas.\n";
        cout << "--------------------------------------------\n";
        system("pause");
        system("CLS");
    }
}
void mainMenu(vector<stClient> &vClients, vector<stUser> &vUsers)
{
    system("CLS");
    short choice;

    cout << "=======================================\n";
    cout << "               Main Menu               \n";
    cout << "=======================================\n";
    cout << "         [1] Show Client List.         \n";
    cout << "         [2] Add New Client.           \n";
    cout << "         [3] Delete Client.            \n";
    cout << "         [4] Update Client.            \n";
    cout << "         [5] Find Client.              \n";
    cout << "         [6] Transactions Menu.                     \n";
    cout << "         [7] Manage Users Menu.                     \n";
    cout << "         [8] Logout.                     \n";
    cout << "\n       Current User: | " << ACTIVE_USER.username << " |\n\n";
    cout << "Choose what do you want to do? [1 to 6]? : ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        showClientList(vClients);
        break;
    case 2:
        addNewClient(vClients);
        break;
    case 3:
        deleteClient(vClients);
        break;
    case 4:
        updateClient(vClients);
        break;
    case 5:
        findClient(vClients);
        break;
    case 6:
        transactionsMenu(vClients);
        break;
    case 7:
        manageUsersMenu(vUsers);
        break;
    case 8:
        loginScreen(vUsers, ACTIVE_USER);
        break;

    default:
        system("CLS");
        mainMenu(vClients, vUsers);
        break;
    }
}

void fillVectorClients(vector<stClient> &vClients)
{
    fstream ClientsFile;
    ClientsFile.open("Clients.txt", ios::in);
    if (ClientsFile.is_open())
    {
        string line;
        while (getline(ClientsFile, line))
        {
            stClient Temp;
            short unwanted_character = 0;
            string tempString;
            for (int i = 0; i < line.length(); i++)
            {
                if (line[i] == '\\' /* separtor */)
                {
                    switch (unwanted_character)
                    {
                    case 0:
                        Temp.accNum = tempString;
                        break;
                    case 1:
                        Temp.pin = tempString;
                        break;
                    case 2:
                        Temp.name = tempString;
                        break;
                    case 3:
                        Temp.phone = stoi(tempString);
                        break;
                    case 4:
                        Temp.balance = stoi(tempString);
                        break;
                    default:
                        break;
                    }
                    tempString = "";
                    unwanted_character++;
                    continue;
                }
                tempString += line[i];
            }
            vClients.push_back(Temp);
        }
    }
}
void fillVectorUsers(vector<stUser> &vUsers)
{
    fstream UsersFile;
    UsersFile.open("Users.txt", ios::in);
    if (UsersFile.is_open())
    {
        string line;
        while (getline(UsersFile, line))
        {
            stUser Temp;
            short unwanted_character = 0;
            string tempString;
            for (int i = 0; i < line.length(); i++)
            {
                if (line[i] == '\\')
                {
                    switch (unwanted_character)
                    {
                    case 0:
                        Temp.username = tempString;
                        break;
                    case 1:
                        Temp.password = tempString;
                        break;
                    case 2:
                        Temp.permissions = stoi(tempString);
                        break;
                    default:
                        break;
                    }
                    tempString = "";
                    unwanted_character++;
                    continue;
                }
                tempString += line[i];
            }
            vUsers.push_back(Temp);
        }
    }
}
void loginScreen(vector<stUser> &vUsers, stUser &activeUser)
{
    activeUser = stUser();
    while (true)
    {
        system("CLS");
        string username;
        string pass;
        stUser Temp;
        bool found = false;
        cout << "=======================================\n";
        cout << "               Login Menu              \n";
        cout << "=======================================\n\n\n";
        cout << "Login Username: ";
        cin >> username;
        for (stUser user : vUsers)
        {
            if (username == user.username)
            {
                Temp = user;
                found = true;
            }
        }
        if (found)
        {
            cout << "Login Password: ";
            cin >> pass;
            if (pass == Temp.password)
            {
                activeUser = Temp;
                break;
            }
            else
            {
                cout << "\nInvalid User...\n\n";
                system("pause");
            }
        }
    }
}
void Program()
{
    vector<stUser> vUsers;
    fillVectorUsers(vUsers);
    loginScreen(vUsers, ACTIVE_USER);
    vector<stClient> vClients;
    fillVectorClients(vClients);
    while (true)
    {
        mainMenu(vClients, vUsers);
    }
}
int main(int argc, char const *argv[])
{
    Program();
    return 0;
}
