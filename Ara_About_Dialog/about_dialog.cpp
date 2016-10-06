#include "about_dialog.h"
#include "ui_about_dialog.h"

About_Dialog::About_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About_Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Mario: About");


    this->mainVBox = new QVBoxLayout;

    this->logo = new QPixmap(":/images/Mario_Logo_Bar.tif");
    logoLbl = new QLabel;
    logoLbl->setPixmap(*logo);
    logoLbl->setContentsMargins(0,0,0,2);

    this->spacerBar = new QPixmap(":/images/Spacer_Bar.tif");
    this->spacerLabel = new QLabel;
    spacerLabel->setPixmap(*spacerBar);
    spacerLabel->setContentsMargins(20,8,0,3);



    this->schoolInfo = new QLabel;
    this->classInfo = new QLabel;
    this->groupMember1 = new QLabel;
    this->groupMember2 = new QLabel;
    this->groupMember3 = new QLabel;
    this->groupMember4 = new QLabel;
    this->groupMember5 = new QLabel;
    this->groupMember6 = new QLabel;
    this->groupMember7 = new QLabel;
    this->groupMember8 = new QLabel;

    this->setLayout(mainVBox);
    mainVBox->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    mainVBox->addWidget(logoLbl);
    logoLbl->show();


    mainVBox->addWidget(schoolInfo);
    mainVBox->addWidget(classInfo);
    mainVBox->addWidget(spacerLabel);
    mainVBox->addWidget(groupMember1);

    schoolInfo->show();
    schoolInfo->setAlignment(Qt::AlignCenter);
    schoolInfo->setText("RCC | Fall 2016");
    schoolInfo->setTextFormat(Qt::RichText);
    schoolInfo->setTextInteractionFlags(Qt::TextBrowserInteraction);
    schoolInfo->setOpenExternalLinks(true);
    schoolInfo->setContentsMargins(0,0,14,0);

    classInfo->show();
    classInfo->setAlignment(Qt::AlignCenter);
    classInfo->setText("CIS 17B | <a href = \"https://github.com/zzDeagle545zz/CSC-17B_Mario\"> Group Project </a>");
    classInfo->setTextFormat(Qt::RichText);
    classInfo->setTextInteractionFlags(Qt::TextBrowserInteraction);
    classInfo->setOpenExternalLinks(true);

    groupMember1->show();
    groupMember1->setAlignment(Qt::AlignCenter);
    groupMember1->setText("Jacob Aragon  : <a href = \"https://github.com/Ka0t1k\"> GitHub </a> ");
    groupMember1->setTextFormat(Qt::RichText);
    groupMember1->setTextInteractionFlags(Qt::TextBrowserInteraction);
    groupMember1->setOpenExternalLinks(true);




}

About_Dialog::~About_Dialog()
{
    delete ui;
}
