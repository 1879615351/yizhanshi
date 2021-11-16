import QtQuick 2.0

Rectangle{
    id:root
    width:90
    height:30
    radius: 9
    border.color: "black"
    border.width: 0
    property alias img_src:icon.source
    property alias img_visible:icon.visible
    property alias text_visible:labeltext.visible
    property alias text_focus:labeltext.focus
    property alias text_text:labeltext.text
    property alias root_color: root.color
    property alias root_border_width: root.border.width
    property bool labeled:false
    color: "#FFA0A0A0"
    Image{
        id:icon
        x:parent.width/2-width/2
        y:parent.height/2-height/2
        width:30
        height:30
    }
    TextInput{
        id:labeltext
        maximumLength:8
        autoScroll:true
        font.bold: true
        font.pointSize: 10
        wrapMode: TextEdit.NoWrap
        x:parent.width/2-width/2
        y:parent.height/2-height/2
        width:60
        height:20
        visible: false
        text:""
    }
}
