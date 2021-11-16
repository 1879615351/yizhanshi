import QtQuick 2.0

Rectangle{
    id:root
    width:50
    height:30
    radius: 10
    property alias img_src:icon.source
    color: "transparent"
    Image{
        id:icon
        x:parent.width/2-width/2
        y:parent.height/2-height/2
        width:25
        height:25
    }
}
