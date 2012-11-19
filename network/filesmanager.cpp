#include "filesmanager.h"
#include "share/registration.h"
#include "core/driveengine.h"
#include <QSettings>
#include <QDebug>

FilesManager::FilesManager(QObject *parent):
    ContentManager(FILE_TYPE, parent)
{
}

FilesManager::~FilesManager()
{
    panel->clear();
    links.clear();
}

void FilesManager::show(void)
{
    QList<ItemInfo::Data> fileItems = parser->getXMLHandler()->getItemInfo()->getFileItems();
    QSettings settings(COMPANY_NAME, APP_NAME);

    clear();
    panel->clear();

    if(sendGetRequest().url() != GET_FULL_ROOT_CONTENT)
    {
        items.push_back(new QTreeWidgetItem(panel));
        items.last()->setText(0, PARENT_FOLDER_SIGN);
    }

    for(int i = 1; i < fileItems.count(); ++i)
    {
        items.push_back(new QTreeWidgetItem(panel));

        items.last()->setText(0, fileItems[i].name);
        items.last()->setIcon(0, QPixmap(fileItems[i].iconPath));
        items.last()->setText(1, fileItems[i].dataOwner);
        items.last()->setText(2, fileItems[i].fileUpdated);
        items.last()->setText(3, fileItems[i].fileSize);
    }

    if(settings.value(INIT_LOAD).toBool())
    {
        emit signalFirstPanelIsLoaded();
    }

    links.push_back(sendGetRequest().url().toString());

    //    SUi::inst()->filesView->setSortingEnabled(true);
    //    SUi::inst()->filesView->sortItems(0, Qt::AscendingOrder);
}

void FilesManager::setPanel(QTreeWidget *p)
{
    panel = p;
}

QTreeWidget* FilesManager::getPanel(void) const
{
    return panel;
}

QString FilesManager::getCurrLink(void) const
{
    return links.last();
}

QString FilesManager::back(void)
{
    QString prevLink;

    if(!links.isEmpty())
    {
        links.pop_back();
        prevLink  = links.last();
        links.pop_back();
    }

    return prevLink;
}

void FilesManager::sort(int column, Qt::SortOrder order)
{
}

void FilesManager::deleteFile(const QString &url)
{
    opMngr->deleteFile(url);
}

void FilesManager::copyFile(const QString &source, const QString &dest)
{
   opMngr->copyFile(source, dest);
}
