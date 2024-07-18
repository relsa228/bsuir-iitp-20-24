#include "databaseservice.h"
#include <QtSql>
#include <iostream>
#include "obfuscate.h"

DataBaseService::DataBaseService()
{

}
QSqlDatabase DataBaseService::OpenDataBase()
{
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("./BankServiceDB.sqlite");
    if(sdb.open())
    {
        this->CreateShema(sdb);
        return sdb;
    }
    else
        return sdb;
}
void DataBaseService::CreateShema(QSqlDatabase db)
{
    QSqlQuery* query = new QSqlQuery(db);
    query->exec((const char*) AY_OBFUSCATE("CREATE TABLE UserTable(UserId INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT, Surname TEXT, RoleID TEXT, Telephone TEXT, Email TEXT, CompanyName TEXT, "
                             "PassportSer TEXT, PassportNum TEXT, Password TEXT, AproveStatus TEXT)"));
    query->exec((const char*) AY_OBFUSCATE("CREATE TABLE BankTable(BIK INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT, Budget INT)"));
    query->exec((const char*) AY_OBFUSCATE("CREATE TABLE CompanyTable(Name TEXT, Type TEXT, UNP TEXT, BankBIK TEXT, Adress TEXT)"));
    query->exec((const char*) AY_OBFUSCATE("CREATE TABLE AccTable(AccName TEXT, UserName TEXT, BankName TEXT, AccId INTEGER PRIMARY KEY AUTOINCREMENT, Money INT, Type TEXT)"));
    query->exec((const char*) AY_OBFUSCATE("CREATE TABLE CreditTable(CreditId INTEGER PRIMARY KEY AUTOINCREMENT, BankName TEXT, UserName TEXT, Money INT, AccIndex INT, Term INT, Procent INT, AproveStatus TEXT)"));
    query->exec((const char*) AY_OBFUSCATE("CREATE TABLE SalaryTable(ProjectId INTEGER PRIMARY KEY AUTOINCREMENT, BankIndex INT, PrevBankIndex INT, CompanyName TEXT, UserName TEXT, AproveBySpec TEXT, AproveBySystem TEXT, AproveStatus TEXT)"));
    query->exec((const char*) AY_OBFUSCATE("CREATE TABLE TransferTable(TransferId INTEGER PRIMARY KEY AUTOINCREMENT, InitName TEXT, SenderId INT, TargetId INT, Sum INT, Aprove TEXT)"));
    query->exec((const char*) AY_OBFUSCATE("CREATE TABLE CreditPlans(BankName TEXT, Procent INT, Term INT)"));
}

