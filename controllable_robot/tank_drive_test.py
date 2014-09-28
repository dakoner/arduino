import math
def tankdrive(x, y):
    if x == 0 and y == 0:
        return 0, 0
    #first Compute the angle in deg

    #First hypotenuse
    z = math.sqrt(x*x + y*y);
    #angle in radians
    rad = math.acos(abs(x)/z);
    #and in degrees
    angle = rad*180/math.pi;

    #Now angle indicates the measure of turn
    #Along a straight line, with an angle o, the turn co-efficient is same
    #this applies for angles between 0-90, with angle 0 the co-eff is -1
    #with angle 45, the co-efficient is 0 and with angle 90, it is 1
    tcoeff = -1 + (angle/90)*2;
    turn = tcoeff * abs(abs(y) - abs(x));
    turn = round(turn*100)/100;

    #And max of y or x is the movement
    move = max(abs(y),abs(x));

    #First and third quadrant
    if( (x >= 0 and y >= 0) or (x < 0 and y < 0) ):
        left = move;
        right = turn;
    else:
        right = move;
        left = turn;

    #Reverse polarity
    if(y < 0):
        left = 0 - left;
        right = 0 - right;


    return left, right
