#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "driveengine.h"
#include <QTextCodec>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    SUi::inst()->setupUi(this);
}

MainWindow::~MainWindow()
{
    SDriveEngine::freeInst();
    SUi::freeInst();
}

void MainWindow::init(void)
{
    {
        CheckUI checkUI;
        if(!checkUI.checkReg()) return;
    }

    SDriveEngine::freeInst();
    SDriveEngine::inst(this)->init();
    SDriveEngine::inst()->getCheckUI()->slotCheckWorkDir(false);

    setConnections();

    SUi::inst()->foldersView->installEventFilter(this);
    SUi::inst()->filesView->installEventFilter(this);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    SUi::inst()->filesView->header()->resizeSection(0, 380);
}

void MainWindow::setConnections(void)
{
    connect(SUi::inst()->actionMenuLogin, SIGNAL(triggered()), SDriveEngine::inst(), SLOT(slotStartLoginFromMenu()));
    connect(SUi::inst()->actionMenuQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(SUi::inst()->actionMenuDownload, SIGNAL(triggered()), SDriveEngine::inst()->getfilesTransferUI(), SLOT(slotDownload()));
    connect(SUi::inst()->actionDownload, SIGNAL(triggered()), SDriveEngine::inst()->getfilesTransferUI(), SLOT(slotDownload()));
    connect(SUi::inst()->actionMenuUpload, SIGNAL(triggered()), SDriveEngine::inst()->getfilesTransferUI(), SLOT(slotUpload()));
    connect(SUi::inst()->actionUpload, SIGNAL(triggered()), SDriveEngine::inst()->getfilesTransferUI(), SLOT(slotUpload()));
    connect(SUi::inst()->actionMenuSettings, SIGNAL(triggered()), SDriveEngine::inst()->getCheckUI(), SLOT(slotCheckWorkDir()));
    connect(SUi::inst()->actionSettings, SIGNAL(triggered()), SDriveEngine::inst()->getCheckUI(), SLOT(slotCheckWorkDir()));
    connect(SUi::inst()->actionMenuDelete, SIGNAL(triggered()), SDriveEngine::inst()->getOperationsUI(), SLOT(slotTriggeredDel()));
    connect(SUi::inst()->actionDelete, SIGNAL(triggered()), SDriveEngine::inst()->getOperationsUI(), SLOT(slotTriggeredDel()));
    connect(SUi::inst()->actionMenuCreateFolder, SIGNAL(triggered()), SDriveEngine::inst()->getOperationsUI(), SLOT(slotCreateFolder()));
    connect(SUi::inst()->actionCreateFolder, SIGNAL(triggered()), SDriveEngine::inst()->getOperationsUI(), SLOT(slotCreateFolder()));   
    connect(SUi::inst()->foldersView, SIGNAL(clicked (const QModelIndex&)), SDriveEngine::inst()->getFoldersUI(), SLOT(slotFoldersViewClicked(const QModelIndex&)));
    connect(SUi::inst()->filesView, SIGNAL(clicked (const QModelIndex&)), SDriveEngine::inst()->getfilesUI(), SLOT(slotFilesViewClicked(const QModelIndex&)));
    connect(SUi::inst()->additionalFoldersView, SIGNAL(clicked (const QModelIndex&)), SDriveEngine::inst()->getfilesUI(), SLOT(slotAdditionalShowFiles(const QModelIndex&)));
    connect(SUi::inst()->filesView->header(), SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)), SDriveEngine::inst()->getfilesUI(), SLOT(slotFilesSortIndicatorChanged(int, Qt::SortOrder)));
    connect(SDriveEngine::inst()->getFoldersManager(), SIGNAL(signalAccessTokenRequired()), SDriveEngine::inst(), SLOT(slotStartLogin()));
    connect(SDriveEngine::inst()->getOAuth2(), SIGNAL(loginDone()), this, SLOT(slotloginDone()));
    connect(SDriveEngine::inst()->getFoldersManager(), SIGNAL(signalAccessTokenRequired()), SDriveEngine::inst(), SLOT(slotStartLogin()));
}

void MainWindow::slotloginDone()
{
    init();
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    return SDriveEngine::inst()->getEventHandler()->event(object, event);
}
