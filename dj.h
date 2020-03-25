#ifndef DJ_H
#define DJ_H
#include <QMediaPlayer>
#include <QFile>
#include <iostream>

class DJ
{
public:
    DJ();
    void play(const QString& soundName);
    void stop(const QString& soundName);
    void volume(const QString& soundName, int volume);
private:
    QMediaPlayer background;
    QMediaPlayer sphereSound;
    QMediaPlayer sphereFound;
};

#endif // DJ_H
