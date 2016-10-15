#include "settings.h"

Settings::Settings(QWidget *parent) : QDialog(parent){
    label = new QLabel(tr("Player Name: "));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);

    bgmLabel = new QLabel(tr("Music"));
    bgmSlider = new QSlider(Qt::Horizontal);
    bgmSpinBox = new QSpinBox;
    bgmSlider->setRange(0,100);
    bgmSpinBox->setRange(0,100);

    sfxLabel = new QLabel(tr("Sound Effects"));
    sfxSlider = new QSlider(Qt::Horizontal);
    sfxSpinBox = new QSpinBox;
    sfxSlider->setRange(0,100);
    sfxSpinBox->setRange(0,100);

    screenSize = new QLabel(tr("Full Screen"));
    fullScreenView = new QRadioButton("On");
    windowedView = new QRadioButton("Off");
    windowedView->setChecked(true);

    confirmButton = new QPushButton(tr("Confirm"));
    cancelButton = new QPushButton(tr("Cancel"));

    connect(bgmSpinBox, SIGNAL(valueChanged(int)), bgmSlider, SLOT(setValue(int)));
    connect(bgmSlider, SIGNAL(valueChanged(int)), bgmSpinBox, SLOT(setValue(int)));
    connect(bgmSlider, SIGNAL(valueChanged(int)), this, SLOT(volumeChanged()));
    connect(sfxSpinBox, SIGNAL(valueChanged(int)), sfxSlider, SLOT(setValue(int)));
    connect(sfxSlider, SIGNAL(valueChanged(int)), sfxSpinBox, SLOT(setValue(int)));
    connect(confirmButton, SIGNAL(clicked(bool)), this, SLOT(confirm()));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));

    bgmSlider->setValue(50);
    sfxSlider->setValue(50);

    QHBoxLayout *firstLayout = new QHBoxLayout;
    firstLayout->addWidget(label);
    firstLayout->addWidget(lineEdit);

    QHBoxLayout *secondLayout = new QHBoxLayout;
    secondLayout->addWidget(screenSize);
    secondLayout->addStretch();
    secondLayout->addWidget(fullScreenView);
    secondLayout->addWidget(windowedView);
    secondLayout->addStretch();

    QHBoxLayout *thirdLayout = new QHBoxLayout;
    thirdLayout->addWidget(bgmLabel);
    thirdLayout->addStretch();
    thirdLayout->addWidget((bgmSlider));
    thirdLayout->addWidget(bgmSpinBox);

    QHBoxLayout *fourthLayout = new QHBoxLayout;
    fourthLayout->addWidget(sfxLabel);
    fourthLayout->addWidget((sfxSlider));
    fourthLayout->addWidget(sfxSpinBox);

    QHBoxLayout *fifthLayout = new QHBoxLayout;
    fifthLayout->addWidget(confirmButton);
    fifthLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(firstLayout);
    mainLayout->addLayout(secondLayout);
    mainLayout->addLayout(thirdLayout);
    mainLayout->addLayout(fourthLayout);
    mainLayout->addLayout(fifthLayout);

    setLayout(mainLayout);
    setWindowTitle("Settings");
}

void Settings::reject(){
    this->revertState();
    QDialog::reject();
}

void Settings::setState(){
    full = fullScreenView->isChecked();
    window = windowedView->isChecked();
    bgm = bgmSlider->value();
    sfx = sfxSlider->value();
}

void Settings::revertState(){
    fullScreenView->setChecked(full);
    windowedView->setChecked(window);
    bgmSlider->setValue(bgm);
    sfxSlider->setValue(sfx);
}

void Settings::alterState(){
    if(full){
        windowedView->setChecked(true);
    } else {
        fullScreenView->setChecked(true);
    }
    this->confirm();
}

void Settings::readSettings(){
    QSettings settings("CSC-17B Mario Group", "Mario Game");
    fullScreenView->setChecked(settings.value("fullscreen", "").toBool());
    bgmSlider->setValue(settings.value("bgm", "").toInt());
    sfxSlider->setValue(settings.value("sfx", "").toInt());
    confirm();
}

void Settings::writeSettings(){
    QSettings settings("CSC-17B Mario Group", "Mario Game");
    settings.setValue("fullscreen", fullScreenView->isChecked());
    settings.setValue("bgm", bgmSlider->value());
    settings.setValue("sfx", sfxSlider->value());
}

void Settings::volumeChanged(){
    emit volumeAdjust(bgmSlider->value());
}

void Settings::confirm(){
    emit fullScreen(fullScreenView->isChecked());
    this->setState();
    this->close();
}