User* DataBaseService::Login(QString email, QString password)
{
    QString encrPassword = QCryptographicHash::hash(password.toLatin1(),QCryptographicHash::Md5).toHex();
    User* user = new User();
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);
    QString sqlInquiry = (const char*) AY_OBFUSCATE("SELECT * FROM UserTable WHERE Email = '");
    sqlInquiry.append(email);
    sqlInquiry.append((const char*) AY_OBFUSCATE("' AND Password = '"));
    sqlInquiry.append(encrPassword);
    sqlInquiry.append((const char*) AY_OBFUSCATE("'"));
    query->exec(sqlInquiry);
    query->next();
    QString checkPassword = query->value(9).toString();
    QString checkAproveStatus = query->value(10).toString();
    if(encrPassword != checkPassword || checkPassword == "")
        return user;
    else if(checkAproveStatus == (const char*) AY_OBFUSCATE("Waiting"))
    {
        user->setPassportSeries((const char*) AY_OBFUSCATE("0"));
        return user;
    }
    else if(checkAproveStatus == (const char*) AY_OBFUSCATE("ban"))
    {
        user->setPassportSeries((const char*) AY_OBFUSCATE("-1"));
        return user;
    }
    else
    {
        user->setName(query->value(1).toString());
        user->setSurname(query->value(2).toString());
        user->setRoleId(query->value(3).toString());
        user->setTelephone(query->value(4).toString());
        user->setEmail(query->value(5).toString());
        user->setCompanyName(query->value(6).toString());
        user->setPassportSeries(query->value(7).toString());
        user->setPassportNum(query->value(8).toString());

        return user;
    }
}
void DataBaseService::AddCustomer(Customer* customer, QString password)
{
    QString encrPassword = QCryptographicHash::hash(password.toLatin1(),QCryptographicHash::Md5).toHex();
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);
    QString sqlInquiry = (const char*) AY_OBFUSCATE("INSERT INTO UserTable(Name, Surname, RoleID, Telephone, Email, CompanyName, PassportSer, PassportNum, Password, AproveStatus) values('");
    sqlInquiry.append(customer->getName());
    sqlInquiry.append((const char*) AY_OBFUSCATE("', '"));
    sqlInquiry.append(customer->getSurname());
    sqlInquiry.append((const char*) AY_OBFUSCATE("', '"));
    sqlInquiry.append(customer->getRoleId());
    sqlInquiry.append((const char*) AY_OBFUSCATE("', '"));
    sqlInquiry.append(customer->getTelephone());
    sqlInquiry.append((const char*) AY_OBFUSCATE("', '"));
    sqlInquiry.append(customer->getEmail());
    sqlInquiry.append((const char*) AY_OBFUSCATE("', '"));
    sqlInquiry.append(customer->getCompanyName());
    sqlInquiry.append((const char*) AY_OBFUSCATE("', '"));
    sqlInquiry.append(customer->getPassportSeries());
    sqlInquiry.append((const char*) AY_OBFUSCATE("', '"));
    sqlInquiry.append(customer->getPassportNum());
    sqlInquiry.append((const char*) AY_OBFUSCATE("', '"));
    sqlInquiry.append(encrPassword);
    sqlInquiry.append((const char*) AY_OBFUSCATE("', 'Waiting')"));
    query->exec(sqlInquiry);
}
void DataBaseService::SetCustomerStatus(int index, QString verdict, QString name)
{
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);
    QString verd;

    if(verdict == "aprove")
    {
        verd = "UPDATE UserTable SET AproveStatus = '";
        verd.append(name);
        verd.append("' WHERE UserId = ");
        verd.append(QString::number(index));
        query->exec(verd);
    }
    else if(verdict == "ban")
    {
        verd = "UPDATE UserTable SET AproveStatus = 'ban' WHERE UserId = ";
        verd.append(QString::number(index));
        query->exec(verd);

        QString find = "SELECT * FROM UserTable WHERE UserId = ";
        find.append(QString::number(index));
        query->exec(find);
        query->next();
        QString email = query->value(5).toString();
        QString banAcc = "UPDATE AccTable SET Type = 'ban' WHERE UserName = '";
        banAcc.append(email);
        banAcc.append("'");
        query->exec(banAcc);
    }
}

