#include "Database.h"

Database::Database(const char* name)
{
	openDatabase(name);
}

statement Database::create_statement(sqlite3* db, const std::string& sql)
{
	if (db)
	{
		sqlite3_stmt* stmt = nullptr;
		int rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &stmt, nullptr);
		if (rc != SQLITE_OK)
		{
			std::cerr << "Unable to create statement: " << sql << " : " << sqlite3_errmsg(db);
			std::exit(EXIT_FAILURE);
		}
		return statement(stmt, sqlite3_finalize);
	}
}

void Database::run(sqlite3_stmt* stmt, stmt_callback callback)
{
}

bool Database::dumpCurrentRow(sqlite3_stmt* stmt)
{
	return false;
}

database Database::openDatabase(const char* name)
{
	sqlite3* db = nullptr;
	auto rc = sqlite3_open(name, &db);
	if (rc != SQLITE_OK)
	{
		std::cerr << "Unable to open database " << name << " : " << sqlite3_errmsg(db);
		sqlite3_close(db);
		std::exit(EXIT_FAILURE);
	}
	else {
		std::cout << "Opened database " << name << " with succes";
	}
	return database(db, sqlite3_close);
}
