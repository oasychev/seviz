#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QToolbar>
#include <QFileDialog>
#include <QDockWidget>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    connect(ui->fileOpenAction, &QAction::triggered, this, &MainWindow::onFileOpen);
    connect(ui->fileSaveAction, &QAction::triggered, this, &MainWindow::onFileSave);
    connect(ui->aboutAction, &QAction::triggered, this, &MainWindow::onAbout);

    m_bookViewer = new EpubRenderer(ui->webEngineView);
    connect(m_bookViewer, &EpubRenderer::bookLoaded, this, &MainWindow::onBookLoaded);

    connect(ui->chapterComboBox, qOverload<int>(&QComboBox::currentIndexChanged), [this](int i) {
        m_bookViewer->showChapter(i);
    });

    setupModules();
}

MainWindow::~MainWindow() {
    delete m_book;
    delete m_bookViewer;
    delete ui;
}

void MainWindow::setupModules() {
    m_manager.forEachModule([&](AbstractModule* module) {
        // для каждой функции плагина
        for (const Feature& f : module->features()) {
            // добавление dock-окна
            f.window->setParent(this);
            f.window->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
            addDockWidget(Qt::BottomDockWidgetArea, f.window);
            f.window->hide();

            // добавление кнопки на тулбар
            QToolBar* toolbar = ui->mainToolBar;
            QAction* action = toolbar->addAction(f.icon, f.text, [this, f](bool checked) {
                if (checked) {
                    f.window->show();
                } else {
                    f.window->hide();
                }
            });
            action->setCheckable(true);
        }
    });
}

void MainWindow::onFileOpen() {
    QString path = QFileDialog::getOpenFileName(this, "Открыть книгу", ".", "Файл EPUB (*.epub)");
    if (!path.isEmpty()) {
        delete m_book;
        m_book = new Book(path, m_bookViewer);
        m_book->open();
    }
}

void MainWindow::onFileSave() {

}

void MainWindow::onAbout() {

}

void MainWindow::onBookLoaded(const QVector<Chapter>& chapters) {
    ui->chapterComboBox->setEnabled(true);
    ui->chapterComboBox->clear();
    for (const auto& c : chapters) {
        ui->chapterComboBox->addItem(c.name);
    }
}