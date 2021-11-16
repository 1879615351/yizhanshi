import QtQuick 2.0

Rectangle{
    id:root
    width:100
    height:100
    radius: 10
    property alias img_src:icon.source
    color: "#FFA0A0A0"
    Image{
        id:icon
        x:parent.width/2-width/2
        y:parent.height/2-height/2
        width:80
        height:80
    }
}
