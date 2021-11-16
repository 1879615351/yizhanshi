import QtQuick 2.0
import QtQuick.Controls 2.3
Rectangle {
    id:root
    width:350
    height:1120
    color: "white"
    signal labelPanelSignal()
    signal trainPanelSignal()
    signal usePanelSignal()
    function onAddLabel(text){
        labelmodel.append({"name":text,"num":0,"percent":0})
    }
    Connections{
        target:labeling
        onSetLabelPercent:{
             labelmodel.get(index+1).num=count
             labelmodel.get(index+1).percent=percent
        }
    }
    Connections{
         target:labeling
         onSetListView:{
             listview.currentIndex=listview.itemAtIndex(n).getIndex()
         }
    }
    Rectangle{
        id:backicon
        x:20
        y:120    //y:120  180
        radius: 10
        width:300
        height:50
        color:"#FF00D8B3"
        Behavior on y{
            NumberAnimation { duration: 100 }
        }
    }
        Image{
            id:labelicon
            x:50
            y:130
            width:25
            height:25
            source:"qrc:/labeling.png"
        }
        Connections{
            target:labeling
            onExportTrainData:{
                labelicon.source="qrc:/exportOK.png"
            }
        }
        Text {
            x:labelicon.x+labelicon.width+30
            y:labelicon.y
            font.bold: true
            font.pointSize: 15
            text: "Label"
        }
        MouseArea{
            x:20
            y:120
            width:300
            height:50
            onClicked: {
                backicon.y=120
                root.labelPanelSignal()
                labeling.tryReleaseCamera()
                labeling.setLabeling()
                //labeling.stopTrain()
                labelicon.source="qrc:/labeling.png"
            }
        }
    Image{
        id:trainicon
        x:50
        y:190
        width:25
        height:25
        source:"qrc:/training.png"
        Behavior on rotation{
                NumberAnimation { duration: 100 }
        }
    }
    Text {
        x:trainicon.x+trainicon.width+30
        y:trainicon.y
        font.bold: true
        font.pointSize: 15
        text: "Train"
    }
    Timer{
        id:timer
        interval:10
        repeat: true
        onTriggered: {
            trainicon.rotation+=30
        }
    }
    MouseArea{
        x:20
        y:180
        width:300
        height:50
        onClicked: {
            trainicon.source="qrc:/trining.png"
            timer.start()
            backicon.y=180
            root.trainPanelSignal()
            labeling.beginTrain()
            labeling.tryReleaseCamera()
        }
    }
    Image{
        id:useicon
        x:50
        y:250
        width:25
        height:25
        source:"qrc:/use.png"
    }
    Text {
        x:useicon.x+useicon.width+30
        y:useicon.y
        font.bold: true
        font.pointSize: 15
        text: "Use"
    }
    MouseArea{
        x:20
        y:240
        width:300
        height:50
        onClicked: {
            backicon.y=240
            root.usePanelSignal()
            //labeling.tryReleaseCamera()
            labeling.beginUse()
        }
    }
    ListView{
        id:listview
        x:20
        y:400
        width:320
        height:450
        clip: true
        model: ListModel{
            id:labelmodel
            ListElement{
                name:"All Images"
                num:0
                percent:1
            }
        }
        ScrollBar.vertical: ScrollBar {       //滚动条
            anchors.right: listview.right
            width: 30
            active: true
            background: Item {            //滚动条的背景样式
                Rectangle {
                    anchors.centerIn: parent
                    height: parent.height
                    width: parent.width * 0.2
                    color: 'grey'
                    radius: width/2
        }
            }
        }
        delegate: Rectangle
        {
            width:288
            height:60
            radius:15
            function getIndex(){
                return  index
            }
            color: listview.currentIndex==getIndex()? "#FFE0E0E0":"white"//区分选中和没选中的颜色
            MouseArea{
                anchors.fill: parent
                onClicked: {
                   labeling.tryReleaseCamera()
                   listview.currentIndex=index
                   labeling.getshowMode(index-1);
                }
            }
            Text{
                id:text
                x:15
                y:8
                font.bold: true
                font.pointSize: 15
                text:name
            }
            Text{
                id:count
                x:240
                y:8
                font.bold: true
                font.pointSize: 15
                text:num.toString()
            }
            ProgressBar{
                     x:text.x
                     y:text.y+25
                     id:control
                     value: percent    //从0到1
                     width: 260
                     height: 15
                     background: Rectangle {   //背景项
                         implicitWidth: control.width
                         implicitHeight: control.height
                          color: "#FFA0A0A0"
                         radius: 10 //圆滑度
                     }
                     contentItem: Item {   //内容项
                         Rectangle {
                             width: control.visualPosition * control.width
                             height: control.height
                             radius: 10
                             color:"#FF00D8B3"
                         }
                     }
                  }
        }
      }
    Component.onCompleted: {
    }
}

