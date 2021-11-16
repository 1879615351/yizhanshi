import QtQuick 2.0

Rectangle {
             id:delegateRec
             property alias trainLabel:label.text
             property alias testLabel:test.text
             property alias img_src: icon.source
             property alias nameText: name.text
             property alias recColor:delegateRec.color
             width:300
             height:300
             radius:35
             Image {
                 id: icon
                 width:200
                 height:200
                 anchors.centerIn: parent
                 source:""
             }
             Rectangle{
                id:labeltext
                x:20
                y:icon.y+icon.height+10
                width:120
                height:30
                radius: 15
                color:"#FF00D8B3"
                Text{
                    id:label
                    anchors.centerIn:parent
                    font.bold: true
                    font.pointSize: 20
                    text:""
                }
             }
             Rectangle{
                 id:testtext
                 x:labeltext.x+labeltext.width+20
                 y:labeltext.y
                 width:120
                 height:30
                 radius: 15
                 color: test.text==label.text?"#FF00D8B3":"#FFFFB6C1"
                 Text{
                     id:test
                     anchors.centerIn:parent
                     font.bold: true
                     font.pointSize: 20
                     text:""
                 }
             }
             Rectangle{
                id:namerec
                y:icon.y-35
                x:icon.x+icon.width/2-width/2
                width:icon.width
                color: "transparent"
                height:30
                Text{
                    id:name
                    font.bold: true
                    font.pointSize: 20
                    anchors.centerIn: namerec
                    text:delegateRec.nameText
                }
             }
             function getIndex(){
                 return  index
             }
}
