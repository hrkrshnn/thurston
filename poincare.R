## An R package to visualize the poincare disc model of the hyperbolic plane

library(plotrix)

ctol = 1e-6

## Draw the circle with centre (0, 0) and radius 1
drawCircle <- function(col="black"){
    draw.arc(0, 0, radius=1, deg1=0, deg2=360, col=col)
}

distance <- function(u1, u2, v1, v2){
    return(sqrt((u1-v1)^2 + (u2-v2)^2))
}

## Returns the angle in polar coordinates corresponding to the point (u1, u2) on
## a circle with center (c1, c2)
findAngle <- function(u1, u2, c1, c2){
    radius = distance(u1, u2, c1, c2)
    ## TODO Return error if the two radius does not match

    theta = acos((u1 - c1)/radius)
    if(abs(c2 + radius*sin(theta) - u2) < ctol){
        return(theta)
    }
    else if(abs(c2 + radius*sin(2*pi - theta) - u2) < ctol){
        return(2*pi - theta)
    }
    else
    {
        warning("Wrong input")
        return(0)
    }
}

## Reference: https://en.wikipedia.org/wiki/Poincar%C3%A9_disk_model
## Draws the geodesic between the points (u1, u2) and (v1, v2)
drawGeodesic  <- function(u1, u2, v1, v2, col="black", extend=F){
    ## The tolerance that we'll use here
    ## The equation for a general circle orthogonal to the unit circle is given
    ## by x^2 + y^2 + ax + by + 1 = 0

    ## This can be rewritten into
    ## (x + a/2)^2 + (y + b/2)^2 = a^2/4 + b^2/4 - 1

    ## The circle is degenerate and becomes a straight line. This is the easy
    ## case.
    if(abs(u1*v2 - u2*v1) < ctol){
        lines(c(u1, v1), c(u2, v2), col=col)
    }
    else{
        denom <- u1*v2 - u2*v1
        uNormSqr  <- u1*u1 + u2*u2
        vNormSqr <- v1*v1 + v2*v2
        a <- (u2*vNormSqr - v2*uNormSqr + u2 - v2)/denom
        b <- (v1*uNormSqr - u1*vNormSqr + v1 - u1)/denom
        r <- sqrt(a*a/4 + b*b/4 - 1)

        angle1 <- findAngle(u1, u2, -a/2, -b/2)
        angle2 <- findAngle(v1, v2, -a/2, -b/2)

        centerAngle <- (angle1 + angle2)/2
        t1 <- -a/2 + r*cos(centerAngle)
        t2 <- -b/2 + r*sin(centerAngle)
        ## This means that the smaller angle needs a plus pi
        if(t1*t1 + t2*t2 > 1) {
        if(angle1 < angle2){
                angle1 <- angle1 + 2*pi
        }
        else{
                angle2 <- angle2 + 2*pi
        }
    }
        draw.arc(-a/2, -b/2, radius=r, angle1=angle1, angle2=angle2, col=col)

    }
}

## Function that does translation. Should work if (x, y) represents a complex
## number or when y = 0 and x is the complex number!
translation <- function(x){
    return((2*1i*x + 1 - x)/(2*1i + 1 - x))
}


## Function that does inversion. Should work if (x, y) represent a complex
## number or when y = 0 and x is the complex number!
inversion <- function(x, y=0){
    return(-x)
}


## An example function to illustrate usage
example <- function(){
    plot(c(), xlim=c(-1, 1), ylim=c(-1, 1), asp=1)
    drawCircle()
    points(c(0.5, -0.5), c(0.5, 0.5))
    ## drawGeodesic(-0.5, 0.5, 0.5, 0.5, col="blue")
    drawGeodesic(0.5, 0.5, -0.5, 0.5, col="blue")
}

## A function that converts a point in the upper half space to the disc model
toDiscModel <- function(z)
{
    return ((z-1i)/(z+1i))
}
