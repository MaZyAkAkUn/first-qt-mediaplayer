
//#include "soundplayer.h"
#include "videoplayer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    VideoPlayer videoPlayer;
    videoPlayer.resize(400, 450);
    videoPlayer.show();

    return application.exec();
}
