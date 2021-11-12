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
	Database() = default;
	Database(const char* name);
	statement CreateStatement(sqlite3* db, const std::string& sql);
	void Run(sqlite3_stmt* stmt, stmt_callback callback = stmt_callback());
	bool DumpCurrentRow(sqlite3_stmt* stmt);
	database OpenDatabase(const char* name);
};

