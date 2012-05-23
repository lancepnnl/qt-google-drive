#ifndef DRIVEENGINE_H
#define DRIVEENGINE_H

#include "oauth2.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"
#include <QFileDialog>
#include <QTreeWidgetItem>
#include "downloadmanager.h"
#include "uploadmanager.h"
#include "filesmanager.h"
#include "foldersmanager.h"
#include "additionalfoldesmanager.h"

class FoldersManager;
class FilesManager;
class AdditionalFoldersManager;

class DriveEngine : public QObject
{
    Q_OBJECT
public:

    enum EObjects
    {
        EFilesView = 0 ,
        EFoldersView
    };

    explicit DriveEngine(QObject *parent = 0);
    ~DriveEngine();

public:
    void init(void);
    OAuth2* getOAuth2(void) const;
    void showFolders(void);
    void showFiles(void);
    void showFilesFromFolderInFilesView(void);
    FoldersManager* getFoldersManager(void) const;

private:
    void setConnections(void);
    int getCurrentModelItemIndex(void) const;
    int getCurrentFileItemIndex(FilesManager *manager) const;
    void download(FilesManager *manager);
    void upload(void);
    bool folderInFilesView(QString &resourceID);

public slots:
    void slotStartLogin();
    void slotStartLoginFromMenu();
    bool slotCheckWorkDir(bool showDlg = true);
    void slotDeleteFileFinished();

private slots:
    void slotDownload(void);
    void slotUpload(void);
    void slotFoldersViewClicked(const QModelIndex&);
    void slotFilesViewClicked(const QModelIndex&);
    void slotAdditionalFoldersViewClicked(const QModelIndex& index);
    void slotFilesSortIndicatorChanged(int logicalIndex, Qt::SortOrder order);
    void slotDel(QObject* object);
    //void slotFoldersShowed();

private:
    OAuth2* oAuth2;
    QWidget* parent;
    DownloadFileManager* downloadManager;
    UploadFileManager* uploadFileManager;
    FoldersManager* foldersManager;
    FilesManager* filesManager;
    AdditionalFoldersManager* additionalFoldersManager;
    bool additionalViewActivated;
};

#endif // DRIVEENGINE_H
