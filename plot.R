toDiscModel <- function(z)
{
    return ((z-1i)/(z+1i))
}


draw <- function(M=4)
{
    outs <- read.csv(paste(M, ".txt", sep=""))
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
    plot(dzs,  asp=1, cex=0.5, col="blue")

}


