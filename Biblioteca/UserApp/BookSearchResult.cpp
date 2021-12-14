#include "BookSearchResult.h"

BookSearchResult::BookSearchResult(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
}

BookSearchResult::~BookSearchResult()
{
}
