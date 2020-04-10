#include "menu.h"
#include "ui_menu.h"


using namespace std;

Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    /* Le validateur sert à restreindre les informations qui sont possibles à rentrer dans le champ de texte
     * ainsi l'utilisateur ne peut pas casser le programme en rentrant des lettres là où l'on attend des
     * nombres
     */

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

    //récupère et charge les paramètres depuis un fichier .ini
    getSettings();

}

Menu::~Menu()
{
    delete ui;
}

void Menu::saveSettings(){
    //enregistre les paramètres avec un fichier.ini, à partir des entrées dans le menu
    QSettings settings("resources/settings.ini",QSettings::IniFormat);
    settings.beginGroup("Maze");
        settings.setValue("width", ui->TextWidth->text().toInt());
        settings.setValue("height", ui->TextHeight->text().toInt());
        settings.setValue("nbSpheres", ui->TextnbSphere->text().toInt());
    settings.endGroup();

    settings.beginGroup("Display");
        settings.setValue("winWidth", ui->TextWinWidth->text().toInt());
        settings.setValue("winHeight", ui->TextWinHeight->text().toInt());
        settings.setValue("FOV", ui->TextFOV->text().toInt());
        settings.setValue("fullscreen", ui->CheckFullscreen->isChecked());
    settings.endGroup();

    settings.beginGroup("Features");
        settings.setValue("snapping", ui->CheckSnapping->isChecked());
        settings.setValue("mouse", ui->CheckMouse->isChecked());
        settings.setValue("keyboard", ui->CheckKeyboard->isChecked());
        settings.setValue("camera", ui->CheckCamera->isChecked());
        settings.setValue("volume", ui->TextVolume->text().toInt());

    settings.endGroup();
}

void Menu::getSettings(){
    //recupère les paramètres dans le fichier .ini puis les applique à l'interface
    QSettings settings("resources/settings.ini",QSettings::IniFormat);
    //Maze
    ui->TextWidth->setText(QString::number(settings.value("Maze/width").toInt()));
        ui->SliderWidth->setSliderPosition(settings.value("Maze/width").toInt());
    ui->TextHeight->setText(QString::number(settings.value("Maze/height").toInt()));
        ui->SliderHeight->setSliderPosition(settings.value("Maze/height").toInt());
    ui->TextnbSphere->setText(QString::number(settings.value("Maze/nbSpheres").toInt()));
        ui->SlidernbSphere->setSliderPosition(settings.value("Maze/nbSpheres").toInt());
    //Display
    ui->TextWinWidth->setText(QString::number(settings.value("Display/winWidth").toInt()));
    ui->TextWinHeight->setText(QString::number(settings.value("Display/winHeight").toInt()));
    ui->TextFOV->setText(QString::number(settings.value("Display/FOV").toInt()));
        ui->SliderFOV->setSliderPosition(settings.value("Display/FOV").toInt());
    ui->CheckFullscreen->setChecked(settings.value("Display/fullscreen").toBool());
    //Features
    ui->CheckSnapping->setChecked(settings.value("Features/snapping").toBool());
    ui->CheckMouse->setChecked(settings.value("Features/mouse").toBool());
    ui->CheckKeyboard->setChecked(settings.value("Features/keyboard").toBool());
    ui->CheckCamera->setChecked(settings.value("Features/camera").toBool());
    ui->TextVolume->setText(QString::number(settings.value("Features/volume").toInt()));
        ui->SliderVolume->setSliderPosition(settings.value("Features/volume").toInt());

}

/* Ces slots permettent de rendre l'interface dynamique,
 * les champs de textes et les sliders sont modifiés
 * lorsque l'autre change
 */

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
void Menu::on_SliderVolume_sliderMoved(int position){
    ui->TextVolume->setText(QString::number(position));
}
void Menu::on_TextVolume_textEdited(const QString &arg1){
    ui->SliderVolume->setSliderPosition(arg1.toInt());
}


//Bouton Jouer
void Menu::on_pushButton_clicked()
{
    //sauvegarde des reglages
    saveSettings();

    //ferme la fenêtre pour lancer le jeu
    MyGLWidget* game = new MyGLWidget();//menu en argument pour récuperer les paramètres du jeu
    game->show();
    this->hide();//cache le menu
}

//bouton quitter dans la barre d'action de la fenêtre
void Menu::on_actionQuit_changed()
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Mindmaze",
                                                                tr("Etes vous certain de vouloir quitter le jeu ?\n"),
                                                                QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn == QMessageBox::Yes) {
        saveSettings();
        exit(0);
    }
}

//surcharge l'action de quitter la fenêtre, est ausi déclenché lorsqu'on appuie sur la coirx rouge
void Menu::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Mindmaze",
                                                                tr("Etes vous certain de vouloir quitter le jeu ?\n"),
                                                                QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        saveSettings();
        event->accept();
        exit(0);
    }
}

