#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->hashTable->resize(ui->spinBoxTableSize->value());

    connect(ui->hashTable, &HashTableWidget::sendMessage, this, &MainWindow::printMessage);

    ui->comboBoxHash->addItem("hi(K) = (hi-1(K) + c × i + d × i2) mod N");
    ui->comboBoxHash->addItem("hi(K) = [hi-1(K) × a × N] mod N;");
    ui->comboBoxHash->addItem("hi(K) = (K mod N) + i × (1+ K mod (N – 2)) mod N");

    connect(ui->pushButtonAdd, &QPushButton::clicked, this,
            [this]() { ui->hashTable->addItem(ui->spinBoxKey->value(), ui->lineEditValue->text()); });

    connect(ui->spinBoxTableSize, &QSpinBox::textChanged, this,
            [this]() { ui->hashTable->resize(ui->spinBoxTableSize->value()); });

    connect(ui->comboBoxHash, &QComboBox::currentTextChanged, this,
            [this]() { ui->hashTable->chooseHash(ui->comboBoxHash->currentIndex()); });

    connect(ui->pushButtonRemove, &QPushButton::clicked, this,
            [this]() { ui->hashTable->removeItem(ui->spinBoxKey->value()); });

    connect(ui->pushButtonFind, &QPushButton::clicked, this, [this]() {
        QRect temp = ui->hashTable->findItem(ui->spinBoxKey->value());
        ui->scrollArea->ensureVisible(temp.x(), temp.y(), 0, 0);

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

