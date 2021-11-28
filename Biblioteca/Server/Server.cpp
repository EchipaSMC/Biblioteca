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
	TCPSocket listener;
	listener.Listen();
	client = listener.Accept();
	RunServer();
}

void Server::RunServer()
{
	int operationCode;
	std::string username, password, result;
	int checkUser;
	statement stmt(nullptr, sqlite3_finalize);
	std::cin >> operationCode;
	PrepareVirtualTable();
	while (true)
	{
		switch (operationCode)
		{
		case 1: // register
			stmt = database.CreateStatement(database.GetDatabase(), queryList.UserServerCheckExistingUsers(username));
			database.Run(stmt.get(), DumpCurrentRow);
			std::getline(getResult, result, '|');
			checkUser = std::stoi(result);
			if (checkUser == 0)
				queryList.UserServerUserInsert(username, password);
			else std::cout << "User already exists";
			getResult.str(std::string());
			getResult.clear();
			break;

		case 2:	// login
			stmt = database.CreateStatement(database.GetDatabase(), queryList.UserServerUsersLogin(username, password));
			database.Run(stmt.get(), DumpCurrentRow);
			std::getline(getResult, result, '|');
			checkUser = std::stoi(result);

			if (checkUser == 1)
			{
				getResult.str(std::string());
				getResult.clear();

				user.SetPassword(password);
				user.SetUsername(username);
				stmt = database.CreateStatement(database.GetDatabase(), queryList.UserServerUsersLoginID(username, password));
				database.Run(stmt.get(), DumpCurrentRow);
				std::getline(getResult, result, '|');
				user.SetUserId(std::stoi(result));
			}
			else
				std::cout << "error login!";

			getResult.str(std::string());
			getResult.clear();

			stmt = database.CreateStatement(database.GetDatabase(), queryList.BorrowedBooksSearch(user.GetUserId()));
			database.Run(stmt.get(), DumpCurrentRow);

			while (std::getline(getResult, username, '|'))
			{
				std::getline(getResult, result, '|');
				borrowedBooks.push_back(BorrowedBooks(std::stoi(username), std::stoi(result)));
			}

			getResult.str(std::string());
			getResult.clear();

			break;

		case 3: // delete user

			stmt = database.CreateStatement(database.GetDatabase(), queryList.UserServerUserDelete(username, password));
			database.Run(stmt.get(), DumpCurrentRow);
			std::getline(getResult, result, '|');
			checkUser = std::stoi(result);

			for (int i = 0; i < borrowedBooks.size(); i++)
			{
				stmt = database.CreateStatement(database.GetDatabase(), queryList.BorrowedBooksDelete(borrowedBooks[i].GetUserId(), borrowedBooks[i].GetBookId()));
				database.Run(stmt.get(), DumpCurrentRow);
				getResult.str(std::string());
				getResult.clear();
			}
			borrowedBooks.clear();
			getResult.str(std::string());
			getResult.clear();
			break;

		case 4:	// logout
			user.SetPassword("");
			user.SetUsername("");
			user.SetUserId(0);
			borrowedBooks.clear();
			break;
		case 5:	// delete booko from borroedbooks

			stmt = database.CreateStatement(database.GetDatabase(), queryList.BorrowedBooksDelete(borrowedBooks[checkUser].GetUserId(), borrowedBooks[checkUser].GetBookId()));
			database.Run(stmt.get(), DumpCurrentRow);
			borrowedBooks.erase(borrowedBooks.begin() + checkUser, borrowedBooks.begin() + checkUser + 1);

			getResult.str(std::string());
			getResult.clear();
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

