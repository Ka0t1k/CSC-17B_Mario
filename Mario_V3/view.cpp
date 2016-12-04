#include "view.h"

View::View(){
    bgm = new QMediaPlaylist;
    this->setFixedSize(QSize(1280, 720));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::sceneSet(QGraphicsScene *scene){

    //uLabel = new QLabel;
   // uLabel->setText(tr("Username: "));

    setScene(scene);
    emit sceneChanged();

   // scene->addWidget(uLabel);
   // uLabel->setGeometry(95,100,50,20);
    //submit = new QPushButton(tr("Submit"));
    //scene->addWidget(submit);
   // submit->setGeometry(95,175,100,20);
    //connect(submit, SIGNAL(clicked()), this, SLOT(closeAll()));

}

View::closeAll()
{
    //uLabel->close();
}

