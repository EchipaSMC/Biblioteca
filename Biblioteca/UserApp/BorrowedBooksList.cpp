#include "BorrowedBooksList.h"
#include "Book.h"
#include "QtMessageBox.h"
#include "BorrowedBookDetails.h"
#include "BookDetails.h"

BorrowedBooksList::BorrowedBooksList(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.borrowedBooksList->setViewMode(QListWidget::IconMode);
	ui.borrowedBooksList->setIconSize(QSize(200, 150));
	ui.borrowedBooksList->setResizeMode(QListWidget::Adjust);
	ui.borrowedBooksList->setSpacing(30);

	ui.borrowedBooksList->clear();
	setAttribute(Qt::WA_DeleteOnClose);

	std::vector<Book> borrowedBooks;//user.GetBorrowedBooks(); //= send input to server and receive a vector (of books) containing all the books matching the search input

	if (/*borrowedBooks.size()*/true)
	{
		disconnect(ui.borrowedBooksList, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
			this, SLOT(onBorrowedBookListItemDoubleClicked(QListWidgetItem*)));
		
		Book book = Book();
		book.setImgUrl("https://images-ext-1.discordapp.net/external/qtZoV_oLQ8gGuMnAW8D1fNMb7g1-bnnVAg8NPInLzM8/https/images.gr-assets.com/books/1447303603s/2767052.jpg");
		book.setAuthor(std::to_string(borrowedBooks.size()));
		book.setIsbn("Ex12334123");
		book.setTitle("Exemplu Titlu");
		

		borrowedBooks.push_back(book);
		borrowedBooks.push_back(book);
		borrowedBooks.push_back(book);
		borrowedBooks.push_back(book);

		QNetworkAccessManager* nam = new QNetworkAccessManager(this);
		connect(nam, &QNetworkAccessManager::finished, this, &BorrowedBooksList::loadImage);

		connect(ui.borrowedBooksList, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
			this, SLOT(onBorrowedBookListItemDoubleClicked(QListWidgetItem*)));

		for each (Book borrowedBook in borrowedBooks)
		{
			QString imageURL = QString::fromStdString(borrowedBook.getImgUrl());

			if (imageURL.indexOf("https") == 0)
			{
				imageURL.remove(4, 1);
			}
			titleAndAuthor = QString::fromStdString(borrowedBook.getTitle() + " " + borrowedBook.getAuthor());

			QUrl imageNoSecureURL = imageURL;
			QNetworkRequest request(imageNoSecureURL);
			nam->get(request);
		}
	}
	else
	{
		QtMessageBox* warningMessage = new QtMessageBox;
		warningMessage->SetMessage("No borrowed books found!");
		warningMessage->show();
	}
}

void BorrowedBooksList::loadImage(QNetworkReply* reply)
{
	QPixmap bookCoverImage;
	bookCoverImage.loadFromData(reply->readAll());
	//ui.label->setPixmap(bookCoverImage);
	QListWidgetItem* item = new QListWidgetItem(bookCoverImage, titleAndAuthor);
	ui.borrowedBooksList->addItem(item);
}

void BorrowedBooksList::onBorrowedBookListItemDoubleClicked(QListWidgetItem* item)
{
	BorrowedBookDetails* details = new BorrowedBookDetails;
	BookDetails book2 = BookDetails("Titlue|Autor|ad afa afds|4.0|2|3|4|5|1|en|https://images-ext-1.discordapp.net/external/qtZoV_oLQ8gGuMnAW8D1fNMb7g1-bnnVAg8NPInLzM8/https/images.gr-assets.com/books/1447303603s/2767052.jpg");
	details->SetLanguage(book2.GetLanguageCode());
	details->SetRating(std::to_string(book2.GetAverageRating()));

	details->SetTitle(item->text().toStdString());
	details->LoadImageFromURL("http://images.gr-assets.com/books/1447303603m/2767052.jpg");
	details->show();
}

BorrowedBooksList::~BorrowedBooksList()
{
}
