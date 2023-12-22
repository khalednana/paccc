#include "player.h"
#include "qtimer.h"

player::player(int** temp) {
    QPixmap playerImage("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanR.png");
    playerImage = playerImage.scaledToWidth(blockDim);
    playerImage = playerImage.scaledToHeight(blockDim);
    pacman = playerImage;
    setPixmap(pacman);
    setPos(blockDim*col+margin, blockDim*row+margin);      //0.5blockdim*27+20, blockdim*23+20
    boardData=new int*[TotalRows];
    for(int i=0;i<TotalRows;i++){
        boardData[i]=new int[TotalColumns];
    }

    for(int i=0;i<TotalRows;i++){
        for(int j=0;j<TotalColumns;j++){
         boardData[i][j]=temp[i][j];

        }
    }
    mouthanim = new QTimer(this);
    connect(mouthanim, SIGNAL(timeout()),this, SLOT(movemouth()));
}

QPair<int, int> player::getCoordinate()
{
    return QPair<int, int> (row, col);
}

void player::move()
{

    if(tempDirect != direct){

        //if he wants to go up or down and he was moving horizontal
        //then we keep going horizontal till we are in the middle of the col
        //then we change direction to be up

        //WE MUST CHECK IF WE PASSED THE MIDDLE OR NOT


        //direct will only change if we are in the right col or row because we check that in changeDic

        //when going to the right, I need to check earlier

        if(  ((direct == 'U') || (direct == 'D')) && ((tempDirect == 'R') || (tempDirect == 'L'))){

            if(Xpos == blockDim*(tempCol)+margin){ //if we are in the middle of the column
                tempDirect = direct;
            }

        }else if(  ((direct == 'R') || (direct == 'L')) && ((tempDirect == 'U') || (tempDirect == 'D'))){
            if(Ypos == blockDim*tempRow+margin){ //if we are in the middle of the row
                tempDirect = direct;
            }
        }else{
            tempDirect = direct;
        }

      }


    //from totalcol-2 to 1
    //from 1 to totalcol-2
    if( (col == TotalColumns-2) && (row == 14) && (tempDirect == 'R')){
        col = 1;
        Xpos = blockDim*col+margin;
    }else if( (col == 1) && (row == 14) && (tempDirect == 'L')){
        col = TotalColumns-2;
        Xpos = blockDim*col+margin;
    }




      if(tempDirect == 'U' && ( (boardData[row-1][col]>0)  || (Ypos != blockDim*(row)+margin))){

          Ypos -=speed;
          row = (Ypos - margin)/blockDim; //this will only increase by 1 when Ypos increases by blockDim!


      }else if (tempDirect == 'D'&& boardData[row+1][col]>0){

          Ypos +=speed;
          row = (Ypos - margin)/blockDim; //this will only increase by 1 when Ypos increases by blockDim!

      }else if (tempDirect == 'L' && (col-1==-1 || boardData[row][col-1]>0 || (Xpos != blockDim*(col)+margin) )  ) {

          Xpos -=speed;
          col = (Xpos - margin)/blockDim;

          if (col == -1){ //shouldn't it be -1?? not 0
              col = TotalColumns-1;
          }



      } else if (tempDirect=='R' && (col+1==TotalColumns||boardData[row][col+1]>0) ){ //you must add the condition R
          Xpos += speed;
          col = (Xpos - margin)/blockDim; // I need only move up or down or maybe change directions when the Xpos or the Ypos - margin % blockDim == 0

          if (col == TotalColumns)//should be totoal columns not, total -1
              col = 0;
      }

      setPos(Xpos, Ypos);

}

void player::changedir(char dir){
    if (dir == 'U'){

       if (!(boardData[row-1][col]<0) ){
           direct = dir;
            tempCol = col;
       }else if (!(boardData[row-1][col+1]<0) && (direct=='R') ){
            direct = dir;
            tempCol = col+1;
       }


    }else if (dir == 'D'){

        if (!(boardData[row+1][col]<0) ){
            direct = dir;
            tempCol = col;
        }else if (!(boardData[row+1][col+1]<0) && (direct=='R') ){
            direct = dir;
            tempCol = col+1;
        }




    } else if (dir == 'L'){



        if (boardData[row][col-1]>0){
            direct = dir;
            tempRow = row;
        }else if( (boardData[row+1][col-1]>0) && (direct == 'D')){
            direct = dir;
            tempRow = row+1;
        }


    }
    else if (dir == 'R'){


        if (boardData[row][col+1]>0){
            direct = dir;
            tempRow = row;
        }else if( (boardData[row+1][col+1]>0) && (direct == 'D')){
            direct = dir;
            tempRow = row+1;
        }

    }
}


void player::reset(){
    row = spawnrow;
    col = spawncol;
    Xpos = blockDim*col+margin;
    Ypos = blockDim*row+margin;
    tempRow = row;
    tempCol = col;
    setPos(Xpos, Ypos);
    direct='R';
    pacman.load("C:/Users/Power/Desktop/PacmanGame-master/Assets/pacmanR.png");
    pacman = pacman.scaledToWidth(blockDim);
    pacman = pacman.scaledToHeight(blockDim);
    setPixmap(pacman);
}

void player::startanim()
{
    mouthanim->start(20);
}

void player::endanim()
{
    mouthanim->stop();
}

int player::getdir()
{
    if (tempDirect == 'U')
        return 0;
    if(tempDirect == 'D')
        return 1;
    if(tempDirect == 'R')
        return 2;


    return 3;

}

void player::movemouth()
{

if(tempDirect == 'R'){
    if(boardData[row][col+1]>0){
        if(frame%6==0)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanClosed.png");
        if(frame%6==1)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanR1.png");
        if(frame%6==2)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanR2.png");
        if(frame%6==3)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanR.png");
        if(frame%6==4)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanR2.png");
        if(frame%6==5)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanR1.png");}
    else
        pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanR.png");
}
if(tempDirect == 'L'){
    if((boardData[row][col-1]>0) || (Xpos != blockDim*(col)+margin)){ //keep animating till the image xpos reaches the edge
        if(frame%6==0)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanClosed.png");
        if(frame%6==1)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanL1.png");
        if(frame%6==2)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanL2.png");
        if(frame%6==3)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanL.png");
        if(frame%6==4)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanL2.png");
        if(frame%6==5)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanL1.png");
    }
    else
        pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanL.png");
}
if(tempDirect == 'U'){
    if((boardData[row-1][col]>0) || (Ypos != blockDim*(row)+margin)){
        if(frame%6==0)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanClosed.png");
        if(frame%6==1)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanU1.png");
        if(frame%6==2)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanU2.png");
        if(frame%6==3)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanU.png");
        if(frame%6==4)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanU2.png");
        if(frame%6==5)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanU1.png");
    }
    else
         pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanU.png");
}
if(tempDirect == 'D'){
    if(boardData[row+1][col]>0){
        if(frame%6==0)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanClosed.png");
        if(frame%6==1)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanD1.png");
        if(frame%6==2)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanD2.png");
        if(frame%6==3)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanD.png");
        if(frame%6==4)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanD2.png");
        if(frame%6==5)
            pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanD1.png");
    }
    else
        pacman.load("/Users/khalednana/Desktop/paccc/PacmanGame-master/Assets/pacmanD.png");
}
    frame++;
    pacman = pacman.scaledToWidth(blockDim);
    pacman = pacman.scaledToHeight(blockDim);
    setPixmap(pacman);
    if(frame==6)
        frame=0;
}