bool DataBaseService::AddCredit(Credit *credit)
{
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);

    QString sqlBank = "SELECT * FROM BankTable WHERE Name = '";
    sqlBank.append(credit->getBankName());
    sqlBank.append("'");
    query->exec(sqlBank);
    query->next();
    qlonglong bankBudget = query->value(2).toLongLong();

    bool check = false;

    if(bankBudget - credit->getSum() > 0)
        check = true;

    if (check)
    {
        QString sqlInquiry = "INSERT INTO CreditTable(BankName, UserName, Money, AccIndex, Term, Procent, AproveStatus) values('";
        sqlInquiry.append(credit->getBankName());
        sqlInquiry.append("', '");
        sqlInquiry.append(credit->getUserName());
        sqlInquiry.append("', ");
        sqlInquiry.append(QString::number(credit->getSum()));
        sqlInquiry.append(", ");
        sqlInquiry.append(QString::number(credit->getAccIndex()));
        sqlInquiry.append(", ");
        sqlInquiry.append(QString::number(credit->getTerm()));
        sqlInquiry.append(", ");
        sqlInquiry.append(QString::number(credit->getProcent()));
        sqlInquiry.append(", 'Waiting')");
        query->exec(sqlInquiry);

        return true;
    }
    else
        return false;
}
bool DataBaseService::AproveCredit(int creditName, Transfer *transfer)
{
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);

    QString getBank = "SELECT * FROM BankTable WHERE Name = '";
    getBank.append(transfer->getInit());
    getBank.append("'");
    query->exec(getBank);
    query->next();

    int budget = query->value(2).toInt();
    if(budget - transfer->getSum() < 0)
        return false;

    QString updateCreditStatus = "UPDATE CreditTable SET AproveStatus = '";
    updateCreditStatus.append(transfer->getAprove());
    updateCreditStatus.append("' WHERE CreditId = ");
    updateCreditStatus.append(QString::number(creditName));
    query->exec(updateCreditStatus);

    QString updateBankBudget = "UPDATE BankTable SET Budget = ";
    updateBankBudget.append(QString::number(budget - transfer->getSum()));
    updateBankBudget.append(" WHERE Name = '");
    updateBankBudget.append(transfer->getInit());
    updateBankBudget.append("'");
    query->exec(updateBankBudget);


    QString findAcc = "SELECT * FROM AccTable WHERE AccId = ";
    findAcc.append(QString::number(transfer->getTargetId()));
    query->exec(findAcc);
    query->next();
    int currentSum = query->value(4).toInt();

    QString updateUserAcc = "UPDATE AccTable SET Money = ";
    updateUserAcc.append(QString::number(currentSum + transfer->getSum()));
    updateUserAcc.append(" WHERE AccId = ");
    updateUserAcc.append(QString::number(transfer->getTargetId()));
    query->exec(updateUserAcc);

    QString addTransfer = "INSERT INTO TransferTable(InitName, TargetId, Sum, Aprove) values('";
    addTransfer.append(transfer->getInit());
    addTransfer.append("', ");
    addTransfer.append(QString::number(transfer->getTargetId()));
    addTransfer.append(", ");
    addTransfer.append(QString::number(transfer->getSum()));
    addTransfer.append(", '");
    addTransfer.append(transfer->getAprove());
    addTransfer.append("')");
    query->exec(addTransfer);

    return true;
}
void DataBaseService::CancleCredit(int index, QString status)
{
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);
    QString cancleCredit;

    if(status == "not aprove")
    {
        cancleCredit = "UPDATE CreditTable SET AproveStatus = 'Cancled' WHERE CreditId = ";
        cancleCredit.append(QString::number(index));
        query->exec(cancleCredit);
    }
    else if (status == "aprove")
    {
        cancleCredit = "UPDATE CreditTable SET AproveStatus = 'Cancled' WHERE CreditId = ";
        cancleCredit.append(QString::number(index));
        query->exec(cancleCredit);

        cancleCredit = "SELECT * FROM CreditTable WHERE CreditId = ";
        cancleCredit.append(QString::number(index));
        query->exec(cancleCredit);
        query->next();

        QString bankName = query->value(1).toString();
        int transferSum = query->value(3).toInt();
        int accIndex = query->value(4).toInt();

        cancleCredit = "SELECT * FROM BankTable WHERE Name = '";
        cancleCredit.append(bankName);
        cancleCredit.append("'");
        query->exec(cancleCredit);
        query->next();
        int bankBudget = query->value(2).toInt() + transferSum;
        cancleCredit = "UPDATE BankTable SET Budget = ";
        cancleCredit.append(QString::number(bankBudget));
        cancleCredit.append(" WHERE Name = '");
        cancleCredit.append(bankName);
        cancleCredit.append("'");
        query->exec(cancleCredit);

        cancleCredit = "SELECT * FROM AccTable WHERE AccId = ";
        cancleCredit.append(QString::number(accIndex));
        query->exec(cancleCredit);
        query->next();
        int accBudget = query->value(4).toInt() - transferSum;
        cancleCredit ="UPDATE AccTable SET Money = ";
        cancleCredit.append(QString::number(accBudget));
        cancleCredit.append(" WHERE AccId = ");
        cancleCredit.append(QString::number(accIndex));
        query->exec(cancleCredit);
    }
}

void DataBaseService::AddBankAccount(BankAccount* bankAccount, QString type)
{
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);

    QString sqlInquiry = "INSERT INTO AccTable(AccName, UserName, BankName, Money, Type) values('";
    sqlInquiry.append(bankAccount->getAccName());
    sqlInquiry.append("', '");
    sqlInquiry.append(bankAccount->getUserName());
    sqlInquiry.append("', '");
    sqlInquiry.append(bankAccount->getBankName());
    sqlInquiry.append("', ");
    sqlInquiry.append(QString::number(bankAccount->getMoney()));
    sqlInquiry.append(", '");
    sqlInquiry.append(type);
    sqlInquiry.append("')");
    query->exec(sqlInquiry);
}
void DataBaseService::CloseBankAccount(QString UserName, int AccId)
{
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);
    QString sqlInquiry = "DELETE FROM AccTable WHERE UserName = '";
    sqlInquiry.append(UserName);
    sqlInquiry.append("' AND AccId = ");
    sqlInquiry.append((QString::number(AccId)));
    query->exec(sqlInquiry);
}

