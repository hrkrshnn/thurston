xsample <- seq(-0.5, 0.5, length.out = 1000)
ysample <- seq(0, 5, length.out = 100)

fundDomain <- function(x, y)
{
    if(-0.5 <= x && x <= 0.5 && x*x + y*y >= 1)
    {
        return(T)
    }
    else
    {
        return(F)
    }
}

xs <- c()
ys <- c()
for(x in xsample)
{
    for(y in ysample)
    {
        if(fundDomain(x, y))
        {
            xs <- c(xs, x)
            ys <- c(ys, y)
        }
    }
}


xs1 <- c()
ys1 <- c()
for(i in 0:(length(xs)-1))
{
    x <- xs[i]
    y <- ys[i]
    xs1 <- c(xs1, -x/(x*x + y*y))
    ys1 <- c(ys1, y/(x*x + y*y))
}

toDiscModel <- function(z)
{
    return ((z-1i)/(z+1i))
}

zs <- c()
for(i in 1:(length(xs)-1))
{
    z <- xs[i] + 1i*ys[i]
    zs <- c(zs, toDiscModel(z))
}
