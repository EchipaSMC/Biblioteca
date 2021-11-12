#include "Database.h"

Database::Database(const char* name)
{
	OpenDatabase(name);
}

statement Database::CreateStatement(sqlite3* db, const std::string& sql)
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

void Database::Run(sqlite3_stmt* stmt, stmt_callback callback)
{
}

bool Database::DumpCurrentRow(sqlite3_stmt* stmt)
{
	if (stmt)
	{
		for (int i = 0; i < sqlite3_column_count(stmt); ++i)
		{
			auto columntype = sqlite3_column_type(stmt, i);
			if (columntype == SQLITE_NULL)
			{
				std::cout << "<NULL>";
			}
			else if (columntype == SQLITE_INTEGER)
			{
				std::cout << sqlite3_column_int64(stmt, i);
			}
			else if (columntype == SQLITE_FLOAT)
			{
				std::cout << sqlite3_column_double(stmt, i);
			}
			else if (columntype = SQLITE_TEXT)
			{
				auto first = sqlite3_column_text(stmt, i);
				std::size_t s = sqlite3_column_bytes(stmt, i);
				std::cout << "'" << (s > 0 ? std::string((const char*)first, s) : "") << "'";
			}
			else if (columntype == SQLITE_BLOB)
			{
				std::cout << "<BLOOOB>";
			}
			std::cout << "|";
		}
		std::cout << std::endl;
		return true;
	}
}

database Database::OpenDatabase(const char* name)
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
