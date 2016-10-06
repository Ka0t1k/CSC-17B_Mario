#include "about_dialog.h"
#include "ui_about_dialog.h"

About_Dialog::About_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About_Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Mario: About");

    this->mainVBox = new QVBoxLayout;
    /*
    this->schoolInfo = new QHBoxLayout;
    this->classInfo = new QHBoxLayout;
    this->groupMember1 = new QHBoxLayout;
    this->groupMember2 = new QHBoxLayout;
    this->groupMember3 = new QHBoxLayout;
    this->groupMember4 = new QHBoxLayout;
    this->groupMember5 = new QHBoxLayout;
    this->groupMember6 = new QHBoxLayout;
    this->groupMember7 = new QHBoxLayout;
    this->groupMember8 = new QHBoxLayout;

    this->aboutMem1 = new QFormLayout;
    this->aboutMem2 = new QFormLayout;
    this->aboutMem3 = new QFormLayout;
    this->aboutMem4 = new QFormLayout;
    this->aboutMem5 = new QFormLayout;
    this->aboutMem6 = new QFormLayout;
    this->aboutMem7 = new QFormLayout;
    this->aboutMem8 = new QFormLayout;

    groupMember1->addLayout(aboutMem1);
    groupMember2->addLayout(aboutMem2);
    groupMember3->addLayout(aboutMem3);
    groupMember4->addLayout(aboutMem4);
    groupMember5->addLayout(aboutMem5);
    groupMember6->addLayout(aboutMem6);
    groupMember7->addLayout(aboutMem7);
    groupMember8->addLayout(aboutMem8);

    mainVBox->addLayout(schoolInfo);
    mainVBox->addLayout(classInfo);
    mainVBox->addLayout(groupMember1);
    mainVBox->addLayout(groupMember2);
    mainVBox->addLayout(groupMember3);
    mainVBox->addLayout(groupMember4);
    mainVBox->addLayout(groupMember5);
    mainVBox->addLayout(groupMember6);
    mainVBox->addLayout(groupMember7);
    mainVBox->addLayout(groupMember8);
    */

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



    mainVBox->addWidget(schoolInfo);
    mainVBox->addWidget(classInfo);
    mainVBox->addWidget(groupMember1);

    schoolInfo->show();
    schoolInfo->setText("RCC | Fall 2016");
    schoolInfo->setTextFormat(Qt::RichText);
    schoolInfo->setTextInteractionFlags(Qt::TextBrowserInteraction);
    schoolInfo->setOpenExternalLinks(true);

    classInfo->show();
    classInfo->setText("CIS 17B | Group Project");
    classInfo->setTextFormat(Qt::RichText);
    classInfo->setTextInteractionFlags(Qt::TextBrowserInteraction);
    classInfo->setOpenExternalLinks(true);

    groupMember1->show();
    groupMember1->setText("Jacob Aragon  : <a href = \"https://github.com/Ka0t1k\"> GitHub </a> ");
    groupMember1->setTextFormat(Qt::RichText);
    groupMember1->setTextInteractionFlags(Qt::TextBrowserInteraction);
    groupMember1->setOpenExternalLinks(true);




}

About_Dialog::~About_Dialog()
{
    delete ui;
}
