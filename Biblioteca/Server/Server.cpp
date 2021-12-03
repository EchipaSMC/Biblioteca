#include "Server.h"
#include "..\TCPSocket\TCPSocket.cpp"
std::stringstream Database::getResult;
/*
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
*/
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
		client.ReceiveInt(operationCode);
		switch (operationCode)
		{
		case 1: // register
			client.Receive(username);
			client.Receive(password);
			stmt = database.CreateStatement(database.GetDatabase(), queryList.UserServerCheckExistingUsers(username));
			database.Run(stmt.get(), Database::DumpCurrentRow);
			std::getline(Database::getResult, result, '|');
			checkUser = std::stoi(result);
			if (checkUser == 0)
				queryList.UserServerUserInsert(username, password);
			else std::cout << "User already exists";
			Database::getResult.str(std::string());
			Database::getResult.clear();
			break;

		case 2:	// login
			client.Receive(username);
			client.Receive(password);
			stmt = database.CreateStatement(database.GetDatabase(), queryList.UserServerUsersLogin(username, password));
			database.Run(stmt.get(), Database::DumpCurrentRow);
			std::getline(Database::getResult, result, '|');
			checkUser = std::stoi(result);

			if (checkUser == 1)
			{
				Database::getResult.str(std::string());
				Database::getResult.clear();

				user.SetPassword(password);
				user.SetUsername(username);
				stmt = database.CreateStatement(database.GetDatabase(), queryList.UserServerUsersLoginID(username, password));
				database.Run(stmt.get(), Database::DumpCurrentRow);
				std::getline(Database::getResult, result, '|');
				user.SetUserId(std::stoi(result));
			}
			else
				std::cout << "error login!";

			Database::getResult.str(std::string());
			Database::getResult.clear();

			stmt = database.CreateStatement(database.GetDatabase(), queryList.BorrowedBooksSearch(user.GetUserId()));
			database.Run(stmt.get(), Database::DumpCurrentRow);

			while (std::getline(Database::getResult, username, '|'))
			{
				std::getline(Database::getResult, result, '|');
				borrowedBooks.push_back(BorrowedBooks(std::stoi(username), std::stoi(result)));
			}

			client.SendInt(borrowedBooks.size());
			for (auto elem : borrowedBooks)
			{
				result = "";
				result += std::to_string(elem.GetUserId());
				result += std::to_string(elem.GetBookId());
			}
			
			Database::getResult.str(std::string());
			Database::getResult.clear();

			break;

		case 3: // delete user

			stmt = database.CreateStatement(database.GetDatabase(), queryList.UserServerUserDelete(username, password));
			database.Run(stmt.get(), Database::DumpCurrentRow);
			std::getline(Database::getResult, result, '|');
			checkUser = std::stoi(result);

			for (int i = 0; i < borrowedBooks.size(); i++)
			{
				stmt = database.CreateStatement(database.GetDatabase(), queryList.BorrowedBooksDelete(borrowedBooks[i].GetUserId(), borrowedBooks[i].GetBookId()));
				database.Run(stmt.get(), Database::DumpCurrentRow);
				Database::getResult.str(std::string());
				Database::getResult.clear();
			}
			borrowedBooks.clear();
			Database::getResult.str(std::string());
			Database::getResult.clear();
			break;

		case 4:	// logout
			user.SetPassword("");
			user.SetUsername("");
			user.SetUserId(0);
			borrowedBooks.clear();
			break;
		case 5:	// delete book from borrowedbooks
			client.ReceiveInt(checkUser);
			stmt = database.CreateStatement(database.GetDatabase(), queryList.BorrowedBooksDelete(borrowedBooks[checkUser].GetUserId(), borrowedBooks[checkUser].GetBookId()));
			database.Run(stmt.get(), Database::DumpCurrentRow);
			borrowedBooks.erase(borrowedBooks.begin() + checkUser, borrowedBooks.begin() + checkUser + 1);
			Database::getResult.str(std::string());
			Database::getResult.clear();
			break;
		case 6: // borrow book
			client.Receive(result);
			stmt = database.CreateStatement(database.GetDatabase(), queryList.BorrowedBooksInsert(user.GetUserId(), std::stoi(result)));
			database.Run(stmt.get(), Database::DumpCurrentRow);
			borrowedBooks.push_back(BorrowedBooks(user.GetUserId(), std::stoi(result)));

			Database::getResult.str(std::string());
			Database::getResult.clear();
			break;
		case 7: //search a book
			client.Receive(result);
			stmt = database.CreateStatement(database.GetDatabase(), queryList.BooksNumOfBookSearch(result));
			database.Run(stmt.get(), Database::DumpCurrentRow);
			std::getline(Database::getResult, username);
			client.SendInt(std::stoi(username));
			
			stmt = database.CreateStatement(database.GetDatabase(), queryList.BooksBookSearch(result));
			for (int i = 0; i < std::stoi(result); i++)
			{
				std::getline(Database::getResult, username);
				client.Send(username);
			}

			Database::getResult.str(std::string());
			Database::getResult.clear();
			break;
			
			
		case 8: //Read a book
			client.Receive(result);

			stmt = database.CreateStatement(database.GetDatabase(), queryList.BookTagsNumGetTags(std::stoi(result)));
			database.Run(stmt.get(), Database::DumpCurrentRow);
			std::getline(Database::getResult, username);
			client.SendInt(std::stoi(username));

			username = "This is a book about: ";

			stmt = database.CreateStatement(database.GetDatabase(), queryList.BookTagsGetTags(std::stoi(result)));
			for (int i = 0; i < std::stoi(result); i++)
			{
				std::getline(Database::getResult, password);
				username += password;
			}
			client.Send(username);

			Database::getResult.str(std::string());
			Database::getResult.clear();
			break;

		case 9: //Change Password
			client.Receive(result);
			stmt = database.CreateStatement(database.GetDatabase(), queryList.UserChangePassword(user.GetUserId(),result));
			database.Run(stmt.get(), Database::DumpCurrentRow);
			user.SetPassword(result);

			Database::getResult.str(std::string());
			Database::getResult.clear();
		default:
			break;
		}
	}
	DropVirtualTable();
}

void Server::PrepareVirtualTable()
{
	auto stmt = database.CreateStatement(database.GetDatabase(), "CREATE VIRTUAL TABLE demo USING spellfix1");
	database.Run(stmt.get(), Database::DumpCurrentRow);
	stmt = database.CreateStatement(database.GetDatabase(), "INSERT INTO demo(word,rank) select original_title,id from Books where original_title is not null");
	database.Run(stmt.get(), Database::DumpCurrentRow);
	stmt = database.CreateStatement(database.GetDatabase(), "INSERT INTO demo(word,rank) select authors,id from Books where authors is not null");
	database.Run(stmt.get(), Database::DumpCurrentRow);
	stmt = database.CreateStatement(database.GetDatabase(), "INSERT INTO demo(word,rank) select isbn,id from Books where isbn is not null");
	database.Run(stmt.get(), Database::DumpCurrentRow);
}

void Server::DropVirtualTable()
{
	auto stmt = database.CreateStatement(database.GetDatabase(), "DROP TABLE demo");
	database.Run(stmt.get(), Database::DumpCurrentRow);
}