QList<BankAccount*>* DataBaseService::GetBankAccounts(QString UserName)
{
    QList<BankAccount*>* list = new QList<BankAccount*>;
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);
    QString sqlInquiry;
    if(UserName == "all")
        sqlInquiry = "SELECT * FROM AccTable";
    else
    {
        sqlInquiry = "SELECT * FROM AccTable WHERE UserName = '";
        sqlInquiry.append(UserName);
        sqlInquiry.append("'");
    }
    query->exec(sqlInquiry);
    while (query->next())
    {
        BankAccount* bankAccount = new BankAccount();
        bankAccount->setAccName(query->value(0).toString());
        bankAccount->setUserName(query->value(1).toString());
        bankAccount->setBankName(query->value(2).toString());
        bankAccount->setAccId(query->value(3).toInt());
        bankAccount->setMoney(query->value(4).toInt());
        bankAccount->setType(query->value(5).toString());
        list->append(bankAccount);
    }

    return list;
}
QList<Credit*>* DataBaseService::GetCredits(QString UserName)
{
    QList<Credit*>* list = new QList<Credit*>;
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);
    QString sqlInquiry;
    if(UserName == "manager")
        sqlInquiry = "SELECT * FROM CreditTable";
    else if (UserName == "all")
        sqlInquiry = "SELECT * FROM CreditTable WHERE AproveStatus = 'Waiting'";
    else
    {
        sqlInquiry = "SELECT * FROM CreditTable WHERE UserName = '";
        sqlInquiry.append(UserName);
        sqlInquiry.append("'");
    }
    query->exec(sqlInquiry);
    while (query->next())
    {
        Credit* credit = new Credit();
        credit->setCreditId(query->value(0).toInt());
        credit->setBankName(query->value(1).toString());
        credit->setUserName(query->value(2).toString());
        credit->setSum(query->value(3).toInt());
        credit->setAccIndex(query->value(4).toInt());
        credit->setTerm(query->value(5).toString().toInt());
        credit->setProcent(query->value(6).toString().toInt());
        credit->setAproveStatus(query->value(7).toString());
        list->append(credit);
    }
    return list;
}
QStringList DataBaseService::GetCompanyName()
{
    QStringList company;
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);
    QString sqlInquiry = "SELECT * FROM CompanyTable";
    query->exec(sqlInquiry);
    while (query->next())
        company.push_back(query->value(0).toString());

    return company;
}
Company* DataBaseService::GetCompany(QString CompanyName)
{
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);
    QString sqlInquiry = "SELECT * FROM CompanyTable WHERE CompanyName = '";
    sqlInquiry.append(CompanyName);
    sqlInquiry.append("'");
    query->exec(sqlInquiry);
    query->next();

    Company* company = new Company();
    company->setAdress(query->value(4).toString());
    company->setBankBIK(query->value(3).toInt());
    company->setCompanyName(query->value(0).toString());
    company->setType(query->value(1).toString());
    company->setUNP(query->value(2).toInt());

    return company;
}
QList<SalaryProject*>* DataBaseService::GetSalaryProjects(QString companyName)
{
    QList<SalaryProject*>* salaryList = new QList<SalaryProject*>;
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);
    QString sqlInquiry;

    if(companyName == "all")
        sqlInquiry = "SELECT * FROM SalaryTable";
    else if (companyName == "manager")
        sqlInquiry = "SELECT * FROM SalaryTable WHERE AproveStatus = 'Aprove by enterprice specialist'";
    else
    {
        sqlInquiry = "SELECT * FROM SalaryTable WHERE CompanyName = '";
        sqlInquiry.append(companyName);
        sqlInquiry.append("'");
    }
    query->exec(sqlInquiry);
    while (query->next())
    {
        SalaryProject* salaryProject = new SalaryProject();
        salaryProject->setIndex(query->value(0).toInt());
        salaryProject->setBIK(query->value(1).toInt());
        salaryProject->setPrevBIK(query->value(2).toInt());
        salaryProject->setCompanyName(query->value(3).toString());
        salaryProject->setUsername(query->value(4).toString());
        salaryProject->setSpecialist(query->value(5).toString());
        salaryProject->setOperator(query->value(6).toString());
        salaryProject->setApproveStatus(query->value(7).toString());
        salaryList->append(salaryProject);
    }

    return salaryList;
}
QList<Bank*>* DataBaseService::GetBanks()
{
    QList<Bank*>* list = new QList<Bank*>;
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);
    QString sqlInquiry = "SELECT * FROM BankTable";
    query->exec(sqlInquiry);
    while (query->next())
    {
        Bank* bank = new Bank();
        bank->setBIK(query->value(0).toInt());
        bank->setName(query->value(1).toString());
        bank->setBudget(query->value(2).toInt());
        list->append(bank);
    }

    return list;
}
QList<Transfer*>* DataBaseService::GetTransfers(QString type)
{
    QList<Transfer*>* list = new QList<Transfer*>;
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);

    QString sqlInquiry;
    if (type == "all")
        sqlInquiry = "SELECT * FROM TransferTable";
    else if (type == "user")
        sqlInquiry = "SELECT * FROM TransferTable WHERE Aprove = 'User transfer'";
    else if (type == "company")
        sqlInquiry = "SELECT * FROM TransferTable WHERE Aprove != 'User transfer' AND Aprove != 'Cancle transfer' AND Aprove != 'Cancled'";
    else if (type == "manager")
        sqlInquiry = "SELECT * FROM TransferTable WHERE Aprove = 'User transfer' OR Aprove = 'Waiting'";

    query->exec(sqlInquiry);

    while (query->next())
    {
        Transfer* transfer = new Transfer();
        transfer->setTransferId(query->value(0).toInt());
        transfer->setInit(query->value(1).toString());
        transfer->setSum(query->value(4).toInt());
        transfer->setTargetId(query->value(3).toInt());
        transfer->setSenderId(query->value(2).toInt());
        transfer->setAprove(query->value(5).toString());
        list->append(transfer);
    }
    return list;
}
QList<CreditCircs*>* DataBaseService::GetCreditCircs()
{
    QList<CreditCircs*>* list = new QList<CreditCircs*>;
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);
    query->exec("SELECT * FROM CreditPlans");

    while(query->next())
    {
        CreditCircs* circs = new CreditCircs();
        circs->setBankName(query->value(0).toString());
        circs->setProc(query->value(1).toInt());
        circs->setTerms(query->value(2).toInt());

        list->push_back(circs);
    }

    return list;
}
QList<User*>* DataBaseService::GetUsers(QString type)
{
    QList<User*>* users = new QList<User*>;
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);
    QString sqlInquiry;
    if (type == "manager")
        sqlInquiry = "SELECT * FROM UserTable WHERE AproveStatus = 'Waiting'";
    else
        sqlInquiry = "SELECT * FROM UserTable WHERE AproveStatus != 'admin'";
    query->exec(sqlInquiry);
    while (query->next())
    {
        User* user = new User();
        user->setUserId(query->value(0).toInt());
        user->setName(query->value(1).toString());
        user->setSurname(query->value(2).toString());
        user->setRoleId(query->value(3).toString());
        user->setTelephone(query->value(4).toString());
        user->setEmail(query->value(5).toString());
        user->setCompanyName(query->value(6).toString());
        user->setPassportSeries(query->value(7).toString());
        user->setPassportNum(query->value(8).toString());
        user->setAproveStatus(query->value(10).toString());
        users->push_back(user);
    }

    return users;
}

