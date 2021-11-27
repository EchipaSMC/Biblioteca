#include "Server.h"
std::stringstream getResult;
bool DumpCurrentRow(sqlite3_stmt* stmt)
{
	if (stmt)
	{
		for (int i = 0; i < sqlite3_column_count(stmt); ++i)
		{
			auto columntype = sqlite3_column_type(stmt, i);
			if (columntype == SQLITE_NULL)
			{
				//std::cout << "<NULL>";
			}
			else if (columntype == SQLITE_INTEGER)
			{
				getResult << sqlite3_column_int64(stmt, i);
			}
			else if (columntype == SQLITE_FLOAT)
			{
				getResult << sqlite3_column_double(stmt, i);
			}
			else if (columntype == SQLITE_TEXT)
			{
				auto first = sqlite3_column_text(stmt, i);
				std::size_t s = sqlite3_column_bytes(stmt, i);
				getResult << (s > 0 ? std::string((const char*)first, s) : "");
			}
			else if (columntype == SQLITE_BLOB)
			{
				//std::cout << "<BLOOOB>";
			}
			std::cout << "|";
		}
		std::cout << std::endl;
		return true;
	}
	return false;
}

Server::Server()
{
	database = Database("dbCarti.db");
	RunServer();
}

void Server::RunServer()
{
	int operationCode;
	std::string username, password, result;
	int checkUser;
	statement stmt(nullptr,sqlite3_finalize);
	std::cin >> operationCode;
	PrepareVirtualTable();
	while (true)
	{
		switch (operationCode)
		{
		case 1:
			stmt = database.CreateStatement(database.GetDatabase(), user.CheckExistingUsers(username));
			database.Run(stmt.get(), DumpCurrentRow);
			std::getline(getResult, result, '|');
			checkUser = std::stoi(result);
			if (checkUser == 0)
				user.UserInsert(username, password);
			else std::cout << "User already exists";
			break;

		case 2:
			break;
		default:
			break;
		}	
	}
	DropVirtualTable();
}

void Server::PrepareVirtualTable()
{
	auto stmt = database.CreateStatement(database.GetDatabase(), "CREATE VIRTUAL TABLE demo USING spellfix1");
	database.Run(stmt.get(), DumpCurrentRow);
	stmt = database.CreateStatement(database.GetDatabase(), "INSERT INTO demo(word,rank) select original_title,id from Books where original_title is not null");
	database.Run(stmt.get(), DumpCurrentRow);
	stmt = database.CreateStatement(database.GetDatabase(), "INSERT INTO demo(word,rank) select authors,id from Books where authors is not null");
	database.Run(stmt.get(), DumpCurrentRow);
	stmt = database.CreateStatement(database.GetDatabase(), "INSERT INTO demo(word,rank) select isbn,id from Books where isbn is not null");
	database.Run(stmt.get(), DumpCurrentRow);
}

void Server::DropVirtualTable()
{
	auto stmt = database.CreateStatement(database.GetDatabase(), "DROP TABLE demo");
	database.Run(stmt.get(), DumpCurrentRow);
}

