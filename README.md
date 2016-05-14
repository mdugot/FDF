# FDF  
3D representation of a surface  
................................................................................  
You can launch FDF with one map in argument :  
> ./fdf test_maps/mars.fdf  

You can also launch it without argument to write your own map in the console.  
You have to use CTRL-D when you have finished.  
> ./fdf  
> Write your own map :  
> 0 0 0 0 0  
> 0 10 10 10 0  
> 0 10 20 10 0  
> 0 10 10 10 0  
> 0 0 0 0 0  
> ^D  
  
Each number indicates the altitude of a point.  
The position x and y of this point corresponds to the column and the line of the number.  
Once it has been launched, you can use the keyboard to change the representation :  
  
Q-E : rotation (on the Y axis).  
A-D : rotation (on the Z axis).  
W-S : rotation (on the X axis).  
  
U-O : dezoom/zoom.  
I-K : move up/down.  
J-L : move left/right.  
  
TAB : change color mode.  
  
1-2 : change color surface.  
3-4 : change color line.  
  
ESC : quit.  
................................................................................  
