#include "Database.h"

Database::Database(const char* name)
{
	openDatabase(name);
}

//statement Database::create_statement(sqlite3* db, const std::string& sql)
//{
//	return statement(db,sql);
//}

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
