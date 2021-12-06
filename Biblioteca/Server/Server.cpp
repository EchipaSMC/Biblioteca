#include "Server.h"
#include "..\TCPSocket\TCPSocket.cpp"
std::stringstream Database::getResult;
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
	PrepareVirtualTable();
	while (true)
	{
		client.ReceiveInt(operationCode);
		switch (operationCode)
		{
		case 1: // register
			Register();
			break;
		case 2:	// login
			Login();
			break;
		case 3: // delete user
			DeleteUser();
			break;
		case 4:	// logout
			Logout();
			break;
		case 5:	// delete book from borrowedbooks
			ReturnBook();
			break;
		case 6: // borrow book
			BorrowBook();
			break;
		case 7: //search a book
			SearchBook();
			break;
		case 8: //Read a book
			ReadBook();
			break;
		case 9: //Change Password
			ChangePassword();
			break;
		case 10: //Prepare book details;
			PrepareBookDetails();
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

void Server::Register()
{
	std::string username, password, result;
	client.Receive(username);
	client.Receive(password);
	auto stmt = database.CreateStatement(database.GetDatabase(), queryList.UserServerCheckExistingUsers(username));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	std::getline(Database::getResult, result, '|');
	if (std::stoi(result) == 0)
		queryList.UserServerUserInsert(username, password);
	else std::cout << "User already exists";
	Database::getResult.str(std::string());
	Database::getResult.clear();
}

void Server::Login()
{
	std::string username, password,result,result2;
	client.Receive(username);
	client.Receive(password);
	auto stmt = database.CreateStatement(database.GetDatabase(), queryList.UserServerUsersLogin(username, password));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	std::getline(Database::getResult, result, '|');

	if (std::stoi(result) == 1)
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

	while (std::getline(Database::getResult, result))
	{
		borrowedBooks.push_back(BorrowedBooks(result));
	}

	client.SendInt(borrowedBooks.size());
	for (auto elem : borrowedBooks)
	{
		result = "";
		result += std::to_string(elem.GetUserId()) + " " + std::to_string(elem.GetBookId()) + " " + elem.GetBorrowDate() + " " + elem.GetReturnDate();
		client.Send(result);
	}

	Database::getResult.str(std::string());
	Database::getResult.clear();
}

void Server::DeleteUser()
{
	auto stmt = database.CreateStatement(database.GetDatabase(), queryList.UserServerUserDelete(user.GetUsername(), user.GetPassword()));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	Database::getResult.str(std::string());
	Database::getResult.clear();

	for (int i = 0; i < borrowedBooks.size(); i++)
	{
		stmt = database.CreateStatement(database.GetDatabase(), queryList.BorrowedBooksDelete(borrowedBooks[i].GetUserId(), borrowedBooks[i].GetBookId()));
		database.Run(stmt.get(), Database::DumpCurrentRow);
		Database::getResult.str(std::string());
		Database::getResult.clear();
	}
	borrowedBooks.clear();
}

void Server::Logout()
{
	user.SetPassword("");
	user.SetUsername("");
	user.SetUserId(0);
	borrowedBooks.clear();
	book = Books();
	bookTags = BookTags();
	ratings = Ratings();
	tags = Tags();
}

void Server::ReturnBook()
{
	int borrowedBookIndex;
	client.ReceiveInt(borrowedBookIndex);
	auto stmt = database.CreateStatement(database.GetDatabase(), queryList.BorrowedBooksDelete(borrowedBooks[borrowedBookIndex].GetUserId(), borrowedBooks[borrowedBookIndex].GetBookId()));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	borrowedBooks.erase(borrowedBooks.begin() + borrowedBookIndex, borrowedBooks.begin() + borrowedBookIndex + 1);
	Database::getResult.str(std::string());
	Database::getResult.clear();
}

void Server::BorrowBook()
{
	int bookId;
	std::string borrowedDate, returningDate;
	client.ReceiveInt(bookId);
	client.Receive(borrowedDate);
	client.Receive(returningDate);
	auto stmt = database.CreateStatement(database.GetDatabase(), queryList.BorrowedBooksInsert(user.GetUserId(), bookId, borrowedDate, returningDate));
	database.Run(stmt.get(), Database::DumpCurrentRow);

	borrowedBooks.push_back(BorrowedBooks(user.GetUserId(), bookId, borrowedDate, returningDate));

	Database::getResult.str(std::string());
	Database::getResult.clear();
}

void Server::SearchBook()
{
	std::string keyword, resultsFound,book;
	client.Receive(keyword);
	auto stmt = database.CreateStatement(database.GetDatabase(), queryList.BooksNumOfBookSearch(keyword));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	std::getline(Database::getResult, resultsFound);
	client.SendInt(std::stoi(resultsFound));

	stmt = database.CreateStatement(database.GetDatabase(), queryList.BooksBookSearch(keyword));
	for (int i = 0; i < std::stoi(resultsFound); i++)
	{
		std::getline(Database::getResult, book);
		client.Send(book);
	}

	Database::getResult.str(std::string());
	Database::getResult.clear();
}

void Server::ReadBook()
{
	int bookId;
	std::string bookText, tags;
	client.ReceiveInt(bookId);

	//auto stmt = database.CreateStatement(database.GetDatabase(), queryList.BookTagsNumGetTags(bookId));
	//database.Run(stmt.get(), Database::DumpCurrentRow);
	//std::getline(Database::getResult, username);
	//client.SendInt(std::stoi(username));

	bookText = "This is a book about: ";

	auto stmt = database.CreateStatement(database.GetDatabase(), queryList.BookTagsGetTags(bookId));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	std::getline(Database::getResult, tags);
	bookText += tags;
	client.Send(bookText);

	Database::getResult.str(std::string());
	Database::getResult.clear();
}

void Server::ChangePassword()
{
	std::string newPassword;
	client.Receive(newPassword);
	auto stmt = database.CreateStatement(database.GetDatabase(), queryList.UserChangePassword(user.GetUserId(), newPassword));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	user.SetPassword(newPassword);

	Database::getResult.str(std::string());
	Database::getResult.clear();
}

void Server::PrepareBookDetails()
{
	int bookId;
	std::string result;
	client.ReceiveInt(bookId);
	auto stmt = database.CreateStatement(database.GetDatabase(), queryList.TagsQuerySearch(std::to_string(bookId)));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	std::getline(Database::getResult, result);
	bookTags = BookTags(result);
	Database::getResult.str(std::string());
	Database::getResult.clear();

	stmt = database.CreateStatement(database.GetDatabase(), queryList.BookGetBookByID(bookId));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	std::getline(Database::getResult, result);
	book = Books(result);
	client.Send(std::to_string(book.GetAverageRating()));
	client.SendInt(book.GetRatings1());
	client.SendInt(book.GetRatings2());
	client.SendInt(book.GetRatings3());
	client.SendInt(book.GetRatings4());
	client.SendInt(book.GetRatings5());
	client.Send(book.GetLanguageCode());
}