bool DataBaseService::TransferCash(Transfer *transfer)
{
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);

    if(transfer->getAprove() == "Corporate reject")
    {
        QString findCorpAcc = "UPDATE TransferTable SET Aprove = 'Cancled'";
        findCorpAcc.append(" WHERE TransferId = ");
        findCorpAcc.append(QString::number(transfer->getTransferId()));
        query->exec(findCorpAcc);
        return true;
    }

    QString findAcc = "SELECT * FROM AccTable WHERE AccId = ";
    findAcc.append(QString::number(transfer->getTargetId()));
    query->exec(findAcc);
    query->next();

    if(query->value(1).toString() == "" || query->value(5).toString() == "ban")
        return false;

    int currentSum = query->value(4).toInt() + transfer->getSum();

    QString updateAcc = "UPDATE AccTable SET Money = ";
    updateAcc.append(QString::number(currentSum));
    updateAcc.append(" WHERE AccId = ");
    updateAcc.append(QString::number(transfer->getTargetId()));
    query->exec(updateAcc);



    findAcc = "SELECT * FROM AccTable WHERE AccId = ";
    findAcc.append(QString::number(transfer->getSenderId()));
    query->exec(findAcc);
    query->next();

    currentSum = query->value(4).toInt() - transfer->getSum();

    updateAcc = "UPDATE AccTable SET Money = ";
    updateAcc.append(QString::number(currentSum));
    updateAcc.append(" WHERE AccId = ");
    updateAcc.append(QString::number(transfer->getSenderId()));
    query->exec(updateAcc);

    QString addTransfer = "INSERT INTO TransferTable(InitName, SenderId, TargetId, Sum, Aprove) values('";
    addTransfer.append(transfer->getInit());
    addTransfer.append("', ");
    addTransfer.append(QString::number(transfer->getSenderId()));
    addTransfer.append(", ");
    addTransfer.append(QString::number(transfer->getTargetId()));
    addTransfer.append(", ");
    addTransfer.append(QString::number(transfer->getSum()));
    addTransfer.append(", '");
    addTransfer.append(transfer->getAprove());
    addTransfer.append("')");
    query->exec(addTransfer);

    if(transfer->getAprove() == "Cancle transfer")
    {
        QString rejectTransfer = "UPDATE TransferTable SET Aprove = 'Cancled' WHERE TransferId = ";
        rejectTransfer.append(QString::number(transfer->getTransferId()));
        query->exec(rejectTransfer);
    }

    return true;
}
void DataBaseService::InOutOperation(Transfer *transfer, int operationIndex)
{
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);

    QString findAcc = "SELECT * FROM AccTable WHERE AccId = ";
    findAcc.append(QString::number(transfer->getSenderId()));
    query->exec(findAcc);
    query->next();

    int currentSum = query->value(4).toInt();
    if (operationIndex == 0)
        currentSum -= transfer->getSum();
    else
        currentSum += transfer->getSum();

    QString updateAcc = "UPDATE AccTable SET Money = ";
    updateAcc.append(QString::number(currentSum));
    updateAcc.append(" WHERE AccId = ");
    updateAcc.append(QString::number(transfer->getSenderId()));
    query->exec(updateAcc);
}

