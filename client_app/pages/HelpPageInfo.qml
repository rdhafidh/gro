import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Item {
    signal kembaliHal1()
    GroupBox {
        id: box
        anchors.fill: parent
        ColumnLayout {
            spacing: 10
            RowLayout {
                spacing: 10
                Label {
                    text: "Petunjuk Penggunaan"
                }
                Button {
                    text: "kembali"
                    onClicked: {
                        kembaliHal1()
                    }
                }
            }
            TextAreaScroll{
                id:htext
				readOnly: true
                width: window.width
                height: window.height
                clip: true
            }
        }
    }
    Component.onCompleted: {
        htext.text="baris 1 \
        \nbaris 2 \
        \nbaris 3"
    }
}
