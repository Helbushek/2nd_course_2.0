#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->hashTable->resize(ui->spinBoxTableSize->value());

    connect(ui->hashTable, &HashTableWidget::sendMessage, this, &MainWindow::printMessage);
    connect(ui->hashTable, &HashTableWidget::scroll, this, [this](QRect item) {
        ui->scrollArea->ensureVisible(item.x(), item.y(), item.width()+10, item.height()+10);
    });

    ui->comboBoxHash->addItem("hi(K) = (hi-1(K) + c × i + d × i2) mod N");
    ui->comboBoxHash->addItem("hi(K) = [hi-1(K) × a × N] mod N;");
    ui->comboBoxHash->addItem("hi(K) = (K mod N) + i × (1+ K mod (N – 2)) mod N");

    connect(ui->pushButtonAdd, &QPushButton::clicked, this, [this]() {
        ui->hashTable->addItem(ui->spinBoxKey->value(), ui->lineEditValue->text());
    });

    connect(ui->spinBoxTableSize, &QSpinBox::textChanged, this, [this]() {
        ui->hashTable->resize(ui->spinBoxTableSize->value());
    });

    connect(ui->comboBoxHash, &QComboBox::currentTextChanged, this,
            [this]() { ui->hashTable->chooseHash(ui->comboBoxHash->currentIndex()); });

    connect(ui->pushButtonRemove, &QPushButton::clicked, this,
            [this]() { ui->hashTable->removeItem(ui->spinBoxKey->value()); });

    connect(ui->pushButtonFind, &QPushButton::clicked, this, [this]() {
        QPair<int, int> pos = ui->hashTable->findItem(ui->spinBoxKey->value());
        if (pos.first == -1 || pos.second == -1)
        {
            return;
        }
        QWidget* item = (ui->hashTable->operator()(pos.first, pos.second));
        ui->scrollArea->ensureVisible(item->x(), item->y(), item->width()+10, item->height()+10);
    });

    connect(ui->pushButtonRandom, &QPushButton::clicked, this, [this]() {
        for (int i = 0; i < ui->spinBoxKey->value(); ++i)
        {
            ui->hashTable->addItem(rand() % ui->spinBoxTableSize->maximum(), "");
        }
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printMessage(const QString &message)
{
    ui->statusbar->showMessage(message);
}

