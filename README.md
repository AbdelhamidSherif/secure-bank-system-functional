# Secure Bank Management System with User Authentication

A comprehensive C++ console application featuring complete bank management with multi-level user authentication, role-based permissions, and advanced security features.

## 🏦 Overview

This Secure Bank Management System represents the most advanced version in the banking system series, built using **Functional Programming** principles with enterprise-level security features. The system implements a complete user authentication system with granular permissions, making it suitable for multi-user banking environments.

### 🎯 Programming Paradigm

This version continues the **Functional Programming** approach while introducing advanced security patterns:
- **Function-based architecture** with clear separation of concerns
- **Authentication middleware** functions for security validation
- **Permission-based access control** through functional checks
- **Stateless session management** with current user context
- **Modular security layers** integrated throughout the application

### 🔄 Future Development

An **Object-Oriented Programming (OOP)** version is planned to showcase different architectural approaches:
- **Class-based security model** (User, Admin, Permission classes)
- **Inheritance hierarchies** for different user roles
- **Polymorphic permission handlers** for flexible access control
- **Design patterns** (Factory, Strategy, Observer, Decorator)
- **Enhanced security through encapsulation**

This secure functional version demonstrates how complex security requirements can be implemented using procedural programming before transitioning to object-oriented design.

## 🆕 What's New in This Version

This secure version builds upon the enhanced transaction system with enterprise-level features:

