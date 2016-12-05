#include "title.h"
#include "loginwindow.h"
Title::Title(View *view, QWidget *parent) : QGraphicsScene(parent){

    viewer = view;
    scroll = new QScrollBar;
    scroll = viewer->horizontalScrollBar();

    //ARA
    /*
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/music/Title.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    selectSFX = new QSoundEffect();
    selectSFX->setSource(QUrl("qrc:/music/Select.wav"));
    */

    background = new AnimatedGraphicsItem;
    background->setPixmap(QPixmap(":/images/background.png"));
    foreground = new QGraphicsPixmapItem(QPixmap(":/images/title.png"));
    //cursor = new QGraphicsPixmapItem(QPixmap(":/images/cursor.png"));
    logo = new QGraphicsPixmapItem(QPixmap(":/images/logo.png"));

    animation = new QPropertyAnimation(background, "pos");
    animation->setLoopCount(-1);
    animation->setDuration(150000);
    animation->setStartValue(QPoint(-width,0));
    animation->setEndValue(QPoint(0,0));
    animation->start();

    /*JB
    QFont font("MV Boli", 30, QFont::Bold);
    start = new QGraphicsTextItem;
    start->setPlainText("S t a r t  G a m e");
    start->setDefaultTextColor(Qt::black);
    start->setFont(font);
    start->setPos((width - start->boundingRect().width()) / 2, height - 275);

    quit = new QGraphicsTextItem;
    quit->setPlainText("Q u i t  G a m e");
    quit->setDefaultTextColor(Qt::black);
    quit->setFont(font);
    quit->setPos((width - quit->boundingRect().width()) / 2, height - 275 + start->boundingRect().height());
    cursor->setPos((width - start->boundingRect().width()) / 2 - cursor->boundingRect().width(), (height - 275 + start->boundingRect().height() / 4));

    addItem(cursor);
    addItem(start);
    addItem(quit);
    */

    logo->setPos((width - logo->boundingRect().width()) / 2, height / 12);
    addItem(background);
    addItem(foreground);
    addItem(logo);
    this->setFocus();
    this->setSceneRect(0,0,1280,720);
    view->sceneSet(this);

    //Push Button for login
    loginButton = new QPushButton(viewer);
    loginButton->setText("Login");
    loginButton->setObjectName(QString("loginButton"));
    loginButton->setGeometry(QRect(540, 500, 100, 32));
    connect(loginButton, SIGNAL(clicked()), this, SLOT(login()));


    //Push Button for new user
    newUserButton = new QPushButton(viewer);
    newUserButton->setText("New User");
    newUserButton->setObjectName(QString("newUserButton"));
    newUserButton->setGeometry(QRect(640, 500, 100, 32));
    connect(newUserButton, SIGNAL(clicked()), this, SLOT(newUser()));

    //Add line edit for username
    userLine = new QLineEdit(viewer);
    userLine->setObjectName(QString("userLine"));
    userLine->setGeometry(QRect(540, 400, 200, 25));

    //Add Label for username
    QFont font("MV Boli", 15, QFont::Bold);
    userName = new QLabel(viewer);
    userName->setFont(font);
    userName->setText("Username");
    userName->setObjectName(QString("username"));
    userName->setGeometry(QRect(430, 400, 100, 25));

    //Add line edit for password
    passLine = new QLineEdit(viewer);
    passLine->setEchoMode(QLineEdit::Password);
   // passLine->setObjectName(QString("passLine"));
    passLine->setGeometry(QRect(540, 450, 200, 25));

    //Add Label For password
    password = new QLabel(viewer);
    password->setFont(font);
    password->setText("Password");
    password->setObjectName(QString("password"));
    password->setGeometry(QRect(430, 450, 100, 25));

    //Add radio button and connect signal to slot
    radioButton = new QRadioButton(viewer);
    radioButton->setObjectName(QString("radioButton"));
    radioButton->setGeometry(QRect(760, 450, 100, 25));
    connect(radioButton, SIGNAL(toggled(bool)), this, SLOT(on_radioButton_toggled(bool)));

    //add radio button text
    radioText = new QLabel(viewer);
    radioText->setText("Show Password");
    radioText->setGeometry(QRect(780, 450, 100, 25));

}

void Title::on_radioButton_toggled(bool checked)
{
    if(checked){
        passLine->setEchoMode(QLineEdit::Normal);
    }
    else{
        passLine->setEchoMode(QLineEdit::Password);
    }
}

 void Title::login(){

   loginButton->close();
   newUserButton->close();
   passLine->close();
   userLine->close();
   userName->close();
   password->close();
   radioButton->close();
   radioText->close();
   scene = new MyScene(scroll,this);
   viewer->sceneSet(scene);
 }

 void Title::newUser(){

     loginWindow = new LoginWindow();
     loginWindow->exec();

 }



void Title::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Up){
        if(selection == 0){
            selection++;
            cursor->moveBy(0,start->boundingRect().height());
        } else{
            selection--;
            cursor->moveBy(0,-start->boundingRect().height());
        }
        emit playSound("select");
    }
    if(event->key() == Qt::Key_Down){
        if(selection == 1){
            selection--;
            cursor->moveBy(0,-start->boundingRect().height());
        } else{
            selection++;
            cursor->moveBy(0,start->boundingRect().height());
        }
        emit playSound("select");
    }
    if(event->key() == Qt::Key_Z){
        if(selection == 0){
            //ARA - added the this pointer to the scene init
            //scene = new MyScene(scroll,this);
            //viewer->sceneSet(scene);
        }
        if(selection == 1){
            qApp->exit();
        }
    }
}