void DataBaseService::CreateSalaryProject(SalaryProject *salaryProject, QString bankName)
{
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);

    QString findPrevBIK = "SELECT * FROM CompanyTable WHERE Name = '";
    findPrevBIK.append(salaryProject->getCompanyName());
    findPrevBIK.append("'");
    query->exec(findPrevBIK);
    query->next();
    int prevBIK = query->value(3).toInt();

    QString findBIK = "SELECT * FROM BankTable WHERE Name = '";
    findBIK.append(bankName);
    findBIK.append("'");
    query->exec(findBIK);
    query->next();
    salaryProject->setBIK(query->value(0).toInt());

    QString sqlCreateSP = "INSERT INTO SalaryTable(BankIndex, CompanyName, UserName, AproveStatus, PrevBankIndex,  AproveBySpec, AproveBySystem) values(";
    sqlCreateSP.append(QString::number(salaryProject->getBIK()));
    sqlCreateSP.append(", '");
    sqlCreateSP.append(salaryProject->getCompanyName());
    sqlCreateSP.append("', '");
    sqlCreateSP.append(salaryProject->getUsername());
    sqlCreateSP.append("', '");
    sqlCreateSP.append(salaryProject->getApproveStatus());
    sqlCreateSP.append("', ");
    sqlCreateSP.append(QString::number(prevBIK));
    sqlCreateSP.append(", 'None', 'None')");
    query->exec(sqlCreateSP);
}
void DataBaseService::AproveSalaryProject(int salaryIndex, QString aproveStatus, QString name, QString type)
{
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);

    QString updateAcc = "UPDATE SalaryTable SET AproveStatus = '";
    updateAcc.append(aproveStatus);
    if (type == "specialist")
        updateAcc.append("', AproveBySpec = '");
    else
        updateAcc.append("', AproveBySystem = '");
    updateAcc.append(name);
    updateAcc.append("' WHERE ProjectId = ");
    updateAcc.append(QString::number(salaryIndex));
    query->exec(updateAcc);

    if(type != "specialist")
    {
        QString findCompany = "SELECT * FROM SalaryTable WHERE ProjectId = ";
        findCompany.append(QString::number(salaryIndex));
        query->exec(findCompany);
        query->next();

        QString companyName = query->value(3).toString();
        int bankIndex = query->value(1).toInt();

        QString findBank = "SELECT * FROM BankTable WHERE BIK = ";
        findBank.append(QString::number(bankIndex));
        query->exec(findBank);
        query->next();

        QString bankName = query->value(1).toString();

        QString updateAcc = "UPDATE AccTable SET BankName = '";
        updateAcc.append(bankName);
        updateAcc.append("' WHERE UserName = '");
        updateAcc.append(companyName);
        updateAcc.append("'");
        query->exec(updateAcc);

        QString updateCompany = "UPDATE CompanyTable SET BankBIK = ";
        updateCompany.append((QString::number(bankIndex)));
        updateCompany.append(" WHERE Name = '");
        updateCompany.append(companyName);
        updateCompany.append("'");
        query->exec(updateCompany);
    }
}
bool DataBaseService::CreateCorporativeTransfer(Transfer *transfer, QString aprove)
{
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);

    QString findCompany = "SELECT * FROM AccTable WHERE AccId = ";
    findCompany.append(QString::number(transfer->getSenderId()));
    query->exec(findCompany);
    query->next();
    QString company = query->value(1).toString();

    QString findAcc = "SELECT * FROM AccTable WHERE AccId = ";
    findAcc.append(QString::number(transfer->getTargetId()));
    query->exec(findAcc);
    query->next();

    if(query->value(1).toString() == "")
        return false;

    if(query->value(5).toString() == "user")
    {
        QString findUser = "SELECT * FROM UserTable WHERE Email = '";
        findUser.append(query->value(1).toString());
        findUser.append("'");
        query->exec(findUser);
        query->next();

        if(query->value(6).toString() != company)
            return false;
    }

    QString addTransfer = "INSERT INTO TransferTable(InitName, SenderId, TargetId, Sum, Aprove) values('";
    addTransfer.append(transfer->getInit());
    addTransfer.append("', ");
    addTransfer.append(QString::number(transfer->getSenderId()));
    addTransfer.append(", ");
    addTransfer.append(QString::number(transfer->getTargetId()));
    addTransfer.append(", ");
    addTransfer.append(QString::number(transfer->getSum()));
    addTransfer.append(", '");
    addTransfer.append(aprove);
    addTransfer.append("')");
    query->exec(addTransfer);
    return true;
}

