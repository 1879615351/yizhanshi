import QtQuick 2.12
import QtQuick.Controls 2.14  //这个版本有菜单栏
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2
Rectangle {
    id:root
    width:1500
    height:1120
    color: "#FFE0E0E0"
    signal miniWindow()
    property int openMode:0
    property bool isdrawing:false
    property int picWidth:1
    property int picHeight:1
    property bool ispressed:false
    property int currrentClassNum:-1
    property real startX     //储存鼠标开始时的坐标
    property real startY
    property real stopX      //储存鼠标结束时的坐标
    property real stopY
    property real bX
    property real bY
    property real eX
    property real eY
    property bool isMouseMoveEnable: false //是否允许鼠标移动绘制事件
    signal addLabel(string text)
    function resetLabel(){
        root.currrentClassNum= -1
        var length=labelmodel.count
        labelinput.text=""
        for(var i=0;i<length;i++)
        {
            labelbtnview.itemAtIndex(i).root_border_width=0
        }
    }
    Connections{
        target:labeling
        onResetCanvs:{
            canvas.mode=1
            canvas.requestPaint()
        }
    }

    function resetALL(){
        pictureRight.visible=false
        pictureLeft.visible=false
        pictureOK.visible=false
        startX=0
        startY=0
        stopX=0
        stopY=0
        bX=0
        bY=0
        eX=0
        eY=0
    }
    function openPicture(){
        root.resetALL()
        root.openMode=1
        pictureRight.visible=true
        pictureLeft.visible=true
    }
    function openVideo(){
        root.resetALL()
        root.openMode=2
        pictureRight.visible=true
        pictureLeft.visible=true
    }
    function openCamera(){
        root.resetALL()
        root.openMode=3
        pictureRight.visible=false
        pictureLeft.visible=false
        pictureOK.visible=true
    }
    Connections{
        target: labeling
        onSetPicLabel:{
            //root.resetALL()
            root.resetLabel()
            labelbtnview.itemAtIndex(type).root_border_width=5
            root.currrentClassNum=type
            bX=bx
            bY=by
            eX=ex
            eY=ey
            canvas.mode=2
            canvas.requestPaint()
        }
    }
    Connections{
        target: labeling
        onSetPicLabel_None:{
            root.resetLabel()
            canvas.mode=1
            canvas.requestPaint()
        }
    }
    Connections{
        target :labeling
        onOpenModeTypeSignal:{
            switch(type)
            {
                case 1:root.openPicture();break;
                case 2:root.openVideo();break;
                case 3:root.openCamera();break;
            }
        }
    }
    Connections{
        target :labeling
        onSetPictureSignal:{
            root.picWidth=pw
            root.picHeight=ph
        }
    }
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
    ImageButtonBig{
        id:exportbtn
        x:root.width-width-100
        y:100
        img_src: "qrc:/export.png"
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                labeling.exportLabelData()
            }
        }
    }
    ImageButtonBig{
        id:picturebtn
        x:exportbtn.x
        y:exportbtn.y+exportbtn.height+20
        img_src: "qrc:/picture.png"
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                folderDialog.open()
            }
        }
    }
    ImageButtonBig{
        id:videobtn
        x:exportbtn.x
        y:picturebtn.y+picturebtn.height+20
        img_src: "qrc:/video.png"
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                videoFileDialog.open()
            }
        }
    }
    ImageButtonBig{
        id:camerabtn
        x:exportbtn.x
        y:videobtn.y+videobtn.height+20
        img_src: "qrc:/camera.png"
        property int clickednum:0
        color: clickednum==0?"#FFA0A0A0":"white"
        Connections{
            target:labeling
            onResetCameraBtn:{
                camerabtn.clickednum=0
            }
        }
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                if(camerabtn.clickednum==0)
                {
                    labeling.getCamera()
                    camerabtn.clickednum=1
                }
                else {
                    labeling.tryReleaseCamera()
                }
            }
        }
    }
    ImageButtonBig{
        id:pictureLabel
        x:exportbtn.x
        y:camerabtn.y+camerabtn.height+20
        img_src: "qrc:/label.png"
        visible: true
        property int  clickednum: 0
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                if(parent.clickednum==0)
                {
                    root.isdrawing=true
                    parent.color="white"
                    canvas.mode=0
                }
                else if(parent.clickednum==1){
                    canvas.mode=-1
                    parent.color="#FFA0A0A0"
                }
                parent.clickednum=(parent.clickednum+1)%2
                //canvas.isMouseMoveEnable = true
            }
        }
    }
    Rectangle{
        id:imageeRec
        x:60
        y:100
        width:  1200
        height: 800
        Keys.enabled: true
        focus: false
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
    Image {
        id:    img
        cache: false  //不缓存防止卡死
        anchors.fill: parent
    }
    Canvas{
           id:canvas;
           property  int mode:-1   //0手画方形  1清空  2 画方形
            anchors.fill:parent
            onPaint: {
                     var ctx = getContext("2d")
                     if(mode==1)  //清空
                      {
                         //ctx.beginPath();
                         ctx.clearRect(0,0,width,height)
                         //ctx.closePath();
                         if(pictureLabel.clickednum==0)
                         {
                             canvas.mode=-1
                         }
                         else if(pictureLabel.clickednum==1)
                         {
                             canvas.mode=0
                         }
                         return
                      }
                       else if(mode==2)  //画方框
                      {
                            //ctx.beginPath();
                            ctx.clearRect(0,0,width,height)
                            //ctx.closePath();
                            ctx.beginPath();
                            ctx.lineWidtn = 3
                            ctx.strokeStyle = "blue";
                            ctx.strokeRect(bX,bY,eX-bX,eY-bY)
                            ctx.closePath();
                         //if(pictureLabel.clickednum==0)
                         //{
                         //    canvas.mode=-1
                         //}
                         //else if(pictureLabel.clickednum==1)
                         //{
                         //    canvas.mode=0
                        // }
                            return
                      }
                      else if(mode ==0)
                      {
                        ctx.beginPath();
                        ctx.lineWidtn = 3
                        ctx.strokeStyle = "blue";
                        if (!isMouseMoveEnable) {
                            ctx.clearRect(0,0,width,height) //清空所画图形
                            return;
                        }
                        if (isMouseMoveEnable){
                            ctx.clearRect(0,0,width,height)
                        }
                        //开始绘制
                        ctx.beginPath()
                        ctx.moveTo(startX,startY)
                        //console.log(startX,startY)

                        //记录移动终点
                        stopX = area.mouseX
                        stopY = area.mouseY

                        //绘制长方形
                        ctx.strokeRect(startX,startY,stopX-startX,stopY-startY)
                        bX=startX
                        bY=startY
                        eX=stopX
                        eY=stopY
                        ctx.closePath();
                        ctx.stroke()
                      }
                    }
                }
    MouseArea{
        id:area
        anchors.fill: parent
        //hoverEnabled: true
        onClicked: {
              imageeRec.focus=true
        }
        onPressed: {
            isMouseMoveEnable = true
            startX = mouse.x;
            startY = mouse.y;
        }
        onReleased: {
            isMouseMoveEnable = false
            //canvas.requestPaint()      //当鼠标released时，调用绘制paint
        }
        onPositionChanged: {
            if (isMouseMoveEnable){
                canvas.requestPaint()   //绘制函数
        }
    }
    }
    }
    Connections{
        target:imgSender  //发送信号的对象的id
        onCallQmlRefeshImg:{    //on+信号名得到槽函数
             img.source = ""
             img.source =  "image://imgProvider"
        }
    }
    TextInput{
        id:labelinput
        width:60
        height: 20
        z:1000
        enabled: focus
        maximumLength:8
        autoScroll:true
        font.bold: true
        font.pointSize: 10
        wrapMode: TextEdit.NoWrap
        visible: false
        onAccepted:{
                if(labelinput.focus==true)
                {
                    if(text!=""&&labeling.findSameName(text)!=true)
                   {
                        root.addLabel(labelinput.text)
                        labelinput.focus=false
                        labelmodel.get(labelmodel.count-1).key=labelinput.text
                        labelbtnview.itemAtIndex(labelmodel.count-1).text_visible=true
                        labelbtnview.itemAtIndex(labelmodel.count-1).root_color= Qt.rgba(Math.random(), Math.random(), Math.random(), 1);//random返回0~1的随机数
                        labelinput.visible=false
                        labeling.addClassName(text)
                        labelbtnview.itemAtIndex(labelmodel.count-1).labeled=true
                        labelmodel.append({"key":"0","value":"0"});
                    }
                    if(text=="")
                    {
                        labelbtnview.itemAtIndex(root.currentSelectLabel).img_visible=true
                        labelinput.visible=false
                    }
                    }
        }
    }
    GridView{
        id:labelbtnview
        x:pictureRight.x+pictureRight.width+50
        y:pictureRight.y
        boundsBehavior: Flickable.StopAtBounds
        model: ListModel{
            id:labelmodel
            ListElement{
                key:""
                value:""
            }
        }
        width: 360
        height:200
        cellWidth: 100
        cellHeight: 40
        delegate: LabelAddBtn{
            img_src: "qrc:/add.png"
            visible: true
            text_text: key
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    labelinput.focus=false
                    parent.img_visible=false
                    if(getIndex()==labelmodel.count-1)
                    {
                        labelinput.text=""
                        labelinput.x=labelbtnview.x+parent.x+parent.width/2-labelinput.width/2
                        labelinput.y=labelbtnview.y+parent.y+parent.height/2-labelinput.height/2
                        labelinput.visible=true
                        labelinput.focus=true
                        return
                    }
                        root.resetLabel()
                        parent.root_border_width=5
                        root.currrentClassNum=getIndex()
                }
            }
            function getIndex(){
                return  index
            }
        }
    }
    ImageButtonBig{
        id:pictureLeft
        x:img.x+img.width/2-width/2+20
        y:img.y+img.height+110
        img_src: "qrc:/left.png"
        visible: false
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                 labeling.changePicture(0)
            }
        }
    }
    ImageButtonBig{
        id:pictureRight
        x:img.x+img.width/2+width/2+70
        y:img.y+img.height+110
        img_src: "qrc:right.png"
        visible:false
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                labeling.changePicture(1)
            }
        }
    }
    ImageButtonBig{
        id:pictureOK
        x:img.x+img.width/2+width/2
        y:img.y+img.height+110
        img_src: "qrc:ok1.png"
        visible:false
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                labeling.addLabelData(root.currrentClassNum,root.bX,root.bY,root.eX,root.eY)
                root.bX=0
                root.bY=0
                root.eX=0
                root.eY=0
                canvas.mode=1
                canvas.requestPaint()
            }
            onPressed: {
                parent.img_src= "qrc:ok2.png"
            }
            onReleased: {
                parent.img_src= "qrc:ok1.png"
            }
        }
    }
    FolderDialog {
        id: folderDialog
        folder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
        onAccepted:{
            labeling.getPictureFloder(1,currentFolder)
        }
    }
    FileDialog{
        id:videoFileDialog
        nameFilters: ["Video Files (*.ts *.mp4 *.avi *.flv *.mkv *.3gp)"];
        onAccepted: {
            labeling.getVideoFile(2,fileUrl)
        }
    }
    Component.onCompleted: {

    }
}
