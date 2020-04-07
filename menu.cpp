#include "menu.h"
#include "ui_menu.h"


using namespace std;

Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    //Largeur
    ui->TextWidth->setValidator( new QIntValidator(3, 25, this) );
    //hauteur
    ui->TextHeight->setValidator( new QIntValidator(3, 25, this) );
    //nombre de spheres à trouver
    ui->TextnbSphere->setValidator( new QIntValidator(1, 5, this) );
    //largeur de la fenêtre d'affichage
    ui->TextWinWidth->setValidator( new QIntValidator(480, 1920, this) );
    //hauteur de la fenêtre d'affichage
    ui->TextWinHeight->setValidator( new QIntValidator(480, 1080, this) );
    //FOV
    ui->TextFOV->setValidator( new QIntValidator(30, 180, this) );
    //Volume
    ui->TextVolume->setValidator( new QIntValidator(0, 100, this) );
}

Menu::~Menu()
{
    delete ui;
}

//largeur
void Menu::on_SliderWidth_sliderMoved(int position){
    ui->TextWidth->setText(QString::number(position));
}
void Menu::on_TextWidth_textEdited(const QString &arg1){
    ui->SliderWidth->setSliderPosition(arg1.toInt());
}
//hauteur
void Menu::on_SliderHeight_sliderMoved(int position){
    ui->TextHeight->setText(QString::number(position));
}
void Menu::on_TextHeight_textEdited(const QString &arg1){
    ui->SliderHeight->setSliderPosition(arg1.toInt());
}
//nombre de spheres
void Menu::on_SlidernbSphere_sliderMoved(int position){
    ui->TextnbSphere->setText(QString::number(position));
}
void Menu::on_TextnbSphere_textEdited(const QString &arg1){
    ui->SlidernbSphere->setSliderPosition(arg1.toInt());
}
//FOV
void Menu::on_SliderFOV_sliderMoved(int position){
    ui->TextFOV->setText(QString::number(position));
}
void Menu::on_TextFOV_textEdited(const QString &arg1){
    ui->SliderFOV->setSliderPosition(arg1.toInt());
}
//Volume
//hauteur
void Menu::on_SliderVolume_sliderMoved(int position){
    ui->TextVolume->setText(QString::number(position));
}
void Menu::on_TextVolume_textEdited(const QString &arg1){
    ui->SliderVolume->setSliderPosition(arg1.toInt());
}
//Bouton Jouer
void Menu::on_pushButton_clicked()
{
    //affectations
    width = ui->TextWidth->text().toInt();
    height = ui->TextHeight->text().toInt();
    nbSpheres = ui->TextnbSphere->text().toInt();
    winWidth = ui->TextWinWidth->text().toInt();
    winHeight= ui->TextWinHeight->text().toInt();
    FOV= ui->TextFOV->text().toInt();
    volume= ui->TextVolume->text().toInt();

    fullscreen = ui->CheckFullscreen->isChecked();
    freeMovement = ! ui->CheckSnapping->isChecked();
    mouse = ui->CheckMouse->isChecked();
    keyboard = ui->CheckKeyboard->isChecked();
    camera = ui ->CheckCamera->isChecked();

    //ferme la fenêtre pour lancer le jeu
    Menu menu;
    MyGLWidget* game = new MyGLWidget(width, height, nbSpheres, winWidth, winHeight, FOV, volume, fullscreen, freeMovement, mouse, keyboard, camera);//menu en argument pour récuperer les paramètres du jeu
    game->show();
    this->hide();//cache le menu
}

void Menu::on_actionQuit_changed()
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Mindmaze",
                                                                tr("Etes vous certain de vouloir quitter le jeu ?\n"),
                                                                QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn == QMessageBox::Yes) {
        exit(0);
    }
}

void Menu::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Mindmaze",
                                                                tr("Etes vous certain de vouloir quitter le jeu ?\n"),
                                                                QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
        exit(0);
    }
}