void DataBaseService::CancleSalaryProject(int index, QString name)
{
    QSqlDatabase db = this->OpenDataBase();
    QSqlQuery* query = new QSqlQuery(db);
    QString cancleSalary = "UPDATE SalaryTable SET AproveStatus = 'Cancled', AproveBySystem = '";
    cancleSalary.append(name);
    cancleSalary.append("' WHERE ProjectId = ");
    cancleSalary.append(QString::number(index));
    query->exec(cancleSalary);

    int updateBIK;
    QString companyName;
    QString bankName;

    QString findBIK = "SELECT * FROM SalaryTable WHERE ProjectId = ";
    findBIK.append(QString::number(index));
    query->exec(findBIK);
    query->next();
    updateBIK = query->value(2).toInt();
    companyName = query->value(3).toString();

    QString updateCompany = "UPDATE CompanyTable SET BankBIK = ";
    updateCompany.append((QString::number(updateBIK)));
    updateCompany.append(" WHERE Name = '");
    updateCompany.append(companyName);
    updateCompany.append("'");
    query->exec(updateCompany);

    QString findBank = "SELECT * FROM BankTable WHERE BIK = ";
    findBank.append(QString::number(updateBIK));
    query->exec(findBank);
    query->next();
    bankName = query->value(1).toString();

    QString updateAcc = "UPDATE AccTable SET BankName = '";
    updateAcc.append(bankName);
    updateAcc.append("' WHERE UserName = '");
    updateAcc.append(companyName);
    updateAcc.append("'");
    query->exec(updateAcc);
}
