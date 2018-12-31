import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "pages"

Window {
    visible: true
    width: 350
    height: 480
    title: qsTr("GRPC Camera Client")
    id:window
    
    SwipeView{
        id:swipe
        currentIndex: 0
        anchors.fill: parent
        interactive: false
        Pane{
            ScrollablePage{ 
                MainPage{
					anchors.fill:parent
					onGotoPageLog:{
						swipe.currentIndex=1
					}
					onGotoPageHelp:{
						swipe.currentIndex=2
					}
				}
            }
        }
        Pane{
            PageLog{ 
                onAskPageMainOuter:{
                    swipe.currentIndex=0
                }
            }
        }
        Pane{
            HelpPage{
                onAskKembali: {
                     swipe.currentIndex=0
                }
            }
        }
    }
    

}
