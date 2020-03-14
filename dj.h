#ifndef DJ_H
#define DJ_H
#include <QMediaPlayer>
#include <QFile>
#include <iostream>

class DJ
{
public:
    DJ();
    void play(QString soundName);
    void stop(QString soundName);
    void volume(QString soundName, int volume);
private:
    QMediaPlayer background;
    QMediaPlayer sphereSound;
    QMediaPlayer sphereFound;
};

#endif // DJ_H
