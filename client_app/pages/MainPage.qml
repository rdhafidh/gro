import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import ImageItemQML 1.0

Item { 
    width: parent.width
    height: parent.height
    property string imagedata:""
    property bool kirimIsRunning: false
    signal gotoPageLog();
    signal gotoPageHelp();
    Connections{
        target: camera
        onEmitResult :{
            //imagedata=buffer
			gambar.setImageBuffer(buffer);
            errorText.text="OK" 
        }
        onEmitConnectError:{
            errorText.text="Koneksi error";
            kirimIsRunning=false
        }
         onEmitServerCameraNotFound:{
             errorText.text="Kamera server tidak ditemukan"
             kirimIsRunning=false
         }
         onEmitServerCameraError:{
             errorText.text="Kamera server error"
             kirimIsRunning=false
         }
    }

    GroupBox{
        anchors.fill: parent
        ColumnLayout{
            ImageItem{
                id: gambar  
                Layout.alignment: Qt.AlignCenter
                // source : "data:image/png;base64," +
                implicitHeight: 250
                implicitWidth: 250
                //source: imagedata!="" ? "data:image/png;base64,"+imagedata : "qrc:/images/ic_perm_media_black_48dp.png"
            }
            RowLayout{
                spacing: 10
                ColumnLayout{
                    RowLayout{
                        Label{
                            text: "Hostname"
                            Layout.preferredWidth:  100
                        }
                        TextField{
                            id:inhost
                            readOnly: false
                            placeholderText: "hostname"
                        }
                    }
                    RowLayout{
                        Label{
                            text: "Port"
                            Layout.preferredWidth:  100
                        }
                        TextField{
                            id:port
                            placeholderText: "port"
                        }
                    }
                    Label{
                        
						Layout.alignment: Qt.AlignHCenter
                        height: 50
                        id:errorText
                        text: "Nothing"
                    }

                    RowLayout{
                        Button{
                            text: "simpan"
                            onClicked: {
                                camera.setup(inhost.text+":"+port.text)
                            }
                        }
                        Button{
                            text: kirimIsRunning==false ? "kirim" : "stop" 
                            onClicked: {
                                if(kirimIsRunning){
									kirimIsRunning=false;
									camera.stopAsking();
								}else{
									kirimIsRunning=true
									camera.startAsking();
								}
                            }
                        } 
                    }
                    RowLayout{
                        Button{
                            text: "log"
                            onClicked: {
                                gotoPageLog()
                            }
                        }
                        Button{
                            text:"bantuan"
                            onClicked:{
                                gotoPageHelp()
                            }
                        }
                    }
                } 
            }
        }
    }

    
}
