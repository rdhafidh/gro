import QtQuick 2.12
import QtQuick.Controls 2.8
import QtQuick.Layouts 1.12

ScrollablePage {
    id: page 
	signal askPageMainOuter()
    PageLogInner{
		width: page.width
		height: 370
		onAskPageMain:{
			askPageMainOuter()
		}
	}
}