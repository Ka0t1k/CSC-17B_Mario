#include "title.h"
#include "loginwindow.h"
#include <QMessageBox>

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

    //Push Button for developer login
    developerButton = new QPushButton(viewer);
    developerButton->setText("Developer Login");
    developerButton->setObjectName(QString("developerButton"));
    developerButton->setGeometry(QRect(640, 535, 100, 32));
    connect(developerButton, SIGNAL(clicked()), this, SLOT(developerLogin()));

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

//Check if Users are in Database
bool Title::chkUsr(Query Input){
    QSqlQuery Q(db);
    QString select;
//Setup a boolean
    bool valid=true;
//Define the Query
   select="SELECT username FROM mario_table WHERE username='"+Input.uName+"'";
    Q.exec(select);
    if(Q.size()==1){
        //Username Taken
        //QMessageBox::warning(this, "Warning", " Username is already taken. Please try again.");

        return false;
    }
    else{
        //QMessageBox::information(this, "Success", " Registration was successful. You may now login.");
        return valid;
    }


}
/*
bool Title::regUsr(Query Input){
//Check user input against the database
    QString insert;
    QSqlQuery Q(db);
    if(chkUsr(Input)){
    //Define SQL Query
        insert="INSERT INTO mario_table (username,password) VALUES ('"+Input.uName+"', SHA1('"+Input.pass+"'))";
        Q.exec(insert);
        return true;
    }
    else{
        return false;
    }

}
*/
Connection Title::createConnection(){

db = QSqlDatabase::addDatabase("QMYSQL");
db.setHostName("209.129.8.7");
db.setDatabaseName("48037");
db.setUserName("48037");
db.setPassword("48037cis17b");
Connection connection;
connection.db = db;
if (!db.open()) {
    qDebug() << "Database error occurred";
    connection.connected = false;
    return connection;
}
connection.connected = true;

return connection;

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

     //Connect to Database
         createConnection();
     //Gather Input
         Query uInput;
         uInput.uName=userLine->text();
         uInput.pass=passLine->text();

         if(userLine->text().isEmpty()){
             QMessageBox msgBox;
             msgBox.setText("You must enter a username.   ");
             msgBox.setWindowTitle("Warning");
             msgBox.exec();
             return;
         }
         if(passLine->text().isEmpty()){
             QMessageBox msgBox2;
             msgBox2.setText("You must enter a password.  ");
             msgBox2.setWindowTitle("Warning");
             msgBox2.exec();
             return;
         }
         qDebug() << uInput.uName;
         qDebug() << uInput.pass;
     //Try to check User
       if(chkUsr(uInput)){
             //Then it worked
           loginButton->close();
           newUserButton->close();
           passLine->close();
           userLine->close();
           userName->close();
           password->close();
           radioButton->close();
           radioText->close();
           developerButton->close();
           scene = new MyScene(scroll,this);
           viewer->sceneSet(scene);
         }
         else{
             //Then it didnt
           QMessageBox msgBox3;
           msgBox3.setText(" Combination of username and/or password incorrect.  ");
           msgBox3.setWindowTitle("Warning");
           msgBox3.exec();
           return;
         }
     /*
     if(userLine->text().isEmpty()){
         QMessageBox msgBox;
         msgBox.setText("You must enter a username.   ");
         msgBox.setWindowTitle("Warning");
         msgBox.exec();
         return;
     }
     if(passLine->text().isEmpty()){
         QMessageBox msgBox2;
         msgBox2.setText("You must enter a password.  ");
         msgBox2.setWindowTitle("Warning");
         msgBox2.exec();
         return;
     }

         loginButton->close();
         newUserButton->close();
         passLine->close();
         userLine->close();
         userName->close();
         password->close();
         radioButton->close();
         radioText->close();
         developerButton->close();
         scene = new MyScene(scroll,this);
         viewer->sceneSet(scene);
         */
 }

 void Title::newUser(){

     loginWindow = new LoginWindow();
     loginWindow->exec();

 }

 void Title::developerLogin(){
     loginButton->close();
     newUserButton->close();
     passLine->close();
     userLine->close();
     userName->close();
     password->close();
     radioButton->close();
     radioText->close();
     developerButton->close();
     scene = new MyScene(scroll,this);
     viewer->sceneSet(scene);
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
