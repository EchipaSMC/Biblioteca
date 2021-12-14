#include "Server.h"
#include "..\TCPSocket\TCPSocket.cpp"
Server::Server()
{
	database = Database("dbCarti.db");
}

void Server::RunServer()
{
	DropVirtualTable();
	PrepareVirtualTable();
	for (int i = 0; i < 100; i++)
	{
		ListenForNewConnection();
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

bool Server::ProcessData(const int& index)
{
	int options;
	if (!clientConnections[index].ReceiveInt(options))
		return false;
	switch (options)
	{
	case 1: // register
		Register(index);
		std::cout << "Processed Register for user. ID = " << index << std::endl;
		break;
	case 2:	// login
		Login(index);
		std::cout << "Processed Login for user. ID = " << index << std::endl;
		break;
	case 3: // delete user
		DeleteUser(index);
		std::cout << "Processed Delete User for user. ID = " << index << std::endl;
		break;
	case 4:	// logout
		Logout(index);
		std::cout << "Processed Logout for user. ID = " << index << std::endl;
		break;
	case 5:	// delete book from borrowedbooks
		ReturnBook(index);
		std::cout << "Processed Return Book for user. ID = " << index << std::endl;
		break;
	case 6: // borrow book
		BorrowBook(index);
		std::cout << "Processed Borrow Book for user. ID = " << index << std::endl;
		break;
	case 7: //search a book
		SearchBook(index);
		std::cout << "Processed Search Book for user. ID = " << index << std::endl;
		break;
	case 8: //Read a book
		ReadBook(index);
		std::cout << "Processed Read Book for user. ID = " << index << std::endl;
		break;
	case 9: //Change Password
		ChangePassword(index);
		std::cout << "Processed Change Password for user. ID = " << index << std::endl;
		break;
	case 10: //Prepare book details;
		PrepareBookDetails(index);
		std::cout << "Processed Book Details for user. ID = " << index << std::endl;
		break;
	case 11://Prolong borrow date
		ProlongBorrowDate(index);
		std::cout << "Processed Prolong Borrow Date for user. ID = " << index << std::endl;
		break;
	default:
		break;
	}

}

void Server::ClientHandler(const int& index)
{
	while (true)
	{
		if (!ProcessData(index))
			break;
	}
	std::cout << "Lost contact with client: id = " << index << std::endl;
	clientConnections[index].CloseConnection();
}

bool Server::ListenForNewConnection()
{
	clientConnections[connectionCounter].Listen();
	SOCKET clientSocket = INVALID_SOCKET;
	if (clientConnections[connectionCounter].GetListenSocket() != INVALID_SOCKET)
	{
		SOCKET listenSocket = clientConnections[connectionCounter].GetListenSocket();
		clientSocket = accept(listenSocket, NULL, NULL);
		if (clientSocket == INVALID_SOCKET)
		{
			std::cerr << "Accept failed with error: " << WSAGetLastError() << std::endl;
			return false;
		}
		else
		{
			std::cout << "Client connected" << std::endl;
			clientConnections[connectionCounter].SetSocket(clientSocket);
			connectionThreads[connectionCounter] = std::thread(&Server::ClientHandler, this, connectionCounter);
			connectionCounter++;
			return true;
		}
	}
}

void Server::Register(const int& index)
{
	bool userExists = false;
	std::string username, password, result;
	clientConnections[index].ReceiveString(username);
	clientConnections[index].ReceiveString(password);
	auto stmt = database.CreateStatement(database.GetDatabase(), queryList.UserServerCheckExistingUsers(username));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	std::getline(Database::getResult, result, '|');
	if (std::stoi(result) != 0)
	{
		userExists = true;
	}
	else queryList.UserServerUserInsert(username, password);
	clientConnections[index].SendBool(userExists);
	Database::getResult.str(std::string());
	Database::getResult.clear();
}

void Server::Login(const int& index)
{
	bool correctInput = false;
	std::string username, password, result, data, bookToSend;
	clientConnections[index].ReceiveString(username);
	clientConnections[index].ReceiveString(password);
	auto stmt = database.CreateStatement(database.GetDatabase(), queryList.UserServerUsersLogin(username, password));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	std::getline(Database::getResult, result, '|');

	if (std::stoi(result) == 1)
	{
		correctInput = true;
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
		correctInput = false;

	Database::getResult.str(std::string());
	Database::getResult.clear();
	clientConnections[index].SendBool(correctInput);
	if (correctInput)
	{
		stmt = database.CreateStatement(database.GetDatabase(), queryList.BorrowedBooksSearch(user.GetUserId()));
		database.Run(stmt.get(), Database::DumpCurrentRow);

		while (std::getline(Database::getResult, result))
		{
			borrowedBooks.push_back(BorrowedBooks(result));
		}

		clientConnections[index].SendInt(borrowedBooks.size());
		for (auto& elem : borrowedBooks)
		{
			stmt = database.CreateStatement(database.GetDatabase(), queryList.BookGetBookByID(elem.GetBookId()));
			database.Run(stmt.get(), Database::DumpCurrentRow);

			std::getline(Database::getResult, data);
			book = Books(data);
			bookToSend = "";
			bookToSend += std::to_string(book.GetBookId()) + "|" + book.GetOriginalTitle() + "|"
				+ book.GetAuthors() + "|" + book.GetISBN() + "|" + book.GetSmallImageURL() + "|" + elem.GetBorrowDate() + "|" + elem.GetReturnDate();
			clientConnections[index].SendString(bookToSend);
		}

		Database::getResult.str(std::string());
		Database::getResult.clear();
	}
}

void Server::DeleteUser(const int& index)
{
	std::string username, password, result;
	int userId;
	clientConnections[index].ReceiveString(username);
	clientConnections[index].ReceiveString(password);
	auto stmt = database.CreateStatement(database.GetDatabase(), queryList.UserServerUserSearch(username, password));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	std::getline(Database::getResult, result);
	user = UserServer(result);
	Database::getResult.str(std::string());
	Database::getResult.clear();

	stmt = database.CreateStatement(database.GetDatabase(), queryList.BorrowedBooksSearch(user.GetUserId()));
	database.Run(stmt.get(), Database::DumpCurrentRow);

	while (std::getline(Database::getResult, result))
	{
		borrowedBooks.push_back(BorrowedBooks(result));
	}
	Database::getResult.str(std::string());
	Database::getResult.clear();

	stmt = database.CreateStatement(database.GetDatabase(), queryList.UserServerUserDelete(username, password));
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
	user = UserServer();
}

void Server::Logout(const int& index)
{
	user.SetPassword("");
	user.SetUsername("");
	user.SetUserId(0);
	borrowedBooks.clear();
	book = Books();
	ratings = Ratings();
	tags.clear();
}

void Server::ReturnBook(const int& index)
{
	std::string username, password, result;
	int borrowedBookIndex;
	clientConnections[index].ReceiveString(username);
	clientConnections[index].ReceiveString(password);
	auto stmt = database.CreateStatement(database.GetDatabase(), queryList.UserServerUserSearch(username, password));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	std::getline(Database::getResult, result);
	user = UserServer(result);
	Database::getResult.str(std::string());
	Database::getResult.clear();

	stmt = database.CreateStatement(database.GetDatabase(), queryList.BorrowedBooksSearch(user.GetUserId()));
	database.Run(stmt.get(), Database::DumpCurrentRow);

	while (std::getline(Database::getResult, result))
	{
		borrowedBooks.push_back(BorrowedBooks(result));
	}
	Database::getResult.str(std::string());
	Database::getResult.clear();

	clientConnections[index].ReceiveInt(borrowedBookIndex);
	stmt = database.CreateStatement(database.GetDatabase(), queryList.BorrowedBooksDelete(borrowedBooks[borrowedBookIndex].GetUserId(), borrowedBooks[borrowedBookIndex].GetBookId()));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	borrowedBooks.erase(borrowedBooks.begin() + borrowedBookIndex, borrowedBooks.begin() + borrowedBookIndex + 1);
	Database::getResult.str(std::string());
	Database::getResult.clear();
	user = UserServer();
}

void Server::BorrowBook(const int& index)
{
	std::string username, password, result;
	clientConnections[index].ReceiveString(username);
	clientConnections[index].ReceiveString(password);
	auto stmt = database.CreateStatement(database.GetDatabase(), queryList.UserServerUserSearch(username, password));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	std::getline(Database::getResult, result);
	user = UserServer(result);
	Database::getResult.str(std::string());
	Database::getResult.clear();

	int bookId;
	std::string borrowedDate, returningDate;
	clientConnections[index].ReceiveInt(bookId);
	clientConnections[index].ReceiveString(borrowedDate);
	clientConnections[index].ReceiveString(returningDate);
	stmt = database.CreateStatement(database.GetDatabase(), queryList.BorrowedBooksInsert(user.GetUserId(), bookId, borrowedDate, returningDate));
	database.Run(stmt.get(), Database::DumpCurrentRow);

	borrowedBooks.push_back(BorrowedBooks(user.GetUserId(), bookId, borrowedDate, returningDate));

	Database::getResult.str(std::string());
	Database::getResult.clear();
	user = UserServer();
}

void Server::SearchBook(const int& index)
{
	std::string keyword, resultsFound, data, bookToSend;
	clientConnections[index].ReceiveString(keyword);
	auto stmt = database.CreateStatement(database.GetDatabase(), queryList.BooksNumOfBookSearch(keyword));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	std::getline(Database::getResult, resultsFound, '|');
	clientConnections[index].SendInt(std::stoi(resultsFound));
	Database::getResult.str(std::string());
	Database::getResult.clear();

	stmt = database.CreateStatement(database.GetDatabase(), queryList.BooksBookSearch(keyword));
	database.Run(stmt.get(), Database::DumpCurrentRow);

	for (int i = 0; i < std::stoi(resultsFound); i++)
	{
		std::getline(Database::getResult, data);
		book = Books(data);
		bookToSend = "";
		bookToSend += std::to_string(book.GetId()) + "|" + book.GetOriginalTitle() + "|"
			+ book.GetAuthors() + "|" + book.GetISBN() + "|" + book.GetSmallImageURL();
		clientConnections[index].SendString(bookToSend);
	}

	Database::getResult.str(std::string());
	Database::getResult.clear();
}

void Server::ReadBook(const int& index)
{
	int bookId;
	std::string bookText, result;
	clientConnections[index].ReceiveInt(bookId);

	bookText = "This is a book about: ";

	auto stmt = database.CreateStatement(database.GetDatabase(), queryList.BookGetBookByID(bookId));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	std::getline(Database::getResult, result);

	book = Books(result);

	stmt = database.CreateStatement(database.GetDatabase(), queryList.TagsGetAllTags(book.GetBestBookId()));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	while (std::getline(Database::getResult, result))
	{
		tags.push_back(result);
	}

	for (auto& i : tags)
	{
		bookText += i.GetTagName() + ", ";
	}

	clientConnections[index].SendString(bookText);

	Database::getResult.str(std::string());
	Database::getResult.clear();
}

void Server::ChangePassword(const int& index)
{

	std::string username, password, result;
	clientConnections[index].ReceiveString(username);
	clientConnections[index].ReceiveString(password);
	auto stmt = database.CreateStatement(database.GetDatabase(), queryList.UserServerUserSearch(username, password));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	std::getline(Database::getResult, result);
	user = UserServer(result);
	Database::getResult.str(std::string());
	Database::getResult.clear();

	std::string newPassword;
	clientConnections[index].ReceiveString(newPassword);
	stmt = database.CreateStatement(database.GetDatabase(), queryList.UserChangePassword(user.GetUserId(), newPassword));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	user.SetPassword(newPassword);

	Database::getResult.str(std::string());
	Database::getResult.clear();
	user = UserServer();
}

void Server::PrepareBookDetails(const int& index)
{
	int bookId;
	std::string result, bookDetails;
	clientConnections[index].ReceiveInt(bookId);
	auto stmt = database.CreateStatement(database.GetDatabase(), queryList.BookGetBookByID(bookId));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	std::getline(Database::getResult, result);

	book = Books(result);
	bookDetails = "";
	bookDetails += book.GetAuthors() + "|" + book.GetTitle() + "|";
	stmt = database.CreateStatement(database.GetDatabase(), queryList.TagsGetAllTags(book.GetBestBookId()));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	while (std::getline(Database::getResult, result))
	{
		bookDetails += result;
		bookDetails.erase(bookDetails.end()-1, bookDetails.end());
		bookDetails += " ";
	}
	bookDetails += '|';
	Database::getResult.str(std::string());
	Database::getResult.clear();

	bookDetails += std::to_string(book.GetAverageRating()) + '|' + std::to_string(book.GetRatings1()) + '|' + std::to_string(book.GetRatings2()) + '|'
		+ std::to_string(book.GetRatings3()) + '|' + std::to_string(book.GetRatings4()) + '|' + std::to_string(book.GetRatings5()) + '|'
		+ book.GetLanguageCode() + '|' + book.GetImageURL();
	clientConnections[index].SendString(bookDetails);
}

void Server::ProlongBorrowDate(const int& index)
{
	std::string username, password, result;
	clientConnections[index].ReceiveString(username);
	clientConnections[index].ReceiveString(password);
	auto stmt = database.CreateStatement(database.GetDatabase(), queryList.UserServerUserSearch(username, password));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	std::getline(Database::getResult, result);
	user = UserServer(result);
	Database::getResult.str(std::string());
	Database::getResult.clear();

	int bookId;
	std::string newReturnDate;
	clientConnections[index].ReceiveInt(bookId);
	clientConnections[index].ReceiveString(newReturnDate);
	stmt = database.CreateStatement(database.GetDatabase(), queryList.BorrowedBooksUpdateReturnDate(user.GetUserId(), bookId, newReturnDate));
	database.Run(stmt.get(), Database::DumpCurrentRow);
	Database::getResult.str(std::string());
	Database::getResult.clear();
	user = UserServer();
}

