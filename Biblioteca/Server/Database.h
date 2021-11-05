#pragma once
#include <sqlite3.h>
#include <iostream>
#include <string>
#include <vector>
#include <functional>


using database = std::unique_ptr<sqlite3, decltype(&sqlite3_close)>;
using statement = std::unique_ptr<sqlite3_stmt, decltype(&sqlite3_finalize)>;
using stmt_callback = std::function<bool(sqlite3_stmt*)>;
class Database
{
public:
	Database(const char* name);
	statement create_statement(sqlite3* db, const std::string& sql);
	void run(sqlite3_stmt* stmt, stmt_callback callback = stmt_callback());
	bool dumpCurrentRow(sqlite3_stmt* stmt);
private:
	database openDatabase(const char* name);
};

