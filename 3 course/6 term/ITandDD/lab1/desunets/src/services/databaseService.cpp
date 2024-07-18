#include "databaseService.h"
#include <iostream>

sqlite3* db;

void dbInit() {
    sqlite3_open("desunetdb.db", &db);
}

int getUsrId(std::string uname) {
    sqlite3_stmt* stmt;

    std::string query = "SELECT id FROM users WHERE uname='" + uname + "';";
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
    sqlite3_step(stmt);

    int id = sqlite3_column_int(stmt, 0);

    return id;
}

bool auth(std::string username, std::string password) {
    sqlite3_stmt* stmt;

    std::string query =  "SELECT id FROM \"users\" WHERE uname='" + username + "' AND pass='" + password + "'";
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
    sqlite3_step(stmt);
    auto id = sqlite3_column_int(stmt, 0);
   
    if (id == 0)
        return false;
    return true;
}

std::vector<std::string> getListOfUsers() {
    std::vector<std::string> result;
    sqlite3_stmt* stmt;

    std::string query =  "SELECT uname FROM \"users\"";
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
    while(sqlite3_step(stmt) != SQLITE_DONE) {
        std::string uname = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        result.push_back(uname);
    }
    return result;
}

std::vector<std::string> getChat(std::string getterId, std::string senderId) {
    std::string query = "SELECT msg, uname FROM msgs JOIN users ON users.id = msgs.sender  WHERE (sender=" + std::to_string(getUsrId(senderId)) + " AND getter=" + std::to_string(getUsrId(getterId)) + ") OR (sender=" + std::to_string(getUsrId(getterId)) + " AND getter=" + std::to_string(getUsrId(senderId)) + ")";

    if (getterId == senderId)
        query += ";";
    else
        query += "AND getter <> sender;";

    std::vector<std::string> result;
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
    while(sqlite3_step(stmt) != SQLITE_DONE) {
        std::string msg = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        std::string sender = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        result.push_back(sender + ": " + msg);
    }
    return result;
}

void saveMsg(std::string getterId, std::string senderId, std::string msg) {
    msg.erase(0, 1);
    std::string query =  "INSERT INTO msgs VALUES ('" + msg + "', " +
    std::to_string(getUsrId(senderId)) + ", " + std::to_string(getUsrId(getterId)) + ");";

    int rc;
    do {
        char* err;
        sqlite3_busy_timeout(db, 10);
        rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
    } while (rc == SQLITE_BUSY);
}

bool saveUsr(std::string username, std::string password) {
    std::string query = "INSERT INTO \"users\" VALUES ('" + username +"', '" + password +"', NULL);";
    int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);

    if (rc != SQLITE_OK)
        return false;
    return true;
}