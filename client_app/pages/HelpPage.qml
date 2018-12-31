import QtQuick 2.9 

ScrollablePage {
    id:hpage 
    signal askKembali()
    HelpPageInfo{
        anchors.fill: parent
        onKembaliHal1: {
            askKembali()
        }
    }
}
