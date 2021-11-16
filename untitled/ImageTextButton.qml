import QtQuick 2.0

Rectangle{
    width:150
    height:50
    radius: 10
    property alias img_src:icon.source
    property alias btntext:btnText.text
    Image{
        id:icon
        x:40
        y:parent.height/2-height/2
        width:25
        height:25
    }
    Text {
        id:btnText
        x:icon.x+icon.width+20
        y:icon.height/2
        font.bold: true
        font.pointSize: 15
        text: "Label"
    }
}
