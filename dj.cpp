#include "dj.h"

DJ::DJ()
{
    // les chemins sont relatifs mais je ne sais pas
    background.setMedia(QUrl::fromLocalFile("./resources/sounds/background.mp3"));
    sphereFound.setMedia(QUrl::fromLocalFile("./resources/sounds/sphereFound.mp3"));
    sphereSound.setMedia(QUrl::fromLocalFile("./resources/sounds/sphereSound.mp3"));
}

void DJ::play(const QString& soundName){
    if (soundName.toUpper() == "BACKGROUND"){
        background.play();
    }else if (soundName.toUpper() == "SPHERESOUND"){
        sphereSound.play();
    }else if (soundName.toUpper() == "SPHEREFOUND"){
        sphereFound.play();
    }
}

void DJ::volume(const QString& soundName, int volume){
    if (soundName.toUpper() == "BACKGROUND"){
        background.setVolume(volume);
    }else if (soundName.toUpper() == "SPHERESOUND"){
        sphereSound.setVolume(volume);
    }else if (soundName.toUpper() == "SPHEREFOUND"){
        sphereFound.setVolume(volume);
    }
}

void DJ::stop(const QString& soundName){
    if (soundName.toUpper() == "BACKGROUND"){
        background.stop();
    }else if (soundName.toUpper() == "SPHERESOUND"){
        sphereSound.stop();
    }else if (soundName.toUpper() == "SPHEREFOUND"){
        sphereFound.stop();
    }
}
