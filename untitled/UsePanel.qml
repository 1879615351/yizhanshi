import QtQuick 2.0
import QtQuick.Controls 2.5
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2
Rectangle {
    id:root
    width:1500
    height:1120
    color: "#FFE0E0E0"
    signal miniWindow()
    Rectangle{
        id:allbutton
        width:1500
        height:120
        color: parent.color
        //color:"red"
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
        Rectangle{
            id:buttonRec
            x:allbutton.width/2-width/2
            y:40
            color: "#D0D0D0D0"
            width:410
            height:60
            radius: 20
            Rectangle{
                id:changebackRec             //x:5  y:5
                x:5           //x:
                y:5
                radius: 20
                color: "white"
                width:100
                height:buttonRec.height-10
                visible: false
                Behavior on x{
                    NumberAnimation { duration: 100 }
                }
            }
            Text
            {
                id:imageText
                x:15
                y:15
                font.bold: true
                font.pointSize: 15
                width:buttonRec.width/3
                height:buttonRec.height
                text:"Images"
                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        changebackRec.visible=true
                        changebackRec.x=parent.x-10
                        folderDialog.open()
                    }
                }
            }
            Text
            {
                id:videoText
                x:120
                y:15
                font.bold: true
                font.pointSize: 15
                width:buttonRec.width/3
                height:buttonRec.height
                text:"Videos"
                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        changebackRec.visible=true
                        changebackRec.x=parent.x-10
                        videoFileDialog.open()
                    }
                }
            }
            Text
            {
                id:cameraText
                x:220
                y:15
                font.bold: true
                font.pointSize: 15
                width:buttonRec.width/3
                height:buttonRec.height
                text:"Camera"
                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        changebackRec.visible=true
                        changebackRec.x=parent.x-10
                        labeling.setDetect(3,"")
                    }
                }
            }
            Text
            {
                id:exportText
                x:320
                y:15
                font.bold: true
                font.pointSize: 15
                width:buttonRec.width/3
                height:buttonRec.height
                text:"Export"
                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        changebackRec.visible=true
                        changebackRec.x=parent.x-10
                    }
                }
            }
        }
    }
    Rectangle{
        id:imageeRec
        x:100
        y:100
        width:  1200
        height: 800
        color: "white"
        Keys.enabled: true
        focus: false
        /*
        function addLabelData(dir)
        {
            if(root.openMode==1||root.openMode==2)
            {
                labeling.addLabelData(root.currrentClassNum,root.bX,root.bY,root.eX,root.eY);labeling.changePicture(dir);
            }
            else{
                labeling.changePicture(dir);
            }
        }
        Keys.onPressed: {
             switch(event.key)
             {
                case  Qt.Key_A:imageeRec.addLabelData(0);event.accepted=true;break;
                case  Qt.Key_D:imageeRec.addLabelData(1);event.accepted=true;break;
             }
        }
        */
    Image {
        id:    img
        cache: false  //不缓存防止卡死
        anchors.fill: parent
    }
    }
    FolderDialog {
        id: folderDialog
        folder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
        onAccepted:{
            labeling.setDetect(1,currentFolder)
        }
    }
    FileDialog{
        id:videoFileDialog
        nameFilters: ["Video Files (*.ts *.mp4 *.avi *.flv *.mkv *.3gp)"];
        onAccepted: {
            labeling.setDetect(2,fileUrl)
        }
    }
    Connections{
        target:detectSender  //发送信号的对象的id
        onCallQmlRefeshImg:{    //on+信号名得到槽函数
             img.source = ""
             img.source =  "image://imgProvider2"
        }
    }
}
