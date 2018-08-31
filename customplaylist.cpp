#include "customplaylist.h"
#include "soundplayer.h"
CustomPlaylist::CustomPlaylist(QWidget* pwgt) : QMediaPlaylist(pwgt)
{
    m_plw = new QListWidget();
    m_plw->setMaximumHeight(200);
    m_plw->setMaximumWidth(200);
    m_plw->setMinimumWidth(200);
    m_plw->setMinimumHeight(200);
    connect(this, SIGNAL(signalCurrentIndexChanged(int)), this, SLOT(slotCurrentIndexChanged(int)));
}
void CustomPlaylist::filesOpened(QStringList* files_list){
    qDebug() << files_list<<endl;
    qDebug() <<files_list->count();
    m_plw->addItems(*files_list);
    for(int i = 0; i < m_plw->count();i++){
        //QVariant some = m_plw->item(1)->data();

        if(CustomPlaylist::addMedia(QUrl::fromLocalFile(m_plw->item(i)->text()))){
            qDebug()<<"Media added successfully! Media: "<< m_plw->item(i)->text()<<endl;

        }
        else{
            qDebug()<<"Error: Media adding failed! Media: "<<m_plw->item(i)->text()<<endl;
        }
    }
    qDebug() <<"index setted"<<endl;
    emit signalCurrentIndexChanged(1);//TODO: fix that


}
void CustomPlaylist::slotCurrentIndexChanged(int index){
    qDebug() <<"Current index: "<< index<<endl;
    CustomPlaylist::m_plw->setCurrentRow(index);


}


void CustomPlaylist::slotDoubleClickedListItem(){
    emit CustomPlaylist::signalDoubleClickedListItem( CustomPlaylist::m_plw->currentRow());
}