> 📌 **Want to see the evolution?** Check out:
> - [Basic Version](https://github.com/AbdelhamidSherif/bank-management-functional-cpp) - Simple CRUD operations
> - [Enhanced Version](https://github.com/AbdelhamidSherif/enhanced-bank-system-functional) - Added transactions

### ✨ Major Security Additions

#### 🔐 **Complete Authentication System**
- **User Login/Logout**: Secure session management with credential validation
- **Password Protection**: All operations require valid user authentication
- **Session Context**: Current user tracking throughout the application
- **Admin Protection**: Special safeguards for administrative accounts

#### 🛡️ **Role-Based Permission System**
- **Granular Permissions**: 7 distinct permission levels for different operations
- **Flexible Access Control**: Individual permissions can be combined
- **Full Admin Access**: Special -1 permission for complete system access
- **Dynamic Permission Checking**: Real-time validation for each operation

#### 👥 **Complete User Management**
- **User CRUD Operations**: Create, read, update, delete user accounts
- **Permission Assignment**: Custom permission configuration for each user
- **User Profile Management**: Comprehensive user information handling
- **Self-Protection**: Users cannot delete themselves or admin accounts

### 📊 **Evolution Comparison**

| Feature | Basic | Enhanced | Secure (Current) |
|---------|--------|----------|------------------|
| **Authentication** | ❌ None | ❌ None | ✅ Complete Login System |
| **User Management** | ❌ None | ❌ None | ✅ Full User CRUD + Permissions |
| **Security** | ❌ Open Access | ❌ Open Access | ✅ Role-Based Access Control |
| **Menus** | 1 Menu (6 options) | 2 Menus | 3 Menus + Login Screen |
| **Permissions** | ❌ None | ❌ None | ✅ 7 Permission Levels |
| **Session Management** | ❌ None | ❌ None | ✅ Current User Context |
| **Data Files** | 1 File | 1 File | 2 Files (Clients + Users) |

## ✨ Core Features

### 🔐 Authentication & Security
- **Secure Login System**: Username/password authentication with validation
- **Session Management**: Persistent user context throughout application lifecycle
- **Permission Validation**: Every operation checked against user permissions
- **Access Control**: Granular control over system features
- **Admin Protection**: Special safeguards for system administrators

### 👥 Client Management (Permission-Protected)
- **View Clients**: Display all client records (requires List permission)
- **Add Clients**: Create new client accounts (requires Add permission)
- **Update Clients**: Modify existing client information (requires Update permission)
- **Delete Clients**: Remove client records (requires Delete permission)
- **Find Clients**: Search for specific clients (requires Find permission)

### 💰 Transaction Management (Permission-Protected)
- **Deposit Operations**: Add funds with transaction confirmation
- **Withdrawal Operations**: Remove funds with balance validation
- **Balance Reports**: System-wide balance calculations and reporting
- **Transaction Security**: All operations require Transaction permission

### 🏗️ User Administration (Admin-Only)
- **User Management**: Complete CRUD operations for user accounts
- **Permission Assignment**: Flexible permission configuration
- **Role Management**: Custom access level definitions
- **Security Controls**: Prevent unauthorized administrative access

## 🔑 Permission System

### Permission Levels (Binary Flags)
```cpp
enum enMainMenuePermissions {
    eAll = -1,              // Full system access (Admin)
    pListClients = 1,       // View client list
    pAddNewClient = 2,      // Create new clients
    pDeleteClient = 4,      // Delete clients
    pUpdateClients = 8,     // Update client information
    pFindClient = 16,       // Search for clients
    pTransactions = 32,     // Access transaction system
    pManageUsers = 64       // User management (Admin only)
};
```

### Example Permission Combinations
- **Basic Teller**: 1 + 2 + 16 + 32 = 51 (List, Add, Find, Transactions)
- **Senior Teller**: 1 + 2 + 8 + 16 + 32 = 59 (All except Delete + User Management)
- **Manager**: All permissions except User Management = 63
- **Administrator**: -1 (Complete system access)

## 📋 Usage

### Initial Login
```
-----------------------------------
    Login Screen
-----------------------------------
Enter UserName? Admin
Enter Password? password
```

### Main Menu (Post-Authentication)
1. **Show Client List** (Permission: pListClients)
2. **Add New Client** (Permission: pAddNewClient)
3. **Delete Client** (Permission: pDeleteClient)
4. **Update Client Info** (Permission: pUpdateClients)
5. **Find Client** (Permission: pFindClient)
6. **Transactions** (Permission: pTransactions)
7. **Manage Users** (Permission: pManageUsers)
8. **Logout** (End session)

### User Management Menu (Admin Only)
1. **List Users** - View all system users
2. **Add New User** - Create new user accounts with custom permissions
3. **Delete User** - Remove user accounts (with protection)
4. **Update User** - Modify user permissions and details
5. **Find User** - Search for specific users
6. **Main Menu** - Return to main system

### Creating a New User
```
Enter Username? john_doe
Enter Password? secure123

Do you want to give full access? Y/N? N

Do you want to give access to :

Show Client List? y/n? y
Add New Client? y/n? y
Delete Client? y/n? n
Update Client? y/n? y
Find Client? y/n? y
Transactions? y/n? y
Manage Users? y/n? n

User Added Successfully!
```

## 🗂️ Data Structure

### Client Structure (Inherited)
```cpp
struct sClient {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete;
};
```

### User Structure (New)
```cpp
struct stLoginDetails {
    string UserName;
    string Password;
    int Permissions;              // Binary combination of permission flags
    bool MarkForDelete_User;
};
```

## 🏗️ Code Architecture

### 🔍 **Major Code Additions**

#### **New Security Functions:**
- `IsValidateLogin()` - Credential validation against user database
- `CheckAccessPermission()` - Real-time permission verification
- `ShowAccessDeniedMessage()` - Security violation handling
- `ShowLoginScreen()` - Authentication interface

#### **User Management Functions:**
- `ReadNewUser()` - User creation with permission assignment
- `ReadPermissions()` - Interactive permission configuration
- `ConvertLinetoRecord_UserDetails()` - User data parsing
- `ConvertRecordToLine_UserDetails()` - User data serialization
- `UserExistsByUserName()` - Username uniqueness validation

#### **Enhanced Navigation:**
- `ShowManageUserMenue()` - Complete user management interface
- `PerfromManageMenueOption()` - User management operation dispatcher
- `GoBackToManageMenue()` - User management navigation helper

### 📈 **Lines of Code Growth:**
- **Basic Version**: ~450 lines
- **Enhanced Version**: ~650 lines
- **Secure Version**: ~950+ lines
- **Growth**: ~300+ lines of security features (46% increase)

## 📁 File Structure

```
secure-bank-system-functional/
│
├── main.cpp           # Complete application source
├── Clients.txt        # Client data storage
├── Users.txt          # User accounts and permissions
├── README.md          # This documentation
└── .gitignore         # Git ignore file
```

## 🔒 Security Features

### Authentication
- **Password-based login** with username validation
- **Session management** with current user context
- **Automatic logout** and session termination

### Authorization
- **Role-based access control** with granular permissions
- **Real-time permission checking** for every operation
- **Administrative protection** against unauthorized access
- **Self-protection mechanisms** (users cannot delete themselves)

### Data Protection
- **File-based persistence** for both clients and users
- **Input validation** throughout the system
- **Confirmation prompts** for destructive operations
- **Data integrity** maintenance across all operations

## 🛠️ Future Enhancements

### Security Improvements
- [ ] Password encryption/hashing (currently plain text)
- [ ] Session timeout and automatic logout
- [ ] Audit logging for all operations
- [ ] Password complexity requirements
- [ ] Account lockout after failed attempts
- [ ] Two-factor authentication support

### System Features
- [ ] Database integration (MySQL/SQLite)
- [ ] Transaction history and reporting
- [ ] Data backup and recovery
- [ ] Multi-branch support
- [ ] Customer self-service portal
- [ ] Mobile app integration API

### Technical Improvements
- [ ] GUI version with modern framework
- [ ] Web-based interface
- [ ] RESTful API development
- [ ] Microservices architecture
- [ ] Cloud deployment support

## 🔗 Related Projects

This project completes the banking system series demonstrating programming paradigm evolution:

### 📂 **Project Evolution Timeline:**
1. **[Basic Bank Management](https://github.com/AbdelhamidSherif/bank-management-functional-cpp)** - Functional programming with CRUD operations
2. **[Enhanced Bank System](https://github.com/AbdelhamidSherif/enhanced-bank-system-functional)** - Added complete transaction management
3. **Current Project** - Enterprise security with user authentication and permissions
4. **Coming Soon** - Object-Oriented Programming (OOP) version for architectural comparison

### 🔄 **Quick Navigation:**
- 🏃‍♂️ **[Go to Basic Version →](https://github.com/AbdelhamidSherif/bank-management-functional-cpp)** - Learn the fundamentals
- 🔄 **[View Enhanced Version →](https://github.com/AbdelhamidSherif/enhanced-bank-system-functional)** - See transaction features
- 🚀 **[View OOP Version →](https://github.com/AbdelhamidSherif/bank-system-oop-cpp)** - Coming soon with class-based design
- 📚 **[See All Banking Projects →](https://github.com/AbdelhamidSherif?tab=repositories&q=bank&type=&language=)** - Complete collection

## 🤝 Contributing

Contributions are welcome! This project demonstrates enterprise-level functional programming concepts and security implementation.

### Steps to Contribute

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/EnhancedSecurity`)
3. Commit your changes (`git commit -m 'Add password encryption'`)
4. Push to the branch (`git push origin feature/EnhancedSecurity`)
5. Open a Pull Request

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👨‍💻 Author

**Abdelhamid Sherif**
- GitHub: [@AbdelhamidSherif](https://github.com/AbdelhamidSherif)
- LinkedIn: [Abdelhamid Sherif](https://linkedin.com/in/abdelhamid-sherif)

## 📞 Support

If you have any questions or need help with the system:
1. Check the existing issues in the repository
2. Create a new issue with a detailed description
3. Contact the maintainer directly

## 🙏 Acknowledgments

- Thanks to all contributors who have helped improve this project
- Inspired by real-world banking systems and enterprise security practices
- Educational demonstration of functional programming with complex security requirements

---

⭐ If you found this project helpful, please give it a star on GitHub!
