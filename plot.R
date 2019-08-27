toDiscModel <- function(z)
{
    return ((z-1i)/(z+1i))
}


## Draw the background for the poincare disc model and fundamental domain
drawBackgroundPoincare <- function()
{
    ## Drawing the first circle
    t <- seq(from=0, to=2*pi, length.out = 1000)
    xs <- cos(t)
    ys <- sin(t)
    plot(xs, ys, cex=0.1, col="grey", asp=1)

    a <- -0.5 + 0.5*sqrt(3)*1i
    b <- 0.5 + 0.5*sqrt(3)*1i

    A <- toDiscModel(a)
    B <- toDiscModel(b)

    segments(Re(A), Im(A), Re(B), Im(B), col="grey", cex=0.1)

    ts <- seq(from=-pi/6, to=0, length.out=1000)
    xs1 <- 1 + 2*sin(ts)
    ys1 <- -2 + 2*cos(ts)

    points(xs1, ys1, cex=0.1, col="grey")
    points(xs1, -ys1, cex=0.1, col="grey")

}

draw <- function(M=4)
{
    outs <- read.csv(paste("out/", M, ".txt", sep=""))
    xs <- outs[[1]]
    ys <- outs[[2]]

    ymax <- max(ys)

    zs <- c()
    dim <- length(xs)
    for(i in 1:length(xs))
    {
        zs <- c(zs, xs[i] + ys[i]*1i)
    }

    dzs <- sapply(zs, toDiscModel)

    ## plot(xs, ys, xlim=c(-1, 1), ylim=c(0, ymax), asp=1, cex=0.5, col="blue")
    drawBackgroundPoincare()
    points(dzs,  asp=1, cex=0.2, col="blue")

}


