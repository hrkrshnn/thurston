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

draw <- function(M=4, poincare=F)
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

    if(poincare)
    {
        dzs <- sapply(zs, toDiscModel)
        drawBackgroundPoincare()
        points(dzs,  asp=1, cex=0.2, col="blue")
    }
    else
    {
        yend <- sqrt(1 - 0.5*0.5)
        plot(c(), xlim=c(-1, 1), ylim=c(0, ymax), asp=1, cex=0.5, col="blue", xlab="", ylab="")
        grid()
        lines(c(0.5, 0.5), c(yend, ymax + 2), col="blue")
        lines(c(-0.5, -0.5), c(yend, ymax + 2), col="blue")
        xseq <- seq(from=-0.5, to=0.5, length.out=1000)
        yseq <- sqrt(1 - xseq*xseq)
        points(xseq, yseq, cex=0.05, col="blue")
        points(xs, ys, cex=1.3, col="black")
    }

}

generatePDFs <- function()
{
    nums <- c(6, 8, 10, 12)
    for(n in nums)
    {
        pdf(paste("out/", n, ".pdf", sep=""))
        draw(n)
        dev.off()
    }
}
