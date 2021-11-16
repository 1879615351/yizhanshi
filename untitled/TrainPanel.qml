import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.14  //这个版本有菜单栏
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2
import Qt.labs.folderlistmodel 2.12
Rectangle {
    id:root
    width:1500
    height:1120
    color: "#FFE0E0E0"
    signal miniWindow()
    property bool firstAppend:true
    ImageButton{
        id:closebtn
        x:root.width-width-70
        y:10
        color: "transparent"
        img_src: "qrc:/close.png"
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered:{
                parent.color="red"
            }
            onExited: {
                parent.color="transparent"
            }
            onClicked: {
                trainprocess.closeTrain()
                Qt.quit()
            }
        }
    }
    ImageButton{
        id:minbtn
        x:closebtn.x-width-10
        y:10
        color: "transparent"
        img_src: "qrc:/min.png"
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onEntered:{
                parent.color="#D0D0D0D0"
            }
            onExited: {
                parent.color="transparent"
            }
            onClicked: {
                root.miniWindow()
            }
        }
    }
    GridView {
         id:picview
         model: ListModel{
            id:dataModel
            ListElement{
                filePath:""
                fileName:""
                train:""
                test:""
            }
         }
         x:170
         y:100
         width: 1200
         height: 900
         cellWidth: 350
         cellHeight:350
         visible: false
         //interactive:false   /禁止滑动
         clip:true
         ScrollBar.vertical: ScrollBar {       //滚动条
             anchors.right: picview.right
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
         delegate:LabeledImgRec{
            img_src:"file:///"+filePath
            nameText:fileName
            trainLabel:train
            testLabel:test
            recColor:picview.currentIndex==getIndex()? "#D0D0D0D0":"#FFE0E0E0"//区分选中和没选中的颜色
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    picview.currentIndex=index   //view的current不会自动变，代理的index自动变
                    console.log(picview.currentIndex,getIndex())
                }
            }
         }
         Connections{
               target:detect
               onSendTestLabel:{
                   //console.log(picview.itemAtIndex(n).trainLabel,mark)
                   console.log(mark)
                   dataModel.get(n).test=mark
               }
         }
         Connections{
             target:labeling
             onSendTrainLabel:{
                    if(root.firstAppend==true)
                    {
                        dataModel.get(0).filePath=filepath
                        dataModel.get(0).fileName=filename
                        dataModel.get(0).train=trainText
                        dataModel.get(0).test=""
                        root.firstAppend=false
                    }
                    else
                    {
                        dataModel.append({"filePath":filepath,"fileName":filename,"train":trainText,"test":""})
                    }
                    picview.visible=true
             }
         }
     }
}
